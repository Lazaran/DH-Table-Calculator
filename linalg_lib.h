// Linear Algebra Library for Robot Arm DH Calculator
#ifndef LINALG_LIB_H
#define LINALG_LIB_H

// Standard Libraries
#include <iostream>
#include <vector>
#include <cmath>

// Using standard namespace
using namespace std;

// Custom Libraries
#include "joint.h"

// ========================
// Prototype Declarations
// ========================

// Map axis integer to orientation vector
vector<int> mapAxisToOrientation(int axis);

// Map orientation vector to axis integer
int mapOrientationToAxis(vector<int> axis);

// Determine X axis based on Z axis using right-hand rule
int RightHandRule(vector<int> zAxis);

// Find orthogonal axis from two existing vectors
vector<int> FindOrthogonalAxis(vector<int> axis1, vector<int> axis2);

// Find the dot product of two vectors
int findDotProduct(vector<int> vec1, vector<int> vec2);

// Gets the magnitude of an integer vector
int getVectorMagnitude(vector<int> vec);

// Find rotation about an axis between two other axes
// Praying this works for theta AND alpha (was built in theta then pulled into separate function)
int findRotationAboutAxis(vector<int> rotation_axis, vector<int> start_axis, vector<int> final_axis);

// Find the DH parameter 'a' between two joints
int findDH_Parameter_a(Joint current_joint, Joint previous_joint);

// Find the DH parameter 'alpha' between two joints
int findDH_Parameter_alpha(Joint current_joint, Joint previous_joint);

// Find the DH parameter 'd' between two joints
int findDH_Parameter_d(Joint current_joint, Joint previous_joint);

// Find the DH parameter 'theta' between two joints
int findDH_Parameter_theta(Joint current_joint, Joint previous_joint);

// ========================
// Function Definitions
// ========================

// Map axis integer to orientation vector
vector<int> mapAxisToOrientation(int axis){
    vector<int> tempAxis = {0,0,1};
    // Map input axis to orientation vector
    switch (axis) {
    // Oriented about Positive X Axis
    case 1:
        tempAxis = {1,0,0};
        break;
    // Oriented about Positive Y Axis
    case 2:
        tempAxis = {0,1,0};
        break;
    // Oriented about Positive Z Axis
    case 3:
        tempAxis = {0,0,1};
        break;
    // Oriented about Negative X Axis
    case 4:
        tempAxis = {-1,0,0};
        break;
    // Oriented about Negative Y Axis
    case 5:
        tempAxis = {0,-1,0};
        break;
    // Oriented about Negative Z Axis
    case 6:
        tempAxis = {0,0,-1};
        break;
    // Invalid Input
    default:
        cout << "\nInvalid axis, use 1/4 for X, 2/5 for Y, 3/6 for Z.";
        cout << "\nNo changes made to orientation.";
        break;
    };
    return tempAxis;
};

// Map orientation vector to axis integer
int mapOrientationToAxis(vector<int> axis){
    int tempAxis = 3;
    // Map input orientation vector to axis integer (Nightmare fuel)
    tempAxis = axis == vector<int>{1,0,0} ? 1 :
               axis == vector<int>{0,1,0} ? 2 :
               axis == vector<int>{0,0,1} ? 3 :
               axis == vector<int>{-1,0,0} ? 4 :
               axis == vector<int>{0,-1,0} ? 5 :
               axis == vector<int>{0,0,-1} ? 6 : 0;
    return tempAxis;
};

// Determine X axis based on Z axis using right-hand rule
int RightHandRule(vector<int> zAxis){
    int xAxis = 0;
    // Set X to X axis if Z is along Z axis
    if (zAxis == vector<int>{0,0,1} || zAxis == vector<int>{0,0,-1}) {
        xAxis = 1;
    }
    // Set X to Y axis if Z is along X axis
    else if (zAxis == vector<int>{1,0,0} || zAxis == vector<int>{-1,0,0}) {
        xAxis = 2;
    }
    // Set X to Z axis if Z is along Y axis
    else if (zAxis == vector<int>{0,1,0} || zAxis == vector<int>{0,-1,0}) {
        xAxis = 3;
    }
    return xAxis;
};

// Find orthogonal axis from two integer vectors
vector<int> FindOrthogonalAxis(vector<int> axis1, vector<int> axis2){
    vector<int> orthogonalAxis = {0, 0, 0};
    // Cross product
    orthogonalAxis[0] = (axis1[1] * axis2[2]) - (axis1[2] * axis2[1]);
    orthogonalAxis[1] = (axis1[2] * axis2[0]) - (axis1[0] * axis2[2]);
    orthogonalAxis[2] = (axis1[0] * axis2[1]) - (axis1[1] * axis2[0]);
    return orthogonalAxis;
};

// Find the dot product of two integer vectors
int findDotProduct(vector<int> vec1, vector<int> vec2){
    int dotProduct = vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
    return dotProduct;
};

// Gets the magnitude of an integer vector
int getVectorMagnitude(vector<int> vec){
    return (vec[0]+vec[1]+vec[2]);
};

// Find rotation about an axis between two other axes
// Praying this works for theta AND alpha (was built in theta then pulled into separate function)
int findRotationAboutAxis(vector<int> rotation_axis, vector<int> start_axis, vector<int> final_axis){
    int start_flip = 0;
    int rotation_angle = 0;
    switch (mapOrientationToAxis(rotation_axis)) {
        // World X axis (1,0,0) = Previous Z 
        case 1:
            // Previous X at World +/- Z
            if (start_axis[2] != 0){
                start_flip = 1;
            }
            // Previous X at World +/- Y
            else if (start_axis[1] != 0){
                start_flip = -1;
            };
            break;
        // World Y axis (0,1,0) = Previous Z 
        case 2:
            // Previous X at World +/- Z
            if (start_axis[2] != 0){
                start_flip = -1;
            }
            // Previous X at World +/- X
            else if (start_axis[0] != 0){
                start_flip = 1;
            };
            break;
        // World Z axis (0,0,1) = Previous Z
        case 3:
            // Previous X at World +/- Y
            if (start_axis[1] != 0){
                start_flip = 1;
            }
            // Previous X at World +/- X
            else if (start_axis[0] != 0){
                start_flip = -1;
            };
            break;
        // World -X axis (-1,0,0) = Previous Z 
        case 4:
            // Previous X at World +/- Z
            if (start_axis[2] != 0){
                start_flip = -1;
            }
            // Previous X at World +/- Y
            else if (start_axis[1] != 0){
                start_flip = 1;
            };
            break;
        // World -Y axis (0,-1,0) = Previous Z 
        case 5:
            // Previous X at World +/- Z
            if (start_axis[2] != 0){
                start_flip = 1;
            }
            // Previous X at World +/- X
            else if (start_axis[0] != 0){
                start_flip = -1;
            };
            break;
        // World -Z axis (0,0,-1) = Previous Z 
        case 6:
            // Previous X at World +/- Y
            if (start_axis[1] != 0){
                start_flip = -1;
            }
            // Previous X at World +/- X
            else if (start_axis[0] != 0){
                start_flip = 1;
            };
            break;
        default:
            throw runtime_error("Finding angle failed, hold on to ur panties!");
            break;
        // Check for sign flip between current and previous axes
        // Assuming sign flip is positive until specified otherwise, which start_flip sets based on which world axes the rotation is happening around and which axis the rotation starts at
    };
    if ((getVectorMagnitude(start_axis) + getVectorMagnitude(final_axis)) == 0){
        rotation_angle = (start_flip*90);
    } 
    else { 
        rotation_angle = (start_flip*(-90));
    };
    return rotation_angle;
};

// Find the DH parameter 'a' between two joints
int findDH_Parameter_a(Joint current_joint, Joint previous_joint){
    // Find the position of the current joint w.r.t. the current X axis
    int currentOffset = findDotProduct(current_joint.getXaxis(), current_joint.getOriginPos());
    // find the orientation of the z axis prevjoint, get the position along it (changed from z axis to x axis, because we measure the distance between joints along the x axis)
    int previousOffset = findDotProduct(current_joint.getXaxis(), previous_joint.getOriginPos());
    // calculate distance between the two positions along the x axis
    if (currentOffset == previousOffset){
        return 0;
    }
    else {
        return currentOffset - previousOffset;
    };
    // thats a?
};

// Find the DH parameter 'alpha' between two joints
int findDH_Parameter_alpha(Joint current_joint, Joint previous_joint){
    // Check for rotation about Z axis orientation
    if (previous_joint.getZaxis() != current_joint.getZaxis()){
        // Measure angle between current and previous X axes, about the previous Z axis
        findRotationAboutAxis(current_joint.getXaxis(), previous_joint.getZaxis(), current_joint.getZaxis());
    }
    else {
        return 0;
    };
    return 0;
};

// Find the DH parameter 'd' between two joints
int findDH_Parameter_d(Joint current_joint, Joint previous_joint){
    // Find the position of the current joint w.r.t. the previous Z axis
    int currentOffset = findDotProduct(previous_joint.getZaxis(), current_joint.getOriginPos());
    // Find the position of the previous joint w.r.t. the previous Z axis
    int previousOffset = findDotProduct(previous_joint.getZaxis(), previous_joint.getOriginPos());
    // calculate distance between the two positions along the x axis
    if (currentOffset == previousOffset){
        return 0;
    }
    else {
        return currentOffset - previousOffset;
    };
    // thats d?
};

// Find the DH parameter 'theta' between two joints
int findDH_Parameter_theta(Joint current_joint, Joint previous_joint){
    // Check for rotation about Z axis orientation
    if ( previous_joint.getXaxis() != current_joint.getXaxis()){
        // Measure angle between current and previous X axes, about the previous Z axis
        findRotationAboutAxis(previous_joint.getZaxis(), previous_joint.getXaxis(), current_joint.getXaxis());
    }
    else {
        return 0;
    }
    return 0;
};

#endif // LINALG_LIB_H
