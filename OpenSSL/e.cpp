#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <openssl/aes.h>
#include <iostream>

using namespace std ;

std::string encrypt(std::string to_encrypt);
std::string decrypt(std::string to_encrypt); 

int main(int argc, char *argv[]){
  // int bytes_read, bytes_written;
  // unsigned char indata[AES_BLOCK_SIZE];
  // unsigned char outdata[AES_BLOCK_SIZE];
  // char infile[1024], *outfile, *tmp;

  // unsigned char ckey[] =  "thiskeyisverybad";
  // unsigned char ivec[] = "dontusethisinput";

  // if (argc <= 1) {
	//   cout << "El 1er argumento debe ser el archivo a encriptar.";
  // } else {
  //   // Obtains the file name
  //   snprintf(infile, 1023, "%s", argv[1]);
  //   // Opens the file in read
  //   FILE *ifp = fopen(infile, "r");
  //   if (ifp == NULL) {
	//     fprintf(stderr, "Error: abriendo %s\n", infile);
  //   } else {

  //     tmp = basename(infile);

  //     outfile = (char*) malloc(strlen(tmp) + 5);
  //     snprintf(outfile, 1023, "%s.enc", tmp);
  //     FILE *ofp = fopen(outfile, "w");

  //     if (ofp == NULL) {
	//       fprintf(stderr, "Error: abriendo %s\n", outfile);
  //     } else {


  //       AES_KEY key;
  //       AES_set_encrypt_key(ckey, 128, &key);
  //       int num = 16;

  //       do {
  //         bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

  //         AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num,AES_ENCRYPT);
  //         bytes_written = fwrite(outdata, 1, bytes_read, ofp);
  //       }while (bytes_read >= AES_BLOCK_SIZE);
  //       fclose(ofp);
  //     }
  //     fclose(ifp);

  //   }
  // }
  std::string encrypted = encrypt("luis solano angie solis emilia viquez cristopher hernandez");

  std::cout << ":() ";

  std::string decrypted = decrypt(encrypted);
  std::cout << "Decrypted: " << decrypted << "\n";
}

std::string encrypt(std::string to_encrypt) {
  std::string result = "";
  int bytes_read, bytes_written;
  unsigned char indata[AES_BLOCK_SIZE];
  unsigned char outdata[AES_BLOCK_SIZE];
  // Create the key
  unsigned char ckey[] =  "df8fd74cecdef7464d4e63dbf3607acd23557bf0";
  // Size 16 for input
  unsigned char ivec[] = "0000000000000000";

  AES_KEY key;
  AES_set_encrypt_key(ckey, 128, &key);
  int num = 16;
  int i = 0;
  int indata_count;
  do {
    indata_count = 0;
    for (int j = i; j < i  + AES_BLOCK_SIZE && j < to_encrypt.size(); ++j) {
      indata[indata_count] = to_encrypt[j];  
      ++indata_count;
    }
    // Encrypt the data
    AES_cfb128_encrypt(indata, outdata, indata_count, &key, ivec, &num, AES_ENCRYPT);
    
    // Store the outdata
    for (int k = 0; k < AES_BLOCK_SIZE; ++k) {
      result += outdata[k];
    }

  } while (indata_count == AES_BLOCK_SIZE);

  return result;
}

std::string decrypt(std::string to_encrypt) {
  std::string result = "";
  int bytes_read, bytes_written;
  unsigned char indata[AES_BLOCK_SIZE];
  unsigned char outdata[AES_BLOCK_SIZE];
  // Create the key
  unsigned char ckey[] =  "df8fd74cecdef7464d4e63dbf3607acd23557bf0";
  // Size 16 for input
  unsigned char ivec[] = "0000000000000000";

  AES_KEY key;
  AES_set_encrypt_key(ckey, 128, &key);
  int num = 16;
  int i = 0;
  int indata_count;
  do {
    indata_count = 0;
    for (int j = i; j < i  + AES_BLOCK_SIZE && j < to_encrypt.size(); ++j) {
      indata[indata_count] = to_encrypt[j];  
      ++indata_count;
    }
    // Encrypt the data
    AES_cfb128_encrypt(indata, outdata, indata_count, &key, ivec, &num, AES_DECRYPT);
    
    // Store the outdata
    for (int k = 0; k < AES_BLOCK_SIZE; ++k) {
      result += outdata[k];
    }

  } while (indata_count == AES_BLOCK_SIZE);

  return result;
}