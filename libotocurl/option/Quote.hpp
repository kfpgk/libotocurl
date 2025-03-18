#ifndef LIBOTOCURL_OPTION_QUOTE_HPP
#define LIBOTOCURL_OPTION_QUOTE_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/Easy.hpp>
#include <libotocurl/wrapper/SList.hpp>

#include <string_view>

namespace otocurl::option {

    /**
     * @brief Wrapper for CURLOPT_QUOTE
     * 
     * This option is both resettable and undoable.
     * 
     * @details
     * Patterns:
     *  - Command
     */
    class Quote : public ResettableOption<wrapper::SList*>, public UndoableOptionImpl<wrapper::SList*> {

    public:
        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] targetValue The target value of the option when being set
         */
        explicit Quote(wrapper::Easy& curlInterface, const std::string_view command);

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] targetValue The target value of the option when being set
         * @param[in] resetValue The reset value of the option when being destructed
         */
        Quote(wrapper::Easy& curlInterface,
            const std::string_view command,
            wrapper::SList* resetValue);
            
        /**
         * @brief Destructor
         */
        ~Quote();

        /**
         * @brief Add a command to the CURLOPT_QUOTE option
         */
        void addCommand(const std::string_view command);

    private:
        wrapper::SList* commands; ///< Container for commands

        /**
         * @brief Returns the target targetValue
         * 
         * Needed for undo functionality
         */
        [[nodiscard]] wrapper::SList* getTargetValue() const override;

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
        void setTo(wrapper::SList* targetValue) override;

    };

}

#endif