/*
* split strings up my delimeters and generate arrays
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

int tokenCount(char * string, char del);

char ** tokenArray(char * string, char * del, int elements);

void freeTokenArray(char ** tokens, int tokenCount);
