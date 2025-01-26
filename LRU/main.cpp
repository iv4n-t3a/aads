#include <iostream>
#include <unordered_map>

template <typename K, typename T>
class LruCache {
  struct Node;

 public:
  LruCache(size_t size_limit) : size_limit_(size_limit) {}

  void Insert(const K& key, const T& value) {
    if (map_.contains(key)) {
      Use(key);
      map_[key].value = value;
      return;
    }

    map_[key] = {key, value, nullptr, most_used_};
    Node* new_node = &map_[key];

    if (map_.size() == 1) {
      most_used_ = new_node;
      least_used_ = new_node;
    } else {
      most_used_->more_used = new_node;
      most_used_ = new_node;
    }

    if (map_.size() > size_limit_) {
      RemoveLeastUsed();
    }
  }

  T& Get(const K& key) {
    if (not map_.contains(key)) {
      throw std::out_of_range("No such key");
    }
    Use(key);
    return map_[key].value;
  }

  void Remove(const K& key) {
    Use(key);
    RemoveLeastUsed();
  }

  void RemoveLeastUsed() {
    least_used_ = least_used_->more_used;
    map_.erase(least_used_->less_used->key);
    least_used_->less_used = nullptr;
  }

 private:
  void Use(const K& key) {
    Node* node = &map_[key];

    if (node == most_used_) {
      return;
    }

    if (node == least_used_) {
      least_used_ = least_used_->more_used;
      least_used_->less_used = nullptr;
    } else {
      node->less_used->more_used = node->more_used;
      node->more_used->less_used = node->less_used;
    }

    node->less_used = most_used_;
    node->more_used = nullptr;
    most_used_->more_used = node;
    most_used_ = node;
  }

  struct Node {
    K key;
    T value;
    Node* more_used = nullptr;
    Node* less_used = nullptr;
  };

  size_t size_limit_;
  Node* least_used_ = nullptr;
  Node* most_used_ = nullptr;
  std::unordered_map<K, Node> map_;
};

int main() {
  size_t queries;
  size_t size_limit;

  std::cin >> queries >> size_limit;

  LruCache<int, int> lru(size_limit);

  char type;
  int key;
  int value;

  for (size_t i = 0; i < queries; ++i) {
    std::cin >> type >> key;

    if (type == '1') {
      try {
        std::cout << lru.Get(key) << '\n';
      } catch (...) {
        std::cout << "-1\n";
      }
    } else {
      std::cin >> value;
      lru.Insert(key, value);
    }
  }
}
