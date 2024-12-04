#include <bits/stdc++.h>
#include <fstream>

const std::string XMAS="XMAS#";
const std::vector<int> xdir{0, 0, 1, 1, 1, -1, -1, -1};
const std::vector<int> ydir{-1, 1, 0, -1, 1, 0, -1, 1};


void findXmas(std::vector<std::string> words, int x, int y, int n, int m, int dir, int idx, long long &xmasCounts) {
    if(idx == 4) xmasCounts++;
    else if(0<=x && x<n && 0<=y && y<m && words[x][y] == XMAS[idx]) findXmas(words, x+xdir[dir], y+ydir[dir], n, m, dir, idx+1, xmasCounts);
}

long long findAllXmas(vector<string> &words) {
    int n = words.size(), m = words[0].size();
    long long xmasCounts = 0;
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j) 
            if(words[i][j] == 'X')
                for(int dir=0; dir<8; ++dir) findXmas(words, i+xdir[dir], j+ydir[dir], n, m, dir, 1, xmasCounts);
    return xmasCounts;
}

void findX_MasMas(std::vector<std::string> &words, int x, int y, int n, int m, long long &x_masCounts) {
    if(0<=x-1 && x+1<n && 0<=y-1 && y+1<m)
        if(words[x-1][y-1]=='M' && words[x+1][y+1]=='S' && words[x-1][y+1]=='M' && words[x+1][y-1]=='S') x_masCounts++;
}

void findX_MasSam(std::vector<std::string> &words, int x, int y, int n, int m, long long &x_masCounts) {
    if(0<=x-1 && x+1<n && 0<=y-1 && y+1<m)
        if(words[x-1][y-1]=='M' && words[x+1][y+1]=='S' && words[x-1][y+1]=='S' && words[x+1][y-1]=='M') x_masCounts++;
}

void findX_SamMas(std::vector<std::string> &words, int x, int y, int n, int m, long long &x_masCounts) {
    if(0<=x-1 && x+1<n && 0<=y-1 && y+1<m)
        if(words[x-1][y-1]=='S' && words[x+1][y+1]=='M' && words[x-1][y+1]=='M' && words[x+1][y-1]=='S') x_masCounts++;
}

void findX_SamSam(std::vector<std::string> &words, int x, int y, int n, int m, long long &x_masCounts) {
    if(0<=x-1 && x+1<n && 0<=y-1 && y+1<m)
        if(words[x-1][y-1]=='S' && words[x+1][y+1]=='M' && words[x-1][y+1]=='S' && words[x+1][y-1]=='M') x_masCounts++;
}

long long findAlX_Mas(vector<string> &words) {
    int n = words.size(), m = words[0].size();
    long long x_masCounts = 0;
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            if(words[i][j] == 'A') {
                findX_MasMas(words, i, j, n, m, x_masCounts);
                findX_MasSam(words, i, j, n, m, x_masCounts);
                findX_SamMas(words, i, j, n, m, x_masCounts);
                findX_SamSam(words, i, j, n, m, x_masCounts);
            }
    return x_masCounts;
}

int main() {
    ifstream inputFile("./input/day4.txt");
    std::vector<string> words;
    std::string word;
    while(inputFile >> word) words.push_back(word);
    inputFile.close();
    long long xmasCounts = findAllXmas(words);
    long long x_masCounts = findAlX_Mas(words);
    std::cout<< "part1: "<< xmasCounts<< std::endl;
    std::cout<< "part2: "<< x_masCounts<< std::endl;
}