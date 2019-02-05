/** @file

    CKHashMap implementation.

    Licensed to the Apache Software Foundation (ASF) under one or more contributor license
    agreements.  See the NOTICE file distributed with this work for additional information regarding
    copyright ownership.  The ASF licenses this file to you under the Apache License, Version 2.0
    (the "License"); you may not use this file except in compliance with the License.  You may
    obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software distributed under the
    License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
    express or implied. See the License for the specific language governing permissions and
    limitations under the License.
 */

#include <ckpp/CKHashMap.h>
#include <swoc/IntrusiveDList.h>

extern "C" {
#include "ck_rhs.h"
}

namespace swoc {

detail::CKBaseHashMap::CKBaseHashMap(Equal equal, Hash hasher) : _table(new ck_rhs) {
  /** Arguments are
   * - Current memory block.
   * - Size of current memory block.
   * - Target size for reallocated memory.
   * - @c true if there are possible read-reclaim races.
   */
  static constexpr auto reallocator = [](void * buffer, size_t, size_t upgrade_size, bool) -> void * {
    return realloc(buffer, upgrade_size);
  };

  /** Arguments are
   * - Current memory block.
   * - Size of current memory block.
   * - @c true if there are possible read-reclaim races.
   */
  static constexpr auto deleter = [] (void * buffer, size_t, bool) -> void{
    free(buffer);
  };

  ck_malloc allocator { malloc, reallocator, deleter };

  ck_rhs_init(_table, CK_RHS_MODE_OBJECT | CK_RHS_MODE_SPMC, hasher, equal, &allocator, 200 /* capacity */, 300 /* seed */);

}

detail::CKBaseHashMap::~CKBaseHashMap() { delete _table; }

bool detail::CKBaseHashMap::insert(void *obj, hash_value_t hash_value) {
  return ck_rhs_put(_table, hash_value, obj);
};

} // namespace swoc
