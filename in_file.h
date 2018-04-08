/**************************************************************
 * input_file -- Data from the input file.                *
 *
 * The current two characters are stored in cur_char and   *
 * next_char *
 *
 * Lines are buffered so that they can be output to     *
 * the screen after a line is assembled.                     *
 *
 * Functions:                                *
 *	in_open  -- Open the input file        *
 *	in_close -- Close the input file        *
 *	read_char -- Reads the next character   *
 *	in_cur_char  -- Returns the current character  *
 *	in_next_char  -- Returns the next character    *
 *	in_flush  -- send lines to the screen     *
 ****************************************************************/

/****************************************************************
 * in_open  -- Opens the input file.                      *
 *							*
 * Parameters						*
 *	name -- char[], name of the input file           *
 *
 * Returns                                  *
 * 0 -- Open Succeeded                      *
 * none zero -- Open Failed                 *
 ****************************************************************/
extern int in_open(const char name[]);

/************************************************************
 * in_close -- Closes the input file.                    *
 *********************************************************/
extern void in_close();

/******************************************************************
 * in_read_char  --  Read the next char from the input file   *
 ****************************************************************/
extern void in_read_char();

/****************************************************************
 * in_cur_char -- Gets the current input character         *
 *
 * Returns
 *	current character.
 ***************************************************************/
extern int in_cur_char();

/***************************************************************
 * in_next_char -- Peeks ahead one character
 *
 * Returns
 *	the next character
 ***************************************************************/
extern int in_next_char();

/***************************************************************
 * in_flush -- Flushes the buffered input lilne to the screen
 ************************************************************/
extern void in_flush();

