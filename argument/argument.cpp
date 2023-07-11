#include <stdexcept>
#include <vector>
#include <sstream>
#include <cstring>

#include "argument.hpp"

Argument::Argument(const int argc, const char** args)
    : argsNumber_(argc)
    , args_(args)
{
    if (argsNumber_ < 3) {
        throw std::runtime_error("Quantity of args is not valid, need more!");
    }
    
    std::vector<std::string> paths{};
    const char* encrypt = "-e";
    const char* decrypt = "-d";

    for (size_t i = 1; i < argsNumber_; i++) {
        if (args_[i][0] == '-') {
            if (strcmp(args_[i], encrypt) == 0) {
                hcmMode_ = hcm::encrypt;
            } 
            else if (strcmp(args_[i], decrypt) == 0) {
                hcmMode_ = hcm::decrypt;
            } else {
                throwException(args_[i], "Unknown arg");
            }
        } else {
            paths.push_back(args_[i]);
            if (paths.size() >= 3) {
                throwException(args_[i], "Invalid arg");
            }
        }
    }
    fromFile_ = paths[0];
    intoFile_ = paths[1];
}

const std::string Argument::fromFile() const {
    return fromFile_;
}

const std::string Argument::intoFile() const {
    return intoFile_;
}

const hcm Argument::hcmMode() const {
    return hcmMode_;
}

void throwException(const std::string& arg, const std::string& message) {
    std::stringstream stream{};
    stream << message << ": " << arg; 
    throw std::runtime_error(stream.str());
}