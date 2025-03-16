#include <libotocurl/storage/char_buffer/ReadWriteBuffer.test.hpp>
#include <libotocurl/storage/char_buffer/ReadWriteBuffer.hpp>
#include <libotocurl/utility/Literals.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <ratio>
#include <span>
#include <string>

using namespace cpplog::logger;
using namespace otocurl::utility::literals;

int main(int argc, char* argv[]) {

    otocurl::storage::char_buffer::unit_test::ReadWriteBufferTest test;

    test.test_clear();
    test.test_byte_array_and_string_write();

    test.test_swap();
    test.copy_construction();
    test.move_construction();
    test.copy_assignment();
    test.move_assignment();

    test.write_1MB_in_1KB_chunks_no_pre_alloc();
    test.write_1MB_in_1KB_chunks_with_pre_alloc();
    test.read_1MB_in_1KB_chunks();
    test.write_1MB_at_once_with_pre_alloc();
    test.read_1MB_at_once();

    log(LogLevel::Result, "curl::storage::char_buffer::ReadWriteBuffer: passed");
    return 0;
}

namespace otocurl::storage::char_buffer::unit_test {

    void ReadWriteBufferTest::test_clear() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer data1;
        std::size_t sizeBefore = data1.getSize();
        std::string stringData {"test content"};

        data1.write(stringData);
        data1.clear();

        std::size_t sizeAfter = data1.getSize();

        assert(sizeBefore == sizeAfter);
    }

    void ReadWriteBufferTest::test_byte_array_and_string_write() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer data1;
        ReadWriteBuffer data2;

        std::string stringData {"test content"};
        char byteArrayData[] {"test content"};

        data1.write(stringData);
        
        std::size_t remaining = 12;
        while (remaining > 0) {
            std::size_t written = data2.write(byteArrayData, remaining);
            remaining -= written;
        }

        assert(data1 == data2);
    }

    void ReadWriteBufferTest::test_swap() {
        log("Running ", LogRequest::functionName());

        ReadWriteBuffer data1{"data1"};
        ReadWriteBuffer data2{"data2"};

        using std::swap;
        swap(data1, data2);

        assert(data1.getString() == "data2");
        assert(data2.getString() == "data1");
    }

    void ReadWriteBufferTest::copy_construction() {
        log("Running ", LogRequest::functionName());

        ReadWriteBuffer data1{"data1"};
        ReadWriteBuffer data2{data1};

        assert(data1.getString() == "data1");
        assert(data2.getString() == "data1");
    }

    void ReadWriteBufferTest::move_construction() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer data1{"data1"};
        ReadWriteBuffer data2{std::move(data1)};

        assert(data1.getString() == "");
        assert(data2.getString() == "data1");
    }

    void ReadWriteBufferTest::copy_assignment() {
        log("Running ", LogRequest::functionName());

        ReadWriteBuffer data1{"data1"};
        ReadWriteBuffer data2{"data2"};
        data2 = data1;

        assert(data1.getString() == "data1");
        assert(data2.getString() == "data1");
    }

    void ReadWriteBufferTest::move_assignment() {
        log("Running ", LogRequest::functionName());

        ReadWriteBuffer data1{"data1"};
        ReadWriteBuffer data2{"data2"};
        data2 = std::move(data1);

        assert(data1.getString() == "");
        assert(data2.getString() == "data1");
    }

    void ReadWriteBufferTest::write_1MB_in_1KB_chunks_no_pre_alloc() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer buffer;

        char byteArrayData[1_KB] {"test content"};
        
        using namespace std::chrono;
        auto start = steady_clock::now();

        for (std::size_t i = 0; i < 1_KB; i++) {
            std::size_t remaining = 1_KB;
            while (remaining > 0) {
                std::size_t written = buffer.write(byteArrayData, remaining);
                remaining -= written;
            }
        }

        auto end = steady_clock::now();
        duration<float, std::milli> executionTime = end - start;

        log(LogLevel::Result, "Test time: " + std::to_string(executionTime.count()) + "ms");

        assert(executionTime < 200ms);
    }

    void ReadWriteBufferTest::write_1MB_in_1KB_chunks_with_pre_alloc() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer buffer(1_MB);

        char byteArrayData[1_KB] {"test content"};
        
        using namespace std::chrono;
        auto start = steady_clock::now();

        for (std::size_t i = 0; i < 1_KB; i++) {
            std::size_t remaining = 1_KB;
            while (remaining > 0) {
                std::size_t written = buffer.write(byteArrayData, remaining);
                remaining -= written;
            }
        }

        auto end = steady_clock::now();
        duration<float, std::milli> executionTime = end - start;

        log(LogLevel::Result, "Test time: " + std::to_string(executionTime.count()) + "ms");

        assert(executionTime < 10ms);
    }

    void ReadWriteBufferTest::read_1MB_in_1KB_chunks() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer buffer(1_MB);

        char byteArrayData[1_KB] {"test content"};

        for (std::size_t i = 0; i < 1_KB; i++) {
            std::size_t remaining = 1_KB;
            while (remaining > 0) {
                std::size_t written = buffer.write(byteArrayData, remaining);
                remaining -= written;
            }
        }

        char* readToData = new char[1_MB];

        using namespace std::chrono;
        auto start = steady_clock::now();

        std::size_t remaining = 1_MB;
        std::size_t i = 0;
        while (remaining > 0) {
            std::size_t read = buffer.read(readToData + i * 1_KB, 1_KB);
            remaining -= read;
            i++;
        }

        auto end = steady_clock::now();
        duration<float, std::milli> executionTime = end - start;

        delete[] readToData;

        log(LogLevel::Result, "Test time: " + std::to_string(executionTime.count()) + "ms");

        assert(executionTime < 10ms);
    }

    void ReadWriteBufferTest::write_1MB_at_once_with_pre_alloc() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer buffer(1_MB);

        char* byteArrayData = new char[1_MB] {"test content"};

        using namespace std::chrono;
        auto start = steady_clock::now();

        std::size_t written = buffer.write(byteArrayData, 1_MB);

        auto end = steady_clock::now();
        duration<float, std::milli> executionTime = end - start;

        delete[] byteArrayData;
        log(LogLevel::Result, 
            "Test time 1MB write: " + std::to_string(executionTime.count()) + "ms");

        assert(executionTime < 10ms);
    }

    void ReadWriteBufferTest::read_1MB_at_once() {
        log("Running ", LogRequest::functionName());
        
        ReadWriteBuffer buffer(1_MB);

        char* byteArrayData = new char[1_MB] {"test content"};

        std::size_t written = buffer.write(byteArrayData, 1_MB);

        char* readToData = new char[1_MB];

        using namespace std::chrono;
        auto start = steady_clock::now();

        std::size_t read = buffer.read(readToData, 1_MB);

        auto end = steady_clock::now();
        duration<float, std::milli> executionTime = end - start;

        delete[] byteArrayData;
        delete[] readToData;
        log(LogLevel::Result, 
            "Test time 1MB read: " + std::to_string(executionTime.count()) + "ms");

        assert(executionTime < 10ms);
    }    

}