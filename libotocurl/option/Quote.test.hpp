#ifndef LIBOTOCURL_OPTION_QUOTE_TEST_HPP
#define LIBOTOCURL_OPTION_QUOTE_TEST_HPP

namespace otocurl::option::unit_test {

	/**
	 * @brief Unit test `Quote` 
	 */
	class QuoteTest {

	public:
		/**
		 * @brief Test `getTargetValue()` with a command
		 */
		void testGetTargetValue() const;

		/**
		 * @brief Test `set()`
		 */
		void testSet() const;

		/**
		 * @brief Test `undo()`
		 */
		void testUndo() const;

	};

}

#endif