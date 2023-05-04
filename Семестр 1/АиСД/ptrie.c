#include <stdio.h>
#include <stdlib.h>

#define ALPHABET 26

typedef struct trie {
    long long count;
    char terminal;
    struct trie* Vertex[ALPHABET];
} ptrie;

    ptrie* root;

    ptrie* BuildPrefixTree() {
        ptrie* child = malloc(sizeof(ptrie));

        for (int i = 0; i < ALPHABET; i++) {
            child->Vertex[i] = 0;
        }

        child->count = 0;
        child->terminal = 0;

        return child;
    }

void Insert(char* string) {
    ptrie* child = root;

    child->count++;
    for (int i = 0; string[i] != '\0'; i++) {
        int letter = string[i] - 'a';
        if (!child->Vertex[letter]) {
            child->Vertex[letter] = BuildPrefixTree();
        }
        child = child->Vertex[letter];
        child->count++;
    }

    child->terminal = 1;
}

char Contains(char* string) {
    ptrie* child = root;

    for (int i = 0; string[i] != '\0'; i++) {
        int letter = string[i] - 'a';
        if (!child->Vertex[letter]) {
            return 0;
        }
        child = child->Vertex[letter];
    }

    return child->terminal;
}


long long CountPrefixes(char* string) {
    ptrie* child = root;

    for (int i = 0; string[i] != '\0'; i++) {
        int letter = string[i] - 'a';
        child = child->Vertex[letter];
        if (!child) {
            return 0;
        }
    }

    return child->count;
}

void Delete(char* string) {
    ptrie* child = root;

    child->count--;
    for (int i = 0; string[i] != '\0'; i++) {
        int letter = string[i] - 'a';
        child = child->Vertex[letter];
        child->count--;
    }

    child->terminal = 0;
}

void CleanPrefixTree(ptrie* trie) {
    if (trie) {
        for (int i = 0; i < ALPHABET; ++i) {
            if (trie->Vertex[i]) {
                CleanPrefixTree(trie->Vertex[i]);
            }
        }
        free(trie);
    }
}

int main()  {
    root = BuildPrefixTree();

    char* type;
    while (1) {
        scanf("%ms", &type);

        if (type[0] == 'E') {
            free(type);
            break;
        }

        if (type[0] == 'I') {
            char* string;
            scanf("%ms", &string);
            if (!Contains(string)) {
                Insert(string);
            }
            free(string);
        }

        if (type[0] == 'D') {
            char* str;
            scanf("%ms", &str);
            if (Contains(str)) {
                Delete(str);
            }
            free(str);
        }

        if (type[0] == 'P') {
            char* str;
            scanf("%ms", &str);
            printf("%lld ", CountPrefixes(str));
            free(str);
        }

        free(type);
    }

    CleanPrefixTree(root);

    return 0;
}