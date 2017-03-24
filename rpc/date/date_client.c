/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "date.h"


void
date_prog_1(char *host)
{
	CLIENT *clnt;
	long  *result_1;
	char *bin_date_1_arg;
	char * *result_2;
	long  str_date_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DATE_PROG, DATE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = bin_date_1((void*)&bin_date_1_arg, clnt);
	if (result_1 == (long *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = str_date_1(&str_date_1_arg, clnt);
	if (result_2 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	date_prog_1 (host);
exit (0);
}
