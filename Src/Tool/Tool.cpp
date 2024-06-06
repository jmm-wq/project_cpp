#include "Tool/Tool.h"

namespace CC {

std::vector<std::string> Split(std::string toSplit, char separator) {
    std::vector<std::string> strings;

    std::string currentString;

    for (unsigned int i = 0; i < toSplit.size(); i++) {
        if (toSplit[i] == separator) {
            if (currentString != "") {
                strings.push_back(currentString);
                currentString = "";
            }
        } else {
            currentString += toSplit[i];
        }
    }

    if (currentString != "") {
        strings.push_back(currentString);
        currentString = "";
    }

    return strings;
}

std::vector<std::string> Split(std::string toSplit,
                               char separator,
                               char ignore) {
    std::vector<std::string> strings;

    std::string currentString;

    for (unsigned int i = 0; i < toSplit.size(); i++) {
        if (toSplit[i] == separator) {
            if (currentString != "") {
                strings.push_back(currentString);
                currentString = "";
            }
        } else if (toSplit[i] == ignore) {
            continue;
        } else {
            currentString += toSplit[i];
        }
    }

    if (currentString != "") {
        strings.push_back(currentString);
        currentString = "";
    }

    return strings;
}

}
