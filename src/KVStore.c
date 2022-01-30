#include "KVStore.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 32
#define MAX_VALUE_LENGTH 128
#define KV_CAPACITY_START 10
#define KV_CAPACITY_INCREASE 5
#define KV_CAPACITY_MAX 2048

static char** keys;
static char** values;
static int size;
static int capacity;

int kvs_init() {
    capacity = KV_CAPACITY_START;
    keys = malloc(capacity * sizeof(char*));
    values = malloc(capacity * sizeof(char*));
    size = 0;
}

int kvs_load(const char* path) {
    FILE* in = fopen(path, "r");
    if (in == NULL) {
        fprintf(stderr, "Given file can not be opened.\n");
        return 1;
    }

    errno = 0;
    int result = 0;
    const char* key = malloc(MAX_KEY_LENGTH);
    const char* value = malloc(MAX_VALUE_LENGTH);
    while (result != EOF) {
        result = fscanf(in, "%s %s\n", key, value);
        if (result != EOF) {
            kvs_add(key, value);
        }
    }

    if (ferror(in) != 0) {
        fprintf(stderr, "Error while reading the file: %s\n", strerror(errno));
    }
    fclose(in);
}

int kvs_add(const char* key, const char* value) {
    assert(size < KV_CAPACITY_MAX);
    if (kvs_find(key) != -1) {
        fprintf(stderr, "Key '%s' is already contained in store.\n", key);
        return 0;
    }
    if (size >= capacity) {
        kvs_enlarge_store();
    }

    int key_len = strlen(key);
    int value_len = strlen(value);

    keys[size] = malloc(key_len);
    values[size] = malloc(value_len);
    memcpy(keys[size], key, key_len);
    memcpy(values[size], value, value_len);

    size++;
}

const char* kvs_get(const char* key) {
    int index = kvs_find(key);
    if (index >= 0) {
        return values[index];
    }
    return NULL;
}

int kvs_remove(const char* key) {
    int index = kvs_find(key);
    if (index >= 0) {
        return kvs_remove_at(index);
    }
    return 0;
}

int kvs_remove_at(int index) {
    if (index >= 0 && index < size) {
        free(keys[index]);
        free(values[index]);
        size--;
        if (index != size) {
            keys[index] = keys[size];
            values[index] = values[size];
            keys[size] = NULL;
            values[size] = NULL;
        }
        return 1;
    }
    return 0;
}

int kvs_get_size() { return size; }

int kvs_get_capacity() { return capacity; }

int kvs_save(const char* path, bool replace) {
    char* mode;
    if (replace) {
        mode = "w";
    } else {
        mode = "a";
    }
    FILE* out = fopen(path, mode);
    if (out == NULL) {
        fprintf(stderr, "Given file can not be opened.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (keys[i] == NULL) continue;
        fprintf(out, "%s %s\n", keys[i], values[i]);
    }

    if (ferror(out) != 0) {
        fprintf(stderr, "Error while writing to file: %s\n", strerror(errno));
    }
    fclose(out);
}

void kvs_cleanup() {
    for (int i = size - 1; i >= 0; i--) {
        kvs_remove_at(i);
    }
    free(keys);
    free(values);
}

static void kvs_enlarge_store() {
    capacity += KV_CAPACITY_INCREASE;
    keys = realloc(keys, capacity * sizeof(char*));
    values = realloc(values, capacity * sizeof(char*));
}

static int kvs_find(const char* key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(key, keys[i]) == 0) {
            return i;
        }
    }
    return -1;
}
