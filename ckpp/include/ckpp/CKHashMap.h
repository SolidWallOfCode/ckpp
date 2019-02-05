/** @file

    CKHashMap is a concurrent hash map, implemented as a wrapper on the Concurrency Kit
    "robin hood hash set".

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

#include <memory>

// Forward declares
extern "C" {
  struct ck_rhs;
}

namespace swoc {

namespace detail {

class CKBaseHashMap {

public:
  using hash_value_t = unsigned long;
  using Hash = hash_value_t (*)(void const*, hash_value_t);
  using Equal = bool (*)(void const * lhs, void const *);
  CKBaseHashMap(Equal equal, Hash hash);
  ~CKBaseHashMap();

  bool insert(void * obj, hash_value_t hash_value);

protected:
  ck_rhs* _table = nullptr;

};

} // namespace detail

template<typename T, bool (*EQUAL)(T const *, T const *), detail::CKBaseHashMap::hash_value_t (*HASH)(T const *)>
class CKHashMap {
  detail::CKBaseHashMap _table;
public:
  using hash_value_t = detail::CKBaseHashMap::hash_value_t;

  CKHashMap() : _table([](void const* lhs, void const * rhs) -> bool { return EQUAL(static_cast<T*>(lhs), static_cast<T*>(rhs)); }
                      ,[](void const* t, unsigned long) -> unsigned long { return HASH(static_cast<T*>(t)); }) {
  }

  bool insert(T* t) {
    return _table.insert(t, HASH(t));
  }
};

}// namespace swoc
