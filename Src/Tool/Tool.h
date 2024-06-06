#ifndef SRC_TOOL_TOOL_H_

#define SRC_TOOL_TOOL_H_

#include <string>
#include <vector>

namespace CC {
/**
 * @brief Split a string in a vector of string depending on a specific character
 * @param toSplit The string that we want to split
 * @param seperator The char used to know when we need to split
 * @return A vector containing all the substring of toSplit
 */
std::vector<std::string> Split(std::string toSplit, char separator);
/**
 * @brief Split a string in a vector of string depending on a specific character
 * @param toSplit The string that we want to split
 * @param seperator The char used to know when we need to split
 * @param ignore Character to ignore
 * @return A vector containing all the substring of toSplit
 */
std::vector<std::string> Split(std::string toSplit, char separator, char ignore);
}  // namespace CC

#endif  // SRC_TOOL_TOOL_H_
