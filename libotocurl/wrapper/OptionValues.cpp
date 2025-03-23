#include <libotocurl/wrapper/OptionValues.hpp>

#include <curl/curl.h>

#include <any>
#include <unordered_map>

namespace otocurl::wrapper {

	[[nodiscard]] std::any OptionValues::get(CURLoption option) const {
		return data.at(option);
	}

	void OptionValues::set(CURLoption option, std::any value) {
		data[option] = value;
	}

}