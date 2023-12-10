#include "_opt.h"
#include <stdio.h>
#include <stddef.h>

static struct options {
    const char *data;
    const char *path;
    int show_help;
}options;

#define OPTION(t, p)                           \
    { t, offsetof(struct options, p) }
static const struct _opt option_spec[] = {
    OPTION("--data=%s", data),
	OPTION("--path=%s", path),
	OPTION("--help", show_help),
    _OPT_END
};

static void show_help(const char *progname){
    printf("usage: %s [options] \n\n", progname);
	printf("External customized options:\n"
	       "    --data=<s>             data name \n"
           "                           (default: \"dataname\")\n"
	       "    --path=<s>             Path \n"
           "                           (default: \"/path/to/where\")\n"
	       "\n");
}

int main(int argc,char *argv[]){
    int ret = 0;
    struct _args temp_args = _ARGS_INIT(argc, argv);

    options.data = "dataname";
    options.path = "/path/to/where";
    // external option parsing 
    if (_opt_parse(&temp_args, &options, option_spec) == -1)
		return 1;
    if (options.show_help) {
		show_help(argv[0]);
    }

    printf("external option: data %s path %s\n",options.data,options.path);

    // internal (main) option parsing
    ret = main_opt_parse(&temp_args);
    free(options.data);
    free(options.path);
    return ret;
}