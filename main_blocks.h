#ifndef MAIN_BLOCKS_H
#define MAIN_BLOCKS_H

// Standard Libraries
#include <vector>

// Using standard namespace
using namespace std;

// Custom Libraries
#include "joint.h"
#include "buildjoint.h"
#include "input_lib.h"
#include "linalg_lib.h"

// ========================
// Prototype Declarations
// ========================

// Determine X axis based on Z axis using right-hand rule
int RightHandRule(vector<int> zAxis);

// Prints Joints Configuration
void JointConfigurationReview(vector<Joint>& Joints);

// Calculates DH Table from Joint Configuration
void CalculateDH_Table(vector<Joint> Joints);

// Allows User to change any part of any Joint
void ChangeJointConfiguration(vector<Joint>& Joints);

// ========================
// Function Definitions
// ========================

// Prints Joints Configuration
void JointConfigurationReview(vector<Joint>& Joints){
    cout << "\n===========================";
    cout << "\nJoint Configuration Review:";
    cout << "\n===========================\n";
    // Loop through joints and print their parameters
    for (int i = 0; i < Joints.size(); i++) {
        cout << "\n===== Joint " << i << " =====\n";
        cout << "|  Joint Index: " << Joints.at(i).getIndex() << endl;
        cout << "|  Joint Type: " << boolToStr_JointType(Joints.at(i).getisRevolute()) << endl;
        cout << "|  Joint Z Orientation: " << stringFromIntVector(Joints.at(i).getZaxis()) << endl;
        cout << "|  Joint X Orientation: " << stringFromIntVector(Joints.at(i).getXaxis()) << endl;
        cout << "|  Joint Position: " << stringFromIntVector(Joints.at(i).getOriginPos()) << endl;            
    };
    cout << "\n===========================";
    cout << "\n    End of Joint Review    ";
    cout << "\n===========================\n";
};

// Allows User to change any part of any Joint
void ChangeJointConfiguration(vector<Joint>& Joints){
    while (true){
        // Select Joint to modify
        cout << "\nThere are " << Joints.size() << " joints. Which Joint would you like to modify?";
        cout << "\nSelecting: ";
        int jointIndex = getInputInt();
        if (jointIndex < 0 || jointIndex >= Joints.size()) {
            cout << "\nInvalid Joint Index.";
            continue;
        }
        while (true) {
            // Select parameter to modify
            cout << "\nYou have selected Joint " << jointIndex << ". What parameter would you like to modify?";
            cout << "\n  1: Joint Type";
            cout << "\n  2: Joint Z Orientation";
            cout << "\n  3: Joint Position";
            cout << "\n Selecting: ";
            int paramChoice = getInputInt();
            // Modify selected parameter
            switch (paramChoice) {
                case 1:
                    // Modify Joint Type
                    Joints.at(jointIndex).setisRevolute(modifyJointType(jointIndex));
                    break;
                case 2:
                    // Modify Joint Z Orientation
                    Joints.at(jointIndex).setZaxis(modifyJointOrientation(jointIndex));
                    break;
                case 3:
                    // Modify Joint Position
                    Joints.at(jointIndex).setPosition(modifyJointPosition(jointIndex));
                    break;
                default:
                    cout << "\nInvalid parameter choice.";
                    break;
            };
            // Ask if user wants to modify another parameter of the same joint
            bool modifyAnotherParam = boolYNQuerySelection(string("\nWould you like to modify another parameter for Joint " + to_string(jointIndex) + "? (Y/N): "), "\nModifying another parameter.", "\nReturning to Joint selection.", "\nInvalid input.", true);
            if (!modifyAnotherParam) {
                break;
            };
        };
        // Ask if user wants to modify another joint
        bool modifyAnotherJoint = boolYNQuerySelection("\nWould you like to modify another Joint? (Y/N): ", "\nModifying another Joint.", "\nExiting Joint modification.", "\nInvalid input.", true);
        if (!modifyAnotherJoint) {
            break;
        };
    };
};

// Internal X axis calculation for each joint based on Z axis orientations
void CalculateXOrientations(vector<Joint>& Joints) {
    // Set base joint X axis using right-hand rule
    Joints.at(0).setXaxis(mapAxisToOrientation(RightHandRule(Joints.at(0).getZaxis())));
    // Iterate over each joint to set X axis based on current and previous Z axis orientations
    for (int i = 1; i < Joints.size(); i++) {
        // Select current and previous joints
        Joint& currentJoint = Joints.at(i);
        Joint& previousJoint = Joints.at(i - 1);
        // Select current and previous Z axis orientations
        vector<int> currentZAxis = currentJoint.getZaxis();
        vector<int> prevZAxis = previousJoint.getZaxis();
        // Check if current Z axis is aligned with previous Z axis
        if (currentZAxis == prevZAxis || currentZAxis == vector<int>{-prevZAxis[0], -prevZAxis[1], -prevZAxis[2]}) {
            // If Z axes are aligned, keep the same X axis as the previous joint
            currentJoint.setXaxis(previousJoint.getXaxis());
        } else {
            // If Z axes are not aligned, choose an X axis that is orthogonal to both Z axes
            currentJoint.setXaxis(FindOrthogonalAxis(currentZAxis, prevZAxis));
        };
    };
    return;
};

// Calculates DH Table from Joint Configuration
// DH Rules for reference:
// a(i): distance along x(i) from x(i) to z(i-1)
// alpha(i): angle about x(i) from z(i-1) to z(i)
// d(i): distance along z(i-1) from z(i-1) to x(i) (for prismatic joints, this is variable)
// theta(i): angle about z(i-1) from x(i-1) to x(i) (for revolute joints, this is variable)
void CalculateDH_Table(vector<Joint> Joints){
    cout << "\nCalculating DH Table:\n";
    cout << "\n===========================";
    cout << "\n      DH Parameters:";
    cout << "\n===========================\n";
    for (int i = 1; i < Joints.size(); i++){
        // for joint i, check a
        // take the x axis orientation of joint i, paired with the origin position of both joint i and joint i-1 and check the distance along that axis
        int aLength = findDH_Parameter_a(Joints.at(i), Joints.at(i-1));
        // for joint i, check alpha
        // calculate angle between z axis of joint i-1 and z axis of joint i around the x axis of joint i
        int alpha = findDH_Parameter_alpha(Joints.at(i), Joints.at(i-1));
        // for joint i, check d
        // take the z axis orientation of joint i, paired with the origin position of both joint i and joint i-1 and check the distance along that axis
        int dLength = findDH_Parameter_d(Joints.at(i), Joints.at(i-1));
        // for joint i, check theta
        // calculate angle between x axis of joint i-1 and x axis of joint i around the z axis of joint i-1
        int theta = findDH_Parameter_theta(Joints.at(i), Joints.at(i-1));
        // send dh values to matrix (not happening lol)
        if (Joints.at(i).getisRevolute()){
            cout << " | Link " << i << ": a = " << aLength << ", alpha = " << alpha << ", d = " << dLength << ", theta = " << string("Theta_" + to_string(i)) << "\n";
        }
        else {
            cout << " | Link " << i << ": a = " << aLength << ", alpha = " << alpha << ", d = " << string("D_" + to_string(i)) << ", theta = " << theta << "\n";
        };
    };
    cout << "\n===========================";
    cout << "\n      End of DH Table      ";
    cout << "\n===========================\n";
};



#endif 