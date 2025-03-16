#ifndef LIBOTOCURL_OPTION_OPTION_STUB_TEST_HPP
#define LIBOTOCURL_OPTION_OPTION_STUB_TEST_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

namespace otocurl::option::unit_test {

    /**
     * @brief Stub object for a resttable and undoable CURLOPT wrapper
     *  
     * @details
     * Patterns:
     *  - Command
     */
    class OptionStub : public ResettableOption<bool>, public UndoableOptionImpl<bool>  {

    public:
        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] value The target value of the option when being set
         */
        explicit OptionStub(bool value) noexcept;

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] value The target value of the option when being set
         * @param[in] resetValue The reset value of the option when being destructed
         */
        OptionStub(bool value, bool resetValue) noexcept;
        
        /**
         * @brief Destructor
         */
        ~OptionStub();

        /**
         * @brief Returns the simulated actual value
         */
        bool getCURLOPTvalue() const;

    private:
        bool value; ///< The target value of the option when being set

        bool stubbedCURLOPTvalue; ///< Represents the value of a CURLOPT in libcurl for testing

        ///< Stub for curl easys interface, needed by base class
        wrapper::unit_test::EasyStub easyStub; 

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