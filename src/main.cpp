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

// test obj file path: D:/coding/cpp/oop/hw/cube.obj

int main() {
    Controller* controller = Controller::GetInstance();
    Viewer viewer;
    viewer.Start();
    
    return 0;
}