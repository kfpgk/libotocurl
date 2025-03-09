#ifndef LIBOTOCURL_STORAGE_CHAR_BUFFER_CHAR_BUFFER_STUB_TEST_HPP
#define LIBOTOCURL_STORAGE_CHAR_BUFFER_CHAR_BUFFER_STUB_TEST_HPP

#include <span>
#include <string>

namespace otocurl::storage::char_buffer::unit_test {

    class CharBufferStub {

    public:
        CharBufferStub(const std::string& data);

        void resetPosition();
        std::span<char> getSpan();

    private:
        std::string data;

    };

}

#endif