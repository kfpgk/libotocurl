#ifndef LIBOTOCURL_STORAGE_VISITOR_FLUSH_HPP
#define LIBOTOCURL_STORAGE_VISITOR_FLUSH_HPP

#include <libotocurl/storage/FileStorage.hpp>
#include <libotocurl/storage/MemoryStorage.hpp>

namespace otocurl::storage::visitor {

    /**
     * @brief Callable object to flush a storage.
     * 
     * Patterns:
     *  - Visitor
     */
    class Flush {
            void operator()(FileStorage& storage);
            void operator()(MemoryStorage& storage);
    };

}

#endif