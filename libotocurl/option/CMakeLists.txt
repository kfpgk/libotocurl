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

    add_executable(OptionNobody_test
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

endif()