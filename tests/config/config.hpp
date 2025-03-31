#ifndef LIBOTOCURL_TESTS_CONFIG_CONFIG_HPP
#define LIBOTOCURL_TESTS_CONFIG_CONFIG_HPP

#include <string_view>

namespace otocurl::integration_test::config {

	constexpr std::string_view testFtpServer = "vm1.ubuntu";

	constexpr std::string_view testFtpServerDir = "test";

}

#endif