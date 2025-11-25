#ifndef JOINT_H
#define JOINT_H

// Standard Libraries
#include <vector>

// Using standard namespace
using namespace std;

// Custom Libraries
#include "input_lib.h"

// Joint Class Definition
class Joint {
private:
    // Joint Index
    int JointIndex;
    // Joint Type: true = revolute, false = prismatic
    bool isRevolute; 
    // Z Orientation relative to base frame; (1,0,0), (0,1,0), (0,0,1)
    vector<int> ZaxisOrientation;
    // X Orientation relative to base frame; (1,0,0), (0,1,0), (0,0,1)
    vector<int> XaxisOrientation;
    // Origin Position
    vector<int> originPosition;

public:

    // Joint Class Constructor
    Joint(int index, bool jointType, vector<int> Zaxis, vector<int> origin) {
        JointIndex = index;
        isRevolute = jointType;
        ZaxisOrientation = Zaxis;
        originPosition = origin;
        XaxisOrientation = {0,0,0}; // Default X axis, to be set later
    };

    // Joint Class Getters

    // Get Joint Index
    int getIndex() {
        return JointIndex;
    };

    // Get Joint Type
    bool getisRevolute() {
        return isRevolute;
    };

    // Get Z Orientation
    vector<int> getZaxis() {
        return ZaxisOrientation;
    };

    // Get X Orientation
    vector<int> getXaxis() {
        return XaxisOrientation;
    };

    // Get Origin Position
    vector<int> getOriginPos() {
        return originPosition;
    };

    // Joint Class Setters

    // Set Joint Index
    void setIndex(int index) {
        JointIndex = index;
        return;
    };

    // Set Joint Type
    void setisRevolute(bool jointType) {
        isRevolute = jointType;
        return;
    };

    // Set Z Orientation
    void setZaxis(vector<int> axis) {
        ZaxisOrientation = axis;
        return;
    };

    // Set X Axis Orientation
    void setXaxis(vector<int> axis) {
        XaxisOrientation = axis;
        return;
    };

    // Set Position
    void setPosition(vector<int> pos) {
        originPosition = pos;
        return;
    };
};
#endif // JOINT_H