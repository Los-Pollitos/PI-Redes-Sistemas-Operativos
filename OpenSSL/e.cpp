#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <openssl/aes.h>
#include <iostream>

using namespace std ;

int main(int argc, char *argv[]){
  int bytes_read, bytes_written;
  unsigned char indata[AES_BLOCK_SIZE];
  unsigned char outdata[AES_BLOCK_SIZE];
  char infile[1024], *outfile, *tmp;

  unsigned char ckey[] =  "thiskeyisverybad";
  unsigned char ivec[] = "dontusethisinput";

  if (argc <= 1) {
	  cout << "El 1er argumento debe ser el archivo a encriptar.";
  } else {
    snprintf(infile, 1023, "%s", argv[1]);
    FILE *ifp = fopen(infile, "r");
    if (ifp == NULL) {
	    fprintf(stderr, "Error: abriendo %s\n", infile);
    } else {
      tmp = basename(infile);
      outfile = (char*) malloc(strlen(tmp) + 5);
      snprintf(outfile, 1023, "%s.enc", tmp);
      FILE *ofp = fopen(outfile, "w");
      if (ofp == NULL) {
	      fprintf(stderr, "Error: abriendo %s\n", outfile);
      } else {
        AES_KEY key;
        AES_set_encrypt_key(ckey, 128, &key);
        int num = 16;

        do {
          bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

          AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num,AES_ENCRYPT);
          bytes_written = fwrite(outdata, 1, bytes_read, ofp);
        }while (bytes_read >= AES_BLOCK_SIZE);
        fclose(ofp);
      }
      fclose(ifp);

    }
  }
}