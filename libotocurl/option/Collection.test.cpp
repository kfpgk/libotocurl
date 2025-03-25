#include <libotocurl/option/Collection.test.hpp>
#include <libotocurl/option/Collection.hpp>
#include <libotocurl/option/OptionStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>
#include <memory>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {

	otocurl::option::unit_test::CollectionTest test;

	test.testSet();

	log(LogLevel::Result, "option::Collection passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void CollectionTest::testSet() const {
		log("Running ", LogRequest::functionName());

		Collection collection;

		std::shared_ptr<OptionStub<int>> option1 = std::make_shared<OptionStub<int>>(5, 1);
		std::shared_ptr<OptionStub<bool>> option2 = std::make_shared<OptionStub<bool>>(false, true);

		collection.add(option1);
		collection.add(option2);

		collection.set();

		assert(option1->getActualValue() == 5);
		assert(option2->getActualValue() == false);
	}

}