#include <libotocurl/wrapper/Base.hpp>
#include <libotocurl/wrapper/GlobalSetup.hpp>

namespace otocurl::wrapper {

    Base::Base() {
        GlobalSetup::init();
    }

}