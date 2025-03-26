#include <libotocurl/parser/StringOperations.test.hpp>
#include <libotocurl/parser/StringOperations.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

int main(int argc, char* argv[]) {

	using namespace cpplog::logger;

	otocurl::parser::string_operations::unit_test::Test test;

	test.testTrim();

	log(LogLevel::Result, "parser::string_operations passed");
	return 0;
}

namespace otocurl::parser::string_operations::unit_test {

	using namespace cpplog::logger;

	void Test::testTrim() const {
		log("Running ", LogRequest::functionName());

		std::string result = trim("  This is a test string  \n");

		assert(result == "This is a test string");
	}

}