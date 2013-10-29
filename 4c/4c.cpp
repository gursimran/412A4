#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

using namespace std;

int main(int argc, char* argv[]){
    
    //Exit if not all inputs provided
    if (argc != 2){
        cout << "Usage: 4c password(string)" << endl;
        return 0;
    }
    
    //Get sha1 of the password
    unsigned char temp[SHA_DIGEST_LENGTH];
    char buf[SHA_DIGEST_LENGTH*2];
    
    memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
    memset(temp, 0x0, SHA_DIGEST_LENGTH);
    
    SHA1((unsigned char *)argv[1], strlen(argv[1]), temp);
    
    for (int i=0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
    }
    
    //open file and seek to position where the hash is currently stored in file
	FILE *fp = fopen ("34682096.program2.exe", "r+");
	unsigned char high, low, byte;
    fseek(fp, 138322, SEEK_SET);
    
    //for evey two bytes of new hash calculated above
    //check if it a number or letter and convert it to hex value (0 to 15)
    //shift the hugh 4 bits left and add the lower 4 bits to it
    //write each new calculate byte to file
    //sha hash above is 40 characters but we reduce it to 20 by adding 2 bytes in
    //one.
    for (int i =0; i < 40; i=i+2){
        if (isdigit(buf[i])){
            high = int(buf[i]) - 48 ;
        }
        else{
            high = (buf[i]) - 87;
        }
        if (isdigit(buf[i+1])){
            low = (buf[i+1]) - 48;
        }
        else{
            low = (buf[i+1]) - 87;
        }
        byte = (high <<4) + low;
        char ch = (char)byte;
        fwrite(&ch, 1, sizeof(ch), fp);
    }
    
    //Close file and print message
    fclose(fp);
    cout << "Patch successful" << endl;
    return 0;
}
