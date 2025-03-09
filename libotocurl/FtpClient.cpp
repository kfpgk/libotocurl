#include <libotocurl/FtpClient.hpp>
#include <libotocurl/Exception.hpp>
#include <libotocurl/wrapper/Url.hpp>
#include <libotocurl/option/Factory.hpp>
#include <libotocurl/option/Generic.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/Collection.hpp>
#include <libotocurl/parser/FtpNobody.hpp>
#include <libotocurl/utility/Debug.hpp>

#define FILESYNC_CURL_URL_FTP_PREFIX "ftp"

namespace otocurl {

    FtpClient::FtpClient(const std::string& serverAddress,
        std::unique_ptr<wrapper::Easy> curlInterface) :
            ProtocolClient(
                std::move(curlInterface),
                std::make_unique<parser::FtpNobody>()) {
    
        init(serverAddress);
    }

    FtpClient::FtpClient(const std::string& serverAddress) :
        ProtocolClient(std::make_unique<parser::FtpNobody>()) {
            
        init(serverAddress);
    }

    void FtpClient::init(const std::string& serverAddress) {
        LIBFILESYNC_CURL_UTILITY_DEBUG_ENTER();
        try {

            std::unique_ptr<option::Collection> options = optionFactory.createCollection();

            options->add(optionFactory.createGeneric(CURLOPT_FTP_SKIP_PASV_IP, 1L));

            activeUrl.setHost(serverAddress);
            activeUrl.setScheme(FILESYNC_CURL_URL_FTP_PREFIX);
            activeUrl.validate();        
            options->add(optionFactory.createGeneric(CURLOPT_URL, activeUrl.getUrl()));
            
            options->add(optionFactory.createGeneric(CURLOPT_WRITEDATA, nullptr));

            options->set();
            curlInterface->perform();

            LIBFILESYNC_CURL_UTILITY_DEBUG("Successfully connected to '" << activeUrl.getUrl() << "'");

        } catch(Exception& e) {
            //e.addContext(__FILE__, __LINE__);
            throw e;
        }
        LIBFILESYNC_CURL_UTILITY_DEBUG_EXIT();   
    }

    void FtpClient::doDeleteRemoteFile() {
        LIBFILESYNC_CURL_UTILITY_DEBUG_ENTER(); 
        try {
            std::unique_ptr<option::Collection> options = optionFactory.createCollection();
            
            std::unique_ptr<option::Quote> volatileQuote = 
                optionFactory.createVolatileQuote();
            volatileQuote->addCommand("CWD /");
            volatileQuote->addCommand("DELE " + getRemoteFilePath());
            options->add(std::move(volatileQuote));

            wrapper::Url url;
            url.setHost(activeUrl.getHost());
            url.setScheme(activeUrl.getScheme());            
            options->add(optionFactory.createGeneric(CURLOPT_URL, url.getUrl()));

            options->add(optionFactory.createGeneric(CURLOPT_WRITEDATA, nullptr));

            options->set();
            curlInterface->perform();
        } catch(Exception& e) {
            //e.addContext(__FILE__, __LINE__);
            throw e;
        }        
        LIBFILESYNC_CURL_UTILITY_DEBUG_EXIT();       
    }

    void FtpClient::doSetCreateMissingDirs(bool value) {
        std::unique_ptr<option::Option> option;
        if (value) {
            option = optionFactory.createGeneric(CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);
        } else {
            option = optionFactory.createGeneric(CURLOPT_FTP_CREATE_MISSING_DIRS, 0L);
        }
        option->set();
    }

    void FtpClient::doCreateRemoteDir() {
        LIBFILESYNC_CURL_UTILITY_DEBUG_ENTER();
        try {
            std::unique_ptr<option::Collection> options = optionFactory.createCollection();
            
            std::unique_ptr<option::Quote> volatileQuote = 
                optionFactory.createVolatileQuote();
            volatileQuote->addCommand("CWD /");
            volatileQuote->addCommand("MKD " + getRemoteDirPath());
            options->add(std::move(volatileQuote));

            wrapper::Url url;
            url.setHost(activeUrl.getHost());
            url.setScheme(activeUrl.getScheme());      
            options->add(optionFactory.createGeneric(CURLOPT_URL, url.getUrl()));

            options->add(optionFactory.createGeneric(CURLOPT_WRITEDATA, nullptr));

            options->set();
            curlInterface->perform();
        } catch(Exception& e) {
            //e.addContext(__FILE__, __LINE__);
            throw e;
        }
        LIBFILESYNC_CURL_UTILITY_DEBUG_EXIT();            
    }

    void FtpClient::doDeleteRemoteDir() {
        LIBFILESYNC_CURL_UTILITY_DEBUG_ENTER();
        try {
            std::unique_ptr<option::Collection> options = optionFactory.createCollection();
            
            std::unique_ptr<option::Quote> volatileQuote = 
                optionFactory.createVolatileQuote();
            volatileQuote->addCommand("CWD /");
            volatileQuote->addCommand("RMD " + getRemoteDirPath());
            options->add(std::move(volatileQuote));

            wrapper::Url url;
            url.setHost(activeUrl.getHost());
            url.setScheme(activeUrl.getScheme());            
            options->add(optionFactory.createGeneric(CURLOPT_URL, url.getUrl()));

            options->add(optionFactory.createGeneric(CURLOPT_WRITEDATA, nullptr));

            options->set();
            curlInterface->perform();
        } catch(Exception& e) {
            //e.addContext(__FILE__, __LINE__);
            throw e;
        }   
        LIBFILESYNC_CURL_UTILITY_DEBUG_EXIT();         
    }

    bool FtpClient::doRemoteEntryExists() const {
        LIBFILESYNC_CURL_UTILITY_DEBUG_ENTER();
        bool entryIsAccessible = true;
        try {
            std::unique_ptr<option::Collection> options = optionFactory.createCollection();
            
            options->add(optionFactory.createVolatileNobody());
            options->add(optionFactory.createGeneric(CURLOPT_WRITEDATA, nullptr));
            options->set();
            curlInterface->perform();
        } catch(Exception& e) {
            entryIsAccessible = false;
        }
        LIBFILESYNC_CURL_UTILITY_DEBUG_EXIT();
        return entryIsAccessible;       
    }

}