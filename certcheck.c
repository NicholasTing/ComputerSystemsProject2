/**
 * Example certifcate code
 * gcc -o certcheck certexample.c -lssl -lcrypto
 *
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 13 May 2018

*/

#include "headers.h"

int main(int argc, char *argv[])
{
    BIO *certificate_bio = NULL;

    //initialise openSSL
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();

    //If didnt enter the path name, exit as an error
    if (argc < 2){
        fprintf(stderr, "Error, need a second argument\n");
        exit(EXIT_FAILURE);
    }

    //Opens the csv file
    FILE* csv_file;
    char line[1024];
    csv_file = fopen(argv[1],"r");

    //Open output_file to write on
    FILE* output_file;
    output_file = fopen("output.csv","w+");

    while (fgets(line, 1024, csv_file))
    {
        //Final string to output to csv file.
        char final_string[2048];

        int i = 0;
        int valid_date = 1;
        int valid_domain_name = 1;
        int valid_key_length = 1;
        int valid_key_usage = 1;
        int valid_basic_constraints = 1;

        //Reads the csv file
        char *certificate_file = strtok(line, ",");
        char *URL = strtok(NULL,"\n");

        //Append to the final_string which is the answer
        strcpy(final_string,certificate_file);
        strcat(final_string,",");
        strcat(final_string,URL);

        //Certificate is invalid until proven otherwise
        int valid = 0;

        //Reads the cert file using fopen
        FILE* cert_file = fopen(certificate_file, "r");

        X509* x509_certificate;

        BIO *bio = BIO_new(BIO_s_mem());

        //create BIO object to read certificate
        certificate_bio = BIO_new(BIO_s_file());

        //Read certificate into BIO
        if (!(BIO_read_filename(certificate_bio, certificate_file)))
        {
            fprintf(stderr, "Error in reading cert BIO filename");
            exit(EXIT_FAILURE);

        }

        if (!(x509_certificate = PEM_read_bio_X509(certificate_bio, NULL, 0, NULL)))
        {
            fprintf(stderr, "Error in loading certificate");
            exit(EXIT_FAILURE);
        }

       
	char* issuer_name = X509_NAME_oneline(X509_get_issuer_name(x509_certificate), 0, 0);

	//1. Validate the not before and not after dates
	valid_date = validate_dates(x509_certificate);

	//2. Validate the domain name (SAN) and wildcards
	valid_domain_name = validate_domain_name(x509_certificate, URL);

	//3. Validate the number of bits
	valid_key_length = validate_key_len(x509_certificate);

	//4. Validate basic constraints
	valid_basic_constraints = validate_basic_constraints(x509_certificate);

	//4. Validate key usage
	valid_key_usage = validate_key_usage(bio, x509_certificate);

	if(valid_date && valid_domain_name && valid_key_length
			&& valid_key_usage && valid_basic_constraints){
		printf("%s is valid certificate!\n\n\n",certificate_file);
		valid = 1;
	}

	//Adds the final output into the output_csv file.
	strcat(final_string,",");
	char string[2];

	snprintf(string, 2,"%d", valid);
	strcat(final_string,string);
	strcat(final_string,"\n");
	fputs(final_string, output_file);

	printf("\n");
	// X509_free(x509_certificate);

    }

    BIO_free_all(certificate_bio);

    exit(0);
}
