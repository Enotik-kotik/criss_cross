#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "crossword.h"

using namespace std;

// Функция для проверки возможности размещения слова
bool canPlace(vector<vector<char>>& grid, const string& word, int x, int y, bool horizontal) {
    int len = word.size();
    if (horizontal) {
        if (y + len > grid[0].size() || y < 0) return false;
        for (int i = 0; i < len; ++i) {
            char c = grid[x][y + i];
            if (c != '.' && c != word[i]) return false;
            if (c == '.' && ((x > 0 && grid[x - 1][y + i] != '.') || (x + 1 < grid.size() && grid[x + 1][y + i] != '.'))) {
                return false;
            }
        }
        if ((y > 0 && grid[x][y - 1] != '.') || (y + len < grid[0].size() && grid[x][y + len] != '.')) {
            return false;
        }
    }
    else {
        if (x + len > grid.size() || x < 0) return false;
        for (int i = 0; i < len; ++i) {
            char c = grid[x + i][y];
            if (c != '.' && c != word[i]) return false;
            if (c == '.' && ((y > 0 && grid[x + i][y - 1] != '.') || (y + 1 < grid[0].size() && grid[x + i][y + 1] != '.'))) {
                return false;
            }
        }
        if ((x > 0 && grid[x - 1][y] != '.') || (x + len < grid.size() && grid[x + len][y] != '.')) {
            return false;
        }
    }
    return true;
}

// Функция для размещения слова
void placeWord(vector<vector<char>>& grid, const string& word, int x, int y, bool horizontal) {
    if (horizontal) {
        for (int i = 0; i < word.size(); ++i) {
            grid[x][y + i] = word[i];
        }
    }
    else {
        for (int i = 0; i < word.size(); ++i) {
            grid[x + i][y] = word[i];
        }
    }
}

// Функция для попытки разместить слово в сетке
bool tryPlaceWord(vector<vector<char>>& grid, const string& word) {
    for (int x = 0; x < grid.size(); ++x) {
        for (int y = 0; y < grid[0].size(); ++y) {
            if (grid[x][y] == '.') continue;

            // Пробуем разместить слово горизонтально
            for (int k = 0; k < word.size(); ++k) {
                if (grid[x][y] == word[k]) {
                    int newX = x;
                    int newY = y - k;
                    if (canPlace(grid, word, newX, newY, true)) {
                        placeWord(grid, word, newX, newY, true);
                        return true;
                    }
                }
            }

            // Пробуем разместить слово вертикально
            for (int k = 0; k < word.size(); ++k) {
                if (grid[x][y] == word[k]) {
                    int newX = x - k;
                    int newY = y;
                    if (canPlace(grid, word, newX, newY, false)) {
                        placeWord(grid, word, newX, newY, false);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Основная функция генерации кроссворда
vector<vector<char>> generateCrossword(const vector<string>& words) {
    const int gridSize = 30; // Увеличиваем размер сетки
    vector<vector<char>> grid(gridSize, vector<char>(gridSize, '.'));//30*30

    int centerX = gridSize / 2, centerY = gridSize / 2;
    placeWord(grid, words[0], centerX, centerY, true);

    // Список слов, которые не удалось разместить
    vector<string> unplacedWords;

    for (int i = 1; i < words.size(); ++i) {
        bool placed = false;
        const string& word = words[i];

        // Пробуем разместить слово в сетке
        for (int x = 0; x < gridSize && !placed; ++x) {
            for (int y = 0; y < gridSize && !placed; ++y) {
                if (grid[x][y] == '.') continue;

                // Пробуем разместить горизонтально
                for (int k = 0; k < word.size(); ++k) {
                    if (grid[x][y] == word[k]) {
                        int newX = x;
                        int newY = y - k;
                        if (canPlace(grid, word, newX, newY, true)) {
                            placeWord(grid, word, newX, newY, true);
                            placed = true;
                            break;
                        }
                    }
                }

                // Пробуем разместить вертикально
                for (int k = 0; k < word.size(); ++k) {
                    if (grid[x][y] == word[k]) {
                        int newX = x - k;
                        int newY = y;
                        if (canPlace(grid, word, newX, newY, false)) {
                            placeWord(grid, word, newX, newY, false);
                            placed = true;
                            break;
                        }
                    }
                }
            }
        }

        // Если слово не размещено, добавляем его в список неразмещенных
        if (!placed) {
            unplacedWords.push_back(word);
        }
    }

    // Проверяем неразмещенные слова в самом конце
    for (const string& word : unplacedWords) {
        if (tryPlaceWord(grid, word)) {
            cout << "Word \"" << word << "\" was placed after final check." << endl;
        }
        else {
            cout << "Warning: Could not place word \"" << word << "\" even after final check." << endl;
        }
    }

    return grid;
}

// Функция для обрезания пустого пространства
vector<vector<char>> trimGrid(const vector<vector<char>>& grid) {
    int top = grid.size(), bottom = 0, left = grid[0].size(), right = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] != '.') {
                top = min(top, i);
                bottom = max(bottom, i);
                left = min(left, j);
                right = max(right, j);
            }
        }
    }

    vector<vector<char>> trimmedGrid;
    for (int i = top; i <= bottom; ++i) {
        vector<char> row(grid[i].begin() + left, grid[i].begin() + right + 1);
        trimmedGrid.push_back(row);
    }
    return trimmedGrid;
}

// Функция для сохранения сетки в файл
void saveGridToFile(const vector<vector<char>>& grid, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    for (const auto& row : grid) {
        for (char c : row) {
            file << (c == '.' ? ' ' : c);
        }
        file << endl;
    }
    file.close();
}