// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program takes robotic arm joint info and produces a DH table
// and the Forward Kinematic Equations for a given arm configuration.
// Written by: Senoga Kaweesa, Sergey Mizerin, Qwyntyn Scurr

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
        
        // User Ready Query Loop
        while (true) {
            string queryText = "\nIf you are ready to begin, press Y to continue, otherwise press N to exit: ";
            // Check if the user wants to run the program
            mainLoop = boolYNQuerySelection(queryText,  "\nGlad to have you onboard!\n",
                                                        "\nLeaving so soon?",
                                                        "\nInvalid input.", true);
            // Double check if user wants to exit
            if (!(mainLoop)) {
                mainLoopConfirm = boolYNQuerySelection( "\nAre you sure you want to quit?: ",
                                                        "\nGoodbye!",
                                                        "\nGlad you're sticking around!",
                                                        "\nInvalid input.", true);
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
        
        // Joint Quantity Input Loop
        while (true) {
            cout << "\nPlease consider your end-effector frame as the final joint in the arm.";
            cout << "\nHow many joints are in your robotic arm: ";
            // Get the number of Joints
            numJoints = getInputInt();
            // Validate input number
            if (numJoints > 0) {
                cout << "\nYou have specified that your arm will have " << numJoints << " joints.";
                // Confirm number of joints
                string confirmText = string("\nThank you, your arm has ") + to_string(numJoints) + " joints.\n";
                bool confirmNumJoints = boolYNQuerySelection("\nIs this correct? (Y/N): ", 
                                                            confirmText, 
                                                            "\nLet's try again.", 
                                                            "\nInvalid input. .", true);
                // Restart joint input if confirmation denied
                if (!(confirmNumJoints)) {
                    continue;
                };
                // Reserve space in Joint vector for joints
                Joints.reserve(numJoints);
                break;
            }
            // Handle invalid input
            else {
                cout << "\nInvalid input. Please enter a positive integer.";
            };
        };

        // Input Joint Parameters
        cout << "\nLet's begin inputting the joint parameters.";
        // Loop through quantity of joints
        for (int i = 0; i < numJoints; i++) {
            cout << "\nInputting Parameters for Joint " << i << ": ";
            // Build Joint i and add to Joints vector
            Joints.push_back(BuildJoint(i));
        };
        // End of Joint Parameters Input
        cout << "\nAll Joints have been inputted successfully!\n";
    

        // Selection Menu Loop
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
            // Get Menu Choice Input
            int menuChoice = getInputInt();

            // Select Option from Menu
            switch(menuChoice){
                // Review Joint Configuration
                case 1:
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
                // Handle Invalid Input
                default:
                    cout << "\nInvalid Input. Please Try again!";
            };
            // Break program loop if user chooses to exit
            if (mainLoopConfirm){
                break;
            };
        };
        break;
    };
    return 0;
};