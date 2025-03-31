enable_testing()

add_executable(test_curl_memory_storage
    memory_storage.cpp
    MemoryStorage.cpp
    ../utility/FileOperations.cpp
)
target_include_directories(test_curl_memory_storage
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${LIBCURL_INCLUDE_DIR}
        ${libcpptest_INCLUDE_DIR}
)
target_link_libraries(test_curl_memory_storage
    PRIVATE
        libotocurl
        CPPTEST::libcpptest
)
add_test(
    NAME "IT CURL Download and Upload to Memory storage"
    COMMAND test_curl_memory_storage
)