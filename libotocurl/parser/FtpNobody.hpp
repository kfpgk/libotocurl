#ifndef LIBOTOCURL_PARSER_FTP_NOBODY_HPP
#define LIBOTOCURL_PARSER_FTP_NOBODY_HPP

#include <libotocurl/parser/Nobody.hpp>

#include <cstddef>
#include <map>
#include <string>

#define LIBFILESYNC_CURL_PARSER_FTP_NOBODY_LENGTH_ID "Content-Length:"
#define LIBFILESYNC_CURL_PARSER_FTP_NOBODY_LENGTH_UNIT_ID "Accept-ranges:"

namespace otocurl::parser {

    class FtpNobody : public Nobody {

        private:
            std::map<std::string, std::size_t> unitMap {
                {"bytes", 1},
                {"Bytes", 1}
            };

            void doParse(const std::string& content) override;

            std::size_t parseLength(const std::string& content);
            std::string parseLengthUnit(const std::string& content);
            
            std::size_t getRatioFromUnit(const std::string& unit);

    };

}

#endif