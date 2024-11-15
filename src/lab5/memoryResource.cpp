#include "include/memoryResource.h"
#include <iostream>
#include <new>

MemoryResource::MemoryResource() = default;

MemoryResource::~MemoryResource() {
    for (auto& [size, block] : allocated_blocks_) {
        ::operator delete(block);
    }
}

void* MemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    auto it = allocated_blocks_.lower_bound(bytes);
    if (it != allocated_blocks_.end()) {
        void* block = it->second;
        allocated_blocks_.erase(it); 
        return block;
    }

    void* block = ::operator new(bytes, std::align_val_t(alignment));
    return block;
}

void MemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    allocated_blocks_.emplace(bytes, p);
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
