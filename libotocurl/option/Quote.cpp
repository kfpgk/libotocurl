#include <libotocurl/option/Quote.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>
#include <libotocurl/wrapper/SList.hpp>

#include <any>
#include <string_view>

namespace otocurl::option {

    Quote::Quote(wrapper::Easy& curlInterface, const std::string_view command) :
        Option(curlInterface),
        commands{new wrapper::SList()} {
        
        addCommand(command);
		if (!actualOptionHoldsList()) {
			setCurrentValue(NULL);
		}
    }

    Quote::Quote(wrapper::Easy& curlInterface,
        const std::string_view command,
        wrapper::SList* resetValue) :
            Option(curlInterface),
            ResettableOption(resetValue),
            commands{new wrapper::SList()}  {

        addCommand(command);
        if (!actualOptionHoldsList()) {
            setCurrentValue(NULL);
        }
    }

    Quote::~Quote() {
        reset();
        delete commands;   
    }

    void Quote::addCommand(const std::string_view command) {
        if (!command.empty()) {
            commands->append(command);
        }
    }    

    wrapper::SList* Quote::getTargetValue() const {
        return commands;
    }

    void Quote::setTo(wrapper::SList* targetValue) {
        if (targetValue) {
            getInterface().setOption(CURLOPT_QUOTE, targetValue->getSListPointer());
        } else {
            getInterface().setOption(CURLOPT_QUOTE, NULL);
        }
    }

    bool Quote::actualOptionHoldsList() const {
        try {
			auto value = std::any_cast<curl_slist*>(getInterface().getOptionValue(curlOption));
			return value != nullptr;
		}
        catch (const std::bad_any_cast& e) {
            return false;
        }
    }

}