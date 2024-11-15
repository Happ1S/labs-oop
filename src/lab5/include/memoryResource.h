#ifndef MemoryResource_H
#define MemoryResource_H

#include <memory_resource>
#include <map>

class MemoryResource : public std::pmr::memory_resource {
public:
    MemoryResource(size_t block_size);
    ~MemoryResource();

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    size_t block_size_;
    char* memory_;
    char* free_memory_;
    std::map<size_t, void*> allocated_blocks_;
};

#endif