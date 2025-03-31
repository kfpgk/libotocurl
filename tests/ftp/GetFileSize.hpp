#ifndef LIBOTOCURL_TESTS_CURL_FTP_GET_FILE_SIZE_HPP
#define LIBOTOCURL_TESTS_CURL_FTP_GET_FILE_SIZE_HPP

#include <libotocurl/utility/Literals.hpp>

#include <libcpptest/integration_test/SingleTest.hpp>

#include <cstddef>
#include <string>

using namespace otocurl::utility::literals;

namespace otocurl::integration_test::ftp {

    class GetFileSize : public cpptest::integration_test::SingleTest {

        public:
            explicit GetFileSize(const std::string& testName,
                const std::string& server,
                const std::string& pathOnServer);

        private:
            std::string server;
            std::string pathOnServer;
            std::string file1Name;
            std::string file1Content;
            std::string file1RemotePath;
            std::string binaryFile1Name;
            std::string binaryFile1RemotePath;
            int binaryFile1Content;

            std::size_t file1Size = 2_MB;
            std::size_t binaryFile1Size = 3_MB;
            std::size_t file1RetrievedSize;
            std::size_t binaryFile1RetrievedSize;
            
            void setup() override;
            void perform() override;
            void evaluate() override;
            void cleanUp() override; 

    };

}

#endif