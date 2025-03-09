#include <libotocurl/storage/char_buffer/visitor/GetSpan.hpp>

namespace otocurl::storage::char_buffer::visitor {

    std::span<char> GetSpan::operator()(ReadBuffer& buffer) {
        return buffer.getSpan();
    }

    std::span<char> GetSpan::operator()(ReadWriteBuffer& buffer) {
        return buffer.getSpan();
    }

    std::span<char> GetSpan::operator()(unit_test::CharBufferStub& buffer) {
        return buffer.getSpan();
    }

}