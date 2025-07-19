#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <random>
#include <type_traits>
#include <utility>

namespace Aads {

template <typename T, std::relation<T, T> Comp = std::less<>>
class Treap {
  struct Node;

  Treap(Node* root) : root_(root) {}

 public:
  Treap() = default;

  Treap(std::initializer_list<T> init_list) {
    int idx = 0;
    for (const auto& value : init_list) {
      Insert(idx++, value);
    }
  }

  Treap(const Treap& treap) { root_ = Copy(treap.root_); }

  Treap(Treap&& treap) {
    root_ = treap.root_;
    treap.root_ = nullptr;
  }

  Treap& operator=(const Treap& other) {
    Clear(root_);
    root_ = Copy(other.root_);
    return *this;
  }

  Treap& operator=(Treap&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
    return *this;
  }

  ~Treap() { Clear(root_); }

  void Insert(size_t index, const T& value) {
    assert(index < Size() + 1);
    auto [left, right] = Split(root_, index);
    Node* node = new Node(value, Random());
    root_ = Merge(Merge(left, node), right);
  }

  void Insert(size_t index, T&& value) {
    auto [left, right] = Split(root_, index);
    Node* node = new Node(std::move(value), Random());
    root_ = Merge(Merge(left, node), right);
  }

  T& operator[](size_t index) {
    auto [new_left, midle] = Split(root_, index);
    auto [new_midle, new_right] = Split(midle, 1);
    T& res = new_midle->value;
    root_ = Merge(Merge(new_left, new_midle), new_right);
    return res;
  }

  T& Min(size_t left, size_t right) {
    auto [new_left, midle] = Split(root_, left);
    auto [new_midle, new_right] = Split(midle, right - left);
    T& res = *new_midle->min;
    root_ = Merge(Merge(new_left, new_midle), new_right);
    return res;
  }

  void Reverse(size_t left, size_t right) {
    if (right == left) {
      return;
    }
    auto [new_left, midle] = Split(root_, left);
    auto [new_midle, new_right] = Split(midle, right - left);
    Reverse(new_midle);
    root_ = Merge(Merge(new_left, new_midle), new_right);
  }

  void Reverse() { Reverse(root_); }

  static Treap Merge(Treap&& left, Treap&& right) {
    Treap res;
    res.root_ = res.Merge(left.root_, right.root_);
    left.root_ = nullptr;
    right.root_ = nullptr;
    return res;
  }

  std::pair<Treap, Treap> Split(size_t del) && {
    auto [left_root, right_root] = Split(root_, del);
    root_ = nullptr;
    return std::make_pair(Treap(left_root), Treap(right_root));
  }

  size_t Size() const {
    if (root_ == nullptr) [[unlikely]] {
      return 0;
    }
    return root_->subtree_size;
  }

  void Print(std::ostream& out = std::cout) { Print(root_, out); }

 private:
  static_assert(not std::is_copy_constructible_v<T> or
                std::is_nothrow_copy_constructible_v<T>);
  static_assert(not std::is_move_constructible_v<T> or
                std::is_nothrow_move_constructible_v<T>);

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    UpdateOrder(left);
    UpdateOrder(right);

    Node* root;
    if (left->priority > right->priority) {
      root = left;
      root->right_child = Merge(left->right_child, right);
    } else {
      root = right;
      root->left_child = Merge(left, right->left_child);
    }
    Update(root);
    return root;
  }

  std::pair<Node*, Node*> Split(Node* root, size_t del) {
    if (root == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }

    UpdateOrder(root);

    if (SubtreeSize(root->left_child) >= del) {
      auto [left, right] = Split(root->left_child, del);
      root->left_child = right;
      Update(root);
      return {left, root};
    }
    auto [left, right] =
        Split(root->right_child, del - SubtreeSize(root->left_child) - 1);
    root->right_child = left;
    Update(root);
    return {root, right};
  }

  Node* Copy(Node* root) {
    if (root == nullptr) {
      return nullptr;
    }
    Node* copy = new Node(*root);
    copy->left_child = Copy(root->left_child);
    copy->right_child = Copy(root->right_child);
    Update(copy);
    return copy;
  }

  static void Clear(Node* subtree) {
    if (subtree == nullptr) {
      return;
    }
    Clear(subtree->left_child);
    Clear(subtree->right_child);
    delete subtree;
  }

  static size_t SubtreeSize(Node* node) {
    return node != nullptr ? node->subtree_size : 0;
  }

  void Update(Node* node) {
    if (node == nullptr) {
      return;
    }

    node->subtree_size = 1;
    node->min = std::addressof(node->value);

    if (node->left_child != nullptr) {
      node->subtree_size += node->left_child->subtree_size;
      if (comp_(*(node->left_child->min), node->value)) {
        node->min = node->left_child->min;
      }
    }
    if (node->right_child != nullptr) {
      node->subtree_size += node->right_child->subtree_size;
      if (comp_(*(node->right_child->min), node->value)) {
        node->min = node->right_child->min;
      }
    }
  }

  static void UpdateOrder(Node* node) {
    if (node != nullptr and node->reversed) {
      std::swap(node->left_child, node->right_child);
      node->reversed = false;
      Reverse(node->left_child);
      Reverse(node->right_child);
    }
  }

  static void Reverse(Node* node) {
    if (node != nullptr) {
      node->reversed = not node->reversed;
    }
  }

  static void Print(const Node* node, std::ostream& out, size_t intend = 0) {
    for (size_t i = 0; i < intend; ++i) {
      out << "  ";
    }
    if (node != nullptr) {
      out << "-> " << node->value << '\n';
      Print(node->left_child, out, intend + 1);
      Print(node->right_child, out, intend + 1);
    } else {
      out << "-> nullptr\n";
    }
  }

  static int Random() {
    static auto rnd = std::mt19937(std::random_device()());
    return rnd();
  }

  struct Node {
    T value;
    int priority;
    size_t subtree_size = 1;
    T* min = nullptr;
    bool reversed = false;
    Node* left_child = nullptr;
    Node* right_child = nullptr;

    Node(const T& val, size_t prior)
        : value(val), priority(prior), min(std::addressof(value)) {}
    Node(T&& val, size_t prior)
        : value(std::move(val)), priority(prior), min(std::addressof(value)) {}
  };

  Node* root_ = nullptr;
  Comp comp_;
};

}  // namespace Aads
