#ifndef LIBOTOCURL_STORAGE_VISITOR_GET_REFERENCE_HPP
#define LIBOTOCURL_STORAGE_VISITOR_GET_REFERENCE_HPP

#include <libotocurl/storage/Storage.hpp>
#include <libotocurl/storage/FileStorage.hpp>
#include <libotocurl/storage/MemoryStorage.hpp>

namespace otocurl::storage::visitor {

    /**
     * @brief Callable object to get reference to a storage's
     * data.
     * 
     * Patterns:
     *  - Visitor
     */
    class GetReference {

        public:
            [[nodiscard]] DataReference operator()(const FileStorage& storage);
            [[nodiscard]] DataReference operator()(MemoryStorage& storage);
    };

}

#endif