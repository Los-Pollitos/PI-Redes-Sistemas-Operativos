#include "security.h"
#include <QCryptographicHash>
#include <QString>

// Requires -lcrypto flag

security::security(){

}

security::~security(){

}

std::string security::hash_string(std::string password) {
    QString answer = QString(QCryptographicHash::hash((password),QCryptographicHash::Md5).toHex());
    return answer.toStdString();
}

std::string security::encrypt(std::string to_encrypt) {
    std::string result = "";
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];
    // Create the key
    unsigned char ckey[] =  "df8fd74cecdef7464d4e63dbf3607acd23557bf0";
    // Size 16 for input
    unsigned char ivec[] = "0000000000000000";
    AES_KEY key;
    AES_set_encrypt_key(ckey, 128, &key);
    int num = 16;
    unsigned long i = 0;
    unsigned long j = 0;
    int indata_count;
    do {
        indata_count = 0;
        for (j = i; j < i  + AES_BLOCK_SIZE && j < to_encrypt.size(); ++j) {
            indata[indata_count] = to_encrypt[j];
            ++indata_count;
        }
        i = j;
        if (indata_count != 0) {
            // Encrypt the data
            AES_cfb128_encrypt(indata, outdata, indata_count, &key, ivec, &num, AES_ENCRYPT);
            // Store the outdata
            for (int k = 0; k < indata_count; ++k) {
                result += outdata[k];
            }
        }
    } while (indata_count == AES_BLOCK_SIZE);
    return result;
}

std::string security::decrypt(std::string to_decrypt) {
    std::string result = "";
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];
    // Create the key
    unsigned char ckey[] =  "df8fd74cecdef7464d4e63dbf3607acd23557bf0";
    // Size 16 for input
    unsigned char ivec[] = "0000000000000000";
    AES_KEY key;
    AES_set_encrypt_key(ckey, 128, &key);
    int num = 16;
    unsigned long i = 0;
    unsigned long j = 0;
    int indata_count;
    do {
        indata_count = 0;
        for (j = i; j < i  + AES_BLOCK_SIZE && j < to_decrypt.size(); ++j) {
            indata[indata_count] = to_decrypt[j];
            ++indata_count;
        }
        i = j;
        if (indata_count != 0) {
            // Encrypt the data
            AES_cfb128_encrypt(indata, outdata, indata_count, &key, ivec, &num, AES_DECRYPT);
            // Store the outdata
            for (int k = 0; k < indata_count; ++k) {
                result += outdata[k];
            }
        }
    } while (indata_count == AES_BLOCK_SIZE);
    return result;
}
