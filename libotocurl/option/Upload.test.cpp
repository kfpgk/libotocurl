#include <libotocurl/option/Upload.test.hpp>
#include <libotocurl/option/Upload.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {
	
	otocurl::option::unit_test::UploadTest test;
	
	test.testGetTargetValueFalse();
	test.testGetTargetValueTrue();

	test.testSetToFalse();
	test.testSetToTrue();

	test.testUndo();
	
	test.testReset();
	test.testResetWithoutResetValue();

	log(LogLevel::Result, "option::Upload: passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void UploadTest::testGetTargetValueFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void UploadTest::testGetTargetValueTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value));

		assert(option.getTargetValue() == value);
	}

	void UploadTest::testSetToFalse() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value));

		option.set();

		assert(option.getActualValue() == value);
	}

	void UploadTest::testSetToTrue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value));

		option.set();

		assert(option.getActualValue() == value);
	}

	void UploadTest::testUndo() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value));

		option.set();
		option.undo();

		assert(option.getActualValue() == false);
	}

	void UploadTest::testReset() const {
		log("Running ", LogRequest::functionName());

		bool value = false;
		bool resetValue = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value, resetValue));

		option.set();
		option.reset();

		assert(option.getActualValue() == true);
	}

	void UploadTest::testResetWithoutResetValue() const {
		log("Running ", LogRequest::functionName());

		bool value = true;

		wrapper::unit_test::EasyStub easyStub;
		option::Upload option(option::Upload(easyStub, value));

		option.set();
		option.reset();

		assert(option.getActualValue() == true);
	}

}