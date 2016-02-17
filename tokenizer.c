/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	// declared list of tokens

	char **list;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
	//allocate memory for tokenizer
	TokenizerT *tk  = (TokenizerT *)malloc(sizeof(TokenizerT));
	
	// have tk point the struct variable
    tk -> list;
	
  return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
	free(tk -> list);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
	// i did not need to use this function
  return NULL;
}


 
 
	//Parameters(tokenizened string)
	//returns 1 if string is float
	//return 0 if it isnt float
int hexCheck(char *c){
	if(strlen(c) < 2 ){
		return FALSE;
	}
	//checks if first char is 0
	if(c[0] != '0'){
		return FALSE;
	}
	// checks if second char is X or x
	if(c[1] != 'X' && c[1] != 'x'){
		return FALSE;
	}
	int i;
	// checks for hex digits 
	for(i = 2; i < strlen(c);i++){
				if((c[i] >= '0' && c[i] <= '9') || ((c[i] >= 'a') && (c[i] <= 'f')) || ((c[i] >= 'A') && (c[i] <= 'F'))){
					continue;
				}
				else{
					return FALSE;
				}
		}
		printf("    HEX\n\n");
		return TRUE;
}

	//Parameters(tokenizened string)
	//returns 1 if string is decimal
	//return 0 if it isnt decimal
int decCheck(char *c){
	 int i;
	 if(c[0] == '0'){
		 return FALSE;
	 }
	 if(strlen(c) == 1){
		 if(isdigit(c[0])){
			 return TRUE;
		 }
		 else{
			 return FALSE;
		 }
	 }
	 for(i = 0; i < strlen(c); i++){
		if((c[i] >= '0' && c[i] <= '9')){
			 continue;
		 }
		else{
		
				 return FALSE;
		}
	} 
		 
		 printf("     Decimal\n\n");
		 return TRUE;
}

	//Parameters(tokenizened string)
	//returns 1 if string is octal
	//return 0 if it isnt octal
int octCheck(char *c){
	if(c[0] != '0'){
		return FALSE;
	}
	int i = 0;
	//checks if all digits are octal digits
	for(i = 1; i < strlen(c); i++){
		if((c[i] >= '0' && c[i] <= '7')){
			 continue;
		 }
		else{
			return FALSE;
		}
	}
	
	printf("       Octal\n\n");
	return TRUE;
}

	//Parameters(tokenizened string)
	//returns 1 if string is float
	//return 0 if it isnt float
int fltCheck(char *c){
	int i;
	int eCount = 0;
	int pCount = 0;
	int iIndex = 0;
	int eIndex = 0;
	int mCount = 0;
	int mIndex = 0;
	int aCount = 0;
	int aIndex = 0;
	if(c[0] == 'e' || c[0] == 'E' || c[0] == '+' || c[0] == '-' || c[0] == '-' || c[0] == '.'){
		return FALSE;
	}
	if(c[0] == '0' && c[1] != '.'){
		return FALSE;
	}
	for(i = 0; i < strlen(c); i++){
		if(c[i] == '.'){
			pCount++;
			iIndex = i;
		}
		if(c[i] == '-' ){
			mCount++;
			mIndex = i;
		}
		if(c[i] == '+' ){
			aCount++;
			aIndex = i;
		}
		if(c[i] == 'e' || c[i] == 'E'){
			eCount++;
			eIndex = i;
		}
		//checks if its a digit or a sign
		if((isdigit(c[i]) != 0 || (c[i] == 'e' || c[i] == 'E' || c[i] == '.'  || c[i] == '-' || c[i] == '+'))){
			 continue;
		 }
		else{
			return FALSE;
		}		
	}
	//checks if sign is the last char of the string
	if(c[strlen(c) -1] == 'e' || c[strlen(c) -1] == 'E' || c[strlen(c) -1] == '.' || c[strlen(c) -1] == '-' ||  c[strlen(c) -1] == '+'){
		return FALSE;
	}
	//checks for at least one e or .
	if((pCount + eCount) == 0){
		return FALSE;
	}
	// checks of multiple e,., +, or -,
	if(eCount > 1 || pCount > 1 || mCount > 1 || aCount > 1){
		return FALSE; 
	}
	//checks if the e is before the .
	if(pCount == 1 && eCount == 1){
		if(eIndex < iIndex){
			return FALSE;
		}
	}
	//checks if theres two signs
	if(mCount == 1 && aCount == 1){
		return FALSE;
	}
	//check if theres e if theres a -/+
	if((mCount == 1 || aCount == 1) && (eCount !=1)){ 
		return FALSE;
	}
	//check if + and e alligned
	if(eCount == 1 && aCount == 1){
		if(aIndex - eIndex != 1){
			return FALSE;
		}
	}
	// check if - and e alligned
	if(eCount == 1 && mCount == 1){
		if(mCount - eIndex != 1){
			return FALSE;
		}
	}
	
	
	printf("        Float\n\n");
	return TRUE;
}

//	adds char c to the end of char array
void combine(char *s, char c){
	int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

	//Parameters(tokenizened string)
	// prints out token
	//checks if the token is a float, oct, hex, decimal or a malformed string
void check(char *temp){
	        int isFlt = 0;
			int isOct = 0;
		    int isDec = 0;
		    int isHex = 0;
			int j;
			for(j = 0; j < strlen(temp); j++){
				printf ("%c",temp[j] );
				
			}	
			if((temp[0]== ' ')){
				return;
			}
			if(strlen(temp) == 0){
				return;
			}
			//check token
			isFlt = fltCheck(temp);
			isOct = octCheck(temp);
			isDec = decCheck(temp);
			isHex = hexCheck(temp);
			// print MAL if all are zero
			if(isDec == FALSE && isOct == FALSE && isFlt == FALSE && isHex == FALSE ){
				
				printf("       MAL\n");
			}
			//reset temp array
			memset(&temp[0], 0, sizeof(temp));
			
					
}
	//Parameters(string of chars)
	//splits the string into tokens
	// checks if the char array is a octal, hex, decimal, or float when theres a space or escape char
void tokenizer(char *d){
	int z;
	char temp[300] = "";
	int l = strlen(d);
	char fullString[l];
	//copy string
	for(z = 0; z < strlen(d); z++){
		fullString[z] = d[z];
		 
	}
	//char *c = fullString;
	char *c = d;
	char a = ' ';
	combine(c, a);
	int i;
	for(i = 0; i < strlen(c); i++){
		// checks for spaces
		if(isspace(c[i])){
			if(isspace(c[i-1])){
				continue;
			}								// should have used isxdigit 
			else if(isalpha(c[i -1]) != 0 && (c[i -1] != 'e' && c[i -1] != 'E' && c[i -1] != 'x' && c[i -1] != 'X' && c[i -1] != '.' && c[i -1] != '-' && c[i -1] != '+' && c[i -1] != 'a' && c[i -1] != 'b' && c[i -1] != 'c' && c[i -1] != 'd' && c[i -1] != 'f' && c[i -1] != 'A' && c[i -1] != 'B' && c[i -1] != 'C' && c[i -1] != 'D' && c[i -1] != 'F')){
				continue;
			}
			else{
				check(temp);
			}// checks of escape chars								// should have used isxdigit
		}else if(isalpha(c[i]) != 0 && (c[i] != 'e' && c[i] != 'E' && c[i] != 'x' && c[i] != 'X' && c[i] != '.' && c[i] != '-' && c[i] != '+' && c[i] != 'a' && c[i] != 'b' && c[i] != 'c' && c[i] != 'd' && c[i] != 'A' && c[i] != 'f' && c[i] != 'B' && c[i] != 'C' && c[i] != 'D' && c[i] != 'F')){
			if(isspace(c[i-1])){
				char escape = c[i];
				printf ("[0x%02x]     %c      \n\n", escape );
			}
			else{
				char escape = c[i];
				check(temp);
				printf ("[0x%02x]     %c      \n\n", escape );
			}
		} //checks for digit or hexdigit or x or . or - or +
		else if(isalpha(c[i]) != 0 || isdigit(c[i]) != 0 || c[i] == '.'  || c[i] == '-' || c[i] == '+') {
			char t = c[i];
			combine(temp,t);
		}
		else{   // prints escape char
			    char escape = c[i];
				check(temp);
				printf ("[0x%02x]     %c      \n\n", escape );
		}
			
		
	}
	c[l -1] = '\0';
}
 
 /*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */
int main(int argc, char **argv) {
	//check if there's no input
	if(argc == 1){ 
		printf("error\n\n\n");
		return -1;
	}
	// print original string
	printf("\nTokenizer    %s\n\n",argv[1]);	
	
	// declare token and allocate memmory for it
	TokenizerT *tk  = (TokenizerT *)malloc(sizeof(TokenizerT));
	
	// call TKCreate for string to be tokenized
	tk = TKCreate(argv[1]);
	
	//tokenize string 
	tokenizer(argv[1]);
	
	// clear memory
    TKDestroy( tk );
  return 0;
}