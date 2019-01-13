/* David Rider
** CS 261
** Aptil 21, 2017
** Assignment 2
*/
/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
*/
int isBalanced(char* s)
{
	if (s == NULL) {
        return 1;
	}

	DynArr *newArray = newDynArr(10);

	char c;
	while((c = nextChar(s)) != '0') {
        switch(c) {
        case '(' :
            pushDynArr(newArray, c);
            break;
        case '[' :
            pushDynArr(newArray, c);
            break;
        case '{' :
            pushDynArr(newArray, c);
            break;
        case ')' :
            if (topDynArr(newArray) == '(') {
                    popDynArr(newArray);
                    break;
            }
            return 0;
        case ']' :
            if (topDynArr(newArray) == '[') {
                    popDynArr(newArray);
                    break;
            }
            return 0;
        case '}' :
            if (topDynArr(newArray) == '{') {
                    popDynArr(newArray);
                    break;
            }
            return 0;
        }
	}
	if (!isEmptyDynArr(newArray)) {
        return 0;
	}
	deleteDynArr(newArray);
	return 1;
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}