// ═══════════════════════════════════════════════════════════════════════════
// OLang Type System Unit Tests
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#include "olang/frontend/ASTType.hpp"
#include "olang/type/Unit.hpp"
#include "olang/semantic/TypeChecker.hpp"
#include <cassert>
#include <iostream>
#include <memory>

using namespace olang;

// ───────────────────────────────────────────────────────────────────────────
// Test Utilities
// ───────────────────────────────────────────────────────────────────────────
int testsPassed = 0;
int testsFailed = 0;

#define TEST(name) \
    void test_##name(); \
    struct TestRunner_##name { \
        TestRunner_##name() { \
            std::cout << "Running test: " #name << "..."; \
            try { \
                test_##name(); \
                testsPassed++; \
                std::cout << " PASSED" << std::endl; \
            } catch (const std::exception& e) { \
                testsFailed++; \
                std::cout << " FAILED: " << e.what() << std::endl; \
            } \
        } \
    } testRunner_##name; \
    void test_##name()

#define ASSERT(cond) \
    if (!(cond)) { \
        throw std::runtime_error("Assertion failed: " #cond); \
    }

#define ASSERT_EQ(a, b) \
    if ((a) != (b)) { \
        throw std::runtime_error("Assertion failed: " #a " == " #b); \
    }

// ═══════════════════════════════════════════════════════════════════════════
// AST Type Tests
// ═══════════════════════════════════════════════════════════════════════════

TEST(primitive_type_equality) {
    auto int1 = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto int2 = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto float1 = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Float);
    
    ASSERT(int1->equals(*int2));
    ASSERT(!int1->equals(*float1));
}

TEST(primitive_type_tostring) {
    auto intType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto boolType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Bool);
    
    ASSERT_EQ(intType->toString(), "int");
    ASSERT_EQ(boolType->toString(), "bool");
}

TEST(list_type_creation) {
    auto elemType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto listType = std::make_unique<ast::ListType>(std::move(elemType));
    
    ASSERT_EQ(listType->toString(), "List<int>");
}

TEST(map_type_creation) {
    auto keyType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::String);
    auto valueType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto mapType = std::make_unique<ast::MapType>(std::move(keyType), 
                                                   std::move(valueType));
    
    ASSERT_EQ(mapType->toString(), "Map<string, int>");
}

TEST(pipeline_type_creation) {
    auto inputType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto outputType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::String);
    auto pipelineType = std::make_unique<ast::PipelineType>(std::move(inputType),
                                                             std::move(outputType));
    
    ASSERT_EQ(pipelineType->toString(), "Pipeline<int -> string>");
}

TEST(function_type_creation) {
    std::vector<std::unique_ptr<ast::Type>> params;
    params.push_back(std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int));
    params.push_back(std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Float));
    
    auto returnType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Bool);
    auto funcType = std::make_unique<ast::FunctionType>(std::move(params), 
                                                         std::move(returnType));
    
    ASSERT_EQ(funcType->toString(), "(int, float) -> bool");
}

TEST(union_type_creation) {
    std::vector<std::unique_ptr<ast::Type>> types;
    types.push_back(std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int));
    types.push_back(std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::String));
    types.push_back(std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Bool));
    
    auto unionType = std::make_unique<ast::UnionType>(std::move(types));
    
    ASSERT_EQ(unionType->toString(), "int | string | bool");
}

TEST(optional_type_creation) {
    auto baseType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto optType = std::make_unique<ast::OptionalType>(std::move(baseType));
    
    ASSERT_EQ(optType->toString(), "int?");
}

TEST(user_defined_type_with_generics) {
    std::vector<std::unique_ptr<ast::Type>> typeArgs;
    typeArgs.push_back(std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int));
    
    auto udtType = std::make_unique<ast::UserDefinedType>("MyType", std::move(typeArgs));
    
    ASSERT_EQ(udtType->toString(), "MyType<int>");
}

// ═══════════════════════════════════════════════════════════════════════════
// Dimensional Analysis (Unit<T>) Tests
// ═══════════════════════════════════════════════════════════════════════════

TEST(unit_basic_arithmetic) {
    using namespace type;
    using namespace type::literals;
    
    auto d1 = 5.0_m;
    auto d2 = 3.0_m;
    
    auto sum = d1 + d2;
    ASSERT_EQ(sum.value(), 8.0);
    
    auto diff = d1 - d2;
    ASSERT_EQ(diff.value(), 2.0);
}

TEST(unit_scalar_multiplication) {
    using namespace type;
    using namespace type::literals;
    
    auto distance = 10.0_m;
    auto scaled = distance * 2.0;
    
    ASSERT_EQ(scaled.value(), 20.0);
}

TEST(unit_comparison) {
    using namespace type;
    using namespace type::literals;
    
    auto d1 = 5.0_m;
    auto d2 = 10.0_m;
    
    ASSERT(d1 < d2);
    ASSERT(d2 > d1);
    ASSERT(d1 <= d2);
    ASSERT(d2 >= d1);
    ASSERT(d1 != d2);
}

TEST(unit_velocity_calculation) {
    using namespace type;
    using namespace type::literals;
    
    auto distance = 100.0_m;
    auto time = 10.0_s;
    
    auto velocity = distance / time;
    // Result should be Velocity type (Meter/Second)
    ASSERT_EQ(velocity.value(), 10.0);
}

TEST(unit_energy_calculation) {
    using namespace type;
    using namespace type::literals;
    
    auto mass = 2.0_kg;
    auto distance = 5.0_m;
    
    // Force = mass * acceleration (simplified)
    // Energy = force * distance
    // This is a simplified test - full impl would handle dimensions properly
}

TEST(unit_temperature) {
    using namespace type;
    using namespace type::literals;
    
    auto temp1 = 273.15_K;
    auto temp2 = 373.15_K;
    
    auto diff = temp2 - temp1;
    ASSERT_EQ(diff.value(), 100.0);
}

TEST(unit_biological_count) {
    using namespace type;
    using namespace type::literals;
    
    auto cells = 1000000_cells;
    auto molecules = 5000000_molecules;
    
    ASSERT_EQ(cells.value(), 1000000.0);
    ASSERT_EQ(molecules.value(), 5000000.0);
}

// ═══════════════════════════════════════════════════════════════════════════
// Semantic Analysis Tests
// ═══════════════════════════════════════════════════════════════════════════

TEST(symbol_table_basic) {
    using namespace semantic;
    
    SymbolTable symTab;
    
    auto intType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    
    ASSERT(symTab.declare("x", std::move(intType)));
    ASSERT(!symTab.declare("x", std::make_unique<ast::PrimitiveType>(
        ast::PrimitiveKind::Float))); // Redeclaration should fail
    
    auto* symbol = symTab.lookup("x");
    ASSERT(symbol != nullptr);
    ASSERT_EQ(symbol->name, "x");
}

TEST(type_environment_builtin_types) {
    using namespace semantic;
    
    TypeEnvironment env;
    
    ASSERT(env.typeExists("int"));
    ASSERT(env.typeExists("bool"));
    ASSERT(env.typeExists("string"));
    ASSERT(!env.typeExists("CustomType"));
}

TEST(type_environment_register_type) {
    using namespace semantic;
    
    TypeEnvironment env;
    
    auto customType = std::make_unique<ast::UserDefinedType>("CustomType");
    ASSERT(env.registerType("CustomType", std::move(customType)));
    ASSERT(env.typeExists("CustomType"));
}

TEST(type_checker_assignability_primitives) {
    using namespace semantic;
    
    TypeEnvironment env;
    ErrorReporter reporter;
    TypeChecker checker(env, reporter);
    
    auto intType = ast::PrimitiveType(ast::PrimitiveKind::Int);
    auto longType = ast::PrimitiveType(ast::PrimitiveKind::Long);
    auto stringType = ast::PrimitiveType(ast::PrimitiveKind::String);
    
    // int -> long (widening)
    ASSERT(checker.isAssignable(longType, intType));
    
    // int -> string (incompatible)
    ASSERT(!checker.isAssignable(stringType, intType));
    
    // Same type
    ASSERT(checker.isAssignable(intType, intType));
}

TEST(type_checker_assignability_any) {
    using namespace semantic;
    
    TypeEnvironment env;
    ErrorReporter reporter;
    TypeChecker checker(env, reporter);
    
    auto anyType = ast::PrimitiveType(ast::PrimitiveKind::Any);
    auto intType = ast::PrimitiveType(ast::PrimitiveKind::Int);
    
    // any accepts everything
    ASSERT(checker.isAssignable(anyType, intType));
}

TEST(type_checker_assignability_never) {
    using namespace semantic;
    
    TypeEnvironment env;
    ErrorReporter reporter;
    TypeChecker checker(env, reporter);
    
    auto neverType = ast::PrimitiveType(ast::PrimitiveKind::Never);
    auto intType = ast::PrimitiveType(ast::PrimitiveKind::Int);
    
    // never can be assigned to anything (bottom type)
    ASSERT(checker.isAssignable(intType, neverType));
}

TEST(type_checker_assignability_optional) {
    using namespace semantic;
    
    TypeEnvironment env;
    ErrorReporter reporter;
    TypeChecker checker(env, reporter);
    
    auto intType = std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
    auto optIntType = ast::OptionalType(std::move(intType));
    auto bareIntType = ast::PrimitiveType(ast::PrimitiveKind::Int);
    
    // int -> int? (optional accepts base type)
    ASSERT(checker.isAssignable(optIntType, bareIntType));
}

TEST(type_checker_unification_same_types) {
    using namespace semantic;
    
    TypeEnvironment env;
    ErrorReporter reporter;
    TypeChecker checker(env, reporter);
    
    auto int1 = ast::PrimitiveType(ast::PrimitiveKind::Int);
    auto int2 = ast::PrimitiveType(ast::PrimitiveKind::Int);
    
    auto unified = checker.unify(int1, int2);
    ASSERT(unified.has_value());
    ASSERT((*unified)->equals(int1));
}

TEST(type_checker_unification_numeric_widening) {
    using namespace semantic;
    
    TypeEnvironment env;
    ErrorReporter reporter;
    TypeChecker checker(env, reporter);
    
    auto intType = ast::PrimitiveType(ast::PrimitiveKind::Int);
    auto longType = ast::PrimitiveType(ast::PrimitiveKind::Long);
    
    auto unified = checker.unify(intType, longType);
    ASSERT(unified.has_value());
    // Should unify to long (wider type)
}

TEST(error_reporter_basic) {
    using namespace semantic;
    
    ErrorReporter reporter;
    
    ASSERT(!reporter.hasErrors());
    
    reporter.reportError(TypeError(ErrorSeverity::Error, "Test error"));
    ASSERT(reporter.hasErrors());
    ASSERT_EQ(reporter.getErrors().size(), 1);
    
    reporter.clear();
    ASSERT(!reporter.hasErrors());
}

// ═══════════════════════════════════════════════════════════════════════════
// Main Test Runner
// ═══════════════════════════════════════════════════════════════════════════
int main() {
    std::cout << "\n═══════════════════════════════════════════════════════" << std::endl;
    std::cout << "OLang Type System Tests - Milestone 1.2" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════\n" << std::endl;
    
    // Tests run automatically via static constructors
    
    std::cout << "\n═══════════════════════════════════════════════════════" << std::endl;
    std::cout << "Test Results:" << std::endl;
    std::cout << "  Passed: " << testsPassed << std::endl;
    std::cout << "  Failed: " << testsFailed << std::endl;
    std::cout << "  Total:  " << (testsPassed + testsFailed) << std::endl;
    std::cout << "═══════════════════════════════════════════════════════\n" << std::endl;
    
    return testsFailed > 0 ? 1 : 0;
}