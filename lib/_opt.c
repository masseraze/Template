#include <stdio.h>
#include <string.h>
#include "_opt.h"

extern const int size_of_option_spec;

int _opt_parse(struct _args *args, void *data, const struct _opt opts[]){
    int opt;
    opterr = 0;// Disable automatic error printing by getopt_long

    while ((opt = getopt_long(args->argc, args->argv, short_options, long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                printf("Option --filename with argument '%s'\n", optarg);
                break;
            case 'F':
                printf("Option --format\n");
                break;
            default:
                //if args->argv is same as opt[]->template
                for(int i=0;i < size_of_option_spec; i++){
                    int opt_length = strcspn(opts[i].templ, "=");
                    // If '=' is not found, use the full length of the template
                    if (opts[i].templ[opt_length] == '\0') {
                        opt_length = strlen(opts[i].templ);
                    }
                    if (strncmp(args->argv[optind - 1], opts[i].templ, opt_length) == 0) {
                        printf("Option recognized in opts: %s\n", args->argv[optind - 1]);
                        //copy the argv after = string to *(data + opts[i].offset)
                        // Check if there's an '=' in the argument
                        char *value = strchr(args->argv[optind - 1], '=');
                        if (value) {
                            // Increment value to point to the character after '='
                            value++;

                            // Get the pointer to the field in the data structure
                            char **field = (char **)((char *)data + opts[i].offset);

                            // Free the old string if it exists
                            if (*field) {
                                free(*field);
                            }

                            // Duplicate the string
                            *field = strdup(value);
                        }
                    }
                }
                break;
        }
    }
    // Additional code to handle other arguments (not options)
    if (optind < args->argc) {
        printf("Non-option arguments: ");
        while (optind < args->argc) {
            char *arg = args->argv[optind++];
            printf("%s ", arg);
        }
        putchar('\n');
    }

    return 0;
}

// int add_arg(){
//     // Handle external 'data' argument
//     if (strncmp(arg, "--data=", 7) == 0) {
//         options_ptr->data = arg + 7; // Skip past "--data="
//     }
//     // Handle external 'path' argument
//     else if (strncmp(arg, "--path=", 7) == 0) {
//         options_ptr->path = arg + 7; // Skip past "--path="
//     }
//     // Handle external 'help' argument
//     else if (strcmp(arg, "--help") == 0) {
//         options_ptr->show_help = 1;
//     }
//     else {
//         printf("Unknown argument: %s\n", arg);
//     }
//     return 0;
// }

// if (optind < argc) {
//     printf("Non-option arguments: ");
//     while (optind < argc) {
//         printf("%s ", argv[optind++]);
//     }
//     putchar('\n');
// }