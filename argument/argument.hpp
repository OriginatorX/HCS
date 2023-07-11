#pragma once
#include <string>

enum class hcm {
    encrypt = 0,
    decrypt = 1
};

class Argument {
public:
    Argument(const int argc, const char** const args);

    const std::string fromFile() const;
    const std::string intoFile() const;
    const hcm hcmMode() const;
private:
    int64_t argsNumber_;
    const char** const args_;
    std::string fromFile_;
    std::string intoFile_;
    hcm hcmMode_;
};

void throwException(const std::string& arg, const std::string& message);
