#include <tests/ftp/UploadDownload.hpp>
#include <libotocurl/FtpClient.hpp>
#include <libotocurl/Exception.hpp>

#include <libcpptest/integration_test/MultiTest.hpp>

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

namespace otocurl::integration_test::ftp {

    using namespace cpptest::integration_test;

    UploadDownload::UploadDownload(const std::string& testName,
        const std::string& server,
        const std::string& pathOnServer) :
            MultiTest(testName),
            server{server},
            pathOnServer{pathOnServer},
            file1Name{"file1"},
            file1RemotePath{ 
                (std::filesystem::path(pathOnServer) / file1Name).string() },
            file1Content{"file1 content"},
            file2Name{"file2"},
            file2RemotePath{
                (std::filesystem::path(pathOnServer) / file2Name).string() },
            file2Content{"file2 content"},
            binaryFile1Name{"file1.bin"},
            binaryFile1RemotePath{
                (std::filesystem::path(pathOnServer) / binaryFile1Name).string() },
            binaryFile1Content{42},
            binaryFile2Name{"file2.bin"} {

        TestCase uploadUninitialized {
            .name = "Upload without defining local and remote paths",
            .perform = std::bind(&UploadDownload::performUploadUninitialized, this),
            .evaluate = std::bind(&UploadDownload::evaluateUploadUninitialized, this)
        };
        addTestCase(uploadUninitialized);

        TestCase uploadInitNonExistingLocal {
            .name = "Upload with local file not existing during initialization",
            .perform = std::bind(&UploadDownload::performUploadInitNonExistingLocal, this),
            .evaluate = std::bind(&UploadDownload::evaluateUploadInitNonExistingLocal, this)
        };
        addTestCase(uploadInitNonExistingLocal);

        TestCase uploadNonExistingLocal {
            .name = "Upload non existing local file",
            .perform = std::bind(&UploadDownload::performUploadNonExistingLocal, this),
            .evaluate = std::bind(&UploadDownload::evaluateUploadNonExistingLocal, this)
        };
        addTestCase(uploadNonExistingLocal);

        TestCase uploadInitializedForDownload {
            .name = "Upload local file initialized for download",
            .perform = std::bind(&UploadDownload::performUploadInitializedForDownload, this),
            .evaluate = std::bind(&UploadDownload::evaluateUploadInitializedForDownload, this)
        };
        addTestCase(uploadInitializedForDownload);

        TestCase downloadUninitialized {
            .name = "Download without defining local and remote paths",
            .perform = std::bind(&UploadDownload::performDownloadUninitialized, this),
            .evaluate = std::bind(&UploadDownload::evaluateDownloadUninitialized, this)
        };
        addTestCase(downloadUninitialized);

        TestCase downloadNonExistingRemote {
            .name = "Download non existing remote file",
            .perform = std::bind(&UploadDownload::performDownloadNonExistingRemote, this),
            .evaluate = std::bind(&UploadDownload::evaluateDownloadNonExistingRemote, this)
        };
        addTestCase(downloadNonExistingRemote);

        TestCase downloadUndefinedRemote {
            .name = "Download with undefined remote path",
            .perform = std::bind(&UploadDownload::performDownloadUndefinedRemote, this),
            .evaluate = std::bind(&UploadDownload::evaluateDownloadUndefinedRemote, this)
        };
        addTestCase(downloadUndefinedRemote);

        TestCase downloadInitializedForUpload {
            .name = "Download local file initialized for upload",
            .perform = std::bind(&UploadDownload::performDownloadInitializedForUpload, this),
            .evaluate = std::bind(&UploadDownload::evaluateDownloadInitializedForUpload, this)
        };
        addTestCase(downloadInitializedForUpload);

        TestCase upload {
            .name = "upload to server",
            .perform = std::bind(&UploadDownload::performUpload, this),
            .evaluate = std::bind(&UploadDownload::evaluateUpload, this)
        };
        addTestCase(upload);

        TestCase download {
            .name = "download from server",
            .perform = std::bind(&UploadDownload::performDownload, this),
            .evaluate = std::bind(&UploadDownload::evaluateDownload, this)
        };
        addTestCase(download);

        TestCase uploadBinaryFile {
            .name = "upload binary file to server",
            .perform = std::bind(&UploadDownload::performUploadBinaryFile, this),
            .evaluate = std::bind(&UploadDownload::evaluateUploadBinaryFile, this)
        };
        addTestCase(uploadBinaryFile);

        TestCase downloadBinaryFile {
            .name = "download binary file from server",
            .perform = std::bind(&UploadDownload::performDownloadBinaryFile, this),
            .evaluate = std::bind(&UploadDownload::evaluateDownloadBinaryFile, this)
        };
        addTestCase(downloadBinaryFile);

    }

    void UploadDownload::setup() {
        std::ofstream localFile(file1Name);
        if (!localFile.is_open()) {
            throw Exception("Cannot open local file for writing.");
        }
        localFile << file1Content << std::endl;
        localFile.close();

        std::ofstream binFile(binaryFile1Name, std::ios::binary | std::ios::out);
        binFile.write(reinterpret_cast<char*>(&binaryFile1Content), sizeof(int));
    }

    void UploadDownload::performUploadUninitialized() {
        otocurl::FtpClient client(server);

        exceptionThrown = false;
        try {
            client.upload();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
    }

    void UploadDownload::evaluateUploadUninitialized() {
        if (!exceptionThrown) {
            throw Exception("Uninitialized upload() unexpectedly did not throw exception.");
        }          
    }

    void UploadDownload::performUploadInitNonExistingLocal() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file2RemotePath);
       
        exceptionThrown = false;
        try {
            client.setLocalFileForUpload(file2Name);
            client.upload();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
        
    }

    void UploadDownload::evaluateUploadInitNonExistingLocal() {
        if (!exceptionThrown) {
            throw Exception("upload() with non existing local file during "\
                "initialization unexpectedly did not throw exception.");
        }          
    }

    void UploadDownload::performUploadNonExistingLocal() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file2RemotePath);
        std::ofstream localFile(file2Name);
        localFile.close();
        client.setLocalFileForUpload(file2Name);
        std::remove(file2Name.c_str());
       
        client.upload();
        
    }

    void UploadDownload::evaluateUploadNonExistingLocal() {
        otocurl::FtpClient client(server);
        client.setRemoteFile(file2RemotePath);
        if (!client.remoteEntryExists()) {
            throw Exception("upload() with non existing local file during "\
                "upload did not upload empty file as expected.");
        }
        client.deleteRemoteFile();          
    }

    void UploadDownload::performUploadInitializedForDownload() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file2RemotePath);
        client.createLocalFileForDownload(file2Name);

        try {
            client.upload();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
    }

    void UploadDownload::evaluateUploadInitializedForDownload() {
        if (!exceptionThrown) {
            throw Exception("upload() with local file path initialized " \
            "for download unexpectedly did not throw exception.");
        }        
    }

    void UploadDownload::performDownloadUninitialized() {
        otocurl::FtpClient client(server);

        exceptionThrown = false;
        try {
            client.download();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
    }

    void UploadDownload::evaluateDownloadUninitialized() {
        if (!exceptionThrown) {
            throw Exception("download() with uninitialized local and remote paths" \
            "unexpectedly did not throw exception.");
        }            
    }

    void UploadDownload::performDownloadNonExistingRemote() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file2RemotePath);
        client.createLocalFileForDownload(file2Name);
        
        exceptionThrown = false;
        try {
            client.download();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
        
    }

    void UploadDownload::evaluateDownloadNonExistingRemote() {
        if (!exceptionThrown) {
            throw Exception("download() non existing remote file unexpectedly "\
                "did not throw exception.");
        }          
    }

    void UploadDownload::performDownloadUndefinedRemote() {
        otocurl::FtpClient client(server);

        client.createLocalFileForDownload(file2Name);

        exceptionThrown = false;
        try {
            client.download();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
        
    }

    void UploadDownload::evaluateDownloadUndefinedRemote() {
        std::remove("localfile"); 
        if (!exceptionThrown) {
            throw Exception("download() with undefined remote path" \
                "unexpectedly did not throw exception.");
        }     
    }

    void UploadDownload::performDownloadInitializedForUpload() {
        otocurl::FtpClient client(server);

        std::ofstream localFile(file2Name);
        client.setLocalFileForUpload(file2Name);
        localFile.close();
        std::remove(file2Name.c_str());

        exceptionThrown = false;
        try {
            client.download();
        } catch (const std::exception& e) {
            exceptionThrown = true;
        }
    }

    void UploadDownload::evaluateDownloadInitializedForUpload() {
        if (!exceptionThrown) {
            throw Exception("download() with local path initialized for " \
                "upload unexpectedly did not throw exception.");
        }         
    }

    void UploadDownload::performUpload() {
        otocurl::FtpClient client(server);

        client.setLocalFileForUpload(file1Name);
        client.setRemoteFile(file1RemotePath);
        client.upload();
    }

    void UploadDownload::evaluateUpload() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file1RemotePath);
        if (!client.remoteEntryExists()) {
            throw Exception("File not found on server after upload");
        }
        client.deleteRemoteFile();
    }

    void UploadDownload::performDownload() {
        
        auto localSetup = [this]() {
            otocurl::FtpClient client(server);
            client.setLocalFileForUpload(file1Name);
            client.setRemoteFile(file1RemotePath);
            client.upload();
        };

        localSetup();

        otocurl::FtpClient client(server);
        client.createLocalFileForDownload(file2Name);
        client.setRemoteFile(file1RemotePath);
        client.download();

    }

    void UploadDownload::evaluateDownload() {
        std::ifstream localFile(file2Name);
        if (!localFile.is_open()) {
            throw Exception("Could not open file for reading");
        }
        std::string line;
        std::getline(localFile, line);
        if (line != file1Content) {
            throw Exception("Content of downloaded file did not meet expectation");
        }
    }

    void UploadDownload::performUploadBinaryFile() {

        otocurl::FtpClient client(server);

        client.setLocalFileForUpload(binaryFile1Name);
        client.setRemoteFile(binaryFile1RemotePath);
        client.upload();

    }

    void UploadDownload::evaluateUploadBinaryFile() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(binaryFile1RemotePath);
        if (!client.remoteEntryExists()) {
            throw Exception("File not found on server after upload");
        }
        client.deleteRemoteFile();
    }

    void UploadDownload::performDownloadBinaryFile() {

        auto localSetup = [this]() {
            otocurl::FtpClient client(server);
            client.setLocalFileForUpload(binaryFile1Name);
            client.setRemoteFile(binaryFile1RemotePath);
            client.upload();
        };

        localSetup();

        otocurl::FtpClient client(server);
        client.createLocalFileForDownload(binaryFile2Name);
        client.setRemoteFile(binaryFile1RemotePath);
        client.download();
    }

    void UploadDownload::evaluateDownloadBinaryFile() {
        std::ifstream binFile(binaryFile2Name, std::ios::out | std::ios::binary);
        int content;
        binFile.read(reinterpret_cast<char*>(&content), sizeof(int));

        if (content != binaryFile1Content) {
            throw Exception("Content of downloaded binary file is not as expected");            
        }
    }

    void UploadDownload::cleanUp() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file1RemotePath);
        client.deleteRemoteFile();     
    }

}