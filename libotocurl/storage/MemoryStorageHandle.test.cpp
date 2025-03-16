#include <libotocurl/storage/MemoryStorageHandle.test.hpp>
#include <libotocurl/storage/MemoryStorage.hpp>
#include <libotocurl/storage/char_buffer/CharBufferStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {

    otocurl::storage::unit_test::MemoryStorageHandleTest test;

    test.test_swap();
    test.copy_construction();
    test.move_construction();
    test.copy_assignment();
    test.move_assignment();

    test.construct_from_friend();
    test.construct_from_friend_with_make_unique();

    otocurl::storage::unit_test::MemoryStorageHandleClassNonFriend nonFriendTest;

    nonFriendTest.construct_from_non_friend();
    nonFriendTest.construct_from_non_friend_with_make_unique();

    log(LogLevel::Result, "curl::storage::MemoryStorageHandle: passed");
    return 0;
}

namespace otocurl::storage::unit_test {

    void MemoryStorageHandleTest::test_swap() {
        log("Running ", LogRequest::functionName());

        std::string data1("Data1");
        std::unique_ptr<MemoryStorageHandle> handle1 =
            constructHandle(data1);

        std::string data2("Data2");
        std::unique_ptr<MemoryStorageHandle> handle2 =
            constructHandle(data2);

        using std::swap;
        swap(*handle1, *handle2);

        std::string handle1Data(handle1->data().data());
        std::string handle2Data(handle2->data().data());
        assert(handle1Data == data2);
        assert(handle2Data == data1);
    }

    void MemoryStorageHandleTest::copy_construction() {
        log("Running ", LogRequest::functionName());

        std::string data1("Data1");
        std::unique_ptr<MemoryStorageHandle> handle1 =
            constructHandle(data1);

        MemoryStorageHandle handle2(*handle1);

        std::string handle1Data(handle1->data().data());
        std::string handle2Data(handle2.data().data());
        assert(handle1Data == data1);
        assert(handle2Data == data1);
    }

    void MemoryStorageHandleTest::move_construction() {
        log("Running ", LogRequest::functionName());

        std::string data1("Data1");
        std::unique_ptr<MemoryStorageHandle> handle1 =
            constructHandle(data1);

        MemoryStorageHandle handle2(std::move(*handle1));

        std::string handle2Data(handle2.data().data());
        assert(!handle1->storage);
        assert(handle2Data == data1);
    }

    void MemoryStorageHandleTest::copy_assignment() {
        log("Running ", LogRequest::functionName());

        std::string data1("Data1");
        std::unique_ptr<MemoryStorageHandle> handle1 =
            constructHandle(data1);

        std::string data2("Data2");
        std::unique_ptr<MemoryStorageHandle> handle2 =
            constructHandle(data2);

        *handle2 = *handle1;

        std::string handle1Data(handle1->data().data());
        std::string handle2Data(handle2->data().data());
        assert(handle1Data == data1);
        assert(handle2Data == data1);
    }

    void MemoryStorageHandleTest::move_assignment() {
        log("Running ", LogRequest::functionName());

        std::string data1("Data1");
        std::unique_ptr<MemoryStorageHandle> handle1 =
            constructHandle(data1);

        std::string data2("Data2");
        std::unique_ptr<MemoryStorageHandle> handle2 =
            constructHandle(data2);

        *handle2 = std::move(*handle1);

        std::string handle2Data(handle2->data().data());
        assert(!handle1->storage);
        assert(handle2Data == data1);
    }

    void MemoryStorageHandleTest::construct_from_friend() {
        log("Running ", LogRequest::functionName());

        std::unique_ptr<MemoryStorage> storage = std::make_unique<MemoryStorage>();

        MemoryStorageHandle handle(
            MemoryStorageHandle::ConstructorPermission{0},
            std::move(storage));

    }

    void MemoryStorageHandleTest::construct_from_friend_with_make_unique() {
        log("Running ", LogRequest::functionName());

        std::unique_ptr<MemoryStorage> storage = std::make_unique<MemoryStorage>();

        std::unique_ptr<MemoryStorageHandle> handle = 
            std::make_unique<MemoryStorageHandle>(
                MemoryStorageHandle::ConstructorPermission{0},
                std::move(storage));

    }

    /**
     * @brief Try to construct an object within a non friend
     * object. 
     * 
     * This does not compile, hence the #if 0. Experimental
     * test.
     */
    void MemoryStorageHandleClassNonFriend::construct_from_non_friend() {
        log("Running ", LogRequest::functionName());

        std::unique_ptr<MemoryStorage> storage = std::make_unique<MemoryStorage>();

#       if 0

        MemoryStorageHandle handle(
            {0},
            std::move(storage));

#       endif

    }

    /**
     * @brief Try to construct an object using `std::make_unique`
     * within a non friend object. 
     * 
     * This does not compile, hence the #if 0. Experimental test.
     */
    void MemoryStorageHandleClassNonFriend::construct_from_non_friend_with_make_unique() {
        log("Running ", LogRequest::functionName());

        std::unique_ptr<MemoryStorage> storage = std::make_unique<MemoryStorage>();

#       if 0

        std::unique_ptr<MemoryStorageHandle> handle = 
            std::make_unique<MemoryStorageHandle>(
                {0},
                std::move(storage));

#       endif

    }  

    std::unique_ptr<MemoryStorageHandle> MemoryStorageHandleTest::constructHandle(
        const std::string& data) {

        /**
         * We construct MemoryStorage with `new`, because constructor taking
         * `CharBufferStub` is private. `MemoryStorageHandleTest` is friend,
         * but `std::make_unique` is not.
         */
        return std::make_unique<MemoryStorageHandle>(
            MemoryStorageHandle::ConstructorPermission{0},
            std::unique_ptr<MemoryStorage>(
                new MemoryStorage(char_buffer::unit_test::CharBufferStub(data))));
    }

}