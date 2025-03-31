#ifndef LIBOTOCURL_TESTS_CURL_STORAGE_FILE_STORAGE_FILE_STORAGE_HPP
#define LIBOTOCURL_TESTS_CURL_STORAGE_FILE_STORAGE_FILE_STORAGE_HPP

#include <libcpptest/integration_test/MultiTest.hpp>

#include <string>

namespace otocurl::integration_test::storage::file_storage {

    class FileStorage : public cpptest::integration_test::MultiTest {

    public:
        FileStorage(const std::string& name);

    private:
        const std::string inputFile1Name;
        const std::string inputFile1Content;
        const std::string inputFile2Name;
        const std::string inputFile2Content;
        bool result;
        bool resultOfPath1;
        bool resultOfPath2;
        bool resultOfIsEmpty;
        bool resultOfIsEqual;

        void setup() override;

        /**
            * @brief Test swap
            */
        void performSwap();
        void evaluateSwap();

        /**
            * @brief Test copy construction
            */
        void performCopyConstruction();
        void evaluateCopyConstruction();

        /**
            * @brief Test move construction
            */
        void performMoveConstruction();
        void evaluateMoveConstruction();

        /**
            * @brief Test copy assignment
            */
        void performCopyAssignment();
        void evaluateCopyAssignment();

        /**
            * @brief Test move assignment
            */
        void performMoveAssignment();
        void evaluateMoveAssignment();
    };

}

#endif