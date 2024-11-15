#include <gtest/gtest.h>
#include "../src/lab5/include/memoryResource.h"
#include "../src/lab5/include/linkinList.h"

struct TestComplexType {
    int id;
    double value;

    TestComplexType(int i = 0, double v = 0.0)
        : id(i), value(v) {}

    bool operator==(const TestComplexType& other) const {
        return id == other.id && 
               value == other.value;
    }
};

class MemoryResourceTest : public ::testing::Test {
protected:
    MemoryResource* resource;

    void SetUp() override {
        resource = new MemoryResource(1024);
    }

    void TearDown() override {
        delete resource;
    }
};

TEST_F(MemoryResourceTest, Allocation) {
    void* ptr1 = resource->allocate(64);
    ASSERT_NE(ptr1, nullptr);

    void* ptr2 = resource->allocate(128);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr1, ptr2);
}

TEST_F(MemoryResourceTest, Deallocation) {
    void* ptr = resource->allocate(64);
    ASSERT_NO_THROW(resource->deallocate(ptr, 64));
}

TEST_F(MemoryResourceTest, MemoryReuse) {
    void* ptr1 = resource->allocate(64);
    resource->deallocate(ptr1, 64);
    void* ptr2 = resource->allocate(64);
    ASSERT_EQ(ptr1, ptr2);
}

TEST_F(MemoryResourceTest, OutOfMemory) {
    void* ptr = nullptr;
    ASSERT_THROW(ptr = resource->allocate(2048), std::bad_alloc);
}

class LinkedListTest : public ::testing::Test {
protected:
    MemoryResource* resource;
    LinkedList<int>* list;
    LinkedList<TestComplexType>* complex_list;

    void SetUp() override {
        resource = new MemoryResource(1024);
        list = new LinkedList<int>(resource);
        complex_list = new LinkedList<TestComplexType>(resource);
    }

    void TearDown() override {
        delete complex_list;
        delete list;
        delete resource;
    }
};

TEST_F(LinkedListTest, EmptyList) {
    ASSERT_TRUE(list->empty());
    ASSERT_EQ(list->size(), 0);
}

TEST_F(LinkedListTest, PushFront) {
    list->push_front(1);
    ASSERT_EQ(list->size(), 1);
    ASSERT_FALSE(list->empty());
}

TEST_F(LinkedListTest, PopFront) {
    list->push_front(1);
    list->push_front(2);
    list->pop_front();
    ASSERT_EQ(list->size(), 1);
}

TEST_F(LinkedListTest, Iterator) {
    std::vector<int> values = {3, 2, 1};
    for (int val : values) {
        list->push_front(val);
    }

    auto it = list->begin();
    for (int expected : values) {
        ASSERT_EQ(*it, expected);
        ++it;
    }
    ASSERT_EQ(it, list->end());
}

TEST_F(LinkedListTest, ComplexTypeOperations) {
    TestComplexType obj1(1, 1.1);
    TestComplexType obj2(2, 2.2);

    complex_list->push_front(obj1);
    complex_list->push_front(obj2);

    ASSERT_EQ(complex_list->size(), 2);
    auto it = complex_list->begin();
    ASSERT_EQ(*it, obj2);
    ++it;
    ASSERT_EQ(*it, obj1);
}

TEST_F(LinkedListTest, MemoryManagement) {
    for (int i = 0; i < 10; ++i) {
        list->push_front(i);
    }
    for (int i = 0; i < 5; ++i) {
        list->pop_front();
    }
    for (int i = 0; i < 5; ++i) {
        list->push_front(i);
    }
    ASSERT_EQ(list->size(), 10);
}

TEST_F(LinkedListTest, Performance) {
    const int operations = 1000;
    for (int i = 0; i < operations; ++i) {
        ASSERT_NO_THROW(list->push_front(i));
    }
    ASSERT_EQ(list->size(), operations);
}

TEST_F(LinkedListTest, OutOfMemoryException) {
    MemoryResource small_resource(64);
    LinkedList<TestComplexType> small_list(&small_resource);
    
    ASSERT_THROW({
        for (int i = 0; i < 1000; ++i) {
            small_list.push_front(TestComplexType(i, i * 1.1));
        }
    }, std::bad_alloc);
}

TEST_F(LinkedListTest, IteratorRequirements) {
    using Iterator = LinkedList<int>::iterator;
    
    ASSERT_TRUE((std::is_same_v<
        std::iterator_traits<Iterator>::iterator_category,
        std::forward_iterator_tag
    >));
    
    ASSERT_TRUE((std::is_same_v<
        std::iterator_traits<Iterator>::value_type,
        int
    >));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}