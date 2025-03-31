#include <tests/ftp/GetFileSize.hpp>
#include <tests/config/config.hpp>

namespace test = otocurl::integration_test;

int main(int argc, char* argv[]) {

    test::ftp::GetFileSize test("curl ftp get file size",
        std::string(test::config::testFtpServer),
        std::string(test::config::testFtpServerDir));

    test.run();

    return 0;
}