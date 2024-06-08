#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    char ch;
    unordered_map<char, Node*> children;
    bool isEndOfWord;

    Node(char c) : ch(c), isEndOfWord(false) {}
};

class Trie {
public:
    Trie() {
        root = new Node('\0');
    }

    void insert(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new Node(ch);
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        Node* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }

private:
    Node* root;
};

void loadDictionary(Trie& trie, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Tidak dapat membukan file kamus!" << endl;
        return;
    }

    string word;
    while (file >> word) {
        trie.insert(word);
    }

    file.close();
}

int main() {
    Trie trie;

    loadDictionary(trie, "words.txt");

    string input;
    cout << "Masukkan kata untuk dicek: ";
    cin >> input;

    if (trie.search(input)) {
        cout << "Penulisan Kata '" << input << "' ditulis dengan benar." << endl;
    } else {
        cout << "Penulisan kata '" << input << "' salah." << endl;
    }

    return 0;
}