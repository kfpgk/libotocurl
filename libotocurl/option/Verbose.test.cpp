#include <libotocurl/option/Verbose.test.hpp>
#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {
	
	otocurl::option::unit_test::VerboseTest test;
	
	test.testGetTargetValueFalse();
	test.testGetTargetValueTrue();

	test.testSetToFalse();
	test.testSetToTrue();
	
	test.testUndo();

	test.testReset();
	test.testResetWithoutResetValue();

	log(LogLevel::Result, "option::Verbose: passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void VerboseTest::testGetTargetValueFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void VerboseTest::testGetTargetValueTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void VerboseTest::testSetToFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value));

		option.set();

		assert(option.getActualValue() == value);
	}

	void VerboseTest::testSetToTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value));

		option.set();

		assert(option.getActualValue() == value);
	}

	void VerboseTest::testUndo() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value));

		option.set();
		option.undo();

		assert(option.getActualValue() == false);
	}

	void VerboseTest::testReset() const {
		log("Running ", LogRequest::functionName());

		bool value = false;
		bool resetValue = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value, resetValue));

		option.set();
		option.reset();

		assert(option.getActualValue() == true);
	}

	void VerboseTest::testResetWithoutResetValue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Verbose option(option::Verbose(easyStub, value));

		option.set();
		option.reset();

		assert(option.getActualValue() == true);
	}

}