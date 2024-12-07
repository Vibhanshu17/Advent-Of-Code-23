#include <bits/stdc++.h>
#include <fstream>

std::pair<long long, std::vector<int>> getResultNums(std::string line) {
    int delimIndex = line.find(":");
    // std::cout<< " delimIndex: "<< delimIndex<< std::endl;
    
    long long result = stoll(line.substr(0, delimIndex));
    std::vector<int> nums;
    size_t start = delimIndex+2, end;
    while ((end = line.find(" ", start)) != string::npos) {
        nums.push_back(stoi(line.substr (start, end - start)));
        start = end + 1;
    }
    nums.push_back(stoi(line.substr(start)));
    return {result, nums};
}

bool canMakeWithAddMult(std::vector<int> nums, long long result, long long curVal, int curIndex) {
    if(curIndex >= nums.size()) return curVal == result;
    return canMakeWithAddMult(nums, result, curVal + nums[curIndex], curIndex+1) || canMakeWithAddMult(nums, result, curVal * nums[curIndex], curIndex+1);
}

bool canMakeWithAddMultConcat(std::vector<int> nums, long long result, long long curVal, int curIndex) {
    if(curIndex >= nums.size()) return curVal == result;
    return canMakeWithAddMultConcat(nums, result, curVal + nums[curIndex], curIndex+1)
        || canMakeWithAddMultConcat(nums, result, curVal * nums[curIndex], curIndex+1)
        || canMakeWithAddMultConcat(nums, result, curVal*pow(10, to_string(nums[curIndex]).size())+nums[curIndex], curIndex+1);
}

int main() {
    ifstream inputFile("./input/day7.txt");
    std::string lines;
    long long addMultCalibrationSum = 0;
    long long addMultConcatCalibrationSum = 0;
    while(getline(inputFile, lines)) {
        auto [result, nums] = getResultNums(lines);
        if(canMakeWithAddMult(nums, result, nums[0], 1)) addMultCalibrationSum += result;
        else if(canMakeWithAddMultConcat(nums, result, nums[0], 1)) addMultConcatCalibrationSum += result;
    }
    std::cout<< "part1: "<< addMultCalibrationSum<< std::endl;
    std::cout<< "part2: "<< addMultCalibrationSum + addMultConcatCalibrationSum << std::endl;

}