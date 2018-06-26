/**
 * Function to check whether it has a valid key length
 *
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 22 May 2018

*/

#include "headers.h"

int validate_key_len(X509* x509_certificate){

    int valid_key_length = 1;

    //Gets the public key
    EVP_PKEY * public_key = X509_get_pubkey(x509_certificate);

    //Gets the key length in bits
    int key_length = EVP_PKEY_bits(public_key);

    //If minimum key length of 2048
    if(key_length >= 2048){
        printf("Valid number of bytes for key\n");
    }

    else{
        valid_key_length = 0;
        printf("Invalid number of bytes\n");
    }

    return valid_key_length;

}
