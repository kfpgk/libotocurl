#ifndef LIBOTOCURL_STORAGE_VISITOR_SETUP_READ_HPP
#define LIBOTOCURL_STORAGE_VISITOR_SETUP_READ_HPP

#include <libotocurl/storage/FileStorage.hpp>
#include <libotocurl/storage/MemoryStorage.hpp>

#include <libotocurl/option/Factory.hpp>

namespace otocurl::storage::visitor {

    /**
     * @brief Callable object to setup a read operation
     * to a storage.
     * 
     * Patterns:
     *  - Visitor
     */
    class SetupRead {

    public:
        explicit SetupRead(const option::Factory& optionFactory);

        void operator()(FileStorage& storage);
        void operator()(MemoryStorage& storage);

    private:
        const option::Factory& optionFactory;

    };

}

#endif