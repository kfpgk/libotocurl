#include <libotocurl/option/Collection.hpp>

namespace otocurl::option {

    Collection::Collection(wrapper::Easy& curlInterface) :
            Option(curlInterface) {

    }

    void Collection::add(
        std::shared_ptr<Option> option) {

        options.push_back(std::move(option));
    }

    void Collection::clear() {
        options.clear();
    }

    void Collection::doSet() {
        for (auto it = options.begin(); it != options.end(); it++) {
            it->get()->set();
        }
    }

}