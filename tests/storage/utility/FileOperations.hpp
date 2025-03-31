#ifndef LIBOTOCURL_TESTS_STORAGE_UTILITY_FILE_OPERATIONS_HPP
#define LIBOTOCURL_TESTS_STORAGE_UTILITY_FILE_OPERATIONS_HPP

#include <filesystem>

namespace otocurl::integration_test::storage::utility {

	namespace file_operations {

        bool haveEqualSize(
            const std::filesystem::path& lhs,
            const std::filesystem::path& rhs);

        bool areEqual(
            const std::filesystem::path& lhs,
            const std::filesystem::path& rhs);
	}

}

#endif