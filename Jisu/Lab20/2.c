#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct entry {
    char key[100];
    int value;
    struct entry* next;
} entry;

entry* hashTable[13];

int stringToInt(char *key) {
    unsigned int number = 0;
    while (*key)
        number += *key++;
    return number % 13;
}

void insert(char *key, int value) {
    unsigned int bucket = stringToInt(key);
    entry* newEntry;
    MALLOC(newEntry, sizeof(entry));
    strcpy(newEntry->key, key);
    newEntry->value = value;
    newEntry->next = hashTable[bucket];
    hashTable[bucket] = newEntry;
}

int search(char *key) {
    unsigned int bucket = stringToInt(key);
    entry* e = hashTable[bucket];
    while (e) {
        if (!strcmp(e->key, key)) return bucket;
        e = e->next;
    }
    return -1;
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (!f) exit(1);

    int num;
    char *word, *input;
    fscanf(f, "%d", &num);

    for(int i = 0; i < 13; i++)
        hashTable[i] = NULL;

    MALLOC(word, sizeof(char) * num);
    for (int i = 0; i < num; i++) {
        fscanf(f, "%s", word);
        insert(word, i+1);
    }

    fclose(f);

    MALLOC(input, sizeof(char) * num);
    while (1) {
        printf("> �˻��� Ű���带 �Է��Ͻÿ�...\n");
        scanf("%s", input);

        if (!strcmp(input, "quit")) break;

        num = search(input);
        if (num == -1) printf("Ű���尡 �������� �ʽ��ϴ�.\n");
        else printf("��Ŷ �ּ� %d�� ����� Ű�����Դϴ�.\n", num);
    }
    free(word);
    free(input);

    return 0;
}