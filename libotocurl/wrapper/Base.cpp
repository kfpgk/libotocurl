#include <libotocurl/wrapper/Base.hpp>
#include <libotocurl/wrapper/GlobalSetup.hpp>

namespace filesync::curl::wrapper {

    Base::Base() {
        GlobalSetup::init();
    }

}