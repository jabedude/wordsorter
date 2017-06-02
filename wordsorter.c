#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "wordsorter.h"

int main (int argc, char **argv)
{
    char *f_words;
    char *all_words = NULL;
    char **toks = NULL;
    size_t tot_sz = 0;
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

    printf("DEBUG: optind argv is: %s\n", argv[optind]);
    printf("DEBUG: number of files is: %d\n", argc - optind);

    if (argc - optind) {
        for (int i = optind; i < argc; i++) {
            f_words = read_file(argv[i]);
            printf("DEBUG: File %s contains %s\n", argv[i], f_words);
            printf("DEBUG: Strlen is %ld\n", strlen(f_words));
            tot_sz += strlen(f_words);
            if (all_words) {
                all_words = (char *) realloc(all_words, sizeof(char) * tot_sz + 1);
                strcat(all_words, f_words);
            } else {
                all_words = (char *) malloc(1 + sizeof(char) * strlen(f_words) + 1);
                strcpy(all_words, f_words);
            }
            free(f_words);
        }
    }

    toks = tok_strings(all_words);
    int tmp = 0;
    while (toks[tmp]) {
        printf("DEBUG: tok %d is: %s\n", tmp, toks[tmp]);
        tmp++;
    }

    printf("DEBUG: tmp is %d\n", tmp);
    qsort(toks, tmp, sizeof(char *), sort_str);

    if (r_flg) {
        tmp--;
        while (tmp >= 0) {
            printf("DEBUG: tok after sort %d is: %s\n", tmp, toks[tmp]);
            tmp--;
        }
    } else {
        tmp = 0;
        while (toks[tmp]) {
            printf("DEBUG: tok after sort %d is: %s\n", tmp, toks[tmp]);
            tmp++;
        }
    }


    free(toks);
    free(all_words);
    return 0;
}

int sort_str(const void *str1, const void *str2)
{
    const char *r1 = *(const char **) str1;
    const char *r2 = *(const char **) str2;
    return strcmp(r1, r2);
}

char **tok_strings(char *words)
{
    int buffsz = 64;
    char **toks = (char **) malloc(sizeof(char**) * buffsz);
    char *tok;
    int pos = 0;

    tok = strtok(words, " ");
    while (tok != NULL) {
        toks[pos] = tok;
        pos++;

        if (pos >= buffsz) {
            buffsz += buffsz;
            toks = (char **) realloc(toks, buffsz);
        }
        tok = strtok(NULL, " ");
    }
    toks[pos] = NULL;
    return toks;
}

char *read_file(char *file)
{
    FILE *fp;
    size_t file_sz = 0;
    char c;
    char *words = NULL;
    int pos = 0;

    printf("DEBUG: filename: %s\n", file);
    fp = fopen(file, "r");
    if (!fp)
        return NULL;
    fseek(fp, 0, SEEK_END);
    file_sz = ftell(fp);
    printf("DEBUG: file %s size is: %ld\n", file, file_sz);
    rewind(fp);
    words = (char *) malloc(sizeof(char) * (file_sz + 1));
    while (true) {
        c = fgetc(fp);
        if (c == EOF) {
            words[pos] = '\0';
            fclose(fp);
            return words;
        } else if (c == '\n') {
            words[pos] = ' ';
        } else {
            words[pos] = c;
        }
        pos++;
    }
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
