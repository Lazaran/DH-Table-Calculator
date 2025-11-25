#ifndef BUILDJOINT_H
#define BUILDJOINT_H

// Standard Libraries
#include <iostream>
#include <vector>
#include <string>

// Custom Libraries
#include "joint.h"
#include "input_lib.h"
#include "linalg_lib.h"

// ========================
// Prototype Declarations
// ========================

// Modify joint type
bool modifyJointType(int idxJoint);

// Modify joint orientation
vector<int> modifyJointOrientation(int idxJoint);

// Modify joint position (CONVERT TO INTEGER VECTOR)
vector<int> modifyJointPosition(int idxJoint);

// Build Joint function prototype
Joint BuildJoint(int idxJoint);

// ========================
// Function Definitions
// ========================

// Modify joint type
bool modifyJointType(int idxJoint){
    // Input loop
    while (true) {
        // Get Joint Type Input
        bool jointType = boolRPQuerySelection("\nIs this Joint Revolute or Prismatic? (R/P): ", 
                                            "\nYou selected Revolute as the joint type.", 
                                            "\nYou selected Prismatic as the joint type.", 
                                            "\nInvalid input. Please enter 'R' for Revolute or 'P' for Prismatic.", true);
        // Confirm Joint Type
        bool confirmJointType = boolYNQuerySelection("\nIs this correct? (Y/N): ", 
                                                    "\nJoint type set successfully.", 
                                                    "\nLet's try again.", 
                                                    "\nInvalid input.", true);
        // Retry if not confirmed
        if (!(confirmJointType)) {
            continue;
        };
        // Return joint type
        return jointType;
    };
};

// Modify joint orientation
vector<int> modifyJointOrientation(int idxJoint){
    // Input loop
    while (true) {
        // Get Joint Orientation Input
        cout << "\nEnter the orientation of the Z axis of Joint " << idxJoint << ": ";
        cout << "\n1 for (1,0,0), 2 for (0,1,0), 3 for (0,0,1), 4 (-1,0,0), 5 (0,-1,0), 6 (0,0,-1): ";
        // Check input for correct type
        vector<int> axisOrientation = mapAxisToOrientation(getInputInt());
        // Confirm Joint Orientation
        bool confirmJointOrientation = boolYNQuerySelection(string("\nIs the orientation " + stringFromIntVector(axisOrientation)) + " correct? (Y/N): ", 
                                                                "\nJoint orientation set successfully.", 
                                                                "\nLet's try again.", 
                                                                "\nInvalid input.", true);
        // Retry if not confirmed
        if (!(confirmJointOrientation)) {
            continue;
        };
        // Return joint orientation
        return axisOrientation;
    };
};

// Modify joint position
vector<int> modifyJointPosition(int idxJoint){
    // Input loop
    while (true) {
        string strPosition;
        cout << "\nEnter the position of Joint " << idxJoint << ": ";
        // Get Joint Position Input and check if input is valid vector format
        strPosition = getInputStr();
        // Retry if format is invalid
        if (!checkForVectorInString(strPosition)){
            continue;
        }
        // Process input string to vector<int> and check if elements are valid
        strPosition = cleanVectorFromString(strPosition);
        // Retry if elements are invalid
        if (!CheckStringyIntVector(strPosition)){
            continue;
        }
        // Confirm Joint Position
        bool confirmJointPosition = boolYNQuerySelection(string("\nIs the position (" + strPosition) + ") correct? (Y/N): ",
                                                                "\nJoint position set successfully.", 
                                                                "\nLet's try again.", 
                                                                "\nInvalid input.", true);
        // Retry if not confirmed
        if (!(confirmJointPosition)) {
            continue;
        };
        // Return joint position as vector<int>
        vector<int>jointPosition = BuildIntVectorFromCleanString(strPosition);
        return jointPosition;
    };
};


// Build Joint Vector by inputting joint parameters
Joint BuildJoint(int idxJoint){
// Output Variables
    bool jointType = true;
    vector<int> jointOrientation = {0,0,0};
    vector<int> jointPosition = {0,0,0};
    // Input Loop
    while (true) {
        // Collect Joint Type
        jointType = modifyJointType(idxJoint);

        // Collect Joint Orientation
        jointOrientation = modifyJointOrientation(idxJoint);

        // Collect Joint Position
        jointPosition = modifyJointPosition(idxJoint);

        // Confirm Joint Parameters
        cout << "\nJoint " << idxJoint << " is " << boolToStr_JointType(jointType) << " with Z orientation " << stringFromIntVector(jointOrientation) << " and Position " << stringFromIntVector(jointPosition) << ".";
        bool confirmJoint = boolYNQuerySelection("\nIs this correct? (Y/N): ", 
                                                "\nJoint parameters set successfully.", 
                                                "\nLet's try again.", 
                                                "\nInvalid input.", true);
        // Retry if not confirmed
        if (!(confirmJoint)) {
            continue;
        };
        break;   
    };
    // Return Constructed Joint
    return Joint(idxJoint, jointType, jointOrientation, jointPosition);
};



#endif // BUILDJOINT_H