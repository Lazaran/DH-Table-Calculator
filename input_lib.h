#ifndef INPUT_LIB_H
#define INPUT_LIB_H

// Standard Libraries
#include <iostream>
#include <cmath>
#include <string>   
#include <vector>
#include <sstream>
#include <algorithm>

// Using standard namespace
using namespace std;

// ========================
// Prototype Declarations
// ========================

// Get integer input from user
int getInputInt();

// Get string input from user
string getInputStr();

// Convert string input to boolean for joint type
bool strToBool_JointType(const string& str);

// Check joint type and return string for display
string boolToStr_JointType(bool jointType);

// Check if the vector string input is valid
bool checkForVectorInString(const string& str);

// Check if the vector string input is valid for int or float vector and remove spaces and outside parentheses
string cleanVectorFromString(const string& str);

// Check comma-separated string for integer vector validity vector
bool CheckStringyIntVector(const string& str);

// Check comma-separated string for float vector validity
// Technically deprecated since position is integer-based now, but kept for potential future use
bool CheckStringyFloatVector(const string& str);

// Build vector<int> from clean comma-separated string
vector<int> BuildIntVectorFromCleanString(const string& str);

// Build vector<float> from clean comma-separated string
// Technically deprecated since position is integer-based now, kept for potential future use
vector<float> BuildFloatVectorFromCleanString(const string& str);

// Convert vector<int> to string for display
string stringFromIntVector(const vector<int>& vec);

// Convert vector<float> to string for display
string stringFromFloatVector(const vector<float>& vec);

// Convert Y/N string input to boolean with default value
bool boolYNQuerySelection(const string& qText, const string& cText, const string& dText, const string& eText, bool defaultValue);

// Convert R/P string input to boolean with default value
bool boolRPQuerySelection(const string& qText, const string& cText, const string& dText, const string& eText, bool defaultValue);

// ========================
// Function Definitions
// ========================

// Get integer input from user
int getInputInt(){
    int num;
    string line;
    // Get line input
    getline(cin, line);
    // Use stringstream for conversion
    stringstream ss(line);
    // Extract integer
    ss >> num;
    // Return the extracted integer
    return num;
};

// Get string input from user
string getInputStr(){
    string line;
    // Get line input
    getline(cin, line);
    // Return the input string
    return line;
};

// Unused function because of boolRPQuerySelection
// Convert string input to boolean for joint type
bool strToBool_JointType(const string& str){
    if (str == "R" || str == "r") {
        return true; // Revolute
    }
    return false; // Prismatic
};

// Check joint type and return string for display
string boolToStr_JointType(bool jointType){
    // Return Revolute if true, Prismatic if false
    if (jointType) {
        return "Revolute";
    } 
    else {
        return "Prismatic";
    };
};

// Check if the vector string input is valid
bool checkForVectorInString(const string& str){
    // Check for presence of parentheses
    if (str.find('(') != string::npos && str.find(')') != string::npos) {
        return true;
    }
    // Invalid format
    else {
        cout << "\nInvalid vector format. Please use parentheses (e.g., (1,2,3)).";
        return false;
    }
};

// Remove spaces and outside parentheses from vector string input and return cleaned string
string cleanVectorFromString(const string& str){
    string cleanedStr = str;
    // Remove spaces using std::remove to avoid ambiguity with C remove()
    cleanedStr.erase(remove(cleanedStr.begin(), cleanedStr.end(), ' '), cleanedStr.end());
    // Remove parentheses if present and string is non-empty
    if (!cleanedStr.empty() && cleanedStr.front() == '(' && cleanedStr.back() == ')') {
        cleanedStr = cleanedStr.substr(1, cleanedStr.size() - 2);
    }
    // Return cleaned string
    return cleanedStr;
};

// Check comma-separated string for integer vector validity vector
bool CheckStringyIntVector(const string& str){
    bool result = false;
    string cleanedStr = str;
    stringstream ss(cleanedStr);
    string item;
    // First pass, checking X element
    // Grab X element
    getline(ss, item, ',');
    // Check if X element is a valid integer
    if (!((all_of(item.begin(), item.end(), ::isdigit)) || (item.front() == '-' && all_of(item.begin() + 1, item.end(), ::isdigit)))) {
        cout << "\nUse integers for vector input in the X position.";
        return result;
    }
    // Second pass, checking Y element
    // Grab Y element
    getline(ss, item, ',');
    // Check if Y element is a valid integer
    if (!((all_of(item.begin(), item.end(), ::isdigit)) || (item.front() == '-' && all_of(item.begin() + 1, item.end(), ::isdigit)))) {
        cout << "\nUse integers for vector input in the Y position.";
        return result;
    }
    // Third pass, checking Z element
    // Grab Z element
    getline(ss, item);
    // Check if Z element is a valid integer
    if (!((all_of(item.begin(), item.end(), ::isdigit)) || (item.front() == '-' && all_of(item.begin() + 1, item.end(), ::isdigit)))) {
        cout << "\nUse integers for vector input in the Z position.";
        return result;
    }
    // If all elements passed checks, return true
    result = true;
    return result;
};

// Check comma-separated string for float vector validity
// Technically deprecated since position is integer-based now, but kept for potential future use
bool CheckStringyFloatVector(const string& str){
    bool result = false;
    string cleanedStr = str;
    stringstream ss(cleanedStr);
    string item;
    // First pass, grabbing X element
    getline(ss, item, '.');
    if (!((all_of(item.begin(), item.end(), ::isdigit)) || (item.front() == '-' && all_of(item.begin() + 1, item.end(), ::isdigit)))) {
        cout << "\nUse floats for vector input in the X position.";
        return result;
    }
    getline(ss, item, ',');
    if (!(all_of(item.begin(), item.end(), ::isdigit))) {
        cout << "\nUse floats for vector input in the X position.";
        return result;
    }
    // Second pass, grabbing Y element
    getline(ss, item, '.');
    if (!((all_of(item.begin(), item.end(), ::isdigit)) || (item.front() == '-' && all_of(item.begin() + 1, item.end(), ::isdigit)))) {
        cout << "\nUse floats for vector input in the Y position.";
        return result;
    }
    getline(ss, item, ',');
    if (!(all_of(item.begin(), item.end(), ::isdigit))) {
        cout << "\nUse floats for vector input in the Y position.";
        return result;
    }
    // Third pass, grabbing Z element
    getline(ss, item, '.');
    if (!((all_of(item.begin(), item.end(), ::isdigit)) || (item.front() == '-' && all_of(item.begin() + 1, item.end(), ::isdigit)))) {
        cout << "\nUse floats for vector input in the Z position.";
        return result;
    }
    getline(ss, item);
    if (!(all_of(item.begin(), item.end(), ::isdigit))) {
        cout << "\nUse floats for vector input in the Z position.";
        return result;
    }
    // If all elements passed checks, return true
    result = true;
    return result;
};

// Build vector<int> from clean comma-separated string
vector<int> BuildIntVectorFromCleanString(const string& str){
    vector<int> result;
    string cleanedStr = str;
    stringstream ss(cleanedStr);
    string item;
    // First pass, grabbing X element
    getline(ss, item, ',');
    // Add X element to result vector
    result.push_back(stoi(item));
    // Second pass, grabbing Y element
    getline(ss, item, ',');
    // Add Y element to result vector
    result.push_back(stoi(item));
    // Third pass, grabbing Z element
    getline(ss, item);
    // Add Z element to result vector
    result.push_back(stoi(item));
    // Return result vector
    return result;
};

// Build vector<float> from clean comma-separated string
// Technically deprecated since position is integer-based now, kept for potential future use
vector<float> BuildFloatVectorFromCleanString(const string& str){
    vector<float> result;
    string cleanedStr = str;
    stringstream ss(cleanedStr);
    string item;
    // First pass, grabbing X element
    getline(ss, item, ',');
    result.push_back(stof(item));
    // Second pass, grabbing Y element
    getline(ss, item, ',');
    result.push_back(stof(item));
    // Third pass, grabbing Z element
    getline(ss, item);
    result.push_back(stof(item));
    return result;
};


// Convert vector<int> to string for display
string stringFromIntVector(const vector<int>& vec){
    string result = "(";
    // Loop through vector elements
    for (int i = 0; i < 3; i++) {
        // Append element to result string
        result += to_string(vec[i]);
        // Add comma if not the last element
        if (i < 2) {
            result += ",";
        }
    }
    // Append closing parenthesis
    result += ")";
    // Return result string
    return result;
};

// Convert vector<float> to string for display
// Technically deprecated since all vectors are integer-based now, but kept for potential future use
string stringFromFloatVector(const vector<float>& vec){
    string result = "(";
    for (int i = 0; i < 3; ++i) {
        result += to_string((round(vec[i]*100)/100));
        if (i < 2) {
            result += ",";
        }
    }
    result += ")";
    return result;
};

// Convert Y/N string input to boolean with default value
bool boolYNQuerySelection(const string& qText, const string& cText, const string& dText, const string& eText, bool defaultValue){
    bool result = defaultValue;
    string responseCode;
    // Input loop
    while (true) {
        // Prompt user with query text
        cout << qText;
        // Get user input
        responseCode = getInputStr();
        // Check for Y/y input
        if ((responseCode == "Y" || responseCode == "y")) {
            // Display confirmation text and break loop
            cout << cText;
            break;
        };
        // Check for N/n input
        if ((responseCode == "N" || responseCode == "n")) {
            // Set result to opposite of default value, display denial text, and break loop
            result = !defaultValue;
            cout << dText;
            break;
        };
        // Handle invalid input by displaying error text
        cout << eText;
    };
    // Return boolean result
    return result;
};

// Convert R/P string input to boolean with default value
bool boolRPQuerySelection(const string& qText, const string& cText, const string& dText, const string& eText, bool defaultValue){
    bool result = defaultValue;
    string responseCode;
    // Input loop
    while (true) {
        // Prompt user with query text
        cout << qText;
        // Get user input
        responseCode = getInputStr();
        // Check for R/r input
        if ((responseCode == "R" || responseCode == "r")) {
            // Display confirmation text and break loop
            cout << cText;
            break;
        };
        // Check for P/p input
        if ((responseCode == "P" || responseCode == "p")) {
            // Set result to opposite of default value, display denial text, and break loop
            result = !defaultValue;
            cout << dText;
            break;
        };
        // Handle invalid input by displaying error text
        cout << eText;
    };
    // Return boolean result
    return result;
};

#endif // INPUT_LIB_H