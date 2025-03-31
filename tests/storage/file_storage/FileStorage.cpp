#include <tests/storage/file_storage/FileStorage.hpp>
#include <tests/storage/utility/FileOperations.hpp>
#include <libotocurl/storage/FileStorage.hpp>
#include <libotocurl/Exception.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace otocurl::integration_test::storage::file_storage {

    using namespace cpptest::integration_test;

    FileStorage::FileStorage(const std::string& testName) :
        MultiTest(testName),
        inputFile1Name{"file1"},
        inputFile1Content{"file 1 content"},
        inputFile2Name{"file2"},
        inputFile2Content{"file 2 content"} {

        TestCase swapTestCase {
            .name = "Swap two buffers",
            .perform = std::bind(&FileStorage::performSwap, this),
            .evaluate = std::bind(&FileStorage::evaluateSwap, this)
        };
        addTestCase(swapTestCase);

        TestCase copyConstruction {
            .name = "Test copy construction",
            .perform = std::bind(&FileStorage::performCopyConstruction, this),
            .evaluate = std::bind(&FileStorage::evaluateCopyConstruction, this)
        };
        addTestCase(copyConstruction);

        TestCase moveConstruction {
            .name = "Test move construction",
            .perform = std::bind(&FileStorage::performMoveConstruction, this),
            .evaluate = std::bind(&FileStorage::evaluateMoveConstruction, this)
        };
        addTestCase(moveConstruction);

        TestCase copyAssignment {
            .name = "Test copy assignment",
            .perform = std::bind(&FileStorage::performCopyAssignment, this),
            .evaluate = std::bind(&FileStorage::evaluateCopyAssignment, this)
        };
        addTestCase(copyAssignment);

        TestCase moveAssignment {
            .name = "Test move assignment",
            .perform = std::bind(&FileStorage::performMoveAssignment, this),
            .evaluate = std::bind(&FileStorage::evaluateMoveAssignment, this)
        };
        addTestCase(moveAssignment);

    }

    void FileStorage::setup() {
        std::ofstream file1(inputFile1Name);
        file1 << inputFile1Content << std::endl;
        std::ofstream file2(inputFile2Name);
        file2 << inputFile2Content << std::endl;
    }

    void FileStorage::performSwap() {
        otocurl::storage::FileStorage storage1(inputFile1Name);
        otocurl::storage::FileStorage storage2(inputFile2Name);

        using std::swap;
        swap(storage1, storage2);

        resultOfPath1 = storage1.getPath() == inputFile2Name;
        resultOfPath2 = storage2.getPath() == inputFile1Name;
    }

    void FileStorage::evaluateSwap() {
        if (!resultOfPath1 || !resultOfPath2) {
            throw Exception("File paths not as expected after swapping");          
        }     
    }

    void FileStorage::performCopyConstruction() {
        otocurl::storage::FileStorage storage1(inputFile1Name);

        otocurl::storage::FileStorage storage2(storage1);

        std::filesystem::path file1FsPath(inputFile1Name);
        resultOfPath1 = storage1.getPath() == inputFile1Name;
        resultOfPath2 = 
            storage2.getPath() == 
                file1FsPath.stem().string() +
                "_copy" + 
                file1FsPath.extension().string();
        
        using namespace utility::file_operations;
        resultOfIsEqual = areEqual(storage1.getPath(), storage2.getPath());
    }

    void FileStorage::evaluateCopyConstruction() {
        if (!resultOfPath1) {
            throw Exception("File path of constructed from object not as expected.");          
        }     
        if (!resultOfPath2) {
            throw Exception("File path of constructed object not as expected.");          
        }        
        if (!resultOfIsEqual) {
            throw Exception("File contents are not equal after copy construction");          
        }
    }

    void FileStorage::performMoveConstruction() {
        otocurl::storage::FileStorage storage1(inputFile1Name);

        otocurl::storage::FileStorage storage2(std::move(storage1));

        resultOfPath1 = storage1.getPath() == "";
        resultOfPath2 = storage2.getPath() == inputFile1Name;
    }

    void FileStorage::evaluateMoveConstruction() {
        if (!resultOfPath1 || !resultOfPath2) {
            throw Exception("File paths not as expected after move construction");          
        }     
    }

    void FileStorage::performCopyAssignment() {
        otocurl::storage::FileStorage storage1(inputFile1Name);

        otocurl::storage::FileStorage storage2(inputFile2Name);

        storage2 = storage1;

        std::filesystem::path file1FsPath(inputFile1Name);
        resultOfPath1 = storage1.getPath() == inputFile1Name;
        resultOfPath2 = 
            storage2.getPath() == 
                file1FsPath.stem().string() +
                "_copy" + 
                file1FsPath.extension().string();
        
        using namespace utility::file_operations;
        resultOfIsEqual = areEqual(storage1.getPath(), storage2.getPath());
    }

    void FileStorage::evaluateCopyAssignment() {
        if (!resultOfPath1) {
            throw Exception("File path of constructed from object not as expected.");          
        }     
        if (!resultOfPath2) {
            throw Exception("File path of constructed object not as expected.");          
        }         
        if (!resultOfIsEqual) {
            throw Exception("File contents are not equal after copy assignment");          
        }
    }

    void FileStorage::performMoveAssignment() {
        otocurl::storage::FileStorage storage1(inputFile1Name);

        otocurl::storage::FileStorage storage2(inputFile2Name);

        storage2 = std::move(storage1);

        resultOfPath1 = storage1.getPath() == "";
        resultOfPath2 = storage2.getPath() == inputFile1Name;
    }

    void FileStorage::evaluateMoveAssignment() {
        if (!resultOfPath1 || !resultOfPath2) {
            throw Exception("File paths not as expected after move construction");          
        }     
    }

}