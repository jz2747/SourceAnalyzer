/********************************************************
 * stat
 *	Produce statistics about a program
 *
 * Usage
 *	stat [option] <file-list>
 *******************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include"ch_type.h"
#include"in_file.h"
#include"token.h"

/********************************************************
 * Line Counter, counts the lines of the file,
 * and output the total line number when got EOF
 *******************************************************/
static int cur_line;

/*********************************************************
 * lc_init -- Initialize the line counter variable
 ********************************************************/
static void lc_init(){
	cur_line = 0;
}

/********************************************************
 * lc_take_token -- Consumes tokens and looks for end
 *			of line tokens.
 *
 * Parameters
 *	token -- The token coming in from input stream
 *
 *******************************************************/
static void lc_take_token(enum TOKEN_TYPE token){
	if(token == T_NEWLINE)
		cur_line++;
}

/*******************************************************
 * lc_line_start -- Outputs the per-line statistics,
 *			namely the current line #
 ******************************************************/
static void lc_line_start(){
	printf("%4d ", cur_line);
}

/*******************************************************
 * lc_eof -- Outputs the eof statistics,
 *		in this case, the total line number
 ******************************************************/
static void lc_eof(){
	printf("Total number of lines: %d\n",cur_line);
}


/*********************************************************
 *********************************************************
 * paren_count -- Counts the nesting level of ().
 *
 ********************************************************/
static int pc_cur_level;
static int pc_max_level;

/*********************************************************
 * pc_init() -- Initialize the () counter variables
 ********************************************************/
void pc_init(){
	pc_cur_level = 0;
	pc_max_level = 0;
}

/********************************************************
 * pc_take_token -- Consumes tokens and looks for () tokens
 *
 * Parameters
 *	token -- The token coming in from the input stream
 *********************************************************/
static void pc_take_token(enum TOKEN_TYPE token){
	switch(token){
		case T_L_PAREN:
			++pc_cur_level;
			if(pc_max_level < pc_cur_level)
				pc_max_level = pc_cur_level;
			break;
		case T_R_PAREN:
			--pc_cur_level;
			break;
		default: break;
	}
}

/**********************************************************
 * pc_line_start -- Prints the per_line statistics of ()
 *********************************************************/
static void pc_line_start(){
	printf("(%-2d ",pc_cur_level);
}

/**********************************************************
 * pc_eof -- Outputs the eof statistics of ()
 *********************************************************/
static void pc_eof(){
	printf("Maximum nesting of () : %d\n", pc_max_level);
}

/*************************************************************
 * ***********************************************************
 * brace_counter -- Counts the nesting level of {}
 ************************************************************/
static int bc_cur_level;
static int bc_max_level;

/*************************************************************
 * bc_init -- Initialize the {} counter variables
 ************************************************************/
static void bc_init(){
	bc_cur_level = 0;
	bc_max_level = 0;
}

/************************************************************
 * bc_take_token -- Consumes tokens and looks for {}
 *
 * Parameters
 *	token -- The token coming in from input stream
 *
 ***********************************************************/
static void bc_take_token(enum TOKEN_TYPE token){
	switch(token){
		case T_L_CURLY:
			++bc_cur_level;
			if(bc_max_level < bc_cur_level)
				bc_max_level = bc_cur_level;
			break;
		case T_R_CURLY:
			--bc_cur_level;
			break;
		default:
			break;
	}
}

/***********************************************************
 * bc_line_start -- Outputs the per_line statistics of {}
 **********************************************************/
static void bc_line_start(){
	printf("{%-2d ",bc_cur_level);
}

/***********************************************************
 * bc_eof -- Outputs the the total {} level when got eof
 **********************************************************/
static void bc_eof(){
	printf("Maximum nesting of {} : %d\n", bc_max_level);
}

/**********************************************************
 **********************************************************
 * Comment counter -- counts the number of lines with and
 *			without comments
 *
 * Notes
 *	this class makes use of two bits
 *	CF_COMMENTS -- a comment was seen
 *	CF_CODE -- code was seen
 *	to collect statistics
 *********************************************************/
static const int CF_COMMENT = (1<<0);
static const int CF_CODE = (1<<1);

// 0   [0] Blank line
// CF_COMMENT [1] comment only line
// CF_CODE [2] code only line
// CF_CODE | CF_COMMENT code and comment line

static int counters[4];
static int flags;

/**********************************************************
 * cc_init -- Initialize the comment count variables
 *********************************************************/
static void cc_init(){
	memset(counters,'\0',sizeof(counters));
	flags = 0;
}

/*********************************************************
 * cc_take_token -- Consumes tokens and looks for comment
 *			tokens.
 *
 * Parameters
 *	token -- The token coming in from the input stream
 *
 ********************************************************/
void cc_take_token(enum TOKEN_TYPE token){
	switch(token){
		case T_COMMENT:
			flags |= CF_COMMENT;
			break;
		case T_NEWLINE:
			++counters[flags];
			flags = 0;
			break;
		default:
			flags |= CF_CODE;
			break;
	}
}

/********************************************************
 * cc_line_start -- outputs the per_line statistics
 ********************************************************/
static void cc_line_start(){
}

/********************************************************
 * cc_eof -- Outputs the overall statistics of code
 *******************************************************/
static void cc_eof(){
	printf("Number of blank lines ................%d\n",counters[0]);
	printf("Number of comment only lines .........%d\n",counters[1]);
	printf("Number of code only lines ............%d\n",counters[2]);
	printf("Number of code and comment lines .....%d\n",counters[3]);
	printf("Comment to code ratio %3.1f%%\n",
			(float)(counters[1] + counters[3]) /
			(float) (counters[2]+counters[3]) * 100.0);
}

/*************************************************************
 * do_file -- Process a single file.
 *
 * Parameters
 *	name -- The name of the file to process
 *
 ************************************************************/
static void do_file(const char *const name){
	enum TOKEN_TYPE cur_token;

	lc_init();
	pc_init();
	bc_init();
	cc_init();

	if(in_open(name) != 0){
		printf("Error: Could not open file %s for reading\n",name);
		return;
	}
	while(1){
		cur_token = next_token();

		lc_take_token(cur_token);
		pc_take_token(cur_token);
		bc_take_token(cur_token);
		cc_take_token(cur_token);

		switch(cur_token){
			case T_NEWLINE:
				lc_line_start();
				pc_line_start();
				bc_line_start();
				cc_line_start();
				in_flush();
				break;
			case T_EOF:
				lc_eof();
				pc_eof();
				bc_eof();
				cc_eof();
				in_close();
				return;
			default:
				break;
		}
	}
}

int main(int argc, char* argv[]){
	char *prog_name = argv[0];

	if(argc == 1){
		printf("Usage is %s [options] <file_list>\n", prog_name);
		exit(8);
	}

	for(; argc>1; argc--){
		do_file(argv[1]);
		++argv;
	}

	return 0;
}
