enable_testing()

add_executable(test_curl_file_storage
    file_storage.cpp
    FileStorage.cpp
    ../utility/FileOperations.cpp
)
target_include_directories(test_curl_file_storage
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${LIBCURL_INCLUDE_DIR}
        ${libcpptest_INCLUDE_DIR}
)
target_link_libraries(test_curl_file_storage
    PRIVATE
        libotocurl
        CPPTEST::libcpptest
)
add_test(
    NAME "IT CURL File Storage Basic Object operations"
    COMMAND test_curl_file_storage
)