#include <iostream>
#include <string>
using namespace std;

// Todo: Define an enum GradeCatergory for the different grade categories (fail, pass, merit and distinction)
enum GradeCategory {
    FAIL,
    PASS,
    MERIT,
    DISTINCTION
};


// Todo:  Function calculateAverage to calculate the average of an array of scores as a float.
float calculateAverage(const int scores[],int size)
{
    int sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += scores[i];
    }
    return static_cast<float>(sum) / size;
}


// Todo: Function classify to assign a grade category based on an average value
// Use if-else constructs to assign the correct level

GradeCategory classify(float average) {
    if (average < 50) {
        return FAIL;
    } else if (average < 65) {
        return PASS;
    } else if (average < 80) {
        return MERIT;
    } else {
        return DISTINCTION;
    }
}

// Todo: Function categoryToString to convert enum value to readable string
// Use a switch to return a string per enum value
string categoryToString(GradeCategory category) {
    switch (category) {
        case FAIL: return "Fail";
        case PASS: return "Pass";
        case MERIT: return "Merit";
        case DISTINCTION: return "Distinction";
        default: return "Unknown";
    }
}


int main() {
    // Todo: Define arrays for student names and corresponding grades

    const int NUMBER_STUDENTS=5;
    string names[NUMBER_STUDENTS];
    int scores[NUMBER_STUDENTS];

    // Todo: Ask the user to input names and grades for each student
    cout << "Enter names and grades for " << NUMBER_STUDENTS << " students:"<< endl;

    for (int i =0; i < NUMBER_STUDENTS; ++i){
        cout << "student"<< (i+1)<< " name:"<<endl;
        cin >> names [i];
        do{
            cout << "student"<< (i+1)<< " score (0-100):"<<endl;
        cin >> scores [i];

        if (scores [i]<0 || scores [i]>100) {cout << "Invalid score. Please enter a score between 0 and 100:" << endl;} 
        }while (scores[i] < 0 || scores[i] > 100);
    }
    
    // Todo: Repeat for each student
    // Check if the number is within 0-100




    // Todo: Calculate the class average
    // Classify the average into a category

    float classAverage = calculateAverage(scores, NUMBER_STUDENTS);
    GradeCategory classCategory = classify(classAverage);
    
    // Todo: Print results
    for (int i = 0; i < NUMBER_STUDENTS; ++i) {
        GradeCategory category = classify(scores[i]);
        cout << names[i] << " scored " << scores[i] << " which is a " << categoryToString(category) << endl;
    }

    
    // Todo: Show class average and corresponding category
    cout << "Class average is " << classAverage << " which is a " << categoryToString(classCategory) << endl;


    
    return 0;
}
