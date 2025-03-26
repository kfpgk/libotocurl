#ifndef LIBOTOCURL_OPTION_QUOTE_HPP
#define LIBOTOCURL_OPTION_QUOTE_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/Easy.hpp>
#include <libotocurl/wrapper/SList.hpp>

#include <curl/curl.h>

#include <functional>
#include <string_view>

namespace otocurl::option {

    namespace unit_test {
        class QuoteTest; ///< Forward declaration for unit test
    }

    /**
     * @brief Wrapper for CURLOPT_QUOTE
     * 
     * This option is both resettable and undoable. A CURLOPT_QUOTE holds a list
     * of protocol specific commands. These commands will be executed upon the next
     * `perform` action, before starting the actual transfer.
     * 
     * @details
     * Patterns:
     *  - Command
     *  - Template
     */
    class Quote : 
        public ResettableOption<wrapper::SList*>, 
        public UndoableOptionImpl<wrapper::SList*> {

    public:
        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] command An initial command added to the option. Additional commands 
         * can be added using the `addCommand()` method.
         */
        explicit Quote(wrapper::Easy& curlInterface, const std::string_view command);

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] command An initial command added to the option. Additional commands
         * can be added using the `addCommand()` method.
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
         * 
         * @parami[in] command The command to be added to the list of commands
         */
        void addCommand(const std::string_view command);

    private:
        /// @brief The CURLOPT identifier
        static constexpr CURLoption curlOption = CURLOPT_QUOTE;

        /// @brief The curl interface for which this option shall be set
        std::reference_wrapper<wrapper::Easy> curlInterface;

        wrapper::SList* commands; ///< Container for commands

        /**
         * @brief Returns the target targetValue
         * 
         * Needed for undo functionality
         * 
         * @return A pointer to a command list data structure
         */
        [[nodiscard]] wrapper::SList* getTargetValue() const override;

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
        void setTo(wrapper::SList* targetValue) override;

        /**
		 * @brief Returns whether the CURLOPT_QUOTE option in the curl interface
         * holds a list or not
         *
		 * @return true if the option holds a list, false otherwise (NULL)
         */
        [[nodiscard]] bool actualOptionHoldsList() const;

        friend class unit_test::QuoteTest; ///< Allow unit test to access private members
    };

}

#endif