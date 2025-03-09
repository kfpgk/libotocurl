#ifndef LIBFILESYNC_CURL_OPTION_COLLECTION_HPP
#define LIBFILESYNC_CURL_OPTION_COLLECTION_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <memory>
#include <deque>

namespace filesync::curl::option {

    /**
     * @brief Collection of CURLOPTs
     * 
     * Patterns:
     *  - Composite of the composite pattern
     */
    class Collection : public Option {

    public:
        explicit Collection(wrapper::Easy& curlInterface);
        void add(std::shared_ptr<Option> option);
        void clear();

    private:
        std::deque<std::shared_ptr<Option>> options;

        virtual void doSet();

    };

}

#endif