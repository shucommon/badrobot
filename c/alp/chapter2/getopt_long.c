#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

// the name of the program
const char *program_name;

// print usage info
void print_usage(FILE *stream, int exit_code)
{
    fprintf(stream, "Usage: %s option [ inputfile ...]\n", program_name);
    fprintf(stream, 
            " -h    --help              display this usage information.\n"
            " -o    --output filename   write output to file.\n"
            " -v    --verbose           print verbose messages.\n");
    exit(exit_code);
}

int main(int argc, char **argv)
{
    int next_option;

    // a string listing valid short options letters
    const char *const short_options = "ho:v";
    // an array describing valid long options.
    const struct option long_options[] = {
        { "help",   0, NULL, 'h'},
        { "output", 1, NULL, 'o'},
        { "verbose",0, NULL, 'v'},
        { NULL,     0, NULL,  0 }, // required at end of array
    };

    // the name of the file to receive program output, or NULL for standard output.
    const char * output_filename = NULL;
    // whether to display verbose messages.
    int verbose = 0;

    program_name = argv[0];

    do {
        next_option = getopt_long( argc, argv, short_options, long_options, NULL);

        switch( next_option )
        {
            case 'h':
                print_usage( stdout, 0 );

            case 'o':
                output_filename = optarg;
                break;

            case 'v':
                verbose = 1;
                break;

            case '?':   // invalid option will reture '?'
                print_usage( stderr, 1 );

            case -1:    // done with options
                break;

            default:
                abort();
        }
    }
    while ( next_option != -1 );

    /* Done with options. OPTIND points to first nonoption argument.
    * For demonstration purposes, print them if the verbose option was
    * specified. 
    */
    if( verbose )
    {
        int i;
        for( i = optind; i < argc; ++i)
            printf("Argument: %s\n", argv[1]);
    }

    return 0;
}

