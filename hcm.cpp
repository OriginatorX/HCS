#include <iostream>

#include "hcm.hpp"

Hcm::Hcm(const HillCipher& hill, const Argument& arg) 
    : arg_(arg)
    , hillCipher_(hill)
    , fileStream_()
{}

void Hcm::start() {
    Timer timer{};
    try {
        std::vector<std::string> messageBuffer{};
    
        fileStream_.open(arg_.fromFile(), std::ios_base::in);
        for (std::string line; std::getline(fileStream_, line);) {
            if (arg_.hcmMode() == hcm::encrypt) {
                messageBuffer.push_back(hillCipher_.encrypt(line));
            } else {
                messageBuffer.push_back(hillCipher_.decrypt(line));
            }
        }
        fileStream_.close();

        fileStream_.open(arg_.intoFile(), std::ios_base::out);
        for (const auto& str : messageBuffer) {
            fileStream_ << str << "\n";
        }
        fileStream_.close();
        std::clog << timer.elapsed() << "\n";
    }
    catch(const std::exception& e) {
        std::clog << timer.elapsed() << "\n";
        std::cerr << e.what() << '\n';
    }
}
