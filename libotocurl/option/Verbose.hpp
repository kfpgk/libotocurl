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
        bool targetValue; ///< The target targetValue of the option when being set

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
    };

}

#endif