#include <iostream>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

// g++ hash.cpp -lcrypto

std::string hash_string(std::string to_hash);

int main() {
	
	std::cout << hash_string("luis") << "\n\n";
	
	std::cout << hash_string("emilia") << "\n\n";

	std::cout << hash_string("jijijijijijijijijijijiji") << "\n\n";

	return 0;
}

std::string hash_string(std::string to_hash) {
	unsigned char hash[20];
	// Hash the information
	SHA1((const unsigned char *)to_hash.c_str(), to_hash.length(), hash);
	std::string result(20, ' ');
	// Copy to result
	for (int i = 0; i < 20; ++i) {
		result[i] = hash[i];
	}
	// Return the result
	return result;
}
