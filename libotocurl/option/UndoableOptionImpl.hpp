#ifndef LIBOTOCURL_OPTION_UNDOABLE_OPTION_IMPL_HPP
#define LIBOTOCURL_OPTION_UNDOABLE_OPTION_IMPL_HPP

#include <libotocurl/option/UndoableOption.hpp>

#include <optional>

namespace otocurl::option {

    /**
     * @brief Implementation of a CURLOPT that supports undo functionality
     */
    template<typename T>
    class UndoableOptionImpl : public UndoableOption {

        public:
            /**
             * @brief Default constructor
             */
            UndoableOptionImpl() = default;

            /**
             * @brief Virtual default destructor
             * 
             * Object may be deleted through derived pointer
             */
            virtual ~UndoableOptionImpl() = default;

        private:
            std::optional<T> previous; ///< Holds undo value if available
            
            /**
             * @brief Perform command to set the CURLOPT to the given value and remember
             * previous value to enable undo
             */
            void doSet() final;

            /**
             * @brief Perform the undo operator if previous value is available
             */
            void doUndo() final;

            /**
             * @brief Pure virtual method to get the target value from concrete class
             */
            [[nodiscard]] virtual T getValue() const = 0;

            /**
             * @brief Pure virtual method to set the option to a specific value
             * 
             * @param[in] value Option will be set to this value
             */
            virtual void setTo(T value) = 0;

    };

}

#include <libotocurl/option/UndoableOptionImpl.tpp>

#endif