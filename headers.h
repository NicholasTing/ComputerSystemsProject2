/**
 * Headers file
 * Coded by : Jing Kun Ting
 * Student Number : 792 886
 * Login ID: ting2
 * Coded first on: 13 May 2018

*/

#ifndef _FILE_H
#define _FILE_H

#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <openssl/asn1.h>

int compare_wildcards(char *first, char *second);
int validate_dates(X509 *x509_certificate);
int validate_key_len(X509 *x509_certificate);
int validate_basic_constraints(X509 *x509_certificate);
int validate_key_usage(BIO* bio, X509 *x509_certificate);
int validate_domain_name(X509 *x509_certificate, char *URL);

#endif
