#ifndef JOINT_H
#define JOINT_H

#include <vector>
using namespace std;

class Joint {
private:
    // Joint Number
    int JointIndex;
    // Joint Type: true = revolute, false = prismatic
    bool isRevolute; 
    // Z Orientation relative to base frame
    vector<int> ZaxisOrientation;
    // X Orientation relative to base frame
    vector<int> XaxisOrientation;
    // World Frame Position
    vector<float> Position;

public:

    // Joint Class Constructor

    Joint(int index, bool jointType, vector<int> Zaxis, vector<float> position) {
        JointIndex = index;
        isRevolute = jointType;
        ZaxisOrientation = Zaxis;
        Position = position;
    }

    // Joint Class Getters

    int getIndex() {
        return JointIndex;
    };

    bool getisRevolute() {
        return isRevolute;
    };

    vector<int> getZaxis() {
        return ZaxisOrientation;
    };

    vector<int> getXaxis() {
        return XaxisOrientation;
    };

    vector<float> getPos() {
        return Position;
    };

    float getXpos() {
        return Position[0];
    };

    float getYpos() {
        return Position[1];
    };

    float getZpos() {
        return Position[2];
    };

    // Joint Class Setters

    void setIndex(int index) {
        JointIndex = index;
        return;
    };

    void setisRevolute(bool jointType) {
        isRevolute = jointType;
        return;
    };

    void setZaxis(vector<int> Zorientation) {
        ZaxisOrientation = Zorientation;
        return;
    };

    void setXaxis(vector<int> Xorientation) {
        XaxisOrientation = Xorientation;
        return;
    };

    void setPos(vector<float> position) {
        Position = position;
        return;
    };

    void setXpos(float xPosition) {
        Position[0] = xPosition;
        return;
    };

    void setYpos(float yPosition) {
        Position[1] = yPosition;
        return;
    };

    void setZpos(float zPosition) {
        Position[2] = zPosition;
        return;
    };


};


#endif // JOINT_H