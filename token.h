/************************************************************
 * token -- Token handling module
 *
 * Functions:
 *	next_token -- Get the next token from input
 **********************************************************/

 //
 // define the enumeration list of tokens
 //
 enum TOKEN_TYPE{
	T_NUMBER,
	T_STRING,
	T_COMMENT,
	T_NEWLINE,
	T_OPERATOR,
	T_L_PAREN,
	T_R_PAREN,
	T_L_CURLY,
	T_R_CURLY,
	T_ID,
	T_EOF
};

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/********************************************************
 * next_token -- reads the next token in an input stream
 *
 * Returns
 *	next token.
 ********************************************************/
extern enum TOKEN_TYPE next_token();
