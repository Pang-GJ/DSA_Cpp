#ifndef ENTRY_H_
#define ENTRY_H_

// 词条模板类
template <typename K, typename V>
struct Entry {
  K key;    // 关键码
  V value;  // 数值

  Entry(K k = K(), V v = V()) : key(k), value(v) {}
  Entry(const Entry<K, V> &e) : key(e.key), value(e.value) {}

  bool operator<(const Entry<K, V> &e) { return key < e.key; }
  bool operator>(const Entry<K, V> &e) { return key > e.key; }
  bool operator==(const Entry<K, V> &e) { return key == e.key; }
  bool operator!=(const Entry<K, V> &e) { return !operator==(e); }
};

#endif  // ENTRY_H_