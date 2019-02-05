extern "C" {
#include "ck_ht.h"
}

#include <stdlib.h>
#include <iostream>

void hasher(ck_ht_hash_t * ht, void const * key, size_t key_len, uint64_t seed) {
//  *ht = 0;
}

void * ck_realloc(void * buffer, size_t, size_t n_plus, bool) {
  return realloc(buffer, n_plus);
}

void ck_free(void * buffer, size_t n, bool) {
  free(buffer);
}

int main(int, char**) {
  std::cout << "Start up" << std::endl;
  ck_ht_t table;
  ck_malloc allocator { malloc, ck_realloc, ck_free };
  ck_ht_init(&table, CK_HT_MODE_BYTESTRING, hasher, &allocator, 200, 300);
  std::cout << "Shut down" << std::endl;
  return 0;
}
