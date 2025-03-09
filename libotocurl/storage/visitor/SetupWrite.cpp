#include <libotocurl/storage/visitor/SetupWrite.hpp>

namespace otocurl::storage::visitor {

    SetupWrite::SetupWrite(const option::Factory& optionFactory) :
        optionFactory{optionFactory} {

    }

    void SetupWrite::operator()(FileStorage& storage) {
        storage.setupWrite(optionFactory);
    }

    void SetupWrite::operator()(MemoryStorage& storage) {
        storage.setupWrite(optionFactory);
    }

}