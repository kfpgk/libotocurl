#ifndef LIBOTOCURL_WRAPPER_OPTION_VALUES_HPP
#define LIBOTOCURL_WRAPPER_OPTION_VALUES_HPP

#include <curl/curl.h>

#include <any>
#include <unordered_map>

namespace otocurl::wrapper {

	/**
	 * @brief Containter holding the values for each CURLOPT
	 */
	class OptionValues {

	public:
		/**
		 * @brief Constructor
		 */
		OptionValues() = default;

		/**
		 * @brief Destructor
		 */
		~OptionValues() = default;

		/**
		 * @brief Get the value of a CURLOPT
		 *
		 * @param[in] option The CURLOPT to get the value for
		 * @return The value of the CURLOPT
		 */
		[[nodiscard]] std::any get(CURLoption option) const;

		/**
		 * @brief Set the value of a CURLOPT
		 *
		 * @param[in] option The CURLOPT to set the value for
		 * @param[in] value The value to set
		 */
		void set(CURLoption option, std::any value);

	private:
		// @brief The managed data
		std::unordered_map<CURLoption, std::any> data{
			{ CURLOPT_VERBOSE,			0L },
			{ CURLOPT_NOBODY,			0L },
			{ CURLOPT_UPLOAD,			0L },
			{ CURLOPT_QUOTE,			NULL }
		};

	};

}

#endif