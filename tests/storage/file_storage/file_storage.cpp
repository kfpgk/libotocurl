#include <tests/storage/file_storage/FileStorage.hpp>

namespace test = otocurl::integration_test;

int main(int argc, char* argv[]) {

    test::storage::file_storage::FileStorage test(
        "curl file storage basic operations");

    test.run();

    return 0;
}