#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>

namespace otocurl::option {

    Option::Option(wrapper::Easy& curlInterface) noexcept :
        curlInterface{ curlInterface } {

    }

    void Option::setInterface(wrapper::Easy& curlInterface) noexcept {
        this->curlInterface = curlInterface;
    }

    void Option::set() {
        doSet();
    }

}