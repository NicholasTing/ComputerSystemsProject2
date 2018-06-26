/**
 * Helper function to validate key usage.
 *
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 22 May 2018

 */

#include "headers.h"

int validate_key_usage(BIO *bio, X509 *x509_certificate){

    int valid_key_usage = 1;

    //Sample code from Chris Culnane repository
    BUF_MEM *bptr = NULL;
    char *buf = NULL;
    int loc;
    loc = X509_get_ext_by_NID(x509_certificate, NID_ext_key_usage, -1);
    X509_EXTENSION *ex = X509_get_ext(x509_certificate, loc);
    X509V3_EXT_print(bio, ex, 0, 0);
    BIO_get_mem_ptr(bio, &bptr);

    //bptr->daa is not NULL terminated - add NULL character
    buf = (char *)malloc( (bptr->length + 1)*sizeof(char) );
    memcpy(buf, bptr->data, bptr->length);
    buf[bptr->length] = '\0';

    char serverAuth[256] = "TLS Web Server Authentication";

    //Checks if TLS Web Server Authentication
    if(strstr(buf,serverAuth) != NULL){
        printf("Valid key usage\n");
    }

    else{
        printf("Invalid key usage\n");
        valid_key_usage = 0;
    }

    return valid_key_usage;
}
