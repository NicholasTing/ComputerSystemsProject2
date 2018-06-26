/**
 * Helper function to validate domain name
 *
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 22 May 2018

*/

#include "headers.h"

int validate_domain_name(X509* x509_certificate, char *URL){

    int valid_domain_name = 1;

    //Validates common name
    int common_name = -1;
    X509_NAME_ENTRY *common_name_entry = NULL;
    ASN1_STRING *common_name_asn1 = NULL;
    char *common_name_str = NULL;

    int idx = -1;
    X509_NAME* sname = X509_get_subject_name(x509_certificate);
    idx = X509_NAME_get_index_by_NID(sname, NID_commonName, -1);
    X509_NAME_ENTRY* entry = X509_NAME_get_entry(sname, idx);
    ASN1_STRING* data = X509_NAME_ENTRY_get_data(entry);

    common_name_str = ASN1_STRING_data(data);
    printf("%s is the common name\n",common_name_str);

    if(strcasecmp(common_name_str,URL)==0)
    {
        printf("Valid common name\n");
        return valid_domain_name;
    }

    else if(compare_wildcards(common_name_str,URL)){
        printf("Valid common name - wildcard\n");
        return valid_domain_name;
    }

    else{

        //Now, cert is invalid until proven otherwise.
        valid_domain_name = 0;

        //Stack of subject alternative names.
        STACK_OF(GENERAL_NAME) *Subject_Alt_Names = NULL;
        int total_SAN = -1;

        // Try to extract the names within the SAN extension from the certificate
        Subject_Alt_Names = X509_get_ext_d2i((X509 *) x509_certificate, NID_subject_alt_name, NULL, NULL);
        if (Subject_Alt_Names == NULL) {
            printf("No san names found\n");
        }
        else{
            total_SAN = sk_GENERAL_NAME_num(Subject_Alt_Names);
            // Check each name within the extension
            for (int i=0; i<total_SAN; i++) {

                const GENERAL_NAME *current_name = sk_GENERAL_NAME_value(Subject_Alt_Names, i);

                if (current_name->type == GEN_DNS) {
                    //Find the san name
                    char *san_name = (char *) ASN1_STRING_data(current_name->d.dNSName);

                    // Make sure there isn't an embedded NULL character in the DNS name
                    if (ASN1_STRING_length(current_name->d.dNSName) != strlen(san_name)) {
                        printf("Invalid, embedded NULL character\n");
                        break;
                    }

                    else {

                        //Compare  hostname with the DNS name
                        char temp_string[256];
                        strcpy(temp_string,URL);
                        if (strcasecmp(san_name, temp_string) == 0) {
                            printf("Valid common name - SAN\n");
                            valid_domain_name = 1;
                            break;
                        }
                        else if(compare_wildcards(san_name,temp_string) == 1){
                            valid_domain_name = 1;
                            break;
                        }
                    }
                }
            }
        }
        return valid_domain_name;
    }
}


