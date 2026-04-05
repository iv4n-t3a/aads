# Aho-Corasick Algorithm

Finds all occurrences of multiple patterns from a dictionary in a text string.

## Algorithm Idea

The Aho-Corasick algorithm builds a finite state automaton (trie) from the pattern dictionary with failure links. It processes the text in a single pass, using failure links to efficiently handle mismatches and find all pattern occurrences simultaneously.

## Complexity

* **Construction**: `O(S)` where `S` is the sum of all pattern lengths
* **Search**: `O(n + m)` where `n` is text length and `m` is the number of matches

## Classes and Methods

### `Aads::Automaton`

Main class implementing the Aho-Corasick automaton.

#### Constructor
```cpp
template <typename Iter>
Automaton(Iter begin, Iter end)
```
Constructs the automaton from a range of pattern strings.

#### Public Methods

**`std::vector<std::list<int>> FindEntries(const std::string& str)`**
- Finds all occurrences of patterns in the given text
- Returns a vector where `result[i]` contains positions (1-indexed, end positions) where pattern `i` occurs
- Time complexity: `O(n + m)` where `n` is text length, `m` is number of matches

## Usage Example

```cpp
#include "AhoCorasick/aho_corasick.hpp"

std::vector<std::string> patterns = {"he", "she", "his", "hers"};
Aads::Automaton automaton(patterns.begin(), patterns.end());

std::string text = "ushers";
auto entries = automaton.FindEntries(text);

// entries[0] contains positions where "he" was found
// entries[1] contains positions where "she" was found
// etc.
```
