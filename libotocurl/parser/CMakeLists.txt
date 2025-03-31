target_sources(libotocurl
    PRIVATE
        Nobody.cpp
        FtpNobody.cpp
        Parser.cpp
        StringOperations.cpp
)

if(BUILD_UNIT_TESTS)
    enable_testing()

    add_executable(ParserStringOperations_test
        StringOperations.test.cpp
    )
    target_include_directories(ParserStringOperations_test
        PRIVATE
            "${CMAKE_SOURCE_DIR}"
            "${libcpplog_INCLUDE_DIR}"
            "${libcurl_INCLUDE_DIR}"
    )
    target_link_libraries(ParserStringOperations_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT parser::string_operations"
        COMMAND ParserStringOperations_test
    )

endif()