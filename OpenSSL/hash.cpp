#include <iostream>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

// g++ hash.cpp -lcrypto

int main() {
	unsigned char hash[SHA256_DIGEST_LENGTH];   // SHA256... es una constante de openssl
	std::string c = "unapalabra@$.*";
	SHA1((const unsigned char *)c.c_str(), c.length(), hash);  // es función del include de la línea 3 (hash)

	int i;
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		printf("%02x ", hash[i]);
	}
	printf("\n");
  std::cout << sizeof(hash) << "\n";

  c = "111111111111111111111111111111111112131231231245123631562462462528572375892374589237589235728395111111111111111111222222222222222222222222222222";
	SHA1((const unsigned char *)c.c_str(), c.length(), hash);  // es función del include de la línea 3 (hash)

  for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		printf("%02x ", hash[i]);
	}
	printf("\n");
  std::cout << sizeof(hash) << "\n";

	return 0;
}

// 46 22 68 ee 7a fe e1 d1 19 75 94 6b 54 9d de a4 cf f1 5b 15