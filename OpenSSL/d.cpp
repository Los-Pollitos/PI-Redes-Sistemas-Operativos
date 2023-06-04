#include <stdio.h>
#include <openssl/aes.h>

int main(int argc, char *argv[])
{
  int bytes_read, bytes_written;
  unsigned char indata[AES_BLOCK_SIZE];
  unsigned char outdata[AES_BLOCK_SIZE];
  if (argc <= 1) {
	  printf("%s will atleast take one argument: the file to be encrypted\n", argv[0]);
  } else {
    unsigned char ckey[] =  "thiskeyisverybad";
    unsigned char ivec[] = "dontusethisinput";
    char infile[1024];
    char* outfile ;
    snprintf(infile, 1023, "%s", argv[1]);
    FILE *ifp = fopen(infile, "r");
    if (ifp == NULL) {
	    fprintf(stderr, "Error: abriendo %s\n", infile);
    } else {
      FILE *ofp = fopen("decrypted", "w");
      if (ofp == NULL) {
	      fprintf(stderr, "Error: abriendo%s\n", outfile);
      } else {
        AES_KEY key;
        AES_set_encrypt_key(ckey, 128, &key);
        int num = 16;
        do {
          bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);
          AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num,AES_DECRYPT);
          bytes_written = fwrite(outdata, 1, bytes_read, ofp);
        } while (bytes_read >= AES_BLOCK_SIZE) ;
        fclose(ofp);
      }
      fclose(ifp);
    }
  }
}