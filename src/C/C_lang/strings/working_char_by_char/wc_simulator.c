#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

/* Lo scopo del programma e' di simulare il comportamento del tool 'wc' dei
sistemi Unix.

Nota: In fase di compilazione, al fine di evitare spiacevoli messaggi di 
      Warning, e'necessario compilare con una delle 'Feature Test Macros'.
      man 7 feature_test_macros per maggiori informazioni. 
$ gcc -std=c11 -Wall -pedantic -D_BSD_SORCE wc_simulator.c
*/

int main(int argc, char *argv[])
{
	FILE *fp;
	const char *set_mode = "r";
    int print_chars = 0;
	int i, tot_alnum, tot_ascii, tot_space, tot_blank, tot_cntrl, tot_lower, 
		tot_upper, tot_digit, tot_graph, tot_print, tot_punct, tot_xdgit;

	tot_alnum = tot_ascii = tot_space = tot_blank = tot_cntrl = tot_lower = 
		tot_upper = tot_digit = tot_graph = tot_print = tot_punct = 
		tot_xdgit = 0;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <filename><print mode>\n"
                "print mode (0) - print full file at the beginning\n"
                "print mode (1) - print only character informations\n", 
                argv[0]);

		exit(EXIT_FAILURE);
	}

	if ((fp = fopen(argv[1], set_mode)) == NULL) {
		fprintf(stderr, "%s: Apertura file.\n", (char *)strerror(errno));
		exit(EXIT_FAILURE);
	}

	while ( (i = fgetc(fp)) != EOF) {
		if (isalnum(i)) tot_alnum++;
		if (isascii(i)) tot_ascii++;
		if (isblank(i)) tot_blank++;
		if (iscntrl(i)) tot_cntrl++;
		if (isspace(i)) tot_space++;
		if (islower(i)) tot_lower++;
		if (isupper(i)) tot_upper++;
		if (isdigit(i)) tot_digit++;
		if (isgraph(i)) tot_graph++;
		if (isprint(i)) tot_print++;
		if (ispunct(i)) tot_punct++;
		if (isxdigit(i)) tot_xdgit++;
	}

    print_chars = atoi(argv[2]);

    if (print_chars == 0) {
        /* Dopo la prima lettura del file il 'file position indicator' puntato
        dallo stream punta alla fine del file, ora e' necessario spostarlo
        all'inizio del file stesso per consentirne una nuova lettura. */
        fseek(fp, 0, SEEK_SET);
        while ((i = fgetc(fp)) != EOF)
            fputc(i, stdout);
    }

    printf("\nPrint character informations of: \'%s\'\n", argv[1]);
	printf("tot_alnum:%5.d, tot_ascii:%5.d, tot_space:%5.d, tot_blank:%5.d\n"
		   "tot_cntrl:%5.d, tot_lower:%5.d, tot_upper:%5.d, tot_digit:%5.d\n"
		   "tot_graph:%5.d, tot_print:%5.d, tot_punct:%5.d, tot_xdgit:%5.d\n",
			tot_alnum, tot_ascii, tot_space, tot_blank, tot_cntrl, tot_lower, 
			tot_upper, tot_digit, tot_graph, tot_print, tot_punct, tot_xdgit);

	fclose(fp);
	
	return(EXIT_SUCCESS);
}
