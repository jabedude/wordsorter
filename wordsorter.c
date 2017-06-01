#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "wordsorter.h"

int main (int argc, char **argv)
{
    int opt = 0;
    int c_val = 0;
    bool r_flg = 0, n_flg = 0, l_flg = 0, s_flg = 0, a_flg = 0, u_flg = 0, h_flg = 0;

    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
            case 'c':
                c_val = atoi(optarg);
                break;
            case 'r':
                r_flg = true;
                break;
            case 'n':
                n_flg = true;
                break;
            case 'l':
                l_flg = true;
                break;
            case 's':
                s_flg = true;
                break;
            case 'a':
                a_flg = true;
                break;
            case 'u':
                a_flg = true;
                break;
            case 'h':
                h_flg = true;
                break;
        }
    }

    if (h_flg) {
        usage(argv[0]);
        return 0;
    }

    return 0;
}

void usage(char *p_name)
{
    fprintf(stderr,
            "Usage: %s [OPTIONS] ... [FILE]\n"
            "-c\t<number>\n"
            "-r\tprint in reverse order\n"
            "-n\tsort words as if they were numbers\n"
            "-l\tsort by length\n"
            "-s\tsort by score in scrabble\n"
            "-a\tsort lexographically\n"
            "-u\tonly print unique words\n", p_name);
}
