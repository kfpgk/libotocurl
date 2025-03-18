#ifndef LIBOTOCURL_OPTION_NOBODY_HPP
#define LIBOTOCURL_OPTION_NOBODY_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/Easy.hpp>

namespace otocurl::option {

	namespace unit_test {
		class NobodyTest; ///< Forward declaration for unit test
	}

    /**
     * @brief Wrapper for CURLOPT_NOBODY
     * 
     * @details
     * Patterns:
     *  - Command
     */
    class Nobody : public ResettableOption<bool>, public UndoableOptionImpl<bool>  {

    public:
        /// @brief The default value of the option
        static constexpr bool defaultValue = false;

        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] targetValue The target value of the option when being set
         */
        explicit Nobody(wrapper::Easy& curlInterface, bool targetValue) noexcept;

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] targetValue The target value of the option when being set
         * @param[in] resetValue The reset value of the option when being destructed
         */
        Nobody(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) noexcept;
        
        /**
         * @brief Destructor
         */
        ~Nobody();

    private:
        bool targetValue; ///< The target value of the option when being set

        /**
         * @brief Returns the target targetValue
         * 
         * Needed for undo functionality
         */
        [[nodiscard]] bool getTargetValue() const override;

        /**
         * @brief Sets the option to the specified targetValue \p targetValue
         * 
         * @param[in] targetValue Option will be set to this targetValue
         * 
         * @details This override `UndoableOption`. `UndoableOption`
         * frees us from overriding the original `Option` method `doSet()`
         * and requires us to provide `setTo()` instead. 
         * `UndoableOption` calls `setTo()` parameterized to specify if a command
         * shall be done or undone.
         */
        void setTo(bool targetValue) override;

		friend class unit_test::NobodyTest; ///< Allow unit test to access private members

    };

}

#endif