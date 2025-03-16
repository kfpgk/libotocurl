add_library(libotocurl 
    Exception.cpp
    ProtocolClient.cpp
    FtpClient.cpp
)

set_target_properties(libotocurl PROPERTIES PREFIX "")

find_package(curl
    REQUIRED
)

find_path(LIBCURL_INCLUDE_DIR
    "curl/curl.h"
    REQUIRED
)

find_package(LIBCPPLOG
    NAMES
        cpplog
        libcpplog
    REQUIRED
)

find_package(LIBCPPTEST
    NAMES
        cpptest
        libcpptest
    REQUIRED
)

target_include_directories(libotocurl
    PUBLIC
        ${LIBCPPLOG_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${LIBCURL_INCLUDE_DIR}
        ${LIBCPPTEST_INCLUDE_DIR}
)

target_link_libraries(libotocurl
    PUBLIC
        ${LIBCPPLOG}
    PRIVATE
        ${LIBCPPTEST}
        CURL::libcurl
)

add_subdirectory(option)
add_subdirectory(parser)
add_subdirectory(storage)
add_subdirectory(wrapper)

if(BUILD_UNIT_TESTS)
    enable_testing()

    add_executable(ProtocolClient_test
        wrapper/EasyStub.test.cpp
        parser/NobodyStub.test.cpp
        ProtocolClient.test.cpp
    )
    target_include_directories(ProtocolClient_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(ProtocolClient_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT ProtocolClient"
        COMMAND ProtocolClient_test
    )
endif()