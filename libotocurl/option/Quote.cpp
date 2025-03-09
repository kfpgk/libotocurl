#include <libotocurl/option/Quote.hpp>
#include <libotocurl/option/Option.hpp>

namespace otocurl::option {

    Quote::Quote(wrapper::Easy& curlInterface,
        const std::string& command) :
            Option(curlInterface),
            commands{new wrapper::SList()} {
        
        addCommand(command);
    }

    Quote::Quote(wrapper::Easy& curlInterface,
        const std::string& command,
        wrapper::SList* resetValue) :
            Option(curlInterface),
            ResettableOption(resetValue),
            commands{new wrapper::SList()}  {

        addCommand(command);       
    }

    Quote::~Quote() {
        reset();
        delete commands;   
    }

    void Quote::addCommand(const std::string& command) {
        if (!command.empty()) {
            commands->append(command);
        }
    }    

    wrapper::SList* Quote::getValue() {
        return commands;
    }

    void Quote::setTo(wrapper::SList* value) {
        if (value) {
            curlInterface.get().setOption(CURLOPT_QUOTE, value->getSListPointer());
        } else {
            curlInterface.get().setOption(CURLOPT_QUOTE, NULL);
        }
    }

}