#include <libotocurl/wrapper/SList.hpp>
#include <libotocurl/wrapper/Exception.hpp>

namespace otocurl::wrapper {

    SList::SList(const std::string& content) {
        append(content);
    }

    SList::~SList() {
        if(handle) {
            curl_slist_free_all(handle);
        }      
    }

    SList::SList(const SList& rhs) {
        if (rhs.handle) {
            this->contents = rhs.contents;
            for (auto&& it = contents.begin(); it != contents.end(); it++) {
                curl_slist* tmpHandle = NULL;
                tmpHandle = curl_slist_append(this->handle, it->c_str());
                if (!tmpHandle) {
                    throw Exception("Failed to append '" + *it + "' to curl_slist.");
                }
                this->handle = tmpHandle;            
            }
        }
    }

    SList::SList(SList&& rhs) {
        using std::swap;
        swap(*this, rhs);
    }

    /**
     * @brief Combined copy- and move assignment operator
     * 
     * Copy-and-swap idiom
     */
    SList& SList::operator=(SList rhs) {
        using std::swap;
        swap(*this, rhs);
        return *this;
    }

    void swap(SList& lhs, SList& rhs) {
        using std::swap;
        swap(lhs.handle, rhs.handle);
        swap(lhs.contents, rhs.contents);        
    }

    /**
     * @brief Create a new  or append to existing
     * curl_slist. The handle is only written in 
     * case of successful operation to make
     * sure not to lose previous list when appending
     * fails.
     */
    void SList::append(const std::string_view content) {            
        curl_slist* tmpHandle = NULL;
        tmpHandle = curl_slist_append(handle, content.data());
        if (!tmpHandle) {
            throw Exception("Failed to append '" + std::string(content) + "' to curl_slist.");
        }
        contents.push_back(content.data());
        handle = tmpHandle;
    }

    bool SList::isEmpty() const {
        return handle == NULL;
    }

    curl_slist* SList::getSListPointer() const {
        return handle;
    }

}