#include "cat_struct.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_file(char* file_name);

void flag_b(char* file_name);

void flag_n(char* file_name);


int
main(int argc, char** argv) {
    int c;

    while ((c = getopt(argc, argv, "n:b:")) != -1)
        switch (c) {
            case 'b':
                flag_b(optarg);
                break;
            case 'n':
                flag_n(optarg);
                break;
            case '?':
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Try 's21_cat --help' for more information.\n");
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
        }
    // if (c == -1) {
    //     for (int i = 1; i < argc; i++) {
    //         print_file(argv[i]);
    //     }
    // }
    return 0;
}

void print_file(char* file_name) {
    FILE* f = fopen(file_name, "rt");

    if (f != NULL) {
        int c = fgetc(f);
        while (c != EOF) {
            putc(c, stdout);
            c = fgetc(f);
        }
        fclose(f);
    } else {
        printf("No such file or directory");
    }
}

void flag_n(char* file_name) {
    FILE* f = fopen(file_name, "rt");
    char ch = fgetc(f);
    if (f != NULL && ch != EOF) {
        int lines = 0;
        printf("%6d\t", lines + 1);
        while (ch != EOF) {
            putc(ch, stdout);
            if (ch == '\n') {
                lines++;
                printf("%6d\t", lines + 1);
            }
            ch = fgetc(f);
        }
        fclose(f);
    } else if (ch == EOF) {
        fclose(f);
        return;
    } else {
        printf("No such file or directory");
    }
}

void flag_b(char* file_name) {
    FILE* f = fopen(file_name, "rt");
    if (f != NULL) {
        char ch = fgetc(f);
        if (ch != EOF) {
            int lines = 0;
            int letters = 0;
            printf("%6d\t", lines + 1);
            while (ch != EOF) {
                if (ch != '\n')
                    putc(ch, stdout);
                letters += 1;
                if (ch == '\n') {
                    if (letters != 1) {
                        lines++;
                        printf("\t%d", letters);
                        printf("\n%6d\t", lines + 1);
                    }
                    letters = 0;
                }
                ch = fgetc(f);
            }
            fclose(f);
        }
    } else {
        printf("No such file or directory");
    }
}
