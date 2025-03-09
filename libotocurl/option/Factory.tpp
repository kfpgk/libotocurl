#include <libotocurl/option/Generic.hpp>

namespace otocurl::option {

    template <typename... Args>
    std::unique_ptr<Option> Factory::createGeneric(
        CURLoption curlOption, Args&&... args) const {

        return std::make_unique<option::Generic<Args...>>(
            curlInterface, curlOption, std::forward<Args>(args)...);
    }    

}