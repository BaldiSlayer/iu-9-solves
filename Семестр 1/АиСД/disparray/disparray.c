#include <stdio.h>
#include <stdlib.h>

long long m;

long long hash(long long key) {
    return key % m;
}


list_t* hash_table;

void InsertToHashTable() {

}

void GetFromHashTable() {
    
}

int main() {
    scanf("%lld", &m);

    //BuildHashTable();

    int i, v;
    while (1) {
        char *type;
        scanf("%ms", &type);

        if (type[0] == 'E') {
            free(type);
            break;
        }

        // ASSIGN
        if (type[1] == 'S') {
            scanf("%d%d", &i, &v);
            // disparray_insert(disparray, i, v);
        }

        // AT
        if (type[1] = 'T') {
            scanf("%d", &i);
            //printf("%d\n", disparray_get(disparray, i));
        }

        free(type);
    }

    return 0;
}
