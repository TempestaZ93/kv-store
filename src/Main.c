#include <stdio.h>

#include "KVStore.h"

int main(int argc, char* argv[]) {
    kvs_init();
    printf("KV Store with size of %d and capacity of %d\n", kvs_get_size(),
           kvs_get_capacity());
    kvs_load("store.db");
    kvs_add("key11", "value11");
    kvs_add("key12", "value12");
    kvs_add("key13", "value13");
    kvs_add("key14", "value14");
    printf("KV Store with size of %d and capacity of %d\n", kvs_get_size(),
           kvs_get_capacity());
    kvs_remove("key12");
    kvs_save("store.db", true);
    kvs_cleanup();
    return 0;
}
