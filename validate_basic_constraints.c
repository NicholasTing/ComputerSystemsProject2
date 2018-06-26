/**
 * Function to check whether it has a valid basic constraint
 *

 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 22 May 2018
 */

#include "headers.h"

int validate_basic_constraints(X509* x509_certificate){

    int valid_basic_constraints = 1;
    //Basic constraints bc
    BASIC_CONSTRAINTS *bc;

    bc = X509_get_ext_d2i(x509_certificate, NID_basic_constraints, NULL, NULL);

    //If the basic constraints is not 0, its invalid.
    if(bc->ca != 0){
        printf("Invalid basic constraints\n");
        valid_basic_constraints = 0;
    }
    else{
        printf("Valid basic constraints\n");
    }

    return valid_basic_constraints;

}
