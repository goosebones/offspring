/*
* split strings up my delimeters and generate arrays
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

/*
* get the number of tokens in a string
* determined by the occurances of the del in the string
*
* @param string  string to parse
* @param del  delimiter to count on
* @return number of tokens in string
*/
int tokenCount(char * string, char del);

/*
* convert a string into a token array
* string is split up by delimiter
*
* @param string   string to tokenize
* @param del  dilimiter to split on
* @param elements  number of tokens in string
* @return array of strings
*/
char ** tokenArray(char * string, char * del, int elements);

/*
* free an allocated token array from memory
*
* @param tokens  array of stirngs to free
* @param tokenCount  size of token array
*/
void freeTokenArray(char ** tokens, int tokenCount);
