#include <gtest/gtest.h>
#include "AhoCorasick/aho_corasick.hpp"

TEST(AutomatonTest, SinglePattern) {
  std::vector<std::string> patterns = {"abc"};
  Aads::Automaton automaton(patterns.begin(), patterns.end());

  std::string text = "abcabc";
  auto entries = automaton.FindEntries(text);

  ASSERT_EQ(entries.size(), 1);
  ASSERT_EQ(entries[0].size(), 2);
  
  auto it = entries[0].begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(AutomatonTest, MultiplePatterns) {
  std::vector<std::string> patterns = {"a", "ab", "abc"};
  Aads::Automaton automaton(patterns.begin(), patterns.end());

  std::string text = "abc";
  auto entries = automaton.FindEntries(text);

  ASSERT_EQ(entries.size(), 3);
  EXPECT_EQ(entries[0].size(), 1);  // "a" at position 1
  EXPECT_EQ(entries[1].size(), 1);  // "ab" at position 2
  EXPECT_EQ(entries[2].size(), 1);  // "abc" at position 3
}

TEST(AutomatonTest, OverlappingPatterns) {
  std::vector<std::string> patterns = {"he", "she", "his", "hers"};
  Aads::Automaton automaton(patterns.begin(), patterns.end());

  std::string text = "ushers";
  auto entries = automaton.FindEntries(text);

  ASSERT_EQ(entries.size(), 4);
  EXPECT_EQ(entries[0].size(), 1);  // "he" found once
  EXPECT_EQ(entries[1].size(), 1);  // "she" found once
  EXPECT_EQ(entries[2].size(), 0);  // "his" not found
  EXPECT_EQ(entries[3].size(), 1);  // "hers" found once
}

TEST(AutomatonTest, NoMatches) {
  std::vector<std::string> patterns = {"xyz"};
  Aads::Automaton automaton(patterns.begin(), patterns.end());

  std::string text = "abcdef";
  auto entries = automaton.FindEntries(text);

  ASSERT_EQ(entries.size(), 1);
  EXPECT_EQ(entries[0].size(), 0);
}

TEST(AutomatonTest, EmptyText) {
  std::vector<std::string> patterns = {"abc"};
  Aads::Automaton automaton(patterns.begin(), patterns.end());

  std::string text = "";
  auto entries = automaton.FindEntries(text);

  ASSERT_EQ(entries.size(), 1);
  EXPECT_EQ(entries[0].size(), 0);
}

TEST(AutomatonTest, RepeatedPattern) {
  std::vector<std::string> patterns = {"aa"};
  Aads::Automaton automaton(patterns.begin(), patterns.end());

  std::string text = "aaaa";
  auto entries = automaton.FindEntries(text);

  ASSERT_EQ(entries.size(), 1);
  EXPECT_EQ(entries[0].size(), 3);  // "aa" at positions 2, 3, 4
}
