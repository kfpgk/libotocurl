#include <libotocurl/storage/visitor/GetReference.hpp>

namespace otocurl::storage::visitor {

    DataReference GetReference::operator()(const FileStorage& storage) {
        return storage.getPath();
    }

    DataReference GetReference::operator()(MemoryStorage& storage) {
        return storage.getDataReference();
    }

}