#include <iostream>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

// g++ hash.cpp -lcrypto

std::string hash_string(std::string to_hash);

int main() {
	
	std::cout << "cjimenez :"<< hash_string("(e!zR$Y6/8TSgRs$") << "\n\n";
	std::cout << "gmora :"<< hash_string("d{QbnP8(}kp") << "\n\n";
	std::cout << "jnuñez :"<< hash_string("Ly=)Z6P4eUE") << "\n\n";
	std::cout << "eguzman :"<< hash_string("3526283_eg@1998") << "\n\n";
	std::cout << "alopez :"<< hash_string("&trabajoFeliz34!") << "\n\n";
	std::cout << "respinoza :"<< hash_string("bRc=Q+->6$") << "\n\n";
	std::cout << "gherrera :"<< hash_string("contrasena?DeAs1stenteMuySegura") << "\n\n";
	std::cout << "rgang :"<< hash_string("r1cardo@gAng_?}") << "\n\n";
	std::cout << "dcabezas :"<< hash_string("kfc&pollo_las_24horas!") << "\n\n";
	std::cout << "d_gmora :"<< hash_string("3526283_eg@1998") << "\n\n";
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
