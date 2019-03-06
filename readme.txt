POINTER SORTER.

> What does this program do?
	PointerSorter is a program that takes an argument through the command line, parses it into different sequences of alphabetic characters, and sorts them in descending alphabetical order (with uppercase having precedence over lowercase). The strings within the command line argument will be separated by non-alphabetic characters (delimiters). 

> Explanation of used data structure-
	The assignment incorporates a 2D array of characters to store the tokens which are passed by user via command line. The 2D array has different sizes as required for strings on each row. We first count the number of tokens in the passed input string, and on basis of that, the outer structure of pointers is created. Once that is done, we create character array for each row, only with length that is sufficient to accommodate the string read. At last, the array of pointers are sorted and printed. Once done, we de-allocate the memory.

> Running time-
	The code written for this assignments uses SELECTION SORT as the main sorting algorithm. So the running time of assignment is in the order of O(n^2).

>Pseudocode and steps :-

1. Validate Command line arguments. If require, show usage and stop.
2. Count number of tokens(n) in input
3. Create structure to store n strings.
4. Iterate on inputString, find length of token, and then create required length string.
5. Copy the token to memory created for string.
6. Sort tokens and the print them.
7. De-allocate memory for tokens.
8. End.

>Explanation for different functions as in code :- 

1- The Create String function-
	This method tries to allocate a char string dynamically and If it is unable to do so, then it Gives error and closes the whole program.

2- Count Token function-
	This method takes the user input and tells how many alphabetic tokens are present.

3- The String copy function-
	This method copies the characters from source string to destination string from index=start(inclusive) to index=end(exclusive)

4- The most important fill token function-
	Precondition: tokens is an array of pointers, and it has already been initialized. However, we need to initialize individual strings inside tokens as per our requirement.

5- The inputted argument checker-
	This method checks if user has passed all required parameters, else Show usage instructions, and abort program.

6- The sorter function-
	This method sorts the tokens alphabetically using selection sort.

7- The String copy function- 
	This method compares two characters. If characters are different, then they are compared based on their natural order (like z comes before a), if characters are same but just their case is different, then lowercase letters come later than uppercase letters.

8- Print Function-
	This method prints the tokens. Precondition: Tokens are alphabetically sorted.

9- The Free function :-
	This method de-allocates the memory assigned for storing the tokens.

10- The main function :-
	This method uses all the above explained functions to make the program run as the required conditions.
