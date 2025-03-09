#include <libotocurl/Exception.hpp>

namespace otocurl {

    Exception::Exception(const std::string& errorMessage) :
        std::runtime_error(errorMessage) {

    }

}