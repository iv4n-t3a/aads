#include <array>
#include <iostream>
#include <list>
#include <queue>
#include <string>

class Automaton {
  static const size_t kAlpSize = 26;
  struct Node;

 public:
  template <typename Iter>
  Automaton(Iter begin, Iter end) {
    root_ = new Node();

    for (Iter it = begin; it != end; ++it) {
      Insert(*it, words_count_);
      words_count_ += 1;
    }

    InitLinks();
  }

  ~Automaton() { Clean(root_); }

  std::vector<std::list<int>> FindEntries(const std::string& str) {
    std::vector<std::list<int>> res(words_count_);
    Node* curnode = root_;
    for (size_t i = 0; i < str.size(); ++i) {
      curnode = curnode->go[str[i] - 'a'];
      Node* entry_node = curnode->is_term ? curnode : curnode->comp;
      while (entry_node->is_term) {
        for (int word_id : entry_node->word_id) {
          res[word_id].push_back(i + 1);
        }
        entry_node = entry_node->comp;
      }
    }
    return res;
  }

 private:
  void Insert(const std::string& str, int word_id) {
    Node* node = root_;
    for (size_t i = 0; i < str.size(); ++i) {
      if (node->to[str[i] - 'a'] == nullptr) {
        node->to[str[i] - 'a'] = new Node();
      }
      node = node->to[str[i] - 'a'];
    }
    node->is_term = true;
    node->word_id.push_back(word_id);
  }

  void InitLinks() {
    std::queue<Node*> queue;
    root_->link = root_;
    root_->comp = root_;
    for (size_t i = 0; i < kAlpSize; ++i) {
      if (root_->to[i] != nullptr) {
        root_->go[i] = root_->to[i];
      } else {
        root_->go[i] = root_;
      }
    }
    queue.push(root_);

    while (not queue.empty()) {
      Node* curnode = queue.front();
      queue.pop();

      for (size_t i = 0; i < kAlpSize; ++i) {
        Node* adj_node = curnode->to[i];
        if (adj_node == nullptr) {
          continue;
        }
        adj_node->link = curnode == root_ ? root_ : curnode->link->go[i];
        adj_node->comp =
            adj_node->link->is_term ? adj_node->link : adj_node->link->comp;
        for (size_t j = 0; j < kAlpSize; ++j) {
          adj_node->go[j] = adj_node->to[j] != nullptr ? adj_node->to[j]
                                                       : adj_node->link->go[j];
        }
        queue.push(adj_node);
      }
    }
  }

  void Clean(Node* node) {
    if (node == nullptr) {
      return;
    }
    for (Node* child : node->to) {
      Clean(child);
    }
    delete node;
  }

  struct Node {
    std::array<Node*, kAlpSize> to;
    std::array<Node*, kAlpSize> go;
    Node* link;
    Node* comp;
    bool is_term = false;
    std::list<int> word_id;
  };

  size_t words_count_ = 0;
  Node* root_ = nullptr;
};

std::string InputPattern(std::istream& inp) {
  std::string pattern;
  inp >> pattern;
  return pattern;
}

std::vector<std::string> InputStrings(std::istream& inp) {
  size_t count;
  inp >> count;

  std::vector<std::string> res(count);
  for (size_t i = 0; i < count; ++i) {
    inp >> res[i];
  }
  return res;
}

void PrintAnswer(std::ostream& outp, const std::vector<std::list<int>>& entries,
                 const std::vector<std::string>& strings) {
  for (size_t i = 0; i < strings.size(); ++i) {
    outp << entries[i].size() << " ";
    for (int entry : entries[i]) {
      outp << entry + 1 - strings[i].size() << " ";
    }
    outp << "\n";
  }
}

int main() {
  std::string pattern = InputPattern(std::cin);
  std::vector<std::string> strings = InputStrings(std::cin);

  Automaton automaton(strings.begin(), strings.end());

  std::vector<std::list<int>> entries = automaton.FindEntries(pattern);
  PrintAnswer(std::cout, entries, strings);
}
