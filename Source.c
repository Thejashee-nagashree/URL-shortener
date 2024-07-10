git//url shortner
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define hash_table_size 1000
#define short_len 20

// Struct containing long and short url's
typedef struct {
    char long_url[100];
    char short_url[short_len];
} URLPair;

// Hash function to generate short URL from long URL
int hash(char* str) {
    int hash = 0;
    for (int i = 0; str[i]; i++)
        hash = (hash * 31 + str[i]) % hash_table_size;
    return hash;
}

// Hash table to store URL pairs
URLPair table[hash_table_size];

// Function to generate a unique short URL
void generateShortURL(char* long_url, char* short_url) {
    int hash_index = hash(long_url);
    int i = 0;
    while (table[(hash_index + i) % hash_table_size].long_url[0])
        i++;
    sprintf(short_url, "%d%d%d", hash_index, i, rand() % 100);
}

// Function to store a URL pair in the hash table
void storeURL(char* long_url) {
    char short_url[ short_len];
    generateShortURL(long_url, short_url);
    int index = hash(long_url);
    strcpy(table[index].long_url, long_url);
    strcpy(table[index].short_url, short_url);
}

// Function to get long URL from short URL
char* getLongURL(char* short_url) {
    for (int i = 0; i < hash_table_size; i++)
        if (!strcmp(table[i].short_url, short_url))
            return table[i].long_url;
    return NULL;
}

// Function to load hash table from file
void loadTable() {
    FILE* fp = fopen("table.txt", "r");
    if (fp == NULL)
        return;
    int index = 0;
    while (fscanf(fp, "%s %s", table[index].long_url, table[index].short_url) != EOF)
        index++;
    fclose(fp);
}

// Function to save hash table to file
void saveTable() {
    FILE* fp = fopen("table.txt", "w");
    if (fp == NULL)
        return;
    for (int i = 0; i < hash_table_size; i++)
        if (table[i].long_url[0])
            fprintf(fp, "%s %s\n", table[i].long_url, table[i].short_url);
    fclose(fp);
}

int main() {
    // Load hash table from file
    loadTable();

    printf("  *   *   *   *   *   *   *   *   *   *   *   *\n");
    printf("* U * R * L * S * H * O * R * T * E * N * E * R *\n");
    printf("  *   *   *   *   *   *   *   *   *   *   *   *\n\n\n");
    // Input long URL
    char long_url[10000];
    printf("Enter a long URL: ");
    scanf("%s", long_url);

    // Check if long URL is already present in hash table
    int index = hash(long_url);
    char* short_url = NULL;
    for (int i = 0; i < hash_table_size; i++) {
        if (!strcmp(table[(index + i) % hash_table_size].long_url, long_url)) {
            short_url = table[(index + i) % hash_table_size].short_url;
            break;
        }
    }

    // If long URL is not present, store URL pair in hash table
    if (!short_url) {
        storeURL(long_url);
        short_url = table[hash(long_url)].short_url;
        // Save hash table to file
        saveTable();
    }

    // Get short URL from hash table
    printf("Short URL: http://tiny.url/%s\n", short_url);

    // Get long URL from short URL
    char* retrieved_long_url = getLongURL(short_url);
    printf("Retrieved Long URL: %s\n", retrieved_long_url);

    return 0;
}


















