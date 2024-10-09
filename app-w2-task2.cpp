#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Structure to store word and its frequency
struct WordFreqPair {
    string word;
    int count;
};

// Function to check if a character is a sentence-ending punctuation
bool isSentenceEnd(char ch) {
    return ch == '.' || ch == '!' || ch == '?';
}

// Function to remove punctuation from a word
string removePunctuation(const string& word) {
    string cleanWord; // Initialize an empty string to hold the cleaned word
    for (char c : word) { // Loop through each character in the input word
        if (!ispunct(c)) { // Check if the character is not punctuation
            cleanWord += c; // Append non-punctuation characters to cleanWord
        }
    }
    return cleanWord; // Return the cleaned word
}

// Function to find if a word already exists in the wordList vector
int findWordIndex(const vector<WordFreqPair>& wordList, const string& word) {
    for (int i = 0; i < wordList.size(); ++i) {
        if (wordList[i].word == word) {
            return i;  // Return index if the word is found
        }
    }
    return -1;  // Return -1 if the word is not found
}

// Function to process the document and generate a summary
void processDocument(const string& filename) {
    ifstream file(filename);  // Open file for reading
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    vector<WordFreqPair> wordList;  // Vector to store WordFreqPair objects
    int numberOfWords = 0;
    int numberOfSentences = 0;
    string word;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);  // Read the line into a stringstream

        while (ss >> word) {  // Extract words from the line
            word = removePunctuation(word); // Clean the word from punctuation

            // If word is not empty after processing
            if (!word.empty()) {
                // Find if the word already exists in the wordList vector
                int index = findWordIndex(wordList, word);
                if (index != -1) {
                    wordList[index].count++;  // Increment count if word exists
                }
                else {
                    // Add a new WordFreqPair object if word does not exist
                    WordFreqPair newPair{ word, 1 };
                    wordList.push_back(newPair);
                }
                numberOfWords++;
            }
        }

        // Check for sentence-ending punctuation in the line
        for (char ch : line) {
            if (isSentenceEnd(ch)) {
                numberOfSentences++;
            }
        }
    }

    // Output results
    cout << "Number of sentences: " << numberOfSentences << endl;
    cout << "Number of words: " << numberOfWords << endl;

    // Output word frequencies in case-sensitive format
    for (const auto& entry : wordList) {
        cout << entry.word << "\t" << entry.count << endl;
    }

    file.close();  // Close the file
}

int main() {
    string filename;

    // Get the filename from the user
    cout << "Enter the filename: ";
    cin >> filename;

    // Process the document to generate a summary
    processDocument(filename);

    return 0;
}
