#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    char* key;
    int value;
} Entry;

typedef struct {
    Entry* entries;
} HashTable;

// Convert string to integer
unsigned int stringtoint(char* key) {
    unsigned int num = 0;
    while (*key) {
        num += *key++;
    }
    return num;
}

// Hash function using division method and stringtoint
unsigned int hash(const char* key) {
    unsigned long hash = stringtoint(key);
    return hash % TABLE_SIZE;
}

// Create a new hash table
HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    table->entries = calloc(TABLE_SIZE, sizeof(Entry));
    return table;
}

// Insert a key-value pair into the hash table using linear probing
void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key);
    while (table->entries[index].key != NULL) {
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    table->entries[index].key = _strdup(key);
    table->entries[index].value = value;
}

// Retrieve a value from the hash table
int get(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    while (table->entries[index].key != NULL) {
        if (strcmp(table->entries[index].key, key) == 0) {
            return table->entries[index].value;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    return -1; // Indicate that the key was not found
}

// Free the memory used by the hash table
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table->entries[i].key != NULL) {
            free(table->entries[i].key);
        }
    }
    free(table->entries);
    free(table);
}

// Function to read the file and populate the hash table
void read_file_and_populate_table(const char* filename, HashTable* table) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    int num_components;
    fscanf(file, "%d", &num_components);

    char key[256];
    for (int i = 0; i < num_components; ++i) {
        fscanf(file, "%s", key);
        insert(table, key, i);
    }

    fclose(file);
}

// Function to check if a character is in the search string
int is_in_search_string(const char* search_string, char character) {
    return strchr(search_string, character) != NULL;
}

// Function to search for keys starting with any of the specified alphabets
void search_by_alphabets(HashTable* table, const char* alphabets) {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table->entries[i].key != NULL && is_in_search_string(alphabets, table->entries[i].key[0])) {
            printf("%s\n", table->entries[i].key);
            found = 1;
        }
    }
    if (!found) {
        printf("키워드가 조내하지 않습니다. 혹은 버킷 주소 xxx에 저장된 키워드입니다.\n");
    }
}

int main(int argc, char* argv[]) {
    HashTable* table = create_table();

    read_file_and_populate_table(argv[1], table);

    char input[256];
    while (1) {
        printf("검색할 키워드를 입력하시오 ");
        scanf("%s", input);

        if (strcmp(input, "quit") == 0) {
            break;
        }
        else {
            printf("'%s'로 시작하는 단어:\n", input);
            search_by_alphabets(table, input);
        }
    }

    free_table(table);
    return 0;
}
