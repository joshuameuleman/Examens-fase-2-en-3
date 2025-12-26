#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (){
    bool success = false;
    string fileName="";
    char ch= '\0';
    ifstream file;
    while (!success) {
        cout<<"Enter a file name: "<<endl;
        getline(cin,fileName);
        file.open(fileName);

            if (file.is_open()) {
            success = true; // we got a valid file, exit the loop
            } else {
            cerr << "Error opening file: " << fileName << endl;
            // loop again and prompt
            }

    }

    // **Open the specified file and read it character by character.**

    while (file.get(ch)) { // read one character at a time
        cout << ch;
    }

    //3. **Count the number of words in the file.**  
    //A word is defined as a sequence of characters separated by spaces, tabs, or newlines.
    int wordCount = 0;
    bool inWord = false;
    file.clear(); 
    file.seekg(0); // terug naar het begin
    while (file.get(ch)) {
        if (isspace(static_cast<unsigned char>(ch))) { 
            if (inWord) {
                inWord = false; // we just exited a word
            }
        } else {
            if (!inWord) {
                inWord = true; // we just entered a word
                wordCount++;
            }
        }
    }
    cout << "\nTotal number of words: " << wordCount << endl;

    file.close();
    return 0;
}


