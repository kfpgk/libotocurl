#include <libotocurl/storage/MemoryStorageHandle.hpp>
#include <libotocurl/Exception.hpp>

namespace otocurl::storage {

    std::span<char> MemoryStorageHandle::data() {
        return storage->getDataReference();
    }

    MemoryStorageHandle::MemoryStorageHandle(
        [[maybe_unused]] ConstructorPermission permission,
        std::unique_ptr<MemoryStorage> storage) :
            storage{std::move(storage)} {

    }

    MemoryStorageHandle::MemoryStorageHandle(const MemoryStorageHandle& rhs) {
        storage = std::make_unique<MemoryStorage>(*rhs.storage);
    }

    MemoryStorageHandle::MemoryStorageHandle(MemoryStorageHandle&& rhs) {
        using std::swap;
        swap(*this, rhs);
    }

    MemoryStorageHandle& MemoryStorageHandle::operator=(MemoryStorageHandle rhs) {
        using std::swap;
        swap(*this, rhs);
        return *this;
    }

    void swap(MemoryStorageHandle& lhs, MemoryStorageHandle& rhs) {
        using std::swap;
        swap(lhs.storage, rhs.storage);
    }

    std::unique_ptr<MemoryStorage> MemoryStorageHandle::extract() {
        if (!storage) {
            throw Exception("Trying to extract empty handle");
        }
        return std::move(storage);
    }

}