#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

namespace Aads {

namespace {

int Binlog(uint64_t num) {
  int res = 0;
  while ((1ULL << res) < num) {
    res += 1;
  }
  return res;
}

}  // namespace

template <typename T>
class PersistentArray {
  struct BaseNode;
  struct Node;
  struct Leaf;

 public:
  template <std::forward_iterator Iter>
  PersistentArray(Iter begin, Iter end) {
    size_ = std::distance(begin, end);
    tree_depth_ = Binlog(size_);
    tree_width_ = 1ULL << tree_depth_;

    if (size_ == 0) {
      return;
    }
    if (size_ == 1) {
      Leaf* root = new Leaf(*begin);
      roots_.push_back(root);
      leafs_to_delete_ = {root};
      return;
    }

    Leaf* leafs = reinterpret_cast<Leaf*>(new std::byte[sizeof(Leaf) * size_]);
    initial_array_ = leafs;
    for (size_t i = 0; i < size_; ++i) {
      new (leafs + i) Leaf(*(begin++));
    }

    Node* tree_nodes = new Node[tree_width_ - 1];
    roots_.push_back(tree_nodes);
    node_arrays_to_delete_ = {tree_nodes};

    for (size_t i = 0; i < tree_width_ - 1; ++i) {
      tree_nodes[i].left =
          2 * i + 1 >= tree_width_ - 1
              ? static_cast<BaseNode*>(leafs + 2 * i + 2 - tree_width_)
              : static_cast<BaseNode*>(tree_nodes + 2 * i + 1);
      tree_nodes[i].right =
          2 * i + 2 >= tree_width_ - 1
              ? static_cast<BaseNode*>(leafs + 2 * i + 3 - tree_width_)
              : static_cast<BaseNode*>(tree_nodes + 2 * i + 2);
    }
  }

  const T& Get(size_t version, size_t index) const {
    if (size_ == 1) {
      return static_cast<Leaf*>(roots_[version])->value;
    }

    BaseNode* node = roots_[version];
    size_t left = 0;
    size_t right = tree_width_ - 1;

    while (left < right) {
      size_t mid = (left + right) / 2;

      if (mid < index) {
        left = mid + 1;
        node = static_cast<Node*>(node)->right;
      } else {
        right = mid;
        node = static_cast<Node*>(node)->left;
      }
    }

    return static_cast<Leaf*>(node)->value;
  }

  template <typename... Args>
  void Set(size_t version, size_t index, Args... args) {
    Leaf* new_leaf = new Leaf(std::forward<Args>(args)...);
    leafs_to_delete_.push_back(new_leaf);
    Set(version, index, new_leaf);
  }

  const T& Get(size_t index) { return Get(Versions() - 1, index); }

  size_t Versions() const {
    // Consider empty array contains one version
    return std::max(roots_.size(), static_cast<size_t>(1));
  }

  size_t Size() const { return size_; }

  ~PersistentArray() {
    for (Node* nodes_arr : node_arrays_to_delete_) {
      delete[] nodes_arr;
    }
    for (Leaf* leafs : leafs_to_delete_) {
      delete leafs;
    }
    if (initial_array_) {
      // TODO: figure out why delete[] initial_array_ causes crash with
      // T == std::string
      for (size_t i = 0; i < size_; ++i) {
        (initial_array_ + i)->~Leaf();
      }
      delete[] reinterpret_cast<std::byte*>(initial_array_);
    }
  }

 private:
  void Set(size_t version, size_t index, Leaf* new_leaf) {
    if (size_ == 1) {
      roots_.push_back(new_leaf);
      return;
    }

    Node* branch = new Node[tree_depth_];
    BaseNode* node = roots_[version];
    size_t left = 0;
    size_t right = tree_width_ - 1;

    roots_.push_back(branch);
    node_arrays_to_delete_.push_back(branch);

    for (size_t i = 0; i < tree_depth_; ++i) {
      branch[i] = *static_cast<Node*>(node);
      size_t mid = (left + right) / 2;

      if (mid < index) {
        left = mid + 1;
        branch[i].right = i + 1 < tree_depth_
                              ? static_cast<BaseNode*>(branch + i + 1)
                              : static_cast<BaseNode*>(new_leaf);
        branch[i].left = static_cast<Node*>(node)->left;
        node = static_cast<Node*>(node)->right;
      } else {
        right = mid;
        branch[i].left = i + 1 < tree_depth_
                             ? static_cast<BaseNode*>(branch + i + 1)
                             : static_cast<BaseNode*>(new_leaf);
        branch[i].right = static_cast<Node*>(node)->right;
        node = static_cast<Node*>(node)->left;
      }
    }
  }

  size_t size_;
  size_t tree_width_;
  size_t tree_depth_;

  std::vector<BaseNode*> roots_;

  Leaf* initial_array_ = nullptr;
  std::vector<Node*> node_arrays_to_delete_;
  std::vector<Leaf*> leafs_to_delete_;

  struct BaseNode {};

  struct Node : BaseNode {
    BaseNode* left = nullptr;
    BaseNode* right = nullptr;
  };

  struct Leaf : BaseNode {
    template <typename... Args>
    Leaf(Args... args) : value(std::forward<Args>(args)...) {}

    T value;
  };
};

}  // namespace Aads
