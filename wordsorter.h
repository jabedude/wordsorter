#ifndef WS_H
#define WS_H

/* Definitions */
#define OPTS "c:rnlsauh"
#define TOK_DELIM " \r\n\t\a"

/* Prototypes */
void usage(char *p_name);
char *read_file(char *file);
char **tok_strings(char *words);
int sort_str(const void *str1, const void *str2);

#endif
