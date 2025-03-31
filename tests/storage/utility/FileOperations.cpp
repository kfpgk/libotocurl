#include <tests/storage/utility/FileOperations.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace otocurl::integration_test::storage::utility {

    namespace file_operations {

        bool haveEqualSize(
            const std::filesystem::path& rhs,
            const std::filesystem::path& lhs) {

            return (std::filesystem::file_size(rhs) == std::filesystem::file_size(lhs));
        }

        bool areEqual(
            const std::filesystem::path& lhs,
            const std::filesystem::path& rhs) {

            std::ifstream lhsStream(lhs.string(), std::ifstream::binary | std::ifstream::ate);
            std::ifstream rhsStream(rhs.string(), std::ifstream::binary | std::ifstream::ate);

            if (lhsStream.fail() || rhsStream.fail()) {
                return false;
            }

            if (!haveEqualSize(lhs, rhs)) {
                return false;
            }

            lhsStream.seekg(0, std::ifstream::beg);
            rhsStream.seekg(0, std::ifstream::beg);
            return std::equal(
                std::istreambuf_iterator<char>(lhsStream.rdbuf()),
                std::istreambuf_iterator<char>(),
                std::istreambuf_iterator<char>(rhsStream.rdbuf()));

        }

    }

}