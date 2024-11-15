#include <gtest/gtest.h>
#include "../src/lab5/include/memoryResource.h"
#include "../src/lab5/include/linkinList.h"

// Тесты для MemoryResource
TEST(MemoryResourceTest, AllocateAndDeallocate) {
    MemoryResource memory_resource;
    void* ptr1 = memory_resource.allocate(100);
    ASSERT_NE(ptr1, nullptr);

    memory_resource.deallocate(ptr1, 100);
}

TEST(MemoryResourceTest, ReuseDeallocatedMemory) {
    MemoryResource memory_resource;

    void* ptr1 = memory_resource.allocate(50);
    memory_resource.deallocate(ptr1, 50);

    void* ptr2 = memory_resource.allocate(50);
    ASSERT_NE(ptr2, nullptr);
    memory_resource.deallocate(ptr2, 50);
}

// Тесты для LinkedList
TEST(LinkedListTest, PushFrontAndAccess) {
    MemoryResource memory_resource;
    LinkedList<int> list{&memory_resource};

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    ASSERT_EQ(list.size(), 3);
    
    auto it = list.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);
}

TEST(LinkedListTest, PopFront) {
    MemoryResource memory_resource;
    LinkedList<int> list{&memory_resource};

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    list.pop_front();
    ASSERT_EQ(list.size(), 2);

    auto it = list.begin();
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);

    list.pop_front();
    list.pop_front();
    ASSERT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, IteratorFunctionality) {
    MemoryResource memory_resource;
    LinkedList<int> list{&memory_resource};

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    int expected_values[] = {1, 2, 3};
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected_values[i++]);
    }
}

TEST(LinkedListTest, WorksWithComplexTypes) {
    struct ComplexType {
        int a;
        std::string b;
    };

    MemoryResource memory_resource;
    LinkedList<ComplexType> list{&memory_resource};

    list.push_front(ComplexType{2, "test2"});
    list.push_front(ComplexType{1, "test1"});

    ASSERT_EQ(list.size(), 2);

    auto it = list.begin();
    EXPECT_EQ(it->a, 1);
    EXPECT_EQ(it->b, "test1");
    ++it;
    EXPECT_EQ(it->a, 2);
    EXPECT_EQ(it->b, "test2");
}
