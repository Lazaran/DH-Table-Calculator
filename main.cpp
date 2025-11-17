#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "joint.h"
using namespace std;

int getInputInt(){
    int num;
    string line;
    getline(cin, line);
    stringstream ss(line);
    ss >> num;
    return num;
};

string getInputStr(){
    string line;
    getline(cin, line);
    return line;
};

// Convert string input to boolean for joint type
bool strToBool(const string& str) {
    if (str == "R" || str == "r") {
        return true; // Revolute
    } else if (str == "P" || str == "p") {
        return false; // Prismatic
    } else {
        throw invalid_argument("Invalid joint type. Use 'R' for Revolute or 'P' for Prismatic.");
    }
};

// Build vector<int> from comma-separated string
// Holding on to the brackets, gotta remove them so the parsing works
vector<int> BuildIntVectorFromString(string inputStr) {
    vector<int> result;
    stringstream ss(inputStr);
    string item;

    while (getline(ss, item, ',')) {
        if (!item.empty()) {
            cout << item << " penis\n";
            result.push_back(stoi(item));
        }
    }

    return result;
}

// Build vector<float> from comma-separated string
vector<float> BuildFloatVectorFromString(string inputStr) {
    vector<float> result;
    result.reserve(3);
    stringstream ss(inputStr);
    float tempNum;
    string item;
    for (int i = 0; i < 3; i++) {
        getline(ss, item, ',');
        stringstream ss_item(item);
        ss_item >> tempNum;
        result[i] = tempNum;
    }
    return result;
};

// Convert vector<int> to string for display
string stringFromIntVector(const vector<int>& vec) {
    string result = "(";
    for (size_t i = 0; i < vec.size(); ++i) {
        result += to_string(vec[i]);
        if (i < vec.size() - 1) {
            result += ",";
        }
    }
    result += ")";
    return result;
};

// Convert vector<float> to string for display
string stringFromFloatVector(const vector<float>& vec) {
    string result = "(";
    for (size_t i = 0; i < vec.size(); ++i) {
        result += to_string(vec[i]);
        if (i < vec.size() - 1) {
            result += ",";
        }
    }
    result += ")";
    return result;
};

// Build Joint Vector by inputting joint parameters
void BuildJointVector(int currentJoint, vector<Joint>& Joints) {
        string temp;
        cout << "\nIs this Joint Revolute or Prismatic? (R/P): ";
        bool jointType = strToBool(getInputStr());
        cout << "\nJoint Orientations are limited to 90 degree rotations\n";
        cout << "Enter the orientation of the Z axis of Joint " << currentJoint << ", eg (0,0,1) for +Z, (0,-1,0) for -Y, etc: ";
        vector<int> jointOrientation = BuildIntVectorFromString(getInputStr());
        cout << jointOrientation[0];
        cout << jointOrientation[1];
        cout << jointOrientation[2];
        cout << "Enter the position of Joint " << currentJoint << ": ";
        vector<float> jointPosition = BuildFloatVectorFromString(getInputStr());
        Joints.push_back(Joint(currentJoint, jointType, jointOrientation, jointPosition));

    };

string checkJointType(bool jointType) {
    if (jointType) {
        return "Revolute";
    } 
    else {
        return "Prismatic";
    };
;}


int main() {

    bool mainloop = true;
    string startCode;
    string confirmCode;
    int numJoints;

    while (mainloop) {

        cout << "Welcome to the DH Calculator!\n";
        cout << "This program takes robotic arm joint info and produces a DH table\n";
        cout << "and the Forward Kinematic Equations for a given arm configuration.\n";
        cout << "If you are ready to begin, press Y to continue, otherwise press N to exit: ";

        // Read Y/N input
        startCode = getInputStr();
        if (startCode.empty() || !(startCode[0] == 'Y' || startCode[0] == 'y')) {
            mainloop = false;
            break;
        }
        
        cout << "\nGlad to have you onboard!\n";

        // Input number of Joints
        while (true) {
            cout << "\nHow many joints are in your robotic arm: ";
            numJoints = getInputInt();
            if (numJoints > 0) {
                break;  // success
            };
            cout << "Invalid input. Please enter a positive integer.\n";
            cout << "\n You have specified that your arm will have " << numJoints << " joints.\n";
            cout << "Is this correct? (Y/N): ";
            confirmCode = getInputStr();
            if (!(confirmCode.empty() || !(startCode[0] == 'Y' || startCode[0] == 'y'))) {
                break;
            };
            cout << "Let's try again.\n";
        };

        cout << "Let's begin inputting the joint parameters.\n";
        
        vector<Joint> Joints;
        Joints.reserve(numJoints);
        // Start inputting joint parameters
        cout << "Inputting Base Joint Parameters:\n";
        cout << "Is your base joint Revolute or Prismatic? (R/P): ";

        // Input base joint type
        bool baseJointType = strToBool(getInputStr());
        Joints.push_back(Joint(0, baseJointType, {0,0,1}, {0.0,0.0,0.0})); // Base Joint
        cout << "Base Joint set as Joint 0, and is " << checkJointType(baseJointType) << " with default Z orientation (0,0,1) and Position (0.0,0.0,0.0)\n";
        
        // Input remaining joint parameters
        for (int i = 1; i < numJoints; i++) {
            while (true){
                // Input joint parameters
                cout << "\nInputting Parameters for Joint " << i << ":\n";
                BuildJointVector(i, Joints);
                // Confirm joint parameters
                cout << "Joint " << Joints[i].getIndex() << " is " << checkJointType(Joints[i].getisRevolute()) << "with Z orientation " << stringFromIntVector(Joints[i].getZaxis()) << " and Position " << stringFromFloatVector(Joints[i].getPos()) << " \n";
                cout << "Is this correct? (Y/N): ";
                confirmCode = getInputStr();
                // If confirmed, break loop
                if (!(confirmCode.empty() || !(startCode[0] == 'Y' || startCode[0] == 'y'))) {
                    "Then Try again!\n";
                    continue;
                }
                break;         
            };
        };
    };
    cout << "Exiting Program. Goodbye!\n";
    return 0;
};