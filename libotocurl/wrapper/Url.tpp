#include <libotocurl/wrapper/Exception.hpp>

namespace otocurl::wrapper {

    template<typename... Args>
    void Url::setPart(CURLUPart part, Args&&... args) {
        CURLUcode rc = curl_url_set(handle, part, std::forward<Args>(args)...);
        if (rc != CURLUE_OK) {
            throw Exception("curl_url_set() failed", rc);
        }
    }

}