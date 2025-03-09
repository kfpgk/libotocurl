#include <libotocurl/storage/visitor/Flush.hpp>

namespace otocurl::storage::visitor {

    void Flush::operator()(FileStorage& storage) {
        storage.flush();
    }

    void Flush::operator()(MemoryStorage& storage) {
        storage.flush();
    }

}