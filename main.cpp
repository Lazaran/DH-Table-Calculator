// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program takes robotic arm joint info and produces a DH table
// and the Forward Kinematic Equations for a given arm configuration.
// Written by: Senoga Kaweesa, Sergey Mizerin, Qwyntyn Scurr, n

// include standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>

// Using standard namespace
using namespace std;

// Include custom libraries
#include "joint.h"
#include "input_lib.h"
#include "transform_matrix.h"
#include "buildjoint.h"
#include "main_blocks.h"

// Main Program
int main() {

    // Main Loop Variables
    bool mainLoop = true;
    bool mainLoopConfirm = false;
    int numJoints = 0;
    vector<Joint> Joints;

    // Main Program Loop
    while (true) {

        // Welcome Message
        cout << "\nWelcome to the DH Calculator!";
        cout << "\nThis program takes robotic arm joint info and produces a DH table";
        cout << "\nand the Forward Kinematic Equations for a given arm configuration.";
        
        // Read Y/N input
        while (true) {
            // Check if user wants to start the program
            string queryText = "\nIf you are ready to begin, press Y to continue, otherwise press N to exit: ";
            mainLoop = boolYNQuerySelection(queryText, "\nGlad to have you onboard!\n", "\nLeaving so soon?", "\nInvalid input.", true);
            // Double check if user wants to exit
            if (!(mainLoop)) {
                mainLoopConfirm = boolYNQuerySelection("\nAre you sure you want to quit?: ", "\nGoodbye!", "\nGlad you're sticking around!", "\nInvalid input.", true);
                // Confirm exit choice
                if (!mainLoopConfirm){
                    continue;
                };
            };
            break;
        };
        // Exit main program if user chooses N
        if (mainLoopConfirm) {
            break;
        };
        
        // Input number of joints
        while (true) {
            // Get the number of joints in the arm
            cout << "\nPlease consider your end-effector frame as the final joint in the arm.";
            cout << "\nHow many joints are in your robotic arm: ";
            numJoints = getInputInt();
            // Validate input
            if (numJoints > 0) {
                cout << "\nYou have specified that your arm will have " << numJoints << " joints.";
                string confirmText = string("\nThank you, your arm has ") + to_string(numJoints) + " joints.\n";
                // Confirm number of joints
                bool confirmNumJoints = boolYNQuerySelection("\nIs this correct? (Y/N): ", confirmText, "\nLet's try again.", "\nInvalid input. .", true);
                // Restart input if confirmation denied
                if (!(confirmNumJoints)) {
                    continue;
                };
                Joints.reserve(numJoints);
                break;  // success
            }
            // Handle invalid input
            else {
                cout << "\nInvalid input. Please enter a positive integer.";
            };
        };

        // Start inputting joint parameters
        cout << "\nLet's begin inputting the joint parameters.";
        cout << "\nInputting Base Joint Parameters: \n";

        // Input base joint type
        while (true) {
            // Get base joint type
            bool baseJointType = modifyJointType(0);
            // Get base joint Z orientation
            vector<int> baseJointOrientation = modifyJointOrientation(0);
            // Add base joint to joint vector
            Joints.push_back(Joint(0, baseJointType, baseJointOrientation, vector<int>{0,0,0}));
            cout << "\nBase Joint set as Joint " << Joints.at(0).getIndex() << ", and is " << boolToStr_JointType(Joints.at(0).getisRevolute()) << " with default Z Orientation " << stringFromIntVector(Joints.at(0).getZaxis()) << " and Position " << stringFromIntVector(Joints.at(0).getZaxis()) << ".\n";
            break;
        };

        // Input remaining joint parameters
        for (int i = 1; i < numJoints; i++) {
            // Input joint parameters
            cout << "\nInputting Parameters for Joint " << i << ": ";
            Joints.push_back(BuildJoint(i));
            // Confirm joint parameters
        };

        cout << "\nAll Joints have been inputted successfully!\n";
    

        // Menu Options
        while (true){
            // Internal X axis calculation for each joint based on Z axis orientations 
            // Done at the top of every menu loop to ensure X axes are always up to date
            CalculateXOrientations(Joints);

            // Display Menu Options
            cout << "\nWhat would you like to do next?:";
            cout << "\n  1: Review Joint Configuration.";
            cout << "\n  2: Calculate DH Table.";
            cout << "\n  3: Change Joint Configuration.";
            cout << "\n  4: Exit Program.";
            cout << "\nSelecting: ";
            int menuChoice = getInputInt();
            // Select Option from Menu
            switch(menuChoice){
                case 1:
                    // Review Joint Configuration
                    cout << "\nYou've selected to review your joint configuration.";
                    JointConfigurationReview(Joints);
                    break;
                // Calculate DH Table
                case 2:
                    cout << "\nYou've selected to calculate the DH table.";
                    CalculateDH_Table(Joints);
                    break;
                // Change Joint Configuration    
                case 3:
                    cout << "\nYou've selected to change your joint configuration";
                    ChangeJointConfiguration(Joints);
                    break;
                // Exit Program
                case 4:
                    // Confirm exit choice
                    mainLoopConfirm = boolYNQuerySelection("\nAre you sure you want to quit?: ", "\nGoodbye!", "\nGlad you're sticking around!", "\nInvalid input.", true);
                    break;
                default:
                cout << "\nInvalid Input. Please Try again!";
            };
            if (mainLoopConfirm){
                break;
            };
        };
        break;
    };
    return 0;
};