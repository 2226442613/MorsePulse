---

## main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <cctype>
#include <limits>

using namespace std;

class MorseCodeApp {
private:
    unordered_map<char, string> charToMorse;
    unordered_map<string, char> morseToChar;

    void initializeMaps() {
        charToMorse = {
            {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
            {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
            {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
            {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
            {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
            {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
            {'Y', "-.--"},  {'Z', "--.."},

            {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
            {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
            {'8', "---.."}, {'9', "----."},

            {'.', ".-.-.-"}, {',', "--..--"}, {'?', "..--.."},
            {'!', "-.-.--"}, {'-', "-....-"}, {'/', "-..-."},
            {'(', "-.--."},  {')', "-.--.-"}, {':', "---..."},
            {';', "-.-.-."}, {'=', "-...-"},  {'+', ".-.-."},
            {'_', "..--.-"}, {'"', ".-..-."}, {'$', "...-..-"},
            {'@', ".--.-."}
        };

        for (const auto& pair : charToMorse) {
            morseToChar[pair.second] = pair.first;
        }
    }

    static void sleepUnits(int units, int baseMs) {
        this_thread::sleep_for(chrono::milliseconds(units * baseMs));
    }

    static string toUpperString(const string& input) {
        string result = input;
        for (char& c : result) {
            c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

public:
    MorseCodeApp() {
        initializeMaps();
    }

    string encodeText(const string& text) {
        string upper = toUpperString(text);
        ostringstream output;
        bool firstToken = true;

        for (char c : upper) {
            if (c == ' ') {
                if (!firstToken) {
                    output << " ";
                }
                output << "/";
                firstToken = false;
            } else if (charToMorse.count(c)) {
                if (!firstToken) {
                    output << " ";
                }
                output << charToMorse[c];
                firstToken = false;
            }
        }

        return output.str();
    }

    string decodeMorse(const string& morse) {
        istringstream input(morse);
        string token;
        ostringstream output;

        while (input >> token) {
            if (token == "/") {
                output << ' ';
            } else if (morseToChar.count(token)) {
                output << morseToChar[token];
            } else {
                output << '?';
            }
        }

        return output.str();
    }

    void simulateLight(const string& morse, int unitMs) {
        cout << "\n--- Light Simulation ---\n";

        for (size_t i = 0; i < morse.size(); ++i) {
            char c = morse[i];

            if (c == '.') {
                cout << "[LIGHT ON ] Dot\n";
                sleepUnits(1, unitMs);
                cout << "[LIGHT OFF]\n";
                sleepUnits(1, unitMs);
            } else if (c == '-') {
                cout << "[LIGHT ON ] Dash\n";
                sleepUnits(3, unitMs);
                cout << "[LIGHT OFF]\n";
                sleepUnits(1, unitMs);
            } else if (c == ' ') {
                sleepUnits(2, unitMs); // extra pause because 1 already added after symbol
            } else if (c == '/') {
                cout << "[WORD GAP]\n";
                sleepUnits(6, unitMs); // extra pause
            }
        }

        cout << "--- End Light Simulation ---\n";
    }

    void simulateAudio(const string& morse, int unitMs) {
        cout << "\n--- Audio Simulation ---\n";

        for (size_t i = 0; i < morse.size(); ++i) {
            char c = morse[i];

            if (c == '.') {
                cout << "BEEP (dot)\a\n";
                sleepUnits(1, unitMs);
                sleepUnits(1, unitMs);
            } else if (c == '-') {
                cout << "BEEP (dash)\a\n";
                sleepUnits(3, unitMs);
                sleepUnits(1, unitMs);
            } else if (c == ' ') {
                sleepUnits(2, unitMs);
            } else if (c == '/') {
                cout << "[WORD GAP]\n";
                sleepUnits(6, unitMs);
            }
        }

        cout << "--- End Audio Simulation ---\n";
    }

    static void showMenu() {
        cout << "\n========== MorsePulse ==========\n";
        cout << "1. Encode text to Morse code\n";
        cout << "2. Decode Morse code to text\n";
        cout << "3. Simulate light transmission\n";
        cout << "4. Simulate audio transmission\n";
        cout << "5. Quit\n";
        cout << "Choose an option: ";
    }
};

int main() {
    MorseCodeApp app;
    int choice = 0;
    int unitMs = 200;

    cout << "Enter Morse timing unit in milliseconds (recommended 150-300): ";
    cin >> unitMs;

    if (cin.fail() || unitMs <= 0) {
        cout << "Invalid input. Using default 200 ms.\n";
        cin.clear();
        unitMs = 200;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        MorseCodeApp::showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid selection.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string text;
            cout << "Enter text: ";
            getline(cin, text);
            string morse = app.encodeText(text);
            cout << "Morse: " << morse << "\n";
        }
        else if (choice == 2) {
            string morse;
            cout << "Enter Morse code (use / between words): ";
            getline(cin, morse);
            string text = app.decodeMorse(morse);
            cout << "Decoded text: " << text << "\n";
        }
        else if (choice == 3) {
            string text;
            cout << "Enter text to transmit as light: ";
            getline(cin, text);
            string morse = app.encodeText(text);
            cout << "Morse: " << morse << "\n";
            app.simulateLight(morse, unitMs);
        }
        else if (choice == 4) {
            string text;
            cout << "Enter text to transmit as audio: ";
            getline(cin, text);
            string morse = app.encodeText(text);
            cout << "Morse: " << morse << "\n";
            app.simulateAudio(morse, unitMs);
        }
        else if (choice == 5) {
            cout << "Goodbye.\n";
            break;
        }
        else {
            cout << "Please choose a valid option.\n";
        }
    }

    return 0;
}
