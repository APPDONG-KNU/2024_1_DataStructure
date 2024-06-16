#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct {
    char key[100];
    int value;
} entry;

entry *hashTable;

int tableSize(int n) {
    int i = n + 1, j, isPrime;

    for(;; i++) {
        isPrime = 1;
        for(j = 2; j * j <= i; j++)
            if(i % j == 0) {
                isPrime = 0;
                break;
            }
        if(isPrime) return i;
    }
}

int stringToInt(char *key, int size) {
    unsigned int number = 0;
    while (*key)
        number += *key++;
    return number % size;
}

void insert(char *key, int value, int size) {
    unsigned int bucket = stringToInt(key, size);
    while (hashTable[bucket].value)
        bucket = (bucket + 1) % size;
    strcpy(hashTable[bucket].key, key);
    hashTable[bucket].value = value;
}

int search(char *key, int size) {
    unsigned int bucket = stringToInt(key, size);
    while (strcmp(hashTable[bucket].key, key)) {
        if (!hashTable[bucket].value)
            return -1;
        bucket = (bucket + 1) % size;
    }
    return bucket; 
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (!f) exit(1);

    int num, size = tableSize(num);
    char *word, *input;
    fscanf(f, "%d", &num);

    MALLOC(hashTable,sizeof(entry) * size);

    MALLOC(word, sizeof(char) * num);
    for (int i = 0; i < num; i++) {
        fscanf(f, "%s", word);
        insert(word, i + 1, size);
    }

    fclose(f);

    MALLOC(input, sizeof(char) * num);
    while (1) {
        printf("> �˻��� Ű���带 �Է��Ͻÿ�...\n");
        scanf("%s", input);

        if (!strcmp(input, "quit")) break;
        
        num = search(input, size);
        if (num == -1) printf("Ű���尡 �������� �ʽ��ϴ�.\n");
        else printf("��Ŷ �ּ� %d�� ����� Ű�����Դϴ�.\n", num);
    }
    free(hashTable);
    free(word);
    free(input);

    return 0;
}