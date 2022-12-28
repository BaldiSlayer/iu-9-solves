
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

char cmp(size_t a, size_t b) {
    if (a < b) {
        return -1;
    }
    if (a == b) {
        return 0;
    }
    return 1;
}

typedef struct {
    // само слово
    char* p;
    // длина этого слова
    int len;
} Word;

typedef struct {
    size_t sz;
    Word* data;
    size_t _i_sz;
} words_array_t;

words_array_t* words;

words_array_t* make_words_array() {
    words_array_t* arr = malloc(sizeof(words_array_t));
    arr->sz = 0;
    arr->data = calloc(10, sizeof(Word));
    arr->_i_sz = 10;
    return arr;
}

void push_back(Word word) {
    if (words->sz == words->_i_sz) {
        words->_i_sz *= 2;
        words->data = realloc(words->data, words->_i_sz * sizeof(Word));
    }
    words->data[words->sz] = word;
    words->sz++;
}

void cleanup_words_array(words_array_t* arr) {
    if (arr) {
        free(arr->data);
    }
    free(arr);
}

int find_words(char* str, words_array_t** words) {
    *words = make_words_array();
    int words_count = 0;
    char prev = ' ';
    char* cur = str;
    while (*cur != '\0') {
        if (isspace(prev) && !isspace(*cur)) {
            char* start = cur;
            while (*cur != '\0' && !isspace(*cur)) {
                ++cur;
            }
            push_back((Word){start, cur - start});
            words_count++;
        } else {
            cur++;
        }
    }
    return words_count;
}

void sorted_string_recovery(size_t words_count, size_t* count, words_array_t* words, char* dest) {
    int dest_index = 0;
    for (size_t i = 0; i < words_count; ++i) {
        size_t j = 0;
        while (count[j] != i) {
            j++;
        }
        size_t ind = 0;
        for (char* p = words->data[j].p; !isspace(*p) && ind < words->data[j].len; ++p) {
            ind++;
            dest[dest_index] = *p;
            dest_index++;
        }
        if (i + 1 != words_count) {
            dest[dest_index] = ' ';
            dest_index++;
        }
        dest[dest_index] = '\0';
    }
}

void csort(char* src, char* dest) {
    words = NULL;
    size_t words_count = find_words(src, &words);
    if (!words_count) {
        return;
    }
    size_t* count = calloc(words_count, sizeof(size_t));
    for (size_t i = 0; i < words_count - 1; ++i) {
        for (size_t j = i + 1; j < words_count; ++j) {
            if (cmp(words->data[i].len, words->data[j].len) <= 0) {
                count[j]++;
            } else {
                count[i]++;
            }
        }
    }
    sorted_string_recovery(words_count, count, words, dest);
    cleanup_words_array(words);
    free(count);
}

signed main() {
    char* str = 0;
    size_t sz = 0;
    getline(&str, &sz, stdin);
    char* ans = calloc(sz, sizeof(char));
    csort(str, ans);
    puts(ans);
    free(ans);
    free(str);
    return 0;
}
