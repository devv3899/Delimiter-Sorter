#include <stdio.h>
#include <stdlib.h>

/*
Steps:
1. Validate Command line arguments. If require, show usage and stop.
2. Count number of tokens(n) in input
3. Create structure to store n strings.
4. Iterate on inputString, find length of token, and then create required length string.
5. Copy the token to memory created for string.
6. Sort tokens and the print them.
7. De-allocate memory for tokens.
8. End.
*/


/*
This method tries to allocate a char string dynamically
If unable to do so, then Gives error and closes the whole
program.
*/
char *createString(int size) {
	char *x = (char *)malloc(sizeof(char) * size);
	if(x == NULL) {
		printf("Malloc failed: Unable to allocate memory\n");
		exit(1);
	}
	return x;
}


/*
Create the array of character pointers to hold the tokens
*/
char **createTokens(int numTokens) {	
	char **tokens = (char **) malloc(sizeof(char *) * numTokens);
	if(tokens == NULL) {
		printf("Malloc failed: Unable to allocate memory. Exiting now!\n");
		exit(1);
	}
	return tokens;
}


/*
Check if a character is an alphabate
*/
int isAlpha(char c) {
	return (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A');
}


/*
This method takes the user input and tells how many alphabatic
tokens are present
*/
int countTokens(char *inputString) {
	int count = 0;
	int i=0;
	int tokenStarted = 0;
	
	while(inputString[i] != '\0') {
		char c = inputString[i];
		
		if(tokenStarted == 0 && isAlpha(c)) {
			tokenStarted = 1;
		} else if(tokenStarted == 1 && !isAlpha(c)) {
			count++;
			tokenStarted = 0;
		}
		
		// move to next character
		i++;
	}
	
	// check if last token was going on, when input finished
	if(tokenStarted != 0) {
		count++;
	}
	return count;
}


/*
This method copies the characters from source string to destination string
from index=start(inclusive) to index=end(exclusive)
*/
void copyString(char *sourceStr, int startIndex, int endIndex, char *destStr) {
	int i;
	
	// copy characters from source to dest
	for(i = startIndex; i < endIndex; i++) {
		destStr[i - startIndex] = sourceStr[i];
	}
	
	// add null terminator at the last of created string
	destStr[endIndex - startIndex] = '\0';
}


/*
Precondition: tokens is an array of pointers, and it has already been
initialized. However, we need to initialize individual strings inside
tokens as per our requirement.
*/
void fillTokens(char *inputStr, char **tokens) {
	
	// to count number ok tokens in string
	int count = 0;
	int i=0;
	
	// This will mark
	int tokenStarted = 0;
	
	// to capture token start and end positon of a token.
	int startPos = 0;
	int endPos = 0;
	
	while(inputStr[i] != '\0') {
		char c = inputStr[i];
		
		// If we find a alphabate, and the token has not started
		if(tokenStarted == 0 && isAlpha(c)) {
			tokenStarted = 1;
			startPos = i;
			
		// If token has already started, and we found a non-alpha character,
		// then we need to stop the token
		} else if(tokenStarted == 1 && !isAlpha(c)) {
			endPos = i;
			
			// allocate memory for token
			// taking one extra character to store null terminator
			tokens[count] = createString(1 + (endPos - startPos));
			
			// copy the string into token from input string
			copyString(inputStr, startPos, endPos, tokens[count]);
			
			count++;
			
			// reset the flag
			tokenStarted = 0;
		}
		
		// move to next character
		i++;
	}
	
	// if while terminating the loop, some token was running, 
	// then fill that too
	if(tokenStarted) {
		endPos = i;
		tokens[count] = createString(1 + (endPos - startPos));
		copyString(inputStr, startPos, endPos, tokens[count]);
	}
}


/*
This method checks if user has passed all required parameters, else
Show usage instructions, and abort program.
*/
void checkIfRequiredParamsPresent(int argc, char *argv[]) {
	
	// There need to be total 2 arguments
	// 1. Program executable
	// 2. String input enclosed within double quotes.
	
	if(argc != 2) {
		printf("Invalid arguments passed.\n");
		printf("Usage: ./pointersorter \"<input-string>\"\n");
		printf("Surround input in quotes to combine as one argument. Exiting now!\n");
		exit(0);
	}
}

// converts an alphabate character to lowercase
char toLower(char c) {
	if(c <= 'Z' && c >= 'A') {
		c = 'a' + ((int)(c - 'A'));
	}
	return c;
}

// checks if a letter is lowercase
int isUpper(char c) {
	return (c <= 'Z' && c >= 'A');
}

// checks if a letter is uppercase
int isLower(char c) {
	return (c <= 'z' && c >= 'a');
}

/*
This method compares two characters. If characters are different,
then they are compared based on their natural order (like a comes before
z), if characters are same but just their case is different, then lowercase letters
come later than uppercase letters.
*/
int compareChars(char c1, char c2) {
	
	if(isUpper(c1) && isLower(c2)) {
		return 1;
	} else if(isUpper(c2) && isLower(c1)) {
		return -1;
	} else {
		// both have same case.
		return (c1 - c2);
	}
}

/*
this method compares two string based on lexical order
*/
int compareStrings(char *str1, char *str2) {
	int i = 0;
	int j = 0;
    while((str1[i] != '\0') && (str2[j] != '\0')) {
        
		if(compareChars(str1[i], str2[j]) == 0) {
            i++; j++;
        } else if(compareChars(str1[i], str2[j]) < 0) {
			return -1;
		} else {
			return 1;
		}
	}
	
	// some string is not over yet.
	if(str1[i] == '\0') {
		return -1;
	}
	if(str2[j] == '\0') {
		return 1;
	}
	
    return 0; // strings are same
}


/*
This method sorts the tokens alphabatically using selection sort
*/
void sortTokens(char **tokens, int numTokens) {
	int i, j, min;
	
	for (i = 0; i < (numTokens - 1); i++) {
		min = i;

		for (j = i + 1; j < numTokens; j++) {
			if (compareStrings(tokens[j], tokens[min]) < 0) {
				min = j;
			}
		}
		if (min != i) {
			char *swap = tokens[i];
			tokens[i] = tokens[min];
			tokens[min] = swap;
		}
	}
}


/*
This method prints the tokens.
Precondition: Tokens are alphabatically sorted.
*/
void printTokens(char **tokens, int numTokens) {
	int i;
	
	for(i=numTokens-1; i>=0; i--) {
		printf("%s\n", tokens[i]);
	}
}


/*
This method de-allocates the memory assigned for storing the tokens.
*/
void freeTokenMemory(char **tokens, int numTokens) {
	int i;
	
	// first delete the individual strings
	for(i=numTokens-1; i>=0; i--) {
		free(tokens[i]);
	}
	
	// delete the array of pointers
	free(tokens);
}


/*
Main method, where execution starts.
*/
int main(int argc, char *argv[]) {
	
	// We check if required arguments are given by user,
	// else show them usage
	checkIfRequiredParamsPresent(argc, argv);
	
	// Read the User input argument
	char *inputString = argv[1];
	
	// find number of tokens in the string
	int numTokens = countTokens(inputString);
	
	// allocate memory for tokens
	char **tokens = createTokens(numTokens);
	
	// fill tokens from user input
	fillTokens(inputString, tokens);
	
	// sort and print the tokens
	sortTokens(tokens, numTokens);
	printTokens(tokens, numTokens);
	
	// free the allocated memory
	freeTokenMemory(tokens, numTokens);
	
	return 0;
}