#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    Entry** entries;
} HashTable;

// Hash function
unsigned int hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    value = value % TABLE_SIZE;
    return value;
}

// Create a new entry
Entry* create_entry(const char* key, int value) {
    Entry* entry = malloc(sizeof(Entry));
    entry->key = malloc(strlen(key) + 1);
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// Create a new hash table
HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    table->entries = malloc(sizeof(Entry*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table->entries[i] = NULL;
    }
    return table;
}

// Insert a key-value pair into the hash table
void insert(HashTable* table, const char* key, int value) {
    unsigned int slot = hash(key);
    Entry* prev = NULL;
    Entry* entry = table->entries[slot];
    if (entry == NULL) {
        table->entries[slot] = create_entry(key, value);
        return;
    }

    
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    prev->next = create_entry(key, value);
}

// Retrieve a value from the hash table
int get(HashTable* table, const char* key) {
    unsigned int slot = hash(key);
    Entry* entry = table->entries[slot];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return -1; // Indicate that the key was not found
}

// Free the memory used by the hash table
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Entry* entry = table->entries[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->entries);
    free(table);
}

// Function to read the file and populate the hash table
void read_file_and_populate_table(const char* filename, HashTable* table) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
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
    for (int i = 0; i < strlen(search_string); ++i) {
        if (search_string[i] == character) {
            return 1;
        }
    }
    return 0;
}

// Function to search for keys starting with any of the specified alphabets
void search_by_alphabets(HashTable* table, const char* alphabets) {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Entry* entry = table->entries[i];
        while (entry != NULL) {
            if (is_in_search_string(alphabets, entry->key[0])) {
                printf("%s\n", entry->key);
                found = 1;
            }
            entry = entry->next;
        }
    }
    if (!found) {
        printf("키워드가 존재하지 않습니다. 혹은 버킷 주소 xxx에 저장된 키워드입니다.\n");
    }
}

int main(int argc,char* argv[]) {
    HashTable* table = create_table();

    read_file_and_populate_table(argv[1], table);

    char input[256];
    while (1) {
        printf("검색할 키워드를 입력하시오...");
        scanf("%s", input);

        if (strcmp(input, "quit") == 0) {
            break;
        }
        else {
            printf("%s:\n", input);
            search_by_alphabets(table, input);
        }
    }

    free_table(table);
    return 0;
}
