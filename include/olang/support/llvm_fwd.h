#pragma once

// olang/support/llvm_fwd.h
//
// LLVM portability shim. When llvm-18-dev is installed, this is a no-op
// and the real LLVM types are used. Without LLVM, it provides stdlib
// replacements that are API-compatible.

#if defined(OLANG_HAVE_LLVM)
#include "llvm/Support/Allocator.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/ArrayRef.h"
#else
// Stdlib fallback when LLVM is not present
#include <string_view>
#include <span>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <new>

namespace llvm {
  using StringRef = std::string_view;
  
  template<typename T>
  using ArrayRef = std::span<const T>;
  
  // Minimal BumpPtrAllocator replacement using stdlib malloc
  class BumpPtrAllocator {
  public:
    BumpPtrAllocator() = default;
    ~BumpPtrAllocator() {
      for (void* ptr : blocks_) {
        std::free(ptr);
      }
    }
    
    void* Allocate(size_t size, size_t align) {
      void* ptr = std::aligned_alloc(align, size);
      if (!ptr) throw std::bad_alloc();
      blocks_.push_back(ptr);
      totalBytes_ += size;
      return ptr;
    }
    
    template<typename T>
    T* Allocate(size_t num = 1) {
      return static_cast<T*>(Allocate(sizeof(T) * num, alignof(T)));
    }
    
    size_t getBytesAllocated() const noexcept {
      return totalBytes_;
    }
    
  private:
    std::vector<void*> blocks_;
    size_t totalBytes_ = 0;
  };
}
#endif
