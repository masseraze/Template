#include "_opt.h"
#include <stdio.h>
#include <stddef.h>

static struct options {
    char *data;
    char *path;
    int show_help;
}options;

#define OPTION(t, p)                           \
    { t, offsetof(struct options, p) }
static const struct _opt option_spec[] = {
    OPTION("--data=%s", data),
	OPTION("--path=%s", path),
	OPTION("--help", show_help),
};

const int size_of_option_spec = sizeof(option_spec) / sizeof(option_spec[0]);

static void show_help(const char *progname){
    fprintf(stderr,"[%s,%d]\n",__func__,__LINE__);
}

int main(int argc,char *argv[]){
    int ret = 0;
    struct _args temp_args = _ARGS_INIT(argc, argv);
    if (_opt_parse(&temp_args, &options, option_spec) == -1)
		return 1;
    if (options.show_help) {
		show_help(argv[0]);
    }
    printf("option data %s path %s\n",options.data,options.path);
    return ret;
}