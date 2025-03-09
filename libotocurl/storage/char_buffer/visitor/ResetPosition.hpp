#ifndef LIBOTOCURL_STORAGE_CHAR_BUFFER_VISITOR_RESET_POSITION_HPP
#define LIBOTOCURL_STORAGE_CHAR_BUFFER_VISITOR_RESET_POSITION_HPP

#include <libotocurl/storage/char_buffer/ReadBuffer.hpp>
#include <libotocurl/storage/char_buffer/ReadWriteBuffer.hpp>
#include <libotocurl/storage/char_buffer/CharBufferStub.test.hpp>

namespace otocurl::storage::char_buffer::visitor {

    class ResetPosition {

        public:
            void operator()(ReadBuffer& buffer);
            void operator()(ReadWriteBuffer& buffer);
            void operator()(unit_test::CharBufferStub& buffer);

    };

}

#endif