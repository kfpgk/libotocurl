#include <libotocurl/storage/visitor/SetupRead.hpp>

namespace otocurl::storage::visitor {

    SetupRead::SetupRead(const option::Factory& optionFactory) :
        optionFactory{optionFactory} {

    }

    void SetupRead::operator()(FileStorage& storage) {
        storage.setupRead(optionFactory);
    }

    void SetupRead::operator()(MemoryStorage& storage) {
        storage.setupRead(optionFactory);
    }

}