#ifndef LIBOTOCURL_STORAGE_CHAR_BUFFER_VISITOR_GET_SPAN_HPP
#define LIBOTOCURL_STORAGE_CHAR_BUFFER_VISITOR_GET_SPAN_HPP

#include <libotocurl/storage/char_buffer/ReadBuffer.hpp>
#include <libotocurl/storage/char_buffer/ReadWriteBuffer.hpp>
#include <libotocurl/storage/char_buffer/CharBufferStub.test.hpp>

#include <span>

namespace otocurl::storage::char_buffer::visitor {

    class GetSpan {

        public:
            std::span<char> operator()(ReadBuffer& buffer);
            std::span<char> operator()(ReadWriteBuffer& buffer);
            std::span<char> operator()(unit_test::CharBufferStub& buffer);

    };

}

#endif