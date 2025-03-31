#include <tests/ftp/GetFileSize.hpp>
#include <libotocurl/FtpClient.hpp>
#include <libotocurl/Exception.hpp>

#include <libcpptest/integration_test/SingleTest.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace otocurl::integration_test::ftp {

    using namespace cpptest::integration_test;

    GetFileSize::GetFileSize(const std::string& testName,
        const std::string& server,
        const std::string& pathOnServer) :
            SingleTest(testName),
            server{server},
            pathOnServer{pathOnServer},
            file1Name{"file1"},
            file1RemotePath{
                (std::filesystem::path(pathOnServer) / file1Name).string() },
            file1Content{"file1 content"},
            binaryFile1Name{"file1.bin"},
            binaryFile1RemotePath{
                (std::filesystem::path(pathOnServer) / binaryFile1Name).string() },
            binaryFile1Content{42} {

    }

    void GetFileSize::setup() {
        std::ofstream localFile(file1Name);
        if (!localFile.is_open()) {
            throw Exception("Cannot open local file for writing.");
        }
        localFile << file1Content << std::endl;
        localFile.close();

        std::ofstream binFile(binaryFile1Name, std::ios::binary | std::ios::out);
        binFile.write(reinterpret_cast<char*>(&binaryFile1Content), sizeof(int));

        std::filesystem::resize_file(file1Name, file1Size);
        std::filesystem::resize_file(binaryFile1Name, binaryFile1Size);

        otocurl::FtpClient client(server);

        client.setRemoteFile(file1RemotePath);
        client.setLocalFileForUpload(file1Name);
        client.upload();   

        client.setRemoteFile(binaryFile1RemotePath);
        client.setLocalFileForUpload(binaryFile1Name);
        client.upload();         
    }

    void GetFileSize::perform() {

        otocurl::FtpClient client(server);

        client.setRemoteFile(file1RemotePath);
        file1RetrievedSize = client.getRemoteFileSize();

        client.setRemoteFile(binaryFile1RemotePath);
        binaryFile1RetrievedSize = client.getRemoteFileSize();

    }

    void GetFileSize::evaluate() {
        if (file1RetrievedSize != file1Size) {
            throw Exception("Retrieved text file size did not match.");
        }
        if (binaryFile1RetrievedSize != binaryFile1Size) {
            throw Exception("Retrieved binary file size did not match.");
        }
    }

    void GetFileSize::cleanUp() {
        otocurl::FtpClient client(server);

        client.setRemoteFile(file1RemotePath);
        client.deleteRemoteFile();

        client.setRemoteFile(binaryFile1RemotePath);
        client.deleteRemoteFile();   
    }

}