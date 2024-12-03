#include <bits/stdc++.h>
#include <fstream>

long long mul(std::string x, std::string y) {
    return std::stol(x) * std::stol(y);
}

long long parseMul(std::string s, bool enableDoDont=false) {
    size_t start = 0, end = 0;
    std::vector<std::pair<long long, int>> mulResults;
    while((start = s.find("mul(", end)) != std::string::npos) {
        end = start + 4;
        std::string x = "", y = "";
        while(end < s.size() && isdigit(s[end])) x += s[end++];
        if(end < s.size() && s[end] == ',') end++;
        else continue;
        while(end < s.size() && isdigit(s[end])) y += s[end++];
        if(end < s.size() && s[end]==')') end++, mulResults.push_back(std::make_pair(mul(x, y), start));
        else continue;
    }

    start = 0;
    long long sum = 0ll;
    size_t mulResultsIndex = 0;
    bool enable = true;
    while((start = s.find("do", start)) != std::string::npos) {
        if(start + 3 < s.size() && s.substr(start, 4) == "do()") {
            while(!enable && mulResults[mulResultsIndex].second < start) mulResultsIndex++;
            while(enable && mulResults[mulResultsIndex].second < start) sum += mulResults[mulResultsIndex++].first;
            enable = true;
            start += 4;
        }
        else if(start + 6 < s.size() && s.substr(start, 7) == "don't()") {
            while(!enable && mulResults[mulResultsIndex].second < start) mulResultsIndex++;
            while(enable && mulResults[mulResultsIndex].second < start) sum += mulResults[mulResultsIndex++].first;
            enable = !enableDoDont | false;
            start += 7;
        }
        else start += 2;
    }
    while(enable && mulResultsIndex < mulResults.size()) sum += mulResults[mulResultsIndex++].first;
    
    return sum;
}

int main() {
    std::ifstream inputFile("./input/day3.txt");
    std::string line, programString = "";
    while(getline(inputFile, line)) {
        programString += line;
    }
    inputFile.close();
    
    long long sumOfMultiplications = parseMul(programString);
    long long sumOfMultiplications2 = parseMul(programString, true);
    std::cout<< "part1: "<< sumOfMultiplications<< std::endl;
    std::cout<< "part2: "<< sumOfMultiplications2<< std::endl;
}
