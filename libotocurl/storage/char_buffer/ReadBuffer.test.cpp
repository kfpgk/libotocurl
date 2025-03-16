#include <libotocurl/storage/char_buffer/ReadBuffer.test.hpp>
#include <libotocurl/storage/char_buffer/ReadBuffer.hpp>
#include <libotocurl/utility/Literals.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <ratio>
#include <span>
#include <string>
#include <vector>

using namespace cpplog::logger;
using namespace otocurl::utility::literals;

int main(int argc, char* argv[]) {

    otocurl::storage::char_buffer::unit_test::ReadBufferTest test;

    test.test_get_size();
    test.test_get_span();
    test.test_get_string();

    test.test_swap();
    test.copy_construction();
    test.move_construction();
    test.copy_assignment();
    test.move_assignment();

    test.read_1MB_in_1KB_chunks();
    test.read_1MB_at_once();

    log(LogLevel::Result, "curl::storage::char_buffer::ReadBuffer: passed");
    return 0;
}

namespace otocurl::storage::char_buffer::unit_test {

    void ReadBufferTest::test_get_size() {
        log("Running ", LogRequest::functionName());
        
        std::vector<char> data{'t','e','s','t',' ','c','o','n','t','e','n','t'};
        ReadBuffer data1{data};

        assert(12 == data1.getSize());
    }

    void ReadBufferTest::test_get_span() {
        log("Running ", LogRequest::functionName());

        std::string stringData {"Test content"};
        ReadBuffer data1(stringData);

        data1.print();

        std::span span = data1.getSpan();

        assert(data1.getSize() == span.size());
        assert(span[0] == 'T');
        assert(span[1] == 'e');
        assert(span[2] == 's');
        assert(span[3] == 't');
        assert(span[4] == ' ');
        assert(span[5] == 'c');
        assert(span[6] == 'o');
        assert(span[7] == 'n');
        assert(span[8] == 't');
        assert(span[9] == 'e');
        assert(span[10] == 'n');
        assert(span[11] == 't');
        assert((void*)span.data() == (void*)data1.data);
    }

    void ReadBufferTest::test_get_string() {
        log("Running ", LogRequest::functionName());

        std::string stringData {"Test content"};
        ReadBuffer data1(stringData);

        data1.print();

        assert(data1.getString() == "Test content");       
    }

    void ReadBufferTest::test_swap() {
        log("Running ", LogRequest::functionName());

        std::string string1("data1");
        std::string string2("data2");
        ReadBuffer data1{string1};
        ReadBuffer data2{string2};

        using std::swap;
        swap(data1, data2);

        assert(data1.getString() == "data2");
        assert(data2.getString() == "data1");
    }

    void ReadBufferTest::copy_construction() {
        log("Running ", LogRequest::functionName());

        std::string string1("data1");
        ReadBuffer data1{string1};
        ReadBuffer data2{data1};

        assert(data1.getString() == "data1");
        assert(data2.getString() == "data1");
    }

    void ReadBufferTest::move_construction() {
        log("Running ", LogRequest::functionName());
        
        std::string string1("data1");
        ReadBuffer data1{string1};
        ReadBuffer data2{std::move(data1)};

        assert(data1.getString() == "");
        assert(data2.getString() == "data1");
    }

    void ReadBufferTest::copy_assignment() {
        log("Running ", LogRequest::functionName());

        std::string string1("data1");
        std::string string2("data2");
        ReadBuffer data1{string1};
        ReadBuffer data2{string2};
        data2 = data1;

        assert(data1.getString() == "data1");
        assert(data2.getString() == "data1");
    }

    void ReadBufferTest::move_assignment() {
        log("Running ", LogRequest::functionName());

        std::string string1("data1");
        std::string string2("data2");
        ReadBuffer data1{string1};
        ReadBuffer data2{string2};
        data2 = std::move(data1);

        assert(data1.getString() == "");
        assert(data2.getString() == "data1");
    }

    void ReadBufferTest::read_1MB_in_1KB_chunks() {
        log("Running ", LogRequest::functionName());
        
        std::string bufferData(1_MB, 'x');
        ReadBuffer buffer(bufferData);

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

    void ReadBufferTest::read_1MB_at_once() {
        log("Running ", LogRequest::functionName());
        
        std::string bufferData(1_MB, 'x');
        ReadBuffer buffer(bufferData);

        char* readToData = new char[1_MB];

        using namespace std::chrono;
        auto start = steady_clock::now();

        std::size_t read = buffer.read(readToData, 1_MB);

        auto end = steady_clock::now();
        duration<float, std::milli> executionTime = end - start;

        delete[] readToData;
        
        log(LogLevel::Result, 
            "Test time 1MB read: " + std::to_string(executionTime.count()) + "ms");

        assert(executionTime < 10ms);
    }    

}