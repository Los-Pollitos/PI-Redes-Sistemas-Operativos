#ifndef SECURITY_H
#define SECURITY_H

// TODO(nosotros): revisar si todos se ocupan
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <string>

class security {
public:
    security();
    ~security();
    std::string hash_string(std::string to_hash);
    std::string encrypt(std::string to_encrypt);
    std::string decrypt(std::string to_decrypt);
};

#endif // SECURITY_H
