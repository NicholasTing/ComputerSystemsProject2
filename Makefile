HEADERS = headers.h

certcheck: certcheck.o compare_wildcards.o validate_dates.o validate_key_len.o validate_basic_constraints.o\
	 validate_key_usage.o validate_domain_name.o headers.h
	gcc -o certcheck certcheck.o compare_wildcards.o validate_basic_constraints.o validate_dates.o\
	 validate_key_len.o validate_key_usage.o validate_domain_name.o -lssl -lcrypto

certcheck.o: certcheck.c
	gcc -c certcheck.c -lssl -lcrypto

compare_wildcards.o: compare_wildcards.c
	gcc -c compare_wildcards.c

validate_dates.o: validate_dates.c
	gcc -c validate_dates.c

validate_key_len.o: validate_key_len.c
	gcc -c validate_key_len.c

validate_basic_constraints.o: validate_basic_constraints.c
	gcc -c validate_basic_constraints.c

validate_key_usage.o: validate_key_usage.c
	gcc -c validate_key_usage.c

validate_domain_name.o: validate_domain_name.c
	gcc -c validate_domain_name.c
clean:
	rm certcheck *.o
