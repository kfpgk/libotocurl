#ifndef LIBOTOCURL_WRAPPER_UNIT_TEST_EASY_STUB_HPP
#define LIBOTOCURL_WRAPPER_UNIT_TEST_EASY_STUB_HPP

#include <libotocurl/wrapper/Easy.hpp>

namespace otocurl::wrapper::unit_test {

    class EasyStub : public Easy {

        private:
            void perform() const override;

    };

}

#endif