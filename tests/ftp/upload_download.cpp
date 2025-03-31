#include <tests/ftp/UploadDownload.hpp>
#include <tests/config/config.hpp>

namespace test = otocurl::integration_test;

int main(int argc, char* argv[]) {

    test::ftp::UploadDownload test("curl ftp upload and download",
        std::string(test::config::testFtpServer), 
        std::string(test::config::testFtpServerDir));

    test.run();

    return 0;
}