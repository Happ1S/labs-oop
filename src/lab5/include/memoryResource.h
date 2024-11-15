#ifndef MEMORYRESOURCE_H
#define MEMORYRESOURCE_H

#include <memory_resource>
#include <map>
#include <cstddef>

class MemoryResource : public std::pmr::memory_resource {
public:
    explicit MemoryResource();
    ~MemoryResource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    // Карта для управления блоками (размер -> указатель на блок)
    std::map<size_t, void*> allocated_blocks_;
};

#endif // MEMORYRESOURCE_H
