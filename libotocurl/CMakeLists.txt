add_library(libotocurl 
    Exception.cpp
    ProtocolClient.cpp
    FtpClient.cpp
)

set_target_properties(libotocurl PROPERTIES PREFIX "")

find_package(curl
    REQUIRED
)

find_path(CURL_INCLUDE_DIR
    "curl/curl.h"
    REQUIRED
)

target_include_directories(libotocurl
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CURL_INCLUDE_DIR}
)

target_link_libraries(libotocurl 
    PRIVATE
        CURL::libcurl
    REQUIRED
)

add_subdirectory(option)
add_subdirectory(parser)
add_subdirectory(storage)
add_subdirectory(wrapper)

if(BUILD_UNIT_TESTS)
    enable_testing()
    add_executable(CurlProtocolClient_test
        wrapper/EasyStub.test.cpp
        parser/NobodyStub.test.cpp
        ProtocolClient.test.cpp
    )
    target_include_directories(CurlProtocolClient_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_BINARY_DIR}
    )
    target_link_libraries(CurlProtocolClient_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT curl::ProtocolClient"
        COMMAND CurlProtocolClient_test
    )
endif()