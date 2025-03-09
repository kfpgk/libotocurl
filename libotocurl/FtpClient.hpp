#ifndef LIBOTOCURL_FTP_CLIENT_HPP
#define LIBOTOCURL_FTP_CLIENT_HPP

#include <libotocurl/ProtocolClient.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <memory>
#include <string>

namespace otocurl {

    /**
     * @brief FTP wrapper for cURL
     */
    class FtpClient : public ProtocolClient {

    public:
        explicit FtpClient(const std::string& serverAddress);
        FtpClient(const std::string& serverAddress,
            std::unique_ptr<wrapper::Easy> curlInterface);

    private:
        void doCreateRemoteDir() override;
        void doDeleteRemoteFile() override;
        void doSetCreateMissingDirs(bool value) override;
        void doDeleteRemoteDir() override;
        bool doRemoteEntryExists() const override;

        void init(const std::string& serverAddress);

    };

}

#endif