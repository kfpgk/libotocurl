#include <libotocurl/ProtocolClient.test.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>
#include <libotocurl/utility/Literals.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {

    otocurl::unit_test::ProtocolClientTest test;

    test.set_bad_host_name();

    test.set_valid_remote_file();
    test.set_remote_file_with_special_chars();
    test.set_non_existing_local_file_for_upload();

    test.download_uninitialized_easy_stubbed();
    test.download_with_uninitialized_local_path_easy_stubbed();

    test.upload_uninitialized_easy_stubbed();
    test.upload_with_uninitialized_local_path_easy_stubbed();

    log(LogLevel::Result, "ProtocolClient: passed");
    return 0;

}

namespace otocurl::unit_test {

    std::string dummyServerAddress = "dummy";

    void ProtocolClientTest::set_bad_host_name() {
		log(LogLevel::Info, "Running set_bad_host_name()");
        
        bool curlExceptionThrown = false;
        try {
            ProtocolClientConcrete client("::dummy::",
                std::make_unique<wrapper::unit_test::EasyStub>());
        } catch (std::exception& e) {
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);   

    }

    void ProtocolClientTest::set_valid_remote_file() {
        log(LogLevel::Info, "Running set_valid_remote_file()");

        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        client.setRemoteFile("dir-path/file");
    }

    void ProtocolClientTest::set_remote_file_with_special_chars() {
        log(LogLevel::Info, "Running set_remote_file_with_special_chars()");

        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        client.setRemoteFile("!./%/:kla");
    }

    void ProtocolClientTest::set_non_existing_local_file_for_upload() {
		log(LogLevel::Info, "Running set_non_existing_local_file_for_upload()");

        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        bool curlExceptionThrown = false;
        try {
            client.setLocalFileForUpload("this_file_does_not_exist.txt");
        } catch (const Exception& e) {
            log(e.what());
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);      
    }

    void ProtocolClientTest::download_uninitialized_easy_stubbed() {
		log(LogLevel::Info, "Running download_uninitialized_easy_stubbed()");

        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        bool curlExceptionThrown = false;
        try {
            client.download();
        } catch (const Exception& e) {
            log(e.what());
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);           
    }

    void ProtocolClientTest::download_with_uninitialized_local_path_easy_stubbed() {
		log(LogLevel::Info, "Running download_with_uninitialized_local_path_easy_stubbed()");

        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        bool curlExceptionThrown = false;
        try {
            client.setRemoteFile("remotefile");
            client.download();
        } catch (const Exception& e) {
            log(e.what());
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);           
    }

    void ProtocolClientTest::upload_uninitialized_easy_stubbed() {
		log(LogLevel::Info, "Running upload_uninitialized_easy_stubbed()");

        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        bool curlExceptionThrown = false;
        try {
            client.upload();
        } catch (const Exception& e) {
            log(e.what());
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);        
    }

    void ProtocolClientTest::upload_with_uninitialized_local_path_easy_stubbed() {
		log(LogLevel::Info, "Running upload_with_uninitialized_local_path_easy_stubbed()");
            
        ProtocolClientConcrete client(dummyServerAddress,
            std::make_unique<wrapper::unit_test::EasyStub>());
        bool curlExceptionThrown = false;
        try {
            client.setRemoteFile("remotefile");
            client.upload();
        } catch (const Exception& e) {
			log(e.what());
            curlExceptionThrown = true;
        }
        assert(true == curlExceptionThrown);        
    }

}