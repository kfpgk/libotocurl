#ifndef LIBOTOCURL_OPTION_VERBOSE_HPP
#define LIBOTOCURL_OPTION_VERBOSE_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

namespace otocurl::option {

    namespace unit_test {
        class VerboseTest; ///< Forward declaration for unit test
    }

    /**
     * @brief Wrapper for CURLOPT_VERBOSE
     * 
     * Patterns:
     *  - Command
     *  - Template
     */
    class Verbose : public ResettableOption<bool>, public UndoableOptionImpl<bool> {

    public:
        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] targetValue The target value of the option when being set
         */
        explicit Verbose(wrapper::Easy& curlInterface, bool targetValue);

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] targetValue The target value of the option when being set
         * @param[in] resetValue The reset value of the option when being destructed
         */
        Verbose(wrapper::Easy& curlInterface, bool targetValue, bool resetValue);

        /**
         * @brief Destructor
         */
        ~Verbose();

    private:
        /// @brief The CURLOPT identifier
        static constexpr CURLoption curlOption = CURLOPT_VERBOSE;

        bool targetValue; ///< The target targetValue of the option when being set

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
         * @brief Returns the value of the CURLOPT_VERBOSE option in the curl interface
         *
         * @return The value of the CURLOPT_VERBOSE option
         */
        [[nodiscard]] bool getActualValue() const;

        friend class unit_test::VerboseTest; ///< Allow unit test to access private members
    };

}

#endif