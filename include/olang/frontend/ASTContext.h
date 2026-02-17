#pragma once
#include <span>
#include <string_view>
#include <utility>
#include "olang/support/llvm_fwd.h"
#include "olang/frontend/AST.h"

namespace olang::ast {

class ASTContext {
public:
  ASTContext()  = default;
  ~ASTContext() = default;
  ASTContext(const ASTContext&)            = delete;
  ASTContext& operator=(const ASTContext&) = delete;

  template <typename T, typename... Args>
  [[nodiscard]] T* make(Args&&... args) {
    static_assert(std::is_base_of_v<ASTNode, T>);
    void* mem = allocator_.Allocate(sizeof(T), alignof(T));
    return new (mem) T(std::forward<Args>(args)...);
  }

  [[nodiscard]] llvm::StringRef intern(std::string_view s) {
    char* buf = static_cast<char*>(allocator_.Allocate(s.size(), 1));
    std::memcpy(buf, s.data(), s.size());
    return {buf, s.size()};
  }

  template <typename T>
  [[nodiscard]] llvm::ArrayRef<T> allocArray(std::span<T> items) {
    T* buf = static_cast<T*>(allocator_.Allocate(items.size()*sizeof(T), alignof(T)));
    std::uninitialized_copy(items.begin(), items.end(), buf);
    return {buf, items.size()};
  }

  [[nodiscard]] size_t bytesAllocated() const noexcept {
    return allocator_.getBytesAllocated();
  }

private:
  llvm::BumpPtrAllocator allocator_;
};

} // namespace olang::ast
