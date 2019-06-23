// Created By: Rahil Agrawal
// Implementation for the GetPaths Function along with helper functions

#include "assignments/wl/word_ladder.h"

#include <algorithm>
#include <queue>
#include <unordered_map>

std::unordered_map<std::string, std::unordered_set<std::string>>
CreateDictionary(const std::unordered_set<std::string>& words, const int& word_length) {
  std::unordered_map<std::string, std::unordered_set<std::string>> word_dict;
  for (const auto& word : words) {
    if (static_cast<int>(word.length()) != word_length)
      continue;
    for (int i = 0; i < word_length; ++i) {
      const auto& key = word.substr(0, i) + "_" + word.substr(i + 1, word_length - i);
      (word_dict[key]).insert(word);
    }
  }
  return word_dict;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
CreateGraph(const std::unordered_set<std::string>& lexicon, const int& word_length) {
  auto word_dict = CreateDictionary(lexicon, word_length);
  std::unordered_map<std::string, std::unordered_set<std::string>> word_graph;
  for (const auto& element : word_dict) {
    for (const auto& word1 : element.second) {
      for (const auto& word2 : element.second) {
        if (word_graph.find(word1) == word_graph.end())
          word_graph[word1] = {};
        if (word_graph.find(word2) == word_graph.end())
          word_graph[word2] = {};
        if (word1.compare(word2) == 0)
          continue;
        (word_graph[word1]).insert(word2);
        (word_graph[word2]).insert(word1);
      }
    }
  }
  return word_graph;
}

bool IsNotVisited(const std::string& wordToCheck, const std::vector<std::string>& path) {
  return (std::find(path.begin(), path.end(), wordToCheck) == path.end());
}

std::unordered_map<std::string, int>
DistFromDest(const std::string& source,
             const std::string& destination,
             std::unordered_map<std::string, std::unordered_set<std::string>>& word_graph) {
  std::unordered_map<std::string, int> distances;
  std::unordered_map<std::string, bool> visited;
  for (auto word : word_graph)
    visited[word.first] = false;
  visited[destination] = true;
  std::queue<std::string> bfs_queue;
  bfs_queue.push(destination);
  distances[destination] = 0;

  while (!bfs_queue.empty()) {
    auto current_word = bfs_queue.front();
    bfs_queue.pop();
    int current_distance = distances[current_word] + 1;
    if (current_word.compare(source) == 0) {
      return distances;
    }
    for (const auto& word : word_graph[current_word]) {
      if (!(visited[word])) {
        visited[word] = true;
        distances[word] = current_distance;
        bfs_queue.push(word);
      }
    }
  }

  return distances;
}

std::vector<std::vector<std::string>> GetPaths(const std::string& source,
                                               const std::string& destination,
                                               const std::unordered_set<std::string>& lexicon) {
  auto word_graph = CreateGraph(lexicon, static_cast<int>(source.length()));
  auto distances = DistFromDest(source, destination, word_graph);

  std::unordered_map<std::string, bool> noPath;
  for (const auto& word : word_graph)
    noPath[word.first] = true;
  std::vector<std::vector<std::string>> ladders;
  std::queue<std::vector<std::string>> paths;
  std::vector<std::string> path;
  path.push_back(source);
  paths.push(path);

  if (source.compare(destination) == 0) {
    if (word_graph.find(source) != word_graph.end())
      ladders.emplace_back(path);
    return ladders;
  }

  while (!paths.empty()) {
    path = paths.front();
    paths.pop();
    std::string last = path[path.size() - 1];
    noPath[last] = false;
    if (last.compare(destination) == 0) {
      for (const auto& word : path)
        noPath[word] = true;
      ladders.emplace_back(path);
      continue;
    }
    if (static_cast<int>(path.size()) + distances[last] > distances[source] + 1)
      continue;
    for (const auto& word : word_graph[last]) {
      if (IsNotVisited(word, path) && noPath[word]) {
        std::vector<std::string> new_path(path);
        new_path.push_back(word);
        paths.push(new_path);
      }
    }
  }
  std::sort(ladders.begin(), ladders.end(),
            [](const std::vector<std::string>& path1, const std::vector<std::string>& path2) {
              for (auto it1 = path1.begin(), it2 = path2.begin();
                   it1 != path1.end() && it2 != path2.end(); ++it1, ++it2) {
                if ((*it1).compare(*it2) == 0)
                  continue;
                return (*it1).compare(*it2) <= 0;
              }
              return true;
            });

  return ladders;
}
