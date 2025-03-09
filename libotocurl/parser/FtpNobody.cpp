#include <libotocurl/parser/FtpNobody.hpp>
#include <libotocurl/Exception.hpp>
#include <libotocurl/utility/Debug.hpp>

#include <cstddef>
#include <iostream>
#include <sstream>

namespace filesync::curl::parser {

    void FtpNobody::doParse(const std::string& content) {

        LIBFILESYNC_CURL_UTILITY_DEBUG_ENTER();

        std::size_t length = parseLength(content);
        std::string unit = parseLengthUnit(content);

        LIBFILESYNC_CURL_UTILITY_DEBUG("Size: '" << length << "'");
        LIBFILESYNC_CURL_UTILITY_DEBUG("Unit: '" << unit << "'");  

        size = length * getRatioFromUnit(unit);

        LIBFILESYNC_CURL_UTILITY_DEBUG_EXIT();

    }

    std::size_t FtpNobody::parseLength(const std::string& content) {

        std::string lengthID(LIBFILESYNC_CURL_PARSER_FTP_NOBODY_LENGTH_ID);
        std::size_t lengthPos =content.find(lengthID);
        if (lengthPos == std::string::npos) {
            throw Exception("Parser error: Could not find length id '" + lengthID + "'");
        }

        std::istringstream sizeStrStream(content.substr(
            lengthPos + lengthID.size(), 
            content.find('\n') - 1 - (lengthPos + lengthID.size())));

        std::size_t length;
        if (!(sizeStrStream >> length)) {
            throw Exception("Could not convert value of '" + lengthID + "' to an integer.");            
        }
          
        return length;
    }

    std::string FtpNobody::parseLengthUnit(const std::string& content) {

        std::string lengthUnitID(LIBFILESYNC_CURL_PARSER_FTP_NOBODY_LENGTH_UNIT_ID);
        std::size_t unitPos =content.find(lengthUnitID);
        if (unitPos == std::string::npos) {
            throw Exception("Parser error: Could not find unit id '" + lengthUnitID + "'");
        }

        std::string lengthUnit = trim(content.substr(
            unitPos + lengthUnitID.size(), 
            content.find('\n') - 1 - (unitPos + lengthUnitID.size())));   

        return lengthUnit;
    }

    std::size_t FtpNobody::getRatioFromUnit(const std::string& unit) {
        auto it = unitMap.find(unit);
        if (it == unitMap.end()) {
            throw Exception("Unknown unit '" + unit + "'");            
        }
        return it->second;
    }

}