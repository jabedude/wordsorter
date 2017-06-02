#ifndef WS_H
#define WS_H

/* Definitions */
#define OPTS "c:rnlsauph"
#define TOK_DELIM " \r\n\t\a"

/* Prototypes */
void usage(char *p_name);
char *read_file(char *file);
char *read_stdin(void);
char **tok_strings(char *words, bool p_flg);
int str_sort(const void *str1, const void *str2);
int len_sort(const void *str1, const void *str2);
int num_sort(const void *str1, const void *str2);
int scrab_sort(const void *str1, const void *str2);

#endif
