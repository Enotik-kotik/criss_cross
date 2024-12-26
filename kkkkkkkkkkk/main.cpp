#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "crossword.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Проверяем, был ли передан аргумент с именем файла
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <output_filename>" << endl;
        return 1;
    }

    // Имя выходного файла из аргумента командной строки
    string outputFilename = argv[1];

    vector<string> words = { "history", "science", "culture", "language", "technology", "mathematics", "philosophy", "geography" };

    // Сортируем слова по длине (от большего к меньшему)
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.size() > b.size();
        });

    // Генерируем кроссворд
    vector<vector<char>> crossword = generateCrossword(words);

    // Обрезаем сетку
    crossword = trimGrid(crossword);

    // Сохраняем сетку в файл
    saveGridToFile(crossword, outputFilename);

    return 0;
}