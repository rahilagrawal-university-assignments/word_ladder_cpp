// Created By: Rahil Agrawal
// Interface for the GetPaths Function

#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <unordered_set>
#include <string>
#include <vector>

std::vector<std::vector<std::string>>
  GetPaths(const std::string&, const std::string&, const std::unordered_set<std::string>&);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
