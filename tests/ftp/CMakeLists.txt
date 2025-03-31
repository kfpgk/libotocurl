enable_testing()

add_executable(test_curl_ftp_upload_download
    upload_download.cpp
    UploadDownload.cpp
)
target_include_directories(test_curl_ftp_upload_download
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${LIBCURL_INCLUDE_DIR}
        ${libcpptest_INCLUDE_DIR}
)
target_link_libraries(test_curl_ftp_upload_download
    PRIVATE 
        libotocurl
        CPPTEST::libcpptest
)
add_test(
    NAME "IT CURL FTP Upload and Download"
    COMMAND test_curl_ftp_upload_download
)

add_executable(test_curl_ftp_get_file_size
    get_file_size.cpp
    GetFileSize.cpp
)
target_include_directories(test_curl_ftp_get_file_size
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${LIBCURL_INCLUDE_DIR}
        ${LIBCPPTEST_INCLUDE_DIR}
)
target_link_libraries(test_curl_ftp_get_file_size
    PRIVATE 
        libotocurl
        CPPTEST::libcpptest
)
add_test(
    NAME "IT CURL FTP Get Remote File Size"
    COMMAND test_curl_ftp_get_file_size
)