#ifndef LIBOTOCURL_WRAPPER_BASE_HPP
#define LIBOTOCURL_WRAPPER_BASE_HPP

namespace otocurl::wrapper {

    /**
     * @brief Base class for all objects that
     * access libcurl directly.
     * 
     * Deriving from this ensures that global
     * initialization for libcurl is performed
     * if needed.
     */
    class Base {

        protected:
            Base();

    };

}

#endif