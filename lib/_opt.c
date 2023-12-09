#include <stdio.h>
#include <string.h>
#include "_opt.h"


int _opt_parse(struct _args *args, void *data, const struct _opt opts[]){
    int opt;

    while ((opt = getopt_long(args->argc, args->argv, short_options, long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                printf("Option --filename with argument '%s'\n", optarg);
                break;
            case 'F':
                printf("Option --format\n");
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