#ifndef LIBOTOCURL_OPTION_NOBODY_HPP
#define LIBOTOCURL_OPTION_NOBODY_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <functional>

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
     *  - Template
     */
    class Nobody : public ResettableOption<bool>, public UndoableOptionImpl<bool>  {

    public:
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
        /// @brief The CURLOPT identifier
        static constexpr CURLoption curlOption = CURLOPT_NOBODY;

        /// @brief The curl interface for which this option shall be set
        std::reference_wrapper<wrapper::Easy> curlInterface;

        bool targetValue; ///< The target value of the option when being set

        /**
         * @brief Returns the target targetValue
         * 
         * Needed for undo functionality
         * 
		 * @return The target value to be set
         */
        [[nodiscard]] bool getTargetValue() const override;

        /**
         * @brief Sets the option to the specified targetValue \p targetValue
         * 
         * @param[in] targetValue Option will be set to this targetValue
         * 
         * @details This overrides `UndoableOption`. `UndoableOption`
         * frees us from overriding the original `Option` method `doSet()`
         * and requires us to provide `setTo()` instead. 
         * `UndoableOption` calls `setTo()` parameterized to specify if a command
         * shall be done or undone.
         */
        void setTo(bool targetValue) override;

        /**
         * @brief Returns the value of the CURLOPT_NOBODY option in the curl interface
         *
         * @return The value of the CURLOPT_NOBODY option
         */
        [[nodiscard]] bool getActualValue() const;

		friend class unit_test::NobodyTest; ///< Allow unit test to access private members

    };

}

#endif