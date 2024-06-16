#include <cassert>
#include <iostream>

const int64_t kMod = 1e9;

template <typename T>
class Tree {
  struct Node;

 public:
  bool Contains(T value) {
    Node* res = Next(root_, value);
    return res != nullptr and res->value == value;
  }

  bool ContainsNext(T value) {
    Node* res = Next(root_, value);
    return res != nullptr;
  }

  T Next(T value) { return Next(root_, value)->value; }

  void Insert(T value) {
    if (Contains(value)) {
      return;
    }
    if (root_ != nullptr) {
      Insert(root_, value);
    } else {
      root_ = new Node({value});
    }
  }

  ~Tree() { Clear(root_); }

 private:
  static Node* Next(Node* node, T value) {
    if (node == nullptr) {
      return nullptr;
    }
    if (value < node->value) {
      Node* res = Next(node->left, value);
      return res != nullptr and res->value >= value ? res : node;
    }
    if (node->value < value) {
      return Next(node->right, value);
    }
    return node;
  }

  static void Insert(Node* node, T value) {
    Node*& child = (value < node->value ? node->left : node->right);
    if (child == nullptr) {
      child = new Node({value});
    } else {
      Insert(child, value);
      Rebalance(node);
    }
  }

  static void Clear(Node* subtree) {
    if (subtree == nullptr) {
      return;
    }
    Clear(subtree->left);
    Clear(subtree->right);
    delete subtree;
  }

  // Источник ската: https://habr.com/ru/articles/150732/
  static Node* Rebalance(Node* root) {
    if (BalanceFactor(root) == 2) {
      if (BalanceFactor(root->right) < 0) {
        root->right = RotateLeft(root->right);
      }
      return RotateLeft(root);
    }

    if (BalanceFactor(root) == -2) {
      if (BalanceFactor(root->left) > 0) {
        root->left = RotateLeft(root->left);
      }
      return RotateRight(root);
    }

    return root;
  }

  static Node* RotateLeft(Node* root) {
    Node* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    UpdateHeight(root);
    UpdateHeight(new_root);
    return new_root;
  }
  static Node* RotateRight(Node* root) {
    Node* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    UpdateHeight(root);
    UpdateHeight(new_root);
    return new_root;
  }

  static int BalanceFactor(Node* node) {
    assert(node != nullptr);
    return Height(node->left) - Height(node->right);
  }
  static int Height(Node* node) { return node == nullptr ? 0 : node->height; }
  static void UpdateHeight(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->height = std::max(Height(node->left), Height(node->right));
  }

  struct Node {
    T value;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  Node* root_ = nullptr;
};

int main() {
  int quries;
  Tree<int64_t> tree;

  std::cin >> quries;

  for (int i = 0; i < quries; ++i) {
    int64_t arg;
    char cmd;
    std::cin >> cmd;

    if (cmd == '+') {
      std::cin >> arg;
      tree.Insert(arg);
    } else if (cmd == '?') {
      std::cin >> arg;
      int64_t next = tree.ContainsNext(arg) ? tree.Next(arg) : -1;
      std::cout << next << std::endl;
    }
  }
}
