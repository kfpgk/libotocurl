#include <tests/storage/memory_storage/MemoryStorage.hpp>
#include <tests/config/config.hpp>

namespace test = otocurl::integration_test;

int main(int argc, char* argv[]) {

    test::storage::memory_storage::MemoryStorage test(
        "curl upload and download to memory storage",
        std::string(test::config::testFtpServer),
        std::string(test::config::testFtpServerDir));

    test.run();

    return 0;
}