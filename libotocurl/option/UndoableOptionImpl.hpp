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
             * @brief Constructor
             * 
             * @param[in] initialValue The initial targetValue used when
             * undoing a command
             */
            UndoableOptionImpl(T initialValue);

            /**
             * @brief Virtual default destructor
             * 
             * Object may be deleted through derived pointer
             */
            virtual ~UndoableOptionImpl() = default;

        private:
            std::optional<T> current; ///< Holds current targetValue which will transition to `previous`
            std::optional<T> previous; ///< Holds undo targetValue if available
            
            /**
             * @brief Perform command to set the CURLOPT to the given targetValue and remember
             * previous targetValue to enable undo
             */
            void doSet() final;

            /**
             * @brief Perform the undo operator if previous targetValue is available
             */
            void doUndo() final;

            /**
             * @brief Pure virtual method to get the target targetValue from concrete class
             */
            [[nodiscard]] virtual T getTargetValue() const = 0;

            /**
             * @brief Pure virtual method to set the option to a specific targetValue
             * 
             * @param[in] targetValue Option will be set to this targetValue
             */
            virtual void setTo(T targetValue) = 0;

    };

}

#include <libotocurl/option/UndoableOptionImpl.tpp>

#endif