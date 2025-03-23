#include <libotocurl/option/Invoker.test.hpp>
#include <libotocurl/option/Invoker.hpp>
#include <libotocurl/option/OptionStub.test.hpp>

#include <libcpplog/logger/Log.hpp>

#include <cassert>
#include <memory>

using namespace cpplog::logger;

int main(int argc, char* argv[]) {

	otocurl::option::unit_test::InvokerTest test;

	test.testInvokeSingleOption();
	test.testInvokeMultipleOptions();

	test.testUndoSingleOption();
	test.testUndoMultipleOptions();

	test.testRedoSingleOption();
	test.testRedoMultipleOptions();

	log(LogLevel::Result, "option::Invoker: passed");
	return 0;
}

namespace otocurl::option::unit_test {

	void InvokerTest::testInvokeSingleOption() const {
		log("Running ", LogRequest::functionName());

		Invoker invoker;

		bool targetValue = true;
		bool initialValue = false;
		using ValueType = decltype(targetValue);

		std::shared_ptr<OptionStub<ValueType>> option =
			std::make_shared<OptionStub<ValueType>>(targetValue, initialValue);

		invoker.set(option);

		assert(option->getActualValue() == targetValue);
	}

	void InvokerTest::testInvokeMultipleOptions() const {
		log("Running ", LogRequest::functionName());

		Invoker invoker;

		bool targetValue1 = true;
		bool initialValue1 = false;
		long targetValue2 = 42;
	    long initialValue2 = 0;

		using ValueType1 = decltype(targetValue1);
		using ValueType2 = decltype(targetValue2);
		
		std::shared_ptr<OptionStub<ValueType1>> option1 =
			std::make_shared<OptionStub<ValueType1>>(targetValue1, initialValue1);

		std::shared_ptr<OptionStub<ValueType2>> option2 =
			std::make_shared<OptionStub<ValueType2>>(targetValue2, initialValue2);

		invoker.set(option1);
		invoker.set(option2);

		assert(option1->getActualValue() == targetValue1);
		assert(option2->getActualValue() == targetValue2);
	}

	void InvokerTest::testUndoSingleOption() const {
		log("Running ", LogRequest::functionName());

		Invoker invoker;

		bool targetValue = true;
		bool initialValue = false;
		using ValueType = decltype(targetValue);

		std::shared_ptr<OptionStub<ValueType>> option =
			std::make_shared<OptionStub<ValueType>>(targetValue, initialValue);

		invoker.set(option);
		invoker.undo();

		assert(option->getActualValue() == initialValue);
	}

	void InvokerTest::testUndoMultipleOptions() const {
		log("Running ", LogRequest::functionName());

		Invoker invoker;

		bool targetValue1 = true;
		bool initialValue1 = false;
		long targetValue2 = 42;
		long initialValue2 = 0;

		using ValueType1 = decltype(targetValue1);
		using ValueType2 = decltype(targetValue2);

		std::shared_ptr<OptionStub<ValueType1>> option1 =
			std::make_shared<OptionStub<ValueType1>>(targetValue1, initialValue1);

		std::shared_ptr<OptionStub<ValueType2>> option2 =
			std::make_shared<OptionStub<ValueType2>>(targetValue2, initialValue2);

		invoker.set(option1);
		invoker.set(option2);

		invoker.undo();
		invoker.undo();

		assert(option1->getActualValue() == initialValue1);
		assert(option2->getActualValue() == initialValue2);
	}

	void InvokerTest::testRedoSingleOption() const {
		log("Running ", LogRequest::functionName());

		Invoker invoker;

		bool targetValue = true;
		bool initialValue = false;
		using ValueType = decltype(targetValue);

		std::shared_ptr<OptionStub<ValueType>> option =
			std::make_shared<OptionStub<ValueType>>(targetValue, initialValue);

		invoker.set(option);
		invoker.undo();
		invoker.redo();

		assert(option->getActualValue() == targetValue);
	}

	void InvokerTest::testRedoMultipleOptions() const {
		log("Running ", LogRequest::functionName());

		Invoker invoker;

		bool targetValue1 = true;
		bool initialValue1 = false;
		long targetValue2 = 42;
		long initialValue2 = 0;

		using ValueType1 = decltype(targetValue1);
		using ValueType2 = decltype(targetValue2);

		std::shared_ptr<OptionStub<ValueType1>> option1 =
			std::make_shared<OptionStub<ValueType1>>(targetValue1, initialValue1);

		std::shared_ptr<OptionStub<ValueType2>> option2 =
			std::make_shared<OptionStub<ValueType2>>(targetValue2, initialValue2);

		invoker.set(option1);
		invoker.set(option2);

		invoker.undo();
		invoker.undo();

		invoker.redo();
		invoker.redo();

		assert(option1->getActualValue() == targetValue1);
		assert(option2->getActualValue() == targetValue2);
	}

}