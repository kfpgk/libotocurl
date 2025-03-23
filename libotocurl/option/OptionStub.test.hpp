#ifndef LIBOTOCURL_OPTION_OPTION_STUB_TEST_HPP
#define LIBOTOCURL_OPTION_OPTION_STUB_TEST_HPP

#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>
#include <libotocurl/wrapper/EasyStub.test.hpp>

namespace otocurl::option::unit_test {

    /**
     * @brief Stub object for a resettable and undoable CURLOPT wrapper
     *  
     * @details
     * Patterns:
     *  - Command
     */
	template<typename T>
    class OptionStub : public ResettableOption<T>, public UndoableOptionImpl<T>  {

    public:
        /**
         * @brief Constructs a persistent option, which is not being reset upon object 
         * destruction.
         * 
         * @param[in] targetValue The target targetValue of the option when being set
         * @param[in] initialValue The simulated initial default value of the CURLOPT
         * in the curl interface
         */
        OptionStub(T targetValue, T initialValue) noexcept;

        /**
         * @brief Constructs a volatile option, which is being reset to \p resetValue upon
         * object destruction.
         * 
         * @param[in] targetValue The target value of the option when being set
         * @param[in] initialValue The simulated initial default value of the CURLOPT 
         * in the curl interface 
         * @param[in] resetValue The reset value of the option when being destructed
         */
        OptionStub(T targetValue, T initialValue, T resetValue) noexcept;
        
        /**
         * @brief Destructor
         */
        ~OptionStub();

        /**
         * @brief Stup method to return a simulated libcurl CURLOPT value
         *
         * @return The value of the option
         */
        [[nodiscard]] T getActualValue() const;

    private:
        T targetValue; ///< The target value of the option when being set

        T stubbedCURLOPTvalue; ///< Represents the targetValue of a CURLOPT in libcurl for testing

        /// @brief Stub for curl easys interface, needed by base class
        wrapper::unit_test::EasyStub easyStub; 

        /**
         * @brief Returns the target targetValue
         * 
         * Needed for undo functionality
         */
        [[nodiscard]] T getTargetValue() const override;

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
        void setTo(T targetValue) override;

    };

}

#include <libotocurl/option/OptionStub.test.tpp>

#endif