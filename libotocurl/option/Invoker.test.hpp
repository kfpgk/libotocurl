#ifndef LIBOTOCURL_OPTION_INVOKER_TEST_HPP
#define LIBOTOCURL_OPTION_INVOKER_TEST_HPP

namespace otocurl::option::unit_test {
	/**
	 * @brief Unit test `Invoker`
	 */
	class InvokerTest {

	public:
		/**
		 * @brief Test `set()` with a single option
		 */
		void testInvokeSingleOption() const;

		/**
		 * @brief Test `set()` with multiple options
		 */
		void testInvokeMultipleOptions() const;

		/**
		 * @brief Test `undo()` with a single option
		 */
		void testUndoSingleOption() const;

		/**
		 * @brief Test `undo()` with multiple options
		 */
		void testUndoMultipleOptions() const;

		/**
		 * @brief Test `redo()` with a single option
		 */
		void testRedoSingleOption() const;

		/**
		 * @brief Test `redo()` with multiple options
		 */
		void testRedoMultipleOptions() const;
	};
}

#endif