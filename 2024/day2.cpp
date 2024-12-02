#include <bits/stdc++.h>
#include <fstream>

vector<int> getNumbers(const string s) {
    size_t start = 0, end;
    vector<int> nums;
    while ((end = s.find(" ", start)) != string::npos) {
        nums.push_back(stoi(s.substr (start, end - start)));
        start = end + 1;
    }
    nums.push_back(stoi(s.substr(start)));
    return nums;
}

// bool isReportSafe(vector<int> &nums) {
//     int n = nums.size();
//     bool isIncSafe = true, isDecSafe = true;
//     for(int i=1; i<n && (isIncSafe || isDecSafe); ++i) {
//         int diff = nums[i] - nums[i-1];
//         isIncSafe &= (1 <= diff && diff <= 3);
//         isDecSafe &= (-3 <= diff && diff <= -1);
//     }
//     return isIncSafe || isDecSafe;
// }

bool isReportSafe(vector<int> &nums, int skipIndex) {
    int n = nums.size();
    bool isIncSafe = true, isDecSafe = true;
    for(int lo=0, hi=1; hi<n && (isIncSafe || isDecSafe); lo++, hi++) {
        if(lo == skipIndex) lo++, hi += lo == hi;
        else if(hi == skipIndex) {
            hi++;
            if(hi == n) break;
        }
        int diff = nums[hi] - nums[lo];
        isIncSafe &= (1 <= diff && diff <= 3);
        isDecSafe &= (-3 <= diff && diff <= -1);
    }
    return isIncSafe || isDecSafe;
}

bool isReportSafeExceptOne(vector<int> &nums) {
    for(int skipIndex=0; skipIndex<nums.size(); ++skipIndex)
        if(isReportSafe(nums, skipIndex)) return true;
    return false;
}

int main() {
    ifstream inputFile("./input/day2.txt");
    string report;
    int safeReportsCount = 0;
    int safeReportsCountExceptOne = 0;
    while(getline(inputFile, report)) {
        vector<int> v = getNumbers(report);
        if(isReportSafe(v, -1)) safeReportsCount++, safeReportsCountExceptOne++;
        else safeReportsCountExceptOne += isReportSafeExceptOne(v);
    }
    inputFile.close();
    cout<< "part1: "<< safeReportsCount<< endl;
    cout<< "part2: "<< safeReportsCountExceptOne<< endl;
}