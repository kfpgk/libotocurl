#include <libotocurl/wrapper/GlobalSetup.hpp>
#include <libotocurl/Exception.hpp>
#include <libotocurl/utility/Debug.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace filesync::curl::wrapper {

    GlobalSetup::GlobalSetup() {
        LIBFILESYNC_CURL_UTILITY_DEBUG("Running curl_global_init()");
        CURLcode ret = curl_global_init(CURL_GLOBAL_DEFAULT);       
        if (ret != 0) {
            throw Exception("curl_global_init() failed:", ret);
        }
    }

    GlobalSetup::~GlobalSetup() {
        LIBFILESYNC_CURL_UTILITY_DEBUG("Running curl_global_cleanup()");
        curl_global_cleanup();
    }

    /**
     * Instantiate the static singleton object to run
     * global curl setup (exactly once).
     */
    void GlobalSetup::init() {
        static GlobalSetup setup;
    }

}