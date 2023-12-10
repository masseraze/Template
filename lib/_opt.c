#include <stdio.h>
#include <string.h>
#include "_opt.h"

extern const int size_of_option_spec;

struct _opt_context {
	void *data;
	const struct _opt *opt;
    int argc;
	char **argv;
    int extopt;
};

int extern_opt_par(struct _opt_context *ctx){
    int i = 0;
    while(ctx->opt[i].templ != NULL){ // End with _OPT_END
        // fprintf(stderr,"[%s ,%d]\n",__func__,__LINE__); //should run three times
        //if args->argv is same as opt[]->template
        int opt_length = strcspn(ctx->opt[i].templ, "=");
        // If '=' is not found, use the full length of the template
        if (ctx->opt[i].templ[opt_length] == '\0') {
            opt_length = strlen(ctx->opt[i].templ);
        }
        for(int j = 1; j < ctx->argc; j++){
            if (strncmp(ctx->argv[j], ctx->opt[i].templ, opt_length) == 0) {
                void *data_tmp = ctx->data; // point to void *data (static option in main.c)
                if(strcmp(ctx->argv[j],"--help") == 0){
                    // fprintf(stderr,"[%s ,%d]\n",__func__,__LINE__);                
                    int *field = (int *)((int)data_tmp + ctx->opt[i].offset);
                    *field = 1;
                    ctx->argc--; // delete external help
                    ctx->extopt++; // count the external option
                    for (int k = j; k < ctx->argc; k++) {
                        ctx->argv[k] = ctx->argv[k + 1];
                    }
                    i++;
                    return 0;
                }
                //copy the argv after = string to *(data + opts[i].offset)
                // Check if there's an '=' in the argument
                char *value = strchr(ctx->argv[j], '=');
                if (value) {
                    // Increment value to point to the character after '='
                    value++;

                    // Get the pointer to the field in the data structure
                    char **field = (char **)((char *)data_tmp + ctx->opt[i].offset);

                    // Free the old string if it exists
                    if (*field) {
                        free(*field);
                    }

                    // Duplicate the string
                    *field = strdup(value);
                }
                ctx->argc--; // delete external option
                ctx->extopt++; // count the external option
                for (int k = j; k < ctx->argc; k++) {
                    ctx->argv[k] = ctx->argv[k + 1];
                }
            }
        }
        
        i++;
    }
}

int _opt_parse(struct _args *args, void *data, const struct _opt opts[]){
    int opt;

    struct _opt_context ctx = {
		.data = data,
		.opt = opts,
        .extopt = 0
	};

    ctx.argc = args->argc;
	ctx.argv = args->argv;

	opt = extern_opt_par(&ctx);
    args->argc = args->argc - ctx.extopt;
    return 0;
}

int main_opt_parse(struct _args *args){
    int opt;
    while ((opt = getopt_long(args->argc, args->argv, short_options, long_options, &option_index)) != -1) {
        switch (opt) {
            //do what need for
            case 'f':
                // e.g. printf("Option --filename with argument '%s'\n", optarg);
                break;
            case 'F':
                // printf("Option --format\n");
                break;
            default:
                break;
        }
    }
    // Additional code to handle other arguments (not options) e.g. <mountpoint>
    if (optind < args->argc) {
        printf("Non-option arguments: ");
        while (optind < args->argc) {
            char *arg = args->argv[optind++];
            printf("%s ", arg);
        }
        putchar('\n');
    }
}