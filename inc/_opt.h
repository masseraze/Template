#ifndef _OPT_H   //Include guard to prevent multiple inclusions
#define _OPT_H

#include <stdlib.h>
#include <getopt.h>
/******************ARGS*********************/
struct _args{
	/** Argument count */
	int argc;

	/** Argument vector.  NULL terminated */
	char **argv;
};

struct hint_s {
	const char *arg;
	const char *str;
};
/**
 * Initializer for 'struct _args'
 */
#define _ARGS_INIT(argc, argv) { argc, argv }


/******************OPTIONS*********************/
struct _opt {
	/** Matching template and optional parameter formatting */
	const char *templ;

	/**
	 * Offset of variable within 'data' parameter
	 * or -1
	 */
	unsigned long offset;
};

/**
 * Last option.	 An array of 'struct _opt' must end with a NULL
 * template value
 */
#define _OPT_END { NULL, 0}

/******************Internal OPTIONS*********************/
static int option_index = 0;
static const char *short_options = "f:F"; // add needed option here
/*!
 * @brief `-f --filename` [?]:  filename to store output 
 */
#define FILENAME_OPTION \
	{"filename", required_argument, 0, 'f'},		/* specify file name*/
/*!
 * @brief `-F --format` Format 
 */
#define FORMAT_OPTION \
	{"format",	no_argument, 0, 'F'},
/*!
 * @brief `-h --help` help 
 */
#define HELP_OPTION \
	{"help",	no_argument, 0, 'h'},

static struct option long_options[] = {
	FILENAME_OPTION
	FORMAT_OPTION
	HELP_OPTION
	{0, 0, 0, 0}
};

static const struct hint_s hint[] = {
	{"<filename>", "file to store"},
	{"          ", "format"},
	{NULL, NULL}
};



int _opt_parse(struct _args *args, void *data, const struct _opt opts[]);
int main_opt_parse(struct _args *args);

#endif
