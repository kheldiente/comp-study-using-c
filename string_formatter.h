#ifndef GUARD_H
#define GUARD_H
char* remove_substring(char *input, char* sub);
char* remove_leading_spaces(char* input);
char* remove_trailing_spaces(char* input);
char* normalize_char_data(char* buffer, char *startTag, char* endTag);
int normalize_int_data(char* buffer, char* startTag, char* endTag);
#endif