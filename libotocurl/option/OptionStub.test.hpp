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
         * @param[in] targetValue The target targetValue of the option when being set
         */
        explicit OptionStub(bool targetValue) noexcept;

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] targetValue The target targetValue of the option when being set
         * @param[in] resetValue The reset targetValue of the option when being destructed
         */
        OptionStub(bool targetValue, bool resetValue) noexcept;
        
        /**
         * @brief Destructor
         */
        ~OptionStub();

        /**
         * @brief Returns the simulated actual targetValue
         */
        bool getCURLOPTvalue() const;

    private:
        bool targetValue; ///< The target targetValue of the option when being set

        bool stubbedCURLOPTvalue; ///< Represents the targetValue of a CURLOPT in libcurl for testing

        /// @brief Stub for curl easys interface, needed by base class
        wrapper::unit_test::EasyStub easyStub; 

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