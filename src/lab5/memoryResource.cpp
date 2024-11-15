#include "include/memoryResource.h"
#include <cassert>
#include <new>

MemoryResource::MemoryResource(size_t block_size)
    : block_size_(block_size), memory_(new char[block_size]), free_memory_(memory_), allocated_blocks_() {}

MemoryResource::~MemoryResource() {
    delete[] memory_;
}

void* MemoryResource::do_allocate(size_t bytes, size_t alignment) {
    assert(bytes <= block_size_ && "Requested allocation size exceeds block size");

    auto it = allocated_blocks_.lower_bound(bytes);
    if (it != allocated_blocks_.end()) {
        void* p = it->second;
        allocated_blocks_.erase(it);
        return p;
    }

    if (free_memory_ + bytes <= memory_ + block_size_) {
        void* p = free_memory_;
        free_memory_ += bytes;
        return p;
    }

    throw std::bad_alloc();
}

void MemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    allocated_blocks_.emplace(bytes, p);
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}