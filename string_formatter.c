#include "string_formatter.h"
#include <sys/time.h>

char* remove_substring(char *input, char *sub) {
    char *match;
    char *output = input;
    int len = strlen(sub);
    while ((match = strstr(output, sub))) {
        *match = '\0';
        strcat(output, match + len);
    }
    return output;
}
char* remove_leading_spaces(char* input) {
    int i, j;
    char *output = input;
    for (i = 0, j = 0;i<strlen(input); i++,j++){
        if (input[i] != ' ') {                          
            output[j] = input[i];                     
        } else {
            j--;
        }                                     
    }
    output[j] = 0;
    return output;
}

char* remove_trailing_spaces(char* input) {
    int len = strlen(input);
    char *output = input;
    if (output[len - 1] == '\n') {
        output[len - 1] = 0;
    }
    return output;
}

char* normalize_char_data(char* buffer, char *startTag, char* endTag) {
    char *formatted1 = remove_substring(buffer, startTag);
    // printf("\nnormalize_char_data->formatted1: %s", formatted1);
    char *formatted2 = remove_substring(formatted1, endTag);
    // printf("\nnormalize_char_data->formatted2: %s", formatted2);
    char *formatted3 = remove_leading_spaces(formatted2);
    // printf("\nnormalize_char_data->formatted3: %s", formatted3);
    char *output = remove_trailing_spaces(formatted3);
    // printf("\nnormalize_char_data->output: %s", output);
    return output;
}

int normalize_int_data(char* buffer, char* startTag, char* endTag) {
    char *formatted1 = remove_substring(buffer, startTag);
    // printf("\nnormalize_int_data->formatted1: %s", formatted1);
    char *formatted2 = remove_substring(formatted1, endTag);
    // printf("\nnormalize_int_data->formatted2: %s", formatted2);
    char *formatted3 = remove_leading_spaces(formatted2);
    // printf("\nnormalize_int_data->formatted3: %s", formatted3);
    char *output = remove_trailing_spaces(formatted3);
    // printf("\nnormalize_int_data->output: %s", output);
    return atoi(output);
}

int generate_random_id() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    int millis = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return abs(millis + (rand() % 100));
}