target_sources(libotocurl 
    PRIVATE
        Option.cpp
        UndoableOption.cpp
        Invoker.cpp
        Collection.cpp
        Factory.cpp
        Nobody.cpp
        Quote.cpp
        Upload.cpp
        Verbose.cpp
)

if(BUILD_UNIT_TESTS)
    enable_testing()

    add_executable(OptionCollection_test
        ../wrapper/EasyStub.test.cpp
        Collection.test.cpp
    )
    target_include_directories(OptionCollection_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(OptionCollection_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT option::Collection"
        COMMAND OptionCollection_test
    )

    add_executable(OptionInvoker_test
        ../wrapper/EasyStub.test.cpp
        Invoker.test.cpp
    )
    target_include_directories(OptionInvoker_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(OptionInvoker_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT option::Invoker"
        COMMAND OptionInvoker_test
    )

    add_executable(OptionNobody_test
        ../wrapper/EasyStub.test.cpp
        Nobody.test.cpp
    )
    target_include_directories(OptionNobody_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(OptionNobody_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT option::Nobody"
        COMMAND OptionNobody_test
    )

    add_executable(OptionQuote_test
        ../wrapper/EasyStub.test.cpp
        Quote.test.cpp
    )
    target_include_directories(OptionQuote_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(OptionQuote_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT option::Quote"
        COMMAND OptionQuote_test
    )

    add_executable(OptionUpload_test
        ../wrapper/EasyStub.test.cpp
        Upload.test.cpp
    )
    target_include_directories(OptionUpload_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(OptionUpload_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT option::Upload"
        COMMAND OptionUpload_test
    )

    add_executable(OptionVerbose_test
        ../wrapper/EasyStub.test.cpp
        Verbose.test.cpp
    )
    target_include_directories(OptionVerbose_test
        PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${LIBCURL_INCLUDE_DIR}
    )
    target_link_libraries(OptionVerbose_test
        PRIVATE
            libotocurl
    )
    add_test(
        NAME "UT option::Verbose"
        COMMAND OptionVerbose_test
    )

endif()