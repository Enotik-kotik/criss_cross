#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <vector>
#include <string>

using namespace std;

bool canPlace(vector<vector<char>>& grid, const string& word, int x, int y, bool horizontal);
void placeWord(vector<vector<char>>& grid, const string& word, int x, int y, bool horizontal);
bool tryPlaceWord(vector<vector<char>>& grid, const string& word);
vector<vector<char>> generateCrossword(const vector<string>& words);
vector<vector<char>> trimGrid(const vector<vector<char>>& grid);
void saveGridToFile(const vector<vector<char>>& grid, const string& filename);

#endif 