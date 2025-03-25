#include <libotocurl/option/Nobody.test.hpp>
#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {
	
	otocurl::option::unit_test::NobodyTest test;
	
	test.testGetTargetValueFalse();
	test.testGetTargetValueTrue();

	test.testSetToFalse();
	test.testSetToTrue();

	test.testUndo();

	test.testReset();
	test.testResetWithoutResetValue();
	
	log(LogLevel::Result, "option::Nobody: passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void NobodyTest::testGetTargetValueFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void NobodyTest::testGetTargetValueTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void NobodyTest::testSetToFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		option.set();

		assert(option.getActualValue() == value);
	}

	void NobodyTest::testSetToTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		option.set();

		assert(option.getActualValue() == value);
	}

	void NobodyTest::testUndo() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		option.set();
		option.undo();

		assert(option.getActualValue() == false);
	}

	void NobodyTest::testReset() const {
		log("Running ", LogRequest::functionName());

		bool value = false;
		bool resetValue = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value, resetValue));

		option.set();
		option.reset();

		assert(option.getActualValue() == true);
	}

	void NobodyTest::testResetWithoutResetValue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Nobody option(option::Nobody(easyStub, value));

		option.set();
		option.reset();

		assert(option.getActualValue() == true);
	}

}