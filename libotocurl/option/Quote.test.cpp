#include <libotocurl/option/Quote.test.hpp>
#include <libotocurl/option/Quote.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {
	
	otocurl::option::unit_test::QuoteTest test;
	
	test.testGetTargetValue();

	test.testSet();

	test.testUndo();
	
	log(LogLevel::Result, "option::Quote: passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void QuoteTest::testGetTargetValue() const {
		log("Running ", LogRequest::functionName());

		wrapper::unit_test::EasyStub easyStub;
		option::Quote option(option::Quote(easyStub, "CWD /"));

		assert(option.getTargetValue() != nullptr);
	}

	void QuoteTest::testSet() const {
		log("Running ", LogRequest::functionName());

		bool value = false;

		wrapper::unit_test::EasyStub easyStub;
		option::Quote option(option::Quote(easyStub, "CWD /"));

		option.set();

		assert(option.actualOptionHoldsList());
	}

	void QuoteTest::testUndo() const {
		log("Running ", LogRequest::functionName());

		wrapper::unit_test::EasyStub easyStub;
		option::Quote option(option::Quote(easyStub, "CWD /"));

		option.set();
		option.undo();

		assert(!option.actualOptionHoldsList());
	}

}