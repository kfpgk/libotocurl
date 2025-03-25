#include <libotocurl/option/Collection.hpp>
#include <libotocurl/option/Option.hpp>

#include <memory>
#include <deque>

namespace otocurl::option {

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