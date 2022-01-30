#ifndef KV_STORE_H_
#define KV_STORE_H_

#include <stdbool.h>

typedef struct {
    char** keys;
    char** values;
    int size;
    int capacity;
} kv_store;

/**
 * This method initializes the store with its default capacity
 */
int kvs_init();

/**
 * This method loads a store from file.
 *
 * @param path path to the file which holds the store
 *
 * @return 1 if the file could be loaded successfully or 0 if not.
 */
int kvs_load(const char* path);

/**
 * Adds a new key value pair to the store, if it is not already contained.
 *
 * @param key unique key of this pair
 * @param value value corrosponding to the key
 *
 * @return 1 if the pair was added or 0 otherwise.
 */
int kvs_add(const char* key, const char* value);

/**
 * tries to get a value with its key.
 *
 * @param key key of the requested value.
 *
 * @return char pointer with the key, or NULL if the key is not found.
 */
const char* kvs_get(const char* key);

/**
 * Removes the pair identified by this key.
 *
 * @param key key of the pair to remove
 *
 * @return 1 if any pair was found with this key or 0 otherwise.
 */
int kvs_remove(const char* key);

/**
 * Removes the pair at this specific index
 *
 * @param index index in the store if the pair to remove.
 *
 * @return 1 if the index is valid or 0 otherwise.
 */
int kvs_remove_at(int index);

/**
 * @return the size of the store.
 */
int kvs_get_size();

/**
 * @return the capacity of the store.
 */
int kvs_get_capacity();

/**
 * Saves the current state of the store to file.
 *
 * @param path path to the file which should hold the store.
 * @param replace flag to control whether the file should be overridden or not.
 *
 * @return 1 if the file was successfully written or 0 otherwise.
 */
int kvs_save(const char* path, bool replace);

/**
 * Cleans up all allocated memory and resets variables.
 */
void kvs_cleanup();

static void kvs_enlarge_store();
static int kvs_find(const char* key);

#endif  // KV_STORE_H_
