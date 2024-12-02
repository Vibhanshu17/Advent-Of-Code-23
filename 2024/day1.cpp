#include <bits/stdc++.h>
#include <fstream>

using namespace std;

pair<int, int> getNums(string s) {
    // space delimiter size: 3
    int idx = s.find(" ");
    return make_pair(stoi(s.substr(0, idx)), stoi(s.substr(idx+3)));
}

int main() {
    ifstream inputFile("./input/day1.txt");
    string nums;
    vector<int> list1, list2;
    map<int, int> freq;
    while(getline(inputFile, nums)) {
        auto [a, b] = getNums(nums);
        list1.push_back(a);
        list2.push_back(b);
        freq[b]++;
    }
    inputFile.close();
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());
    int n = list1.size();   assert(list2.size() == n);

    long long sumOfDistances = 0, similarityScore = 0;
    for(int i=0; i<n; ++i) {
        sumOfDistances += abs(list1[i] - list2[i]);
        similarityScore += list1[i] * freq[list1[i]];
    }
    cout<< "par1: "<< sumOfDistances<< endl;
    cout<< "part2: "<< similarityScore<< endl;
}