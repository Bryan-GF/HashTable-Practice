
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Hash table key/value pair with linked list pointer
 ****/
typedef struct LinkedPair {
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/****
  Hash table with linked pairs
 ****/
typedef struct HashTable {
  int capacity;
  LinkedPair **storage;
} HashTable;

/****
  Create a key/value linked pair to be stored in the hash table.
 ****/
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = strdup(key);
  pair->value = strdup(value);
  pair->next = NULL;

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/****
  Fill this in.

  All values in storage should be initialized to NULL
 ****/
HashTable *create_hash_table(int capacity)
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(LinkedPair));
  return ht;
}

/****
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 ****/
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  
  int hashed = hash(key, ht->capacity);
  
  LinkedPair *newpair = create_pair(key, value);
  
  LinkedPair *iteratepair = ht->storage[hashed];
  
 
  if (ht->storage[hashed] != NULL) {
    
    while(iteratepair->next != NULL && iteratepair->key != key) {
      iteratepair = iteratepair->next;
    }
    iteratepair->next = newpair;
    
  } else if (ht->storage[hashed] == NULL) {
      
    ht->storage[hashed] = newpair;
    fprintf(stderr, "Test %s\n", ht->storage[hashed]->value);
    
  }

}

/****
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(HashTable *ht, char *key)
{
  int hashed = hash(key, ht->capacity);
  LinkedPair *iteratepair = ht->storage[hashed];
  while(iteratepair != NULL && strcmp(iteratepair->key, key) != 0) {
    iteratepair = iteratepair->next;
  }
  iteratepair = NULL;
  destroy_pair(iteratepair);
  
  // Remove linkedpair. Free and set to null.

}

/****
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 ****/
char *hash_table_retrieve(HashTable *ht, char *key)
{
  int hashed = hash(key, ht->capacity);
  LinkedPair *iteratepair = ht->storage[hashed];
  while(iteratepair != NULL && strcmp(iteratepair->key, key) != 0) {
    iteratepair = iteratepair->next;
  }
  if(iteratepair != NULL) {
    return iteratepair->value;
  }
  return NULL;
  
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(HashTable *ht)
{
    
  for(int i = 0; i < ht->capacity; i++) {
    while(ht->storage[i] != NULL) {
      LinkedPair *hold = ht->storage[i]->next;
      free(ht->storage[i]);
      ht->storage[i] = hold;
    }
  }
  free(ht->storage);
  free(ht);

}

/****
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 ****/
HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht = malloc(sizeof(HashTable));
  new_ht->capacity = ht->capacity * 2;
  new_ht->storage = calloc(ht->capacity * 2, sizeof(LinkedPair));
  
  for(int i = 0; i < ht->capacity; i++) {
    fprintf(stderr, "Hello\n");
    LinkedPair *iterator = ht->storage[i];
    
    while(iterator != NULL) {
      fprintf(stderr, "Last");
      hash_table_insert(new_ht, iterator->key, iterator->value);
      fprintf(stderr, "Testeee");
      iterator = iterator->next;
      fprintf(stderr, "Check\n %s", iterator);
    }
  }
  
  destroy_hash_table(ht);
  return new_ht;
}


#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");
  
  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));
  
  
  int old_capacity = ht->capacity;
  ht = hash_table_resize(ht);
  int new_capacity = ht->capacity;
  
  printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
