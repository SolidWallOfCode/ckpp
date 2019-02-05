#!/bin/sh
PATCH="$(cat <<'PATCH'
diff --git a/src/ck_ht_hash.h b/src/ck_ht_hash.h
index cd3d7a5..f2e65b0 100644
--- a/src/ck_ht_hash.h
+++ b/src/ck_ht_hash.h
@@ -195,12 +195,12 @@ static inline uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed

   switch(len & 7)
   {
-  case 7: h ^= (uint64_t)(data2[6]) << 48;
-  case 6: h ^= (uint64_t)(data2[5]) << 40;
-  case 5: h ^= (uint64_t)(data2[4]) << 32;
-  case 4: h ^= (uint64_t)(data2[3]) << 24;
-  case 3: h ^= (uint64_t)(data2[2]) << 16;
-  case 2: h ^= (uint64_t)(data2[1]) << 8;
+  case 7: h ^= (uint64_t)(data2[6]) << 48; // FALLTHROUGH
+  case 6: h ^= (uint64_t)(data2[5]) << 40; // FALLTHROUGH
+  case 5: h ^= (uint64_t)(data2[4]) << 32; // FALLTHROUGH
+  case 4: h ^= (uint64_t)(data2[3]) << 24; // FALLTHROUGH
+  case 3: h ^= (uint64_t)(data2[2]) << 16; // FALLTHROUGH
+  case 2: h ^= (uint64_t)(data2[1]) << 8; // FALLTHROUGH
   case 1: h ^= (uint64_t)(data2[0]);
           h *= m;
   };
PATCH
)"

if (echo "${PATCH}" | patch -p1 --forward --reject-file -) ; then
  echo Patched CK
fi

exit 0
