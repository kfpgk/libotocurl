#ifndef LIBOTOCURL_OPTION_VERBOSE_HPP
#define LIBOTOCURL_OPTION_VERBOSE_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/Easy.hpp>

namespace otocurl::option {

    /**
     * @brief Wrapper for CURLOPT_VERBOSE
     * 
     * Patterns:
     *  - Command
     */
    class Verbose : public ResettableOption<bool>, public UndoableOptionImpl<bool> {

    public:
        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] value The target value of the option when being set
         */
        explicit Verbose(wrapper::Easy& curlInterface, bool value);

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] value The target value of the option when being set
         * @param[in] resetValue The reset value of the option when being destructed
         */
        Verbose(wrapper::Easy& curlInterface, bool value, bool resetValue);

        /**
         * @brief Destructor
         */
        ~Verbose();

    private:
        bool value; ///< The target value of the option when being set

        /**
         * @brief Returns the target value
         * 
         * Needed for undo functionality
         */
        [[nodiscard]] bool getValue() const override;

        /**
         * @brief Sets the option to the specified value \p value
         * 
         * @param[in] value Option will be set to this value
         * 
         * @details This override `UndoableOption`. `UndoableOption`
         * frees us from overriding the original `Option` method `doSet()`
         * and requires us to provide `setTo()` instead. 
         * `UndoableOption` calls `setTo()` parameterized to specify if a command
         * shall be done or undone.
         */
        void setTo(bool value) override;
    };

}

#endif