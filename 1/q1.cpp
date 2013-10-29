#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#define HASHTOMATCH "6a071eb5043593fa52b9d244fb468cef1da0ba26"
#define salt "tV"

using namespace std;

void shaOfString(string str)
{
    unsigned char digest[SHA_DIGEST_LENGTH];
    char *a=new char[str.size()+1];
    a[str.size()]=0;
    memcpy(a,str.c_str(),str.size());
    
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, a, strlen(a));
    SHA1_Final(digest, &ctx);
    
    char mdString[SHA_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    
    if (strcmp(mdString, HASHTOMATCH) == 0){
            printf("SHA1 digest: %s   %s\n", str.c_str(), mdString);
            exit(0);
    }
    free(a);
}

void displayPermutation(string permutation[], int length){
    int i=0;
    string result;
    for (i=0;i<length;i++){
        result = result + permutation[i] ;
    }
    shaOfString(salt+result);
}

void getPermutations(string operatorBank[], int operatorCount,
        string permutation[],int permutationLength, int curIndex){
    int i;
    //stop recursion condition
    if(curIndex == permutationLength){
        displayPermutation(permutation,permutationLength);
    }
    else{
        for(i = 0; i < operatorCount; i++){
            permutation[curIndex] = operatorBank[i];
            getPermutations(operatorBank,operatorCount,permutation,
                permutationLength,curIndex+1);
        }
    }
}

int main ()
{
    int operatorCount = 10;
    int permutationLength = 4;
    string operatorBank[] = {"0","1","2","3","4","5","6","7","8","9"};
    string permutation[] = {"","","",""}; //empty string
    int curIndex = 0;
    getPermutations(operatorBank,operatorCount,permutation,
                                permutationLength,curIndex);
    return 0;
}
