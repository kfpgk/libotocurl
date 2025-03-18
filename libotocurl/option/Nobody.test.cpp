#include <libotocurl/option/Nobody.test.hpp>
#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

#include <libcpplog/logger/Log.hpp>
#include <libcpplog/debug/Debug.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {
	
	otocurl::option::unit_test::NobodyTest test;
	
	test.testGetTargetValueFalse();
	test.testGetTargetValueTrue();

	test.testSetToFalse();
	test.testSetToTrue();
	
	log(LogLevel::Result, "option::Nobody: passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void NobodyTest::testGetTargetValueFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub<decltype(value)> easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void NobodyTest::testGetTargetValueTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub<decltype(value)> easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void NobodyTest::testSetToFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub<long> easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		option.set();

		if (easyStub.getOptionValue() != value) {
			DEBUG("Expected: " << value);
			DEBUG("Actual: " << easyStub.getOptionValue());
		}

		assert(easyStub.getOptionValue() == value);
	}

	void NobodyTest::testSetToTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub<decltype(value)> easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		option.set();

		assert(easyStub.getOptionValue() == value);
	}

}