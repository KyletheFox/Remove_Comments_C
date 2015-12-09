#include <stdio.h>

#define out 0
#define readSlash 1
#define inComment 2
#define readStar 3
#define inQuote 4

int main (int argv, char **argccp) {
	
	char c;  		/* Input from file */
	int state = out; 	/* State of input. Default out */
	char lineCount = 0;
	char errorLineC, errorLineQ;
	char commentSpace;

	while((c=getchar())!=EOF) {
		
		if (commentSpace && c!=' ')
			putchar(' ');
			commentSpace=0;

		if (c=='\n')
			lineCount++;

		switch (state)
		{
		case out:
			if (c == '/')
				state = readSlash;
			else if (c == '"')  {
				state = inQuote;
				putchar(c);
				errorLineQ = lineCount;
			}
			else
				putchar(c);
			break;
		case readSlash:
			if (c =='*') {
				state = inComment;
				errorLineC = lineCount;
			}
			else {
				state = out;
				putchar('/');
				putchar(c);
			}
			break;
		case inComment:
			if (c=='*')
				state = readStar;
			break;
		case readStar:
			if (c=='/') {
				state = out;
				errorLineC=0;
				commentSpace=1;
			}
			else
				state = inComment;
			break;
		case inQuote:
			if (c=='"') {
				state = out;
				putchar(c);
				errorLineQ=0;
			}
			else
				putchar(c);
			break;
		} /* End Switch */

	}  /* End While */

	if (errorLineC)
		printf("\nERROR: unfinished comment on line %i\n", errorLineC);
	if (errorLineQ)
		printf("\nERROR: unfinished quote on line %i\n", errorLineQ);

	return 0;
		
} /* End Main */
