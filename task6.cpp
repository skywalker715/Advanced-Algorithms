#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> formatText(const string& inputText, int maxWidth) {
    istringstream stream(inputText);
    string word;
    vector<string> formattedLines;
    string line;

    while (stream >> word) {
        if (line.length() + word.length() + 1 > maxWidth) {
            formattedLines.push_back(line);
            line = word;
        } else {
            if (!line.empty()) line += " ";
            line += word;
        }
    }

    if (!line.empty()) {
        formattedLines.push_back(line);
    }

    return formattedLines;
}

int main() {
    string text = "Mary loves to sing and perform tapdancing.";
    int maxWidth = 10;
    vector<string> wrappedText = formatText(text, maxWidth);

    for (size_t i = 0; i < wrappedText.size(); i++) {
        cout << "Line " << i + 1 << ": " << wrappedText[i] << endl;
    }

    return 0;
}
