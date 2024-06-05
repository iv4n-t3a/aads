#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

class Treap {
  struct Node;

 public:
  ~Treap() { Clear(root_); }

  void Insert(int idx, int value, int priority) {
    auto [left, right] = Split(root_, idx);
    Node* node = new Node(value, priority);
    root_ = Merge(Merge(left, node), right);
  }

  int Min(int left, int right) {
    auto [new_left, midle] = Split(root_, left - 1);
    auto [new_midle, new_right] = Split(midle, right - left + 1);
    int res = new_midle->min;
    root_ = Merge(Merge(new_left, new_midle), new_right);
    return res;
  }

  void Reverse(int left, int right) {
    if (right == left) {
      return;
    }
    auto [new_left, midle] = Split(root_, left - 1);
    auto [new_midle, new_right] = Split(midle, right - left + 1);
    Reverse(new_midle);
    root_ = Merge(Merge(new_left, new_midle), new_right);
  }

 private:
  static Node* Merge(Node* left, Node* right) {
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

  static std::pair<Node*, Node*> Split(Node* root, int del) {
    if (root == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }
    UpdateOrder(root);

    if (SubtreeSize(root->left_child) + 1 <= del) {
      Node* tree_left = root;
      auto split_tree =
          Split(root->right_child, del - SubtreeSize(root->left_child) - 1);
      tree_left->right_child = split_tree.first;
      Update(tree_left);
      Update(split_tree.second);
      return {tree_left, split_tree.second};
    }
    Node* tree_right = root;
    auto split_tree = Split(root->left_child, del);
    tree_right->left_child = split_tree.second;
    Update(tree_right);
    Update(split_tree.first);
    return {split_tree.first, tree_right};
  }

  static void Clear(Node* subtree) {
    if (subtree == nullptr) {
      return;
    }
    Clear(subtree->left_child);
    Clear(subtree->right_child);
    delete subtree;
  }

  static int SubtreeSize(Node* node) {
    return node != nullptr ? node->subtree_size : 0;
  }

  static void Update(Node* node) {
    if (node != nullptr) {
      node->Update();
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

  struct Node {
    int value;
    int priority;
    int subtree_size = 1;
    int min = std::numeric_limits<int>::max();
    bool reversed = false;
    Node* left_child = nullptr;
    Node* right_child = nullptr;

    Node(int val, int prior) : value(val), priority(prior), min(val) {}

    void Update() {
      subtree_size = (left_child != nullptr ? left_child->subtree_size : 0) +
                     (right_child != nullptr ? right_child->subtree_size : 0) +
                     1;
      min = std::min(
          std::min((left_child != nullptr ? left_child->min : value),
                   (right_child != nullptr ? right_child->min : value)),
          value);
    }
  };

  Node* root_ = nullptr;
};

int main() {
  std::srand(std::time(nullptr));

  size_t elements;
  int queryies;
  std::cin >> elements >> queryies;

  Treap treap;

  for (size_t i = 0; i < elements; ++i) {
    int num;
    std::cin >> num;
    treap.Insert(i, num, std::rand());
  }

  char cmd;
  int left;
  int right;

  for (int i = 0; i < queryies; ++i) {
    std::cin >> cmd >> left >> right;
    if (cmd == '1') {
      treap.Reverse(left, right);
    } else {
      std::cout << treap.Min(left, right) << "\n";
    }
  }
}
