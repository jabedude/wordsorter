#include <ctype.h>
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
    bool r_flg = 0, n_flg = 0, l_flg = 0, s_flg = 0, a_flg = 1, u_flg = 0, p_flg = 0, h_flg = 0;

    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
            case 'c':
                c_val = atoi(optarg);
                if (!c_val) {
                    usage(argv[0]);
                    return 1;
                }
                break;
            case 'r':
                r_flg = !r_flg;
                break;
            case 'n':
                n_flg = true;
                s_flg = false;
                l_flg = false;
                a_flg = false;
                break;
            case 'l':
                l_flg = true;
                n_flg = false;
                s_flg = false;
                a_flg = false;
                break;
            case 's':
                s_flg = true;
                l_flg = false;
                n_flg = false;
                a_flg = false;
                break;
            case 'a':
                a_flg = true;
                s_flg = false;
                l_flg = false;
                n_flg = false;
                break;
            case 'u':
                u_flg = true;
                break;
            case 'p':
                p_flg = true;
                break;
            case 'h':
                h_flg = true;
                break;
            default:
                usage(argv[0]);
                return 1;
        }
    }

    if (h_flg) {
        usage(argv[0]);
        return 0;
    }
#ifdef DEBUG
    printf("DEBUG: optind argv is: %s\n", argv[optind]);
    printf("DEBUG: number of files is: %d\n", argc - optind);
#endif

    /* If user passed filenames on command line */
    if (argc - optind) {
        for (int i = optind; i < argc; i++) {
            f_words = read_file(argv[i]);
#ifdef DEBUG
            printf("DEBUG: File %s contains %s\n", argv[i], f_words);
            printf("DEBUG: Strlen is %ld\n", strlen(f_words));
#endif
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
    } else {
        all_words = read_stdin();
    }

    toks = tok_strings(all_words, p_flg);
    int tmp = 0, len = 0;
    while (toks[tmp]) {
#ifdef DEBUG
        printf("DEBUG: tok %d is: %s\n", tmp, toks[tmp]);
#endif
        tmp++;
        len++;
    }

#ifdef DEBUG
    printf("DEBUG: tmp is %d\n", tmp);
#endif
    if (s_flg)
        qsort(toks, tmp, sizeof(char *), scrab_sort);
    else if (l_flg)
        qsort(toks, tmp, sizeof(char *), len_sort);
    else if (n_flg)
        qsort(toks, tmp, sizeof(char *), num_sort);
    else if (a_flg)
        qsort(toks, tmp, sizeof(char *), str_sort);
    else {
        usage(argv[0]);
        return 1;
    }

    if (u_flg) {
        if (r_flg) {
            tmp--;
            while (tmp >= 0) {
                if (c_val && (tmp + 1 == len - c_val))
                    break;
                if (tmp + 1 == len)
                    printf("%s\n", toks[tmp]);
                else if (strcmp(toks[tmp], toks[tmp + 1]))
                    printf("%s\n", toks[tmp]);
                tmp--;
            }
        } else {
            tmp = 0;
            while (toks[tmp]) {
                if (tmp + 1 == len)
                    printf("%s\n", toks[tmp]);
                else if (strcmp(toks[tmp], toks[tmp + 1]))
                    printf("%s\n", toks[tmp]);
                if (c_val && tmp == c_val)
                    break;
                tmp++;
            }
        }
    } else {
        if (r_flg) {
            tmp--;
            while (tmp >= 0) {
                if (c_val && (tmp + 1 == len - c_val))
                    break;
                printf("%s\n", toks[tmp]);
                tmp--;
            }
        } else {
            tmp = 0;
            while (toks[tmp]) {
                if (c_val && tmp == c_val)
                    break;
                printf("%s\n", toks[tmp]);
                tmp++;
            }
        }
    }

    free(toks);
    free(all_words);
    return 0;
}

char *read_stdin(void)
{
    int buffsz = 64;
    char *words = (char *) malloc(sizeof(char) * buffsz);
    int p, pos = 0;

    if (!words) {
        fprintf(stderr, "Malloc error!\n");
        return NULL;
    }

    while (true) {
        p = getchar();
        if (p == EOF) {
            words[pos] = '\0';
            return words;
        } else if (p == '\t' || p == '\n') {
            words[pos] = ' ';
        } else {
            words[pos] = p;
        }
        pos++;

        if (pos >= buffsz) {
            buffsz += buffsz;
            words = (char *) realloc(words, buffsz);

            if (!words) {
                fprintf(stderr, "Malloc error!\n");
                return NULL;
            }
        }
    }
}

int num_sort(const void *str1, const void *str2)
{
    const int r1 = atoi(*(const char **) str1);
    const int r2 = atoi(*(const char **) str2);
    return (r1 > r2);
}

int len_sort(const void *str1, const void *str2)
{
    const char *r1 = *(const char **) str1;
    const char *r2 = *(const char **) str2;
    size_t one_sz = strlen(r1);
    size_t two_sz = strlen(r2);

    return (one_sz > two_sz);
}

int str_sort(const void *str1, const void *str2)
{
    const char *r1 = *(const char **) str1;
    const char *r2 = *(const char **) str2;
    return strcmp(r1, r2);
}

int scrab_sort(const void *str1, const void *str2)
{
    int scr1 = 0, scr2 = 0;
    char c;
    const char *r1 = *(const char **) str1;
    const char *r2 = *(const char **) str2;
#ifdef DEBUG
    printf("DEBUG: r1 is %s\n", r1);
#endif

    for (size_t i = 0; i < strlen(r1); i++) {
        c = tolower(r1[i]);
        if (c == 'e' || c == 'a' || c == 'i' || c == 'o' || c == 'n' || 
            c == 'r' || c == 't' || c == 'l' || c == 's' || c == 'u')
                scr1++;
        else if (c == 'd' || c == 'g')
            scr1 += 2;
        else if (c == 'b' || c == 'c' || c == 'm' || c == 'p')
            scr1 += 3;
        else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y')
            scr1 += 4;
        else if (c == 'k')
            scr1 += 5;
        else if (c == 'j' || c == 'x')
            scr1 += 8;
        else if (c == 'q' || c == 'z')
            scr1 += 10;
        else
            scr1 += 0;
    }
    for (size_t i = 0; i < strlen(r2); i++) {
        c = tolower(r2[i]);
        if (c == 'e' || c == 'a' || c == 'i' || c == 'o' || c == 'n' || 
            c == 'r' || c == 't' || c == 'l' || c == 's' || c == 'u')
                scr2++;
        else if (c == 'd' || c == 'g')
            scr2 += 2;
        else if (c == 'b' || c == 'c' || c == 'm' || c == 'p')
            scr2 += 3;
        else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y')
            scr2 += 4;
        else if (c == 'k')
            scr2 += 5;
        else if (c == 'j' || c == 'x')
            scr2 += 8;
        else if (c == 'q' || c == 'z')
            scr2 += 10;
        else
            scr2 += 0;
    }

#ifdef DEBUG
    printf("DEBUG: Score %s is %d. Score %s is %d\n", r1, scr1, r2, scr2);
#endif

    return (scr1 > scr2);
}

char **tok_strings(char *words, bool p_flg)
{
    int buffsz = 1;

    for (size_t i = 0;  i < strlen(words); i++) {
        if (isspace(words[i]))
            buffsz++;
    }

    char **toks = (char **) malloc(sizeof(char**) * buffsz);
    char *tok;
    int pos = 0;

    tok = strtok(words, " ");
    while (tok != NULL) {
        if (p_flg) {
            if (ispunct(tok[strlen(tok) - 1]))
                tok[strlen(tok) - 1] = '\0';
        }
        toks[pos] = tok;
        pos++;

        if (pos >= buffsz) {
#ifdef DEBUG
            printf("DEBUG: bufsz is: %d\n", buffsz);
            printf("DEBUG: pos is: %d\n", pos);
#endif
            buffsz += buffsz;
#ifdef DEBUG
            printf("DEBUG: bufsz before realloc is: %d\n", buffsz);
#endif
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

#ifdef DEBUG
    printf("DEBUG: filename: %s\n", file);
#endif
    fp = fopen(file, "r");
    if (!fp)
        return NULL;
    fseek(fp, 0, SEEK_END);
    file_sz = ftell(fp);
#ifdef DEBUG
    printf("DEBUG: file %s size is: %ld\n", file, file_sz);
#endif
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
            "-c\t<number of lines to print>\n"
            "-r\tprint in reverse order\n"
            "-n\tsort words as if they were numbers\n"
            "-l\tsort by length\n"
            "-s\tsort by score in scrabble\n"
            "-a\tsort lexographically\n"
            "-u\tonly print unique words\n"
            "-h\tprint this help message\n", p_name);
}
