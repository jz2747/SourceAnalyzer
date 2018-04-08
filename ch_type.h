/*********************************************************
 * char_type -- Character type module
 *******************************************************/
enum CHAR_TYPE{
	C_EOF,
	C_WHITE,
	C_NEWLINE,
	C_ALPHA,
	C_DIGIT,
	C_OPERATOR,
	C_SLASH,
	C_L_PAREN,
	C_R_PAREN,
	C_L_CURLY,
	C_R_CURLY,
	C_SINGLE,    // '\''
	C_DOUBLE,
	C_HEX_DIGIT,
	C_ALPHA_NUMERIC
};

/******************************************************
 * is_char_type -- Determines if a character belongs
 *			to a given type
 *
 * Parameters
 *	ch -- Character to check
 *	kind -- Type to check against
 *
 * Returns
 *	0 -- Not of the type kind
 *	1 -- Of the type kind
 ******************************************************/
extern int is_char_type(int ch, enum CHAR_TYPE kind);

/******************************************************
 * get_char_type -- Given a character, returns its type
 *
 * Notes
 *	we return simple types, C_HEX_DIGIT and
 *	C_ALPHA_NUMERIC are not returned
 *
 * Parameters:
 *	ch -- Character having the type we want
 *
 * Returns
 *	character type from enum CHAR_TYPE
 ******************************************************/
extern enum CHAR_TYPE get_char_type(int ch);
