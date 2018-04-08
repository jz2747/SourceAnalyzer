/******************************************************
 * ch_type package
 *
 * This module is used to determine the type of 
 * characters
 *
 * Public functions:
 *	init_char_type
 *	get_char_type
 *	is_char_type
 *
 *****************************************************/
#include<stdio.h>
#include"ch_type.h"

static enum CHAR_TYPE type_info[256];
static int ch_setup = 0;
/******************************************************
 * fill_range -- Fills in a range of types for the
 *			character type class
 *
 * Parameters
 *	start, end -- Range of items to fill in
 *	type -- Type to use for filling
 *
 *****************************************************/
static void fill_range(int start, int end, enum CHAR_TYPE type){
	int cur_ch;
	for(cur_ch = start; cur_ch <= end; cur_ch++)
		type_info[cur_ch] = type;
}

static void init_char_type(){
	fill_range(0,255,C_WHITE);

	fill_range('A','Z',C_ALPHA);
	fill_range('a','z',C_ALPHA);
	type_info['_'] = C_ALPHA;

	fill_range('0','9',C_DIGIT);

	type_info['!'] = C_OPERATOR;
	type_info['#'] = C_OPERATOR;
	type_info['$'] = C_OPERATOR;
	type_info['%'] = C_OPERATOR;
	type_info['^'] = C_OPERATOR;
	type_info['&'] = C_OPERATOR;
	type_info['*'] = C_OPERATOR;
	type_info['-'] = C_OPERATOR;
	type_info['+'] = C_OPERATOR;
	type_info['='] = C_OPERATOR;
	type_info['|'] = C_OPERATOR;
	type_info['~'] = C_OPERATOR;
	type_info[','] = C_OPERATOR;
	type_info[':'] = C_OPERATOR;
	type_info['?'] = C_OPERATOR;
	type_info['.'] = C_OPERATOR;
	type_info['<'] = C_OPERATOR;
	type_info['>'] = C_OPERATOR;
	type_info['/'] = C_SLASH;
	type_info['\n'] = C_NEWLINE;
	type_info['('] = C_L_PAREN;
	type_info[')'] = C_R_PAREN;
	type_info['{'] = C_L_CURLY;
	type_info['}'] = C_R_CURLY;
	type_info['"'] = C_DOUBLE;
	type_info['\''] = C_SINGLE;
}

/***********************************************************
 * is_char_type -- Determine if a character belongs to a given type
 *
 * Parameters
 *	ch -- Character to check
 *	kind -- Type to check against
 *
 * Returns
 *	0 -- Character is not of the kind
 *	1 -- Character is of the kind
 ***********************************************************/
int is_char_type(int ch, enum CHAR_TYPE kind){
	if(!ch_setup){
		init_char_type();
		ch_setup = 1;
	}

	if(ch == EOF)
		return (kind == C_EOF);

	switch(kind){
		case C_HEX_DIGIT:
			if(type_info[ch] == C_DIGIT)
				return 1;
			if(ch >= 'A' && ch <= 'F')
				return 1;
			if(ch >= 'a' && ch <= 'f')
				return 1;
			return 0;
		case C_ALPHA_NUMERIC:
			return is_char_type(ch, C_ALPHA) || is_char_type(ch,C_DIGIT);
		default:
			return (type_info[ch] == kind);
	}
}

/***************************************************************
 * get_char_type -- Given a character, returns its type
 *
 * Note
 *	only returns simple type, won't return C_HEX_DIGIT
 *	or C_ALPHA_NUMERIC
 *
 * Parameters
 *	ch -- character to check
 *
 * Returns
 *	character type.
 ***********************************************************/
enum CHAR_TYPE get_char_type(int ch){
	if(!ch_setup){
		init_char_type();
		ch_setup = 1;
	}

	if(ch == EOF)
		return C_EOF;

	return type_info[ch];
}

