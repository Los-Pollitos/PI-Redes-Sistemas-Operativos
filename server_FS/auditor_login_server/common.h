#ifndef COMMON_H
#define COMMON_H

#include "security.h"
#include <iostream>

class common {
public:
    void encrypt(std::string& to_encrypt, std::string& encrypted) {
        encrypted = "";
        security security_manager;
        std::string buffer = security_manager.encrypt(to_encrypt);
        for (size_t i = 0; i < buffer.length(); ++i) {
            encrypted += std::to_string((int)buffer[i]);
            encrypted += ".";
        }
    }

    void decrypt(std::string& to_decrypt, std::string& decrypted) {
        security security_manager;
        std::string temp = "";

        for (size_t i = 0; i < to_decrypt.length(); ++i) {
            if (to_decrypt[i] != '.') {
                if (to_decrypt[i+1] == '.') {
                    temp += (char)(to_decrypt[i]-48);
                } else if (to_decrypt[i+2] == '.'){
                    temp += (char)(((int)to_decrypt[i]) - 48)*10 +(((int)to_decrypt[i+1]) - 48);
                    ++i; // ignore i+1
                } else {
                    temp += (char)(((int)to_decrypt[i] - 48)*100 + ((int)to_decrypt[i+1] -48)*10 - +(((int)to_decrypt[i+2] -48)));
                    i+=2; // ignore i+2
                }
                // next one would be a '.'
                i++;
            }
        }
        decrypted = security_manager.decrypt(temp);
    }
};

#endif // COMMON_H
