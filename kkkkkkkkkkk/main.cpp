#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "crossword.h"

using namespace std;

int main(int argc, char* argv[]) {
    // ���������, ��� �� ������� �������� � ������ �����
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <output_filename>" << endl;
        return 1;
    }

    // ��� ��������� ����� �� ��������� ��������� ������
    string outputFilename = argv[1];

    vector<string> words = { "history", "science", "culture", "language", "technology", "mathematics", "philosophy", "geography" };

    // ��������� ����� �� ����� (�� �������� � ��������)
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.size() > b.size();
        });

    // ���������� ���������
    vector<vector<char>> crossword = generateCrossword(words);

    // �������� �����
    crossword = trimGrid(crossword);

    // ��������� ����� � ����
    saveGridToFile(crossword, outputFilename);

    return 0;
}