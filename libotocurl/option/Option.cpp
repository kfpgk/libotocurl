#include <libotocurl/option/Option.hpp>
#include <libotocurl/Exception.hpp>

namespace filesync::curl::option {

    Option::Option(wrapper::Easy& curlInterface) :
        curlInterface{ curlInterface } {

    }

    void Option::setEasy(wrapper::Easy& curlInterface) {
        this->curlInterface = curlInterface;
    }

    void Option::set() {
        doSet();
    }

}