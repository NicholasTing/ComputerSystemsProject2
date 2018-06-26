/**
 * Function to check whether its a valid date
 *
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 22 May 2018

*/

#include "headers.h"

int validate_dates(X509* x509_certificate){

    int valid_date = 1;

    //Current time
    ASN1_TIME *now_asn1time;

    //Checks the not before and not after dates.
    const ASN1_TIME *before = X509_get_notBefore(x509_certificate);
    const ASN1_TIME *after = X509_get_notAfter(x509_certificate);

    //Gets the current time in ASN1_TIME format
    now_asn1time = ASN1_TIME_new();
    ASN1_TIME_set(now_asn1time, time(NULL));

    int day, sec;
    //Validate the Not After date
    ASN1_TIME_diff(&day, &sec, now_asn1time, after);

    //If day or sec is greater/equal than 0, it is a valid not after date.
    if (day >= 0 || sec >= 0){
        printf("Valid time after\n");
    }
    else{
        valid_date = 0;
    }

    //Validate the Not Before date
    ASN1_TIME_diff(&day,&sec,before,now_asn1time);

    //If day or sec is greater/equal than 0, it is a valid not before date.
    if(day >= 0 || sec >= 0){
        printf("Valid time before\n");
    }
    else{
        valid_date = 0;
    }

    return valid_date;

}
