#include <stdexcept>
#include <unordered_map>

namespace Aads {

template <typename K, typename T>
class LruCache {
  struct Node;

 public:
  LruCache(size_t size_limit) : size_limit_(size_limit) {}

  T& operator[](const K& key) {
    if (map_.contains(key)) {
      Use(key);
      return map_[key].value;
    }

    map_[key] = {key, T{}, nullptr, most_used_};
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

    return map_[key].value;
  }

  T& GetWithoutUse(const K& key) {
    if (!map_.contains(key)) {
      throw std::out_of_range("No such key");
    }
    return map_[key].value;
  }

  bool Contains(const K& key) const { return map_.contains(key); }

  void RemoveLeastUsed() {
    least_used_ = least_used_->more_used;
    map_.erase(least_used_->less_used->key);
    least_used_->less_used = nullptr;
  }

  void Remove(const K& key) {
    SetLeastUsed(key);
    RemoveLeastUsed();
  }

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

  size_t Size() const { return map_.size(); }

  void UpdateLimit(size_t new_limit) {
    while (Size() > new_limit) {
      RemoveLeastUsed();
    }
    size_limit_ = new_limit;
  }

 private:
  void SetLeastUsed(const K& key) {
    Node* node = &map_[key];

    if (node == least_used_) {
      return;
    }

    if (node == most_used_) {
      most_used_ = most_used_->less_used;
      most_used_->more_used = nullptr;
    } else {
      node->more_used->less_used = node->less_used;
      node->less_used->more_used = node->more_used;
    }

    node->more_used = least_used_;
    node->less_used = nullptr;
    least_used_->less_used = node;
    least_used_ = node;
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

}  // namespace Aads
