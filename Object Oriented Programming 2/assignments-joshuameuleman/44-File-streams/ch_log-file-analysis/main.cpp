#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// voor 2b - manual ASCII to-lower conversion (avoids <cctype>)
string toLowerCase(const string& str) {
    string lowerStr = str;
    for (size_t i = 0; i < lowerStr.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(lowerStr[i]);
        if (c >= 'A' && c <= 'Z') {
            lowerStr[i] = static_cast<char>(c - 'A' + 'a');
        }
    }
    return lowerStr;
}

int main(){

    int errorCount=0;
    int warningCount=0;
    int infoCount=0;
    string LogFile="";    
    string line="";
    int totalLine=0;
    string messages[1000];   
    int counts[1000];        
    int uniqueCount = 0;     
    vector<string> allLines; 
    vector<string> allLinesLower; // lowercase copies for case-insensitive search
    string filter="";
    bool success = false;
    ifstream file;

    while (!success) {
        cout << "Enter a log file (ex. server.log): " << endl;

        getline(cin, LogFile);
        file.open(LogFile);
        if (file.is_open()) {
            success = true; // we got a valid file, exit the loop
        } else {
            cerr << "Error opening file: " << LogFile << endl;
            // loop again and prompt
        }
    }
 


    


    while (getline(file, line)) {
        totalLine++;
        allLines.push_back(line);

        // create lowercase copy for case-insensitive checks
        string lineLower = toLowerCase(line);
        allLinesLower.push_back(lineLower);

        if (lineLower.find("error") != string::npos) {
            errorCount++;
        }
        if (lineLower.find("warning") != string::npos) {
            warningCount++;
        }
        if (lineLower.find("info") != string::npos) {
            infoCount++;
        }
// Extract message after log type
         size_t pos = line.find(": ");
        if (pos != string::npos) {
            string message = line.substr(pos + 2);

            
            bool found = false;
            for (int i = 0; i < uniqueCount; i++) {
                if (messages[i] == message) {
                    counts[i]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                messages[uniqueCount] = message;
                counts[uniqueCount] = 1;
                uniqueCount++;
            }
        }


    }

    cout<<"Total number of lines:"<< totalLine<<endl;
    cout<<"Total number of ERRORS: "<< errorCount<<endl;
    cout<<"Total number of WARNINGS: "<< warningCount<<endl;
    cout<<"Total number of INFO'S: "<< infoCount<<endl;
// Display top 3 most frequent messages
    for (int k = 0; k < 3; k++) {
        int maxIndex = -1;
        int maxValue = -1;

        for (int i = 0; i < uniqueCount; i++) {
            if (counts[i] > maxValue) {
                maxValue = counts[i];
                maxIndex = i;
            }
        }

        if (maxIndex != -1 && maxValue > 0) {
            cout << k+1 << ". " << messages[maxIndex]
                 << " - " << counts[maxIndex] << " times" << endl;
            counts[maxIndex] = 0; 
        }
    }

         while (true) {
        cout << "\nEnter log type to filter (ERROR, WARNING, INFO) or 'q' to quit: ";
        cin >> filter;

        string filterLower = toLowerCase(filter);
        if (filterLower == "q") {
            break;
        }

        bool valid = (filterLower == "error"  || filterLower == "warning" || filterLower == "info");
        if (!valid) {
            cout << "Invalid filter type. Try again." << endl;
            continue;
        }

        cout << "\nFiltered " << filter << " logs:\n";
        for (size_t idx = 0; idx < allLines.size(); ++idx) {
            if (allLinesLower[idx].find(filterLower) != string::npos) {
                cout << allLines[idx] << endl;
            }
        }
    }

    cout << "Exiting program.\n";

     
    file.close();





return 0;

}