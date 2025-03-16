#include <libotocurl/storage/FileStorage.test.hpp>
#include <libotocurl/storage/FileStorage.hpp>
#include <libotocurl/option/Factory.hpp>
#include <libotocurl/wrapper/Easy.hpp>
#include <libotocurl/utility/Literals.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;
using namespace otocurl::utility::literals;

int main(int argc, char* argv[]) {

    otocurl::storage::unit_test::FileStorageTest fileStorageTest;

    fileStorageTest.set_input_filesize_to_0();
    fileStorageTest.set_input_filesize_to_1KB();
    fileStorageTest.set_input_filesize_to_2047MB();
    fileStorageTest.set_input_filesize_to_2GB();
    fileStorageTest.set_input_filesize_to_99TB();
    fileStorageTest.set_input_filesize_to_n1KB();

    log(LogLevel::Result, "curl::storage::FileStorage: passed");
    return 0;
}

namespace otocurl::storage::unit_test {

    void FileStorageTest::set_input_filesize_to_0() {
        log("Running ", LogRequest::functionName());
        
        wrapper::Easy easy;
        option::Factory factory(easy);
        storage::FileStorage fileStorage("any");

        fileStorage.setInputFileSize(factory, 0);
    }

    void FileStorageTest::set_input_filesize_to_1KB() {
        log("Running ", LogRequest::functionName());

        wrapper::Easy easy;
        option::Factory factory(easy);
        storage::FileStorage fileStorage("any");

        fileStorage.setInputFileSize(factory, 1_KB);
    }

    void FileStorageTest::set_input_filesize_to_2047MB() {
        log("Running ", LogRequest::functionName());

        wrapper::Easy easy;
        option::Factory factory(easy);
        storage::FileStorage fileStorage("any");

        fileStorage.setInputFileSize(factory, 2047_MB);
    }

    void FileStorageTest::set_input_filesize_to_2GB() {
        log("Running ", LogRequest::functionName());

        wrapper::Easy easy;
        option::Factory factory(easy);
        storage::FileStorage fileStorage("any");
        
        fileStorage.setInputFileSize(factory, 2_GB);
    }

    void FileStorageTest::set_input_filesize_to_99TB() {
        log("Running ", LogRequest::functionName());

        wrapper::Easy easy;
        option::Factory factory(easy);
        storage::FileStorage fileStorage("any");
        fileStorage.setInputFileSize(factory, 99_TB);
    }

    void FileStorageTest::set_input_filesize_to_n1KB() {
        log("Running ", LogRequest::functionName());

        wrapper::Easy easy;
        option::Factory factory(easy);
        storage::FileStorage fileStorage("any");
        bool curlExceptionThrown = false;

        try {
            fileStorage.setInputFileSize(factory, -1_KB);
        } catch (const std::exception& e) {
            log(LogLevel::Info, e);
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);       
    }

}