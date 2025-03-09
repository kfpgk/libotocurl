#ifndef LIBOTOCURL_PARSER_NOBODY_STUB_TEST_HPP
#define LIBOTOCURL_PARSER_NOBODY_STUB_TEST_HPP

#include <libotocurl/parser/Nobody.hpp>

#include <string>

namespace otocurl::parser::unit_test {

    class NobodyStub : public Nobody {

    private:
        void doParse(const std::string& content) override;

    };

}

#endif