// Created By: Rahil Agrawal
// Driver file for accepting input and printing output

#include <iostream>
#include <string>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

void GetWords(std::string& start, std::string& end);
void PrintPaths(std::vector<std::vector<std::string>> paths);

int main() {
  const auto& lexicon = GetLexicon("assignments/wl/words.txt");
  std::string start;
  std::string end;
  GetWords(start, end);
  PrintPaths(GetPaths(start, end, lexicon));
}

void PrintPaths(std::vector<std::vector<std::string>> paths) {
  if (paths.size() == 0) {
    std::cout << "No ladder found." << std::endl;
    return;
  }
  std::cout << "Found ladder: ";

  for (std::vector<std::string> path : paths) {
    for (auto word = path.cbegin(); word != path.cend(); ++word)
      std::cout << *word << " ";
    std::cout << std::endl;
  }
}

void GetWords(std::string& start, std::string& end) {
  std::cout << "Enter start word (RETURN to quit): ";
  std::getline(std::cin, start);

  if (start.length() == 0)
    exit(0);

  std::cout << "Enter destination word: ";
  std::getline(std::cin, end);
}
