// [file name] : main.cpp
// [function] : main function of the program
// [author] : Huayu Chen
// [date] : 2024/8/7

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/7
// author: Huayu Chen
// edit: add main function
// reason: to test the program
// -----------------------------------------------------------

#include "Model/Element3D/point3d.hpp"
#include "Model/FileIO/model3dobjimporter.hpp"
#include "Model/Element3D/face3d.hpp"
#include "Model/FileIO/model3dobjexporter.hpp"
#include "Controller/controller.hpp"
#include "Message/argument.hpp"
#include "Message/response.hpp"
#include "Viewer/viewer.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main() {
    Controller* controller = Controller::GetInstance();
    Viewer viewer;
    viewer.Start();
    return 0;
}