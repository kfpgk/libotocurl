#ifndef LIBOTOCURL_STORAGE_STORAGE_HPP
#define LIBOTOCURL_STORAGE_STORAGE_HPP

#include <libotocurl/storage/FileStorage.hpp>
#include <libotocurl/storage/MemoryStorage.hpp>

#include <filesystem>
#include <span>
#include <variant>

namespace otocurl::storage {

    using Storage = std::variant<FileStorage, MemoryStorage>;

    using DataReference = std::variant<std::filesystem::path, std::span<char>>;

}

#endif