#ifndef LIBOTOCURL_OPTION_NOBODY_TEST_HPP
#define LIBOTOCURL_OPTION_NOBODY_TEST_HPP

namespace otocurl::option::unit_test {

	/**
	 * @brief Unit test `Nobody` 
	 */
	class NobodyTest {

	public:
		/**
		 * @brief Test `getTargetValue()` with false
		 */
		void testGetTargetValueFalse() const;

		/**
		 * @brief Test `getTargetValue()` with true
		 */
		void testGetTargetValueTrue() const;

		/**
		 * @brief Test `set()` with `false
		 */
		void testSetToFalse() const;

		/**
		 * @brief Test `set()` with `true
		 */
		void testSetToTrue() const;

	};

}

#endif