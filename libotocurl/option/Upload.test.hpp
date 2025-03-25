#ifndef LIBOTOCURL_OPTION_UPLOAD_TEST_HPP
#define LIBOTOCURL_OPTION_UPLOAD_TEST_HPP

namespace otocurl::option::unit_test {

	/**
	 * @brief Unit test `Upload` 
	 */
	class UploadTest {

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
		 * @brief Test `set()` with false
		 */
		void testSetToFalse() const;

		/**
		 * @brief Test `set()` with true
		 */
		void testSetToTrue() const;

		/**
		 * @brief Test `undo()`
		 */
		void testUndo() const;

		/**
		 * @brief Test `reset()`
		 */
		void testReset() const;

		/**
		 * @brief Test `reset()` without reset value
		 */
		void testResetWithoutResetValue() const;

	};

}

#endif