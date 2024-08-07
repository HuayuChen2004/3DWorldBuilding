// this file is the implementation of the Viewer class
// it contains the implementation of various user interface functions
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/1
// author: Huayu Chen
// edit: implement start function and show import model function
//       improve structure of the interaction of the viewer and controller
// reason: to improve the user interface and interaction with the controller
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: implement the rest of the functions about the diaplay and modification 
//       of the 3D model
// reason: to add various functions of the interface
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add functions to display the model
//       add functions to handle responses
// reason: to support displaying the model and handling responses
// -----------------------------------------------------------
// date: 2024/8/4
// author: Huayu Chen





#include "viewer.hpp"
#include <iostream>
#include <exception>
#include "../Message/argument.hpp"
#include "../Message/response.hpp"
#include "../Controller/controller.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <regex>
#include "../Model/Element3D/face3d.hpp"
#include "../Model/Element3D/line3d.hpp"
#include "../Model/Element3D/point3d.hpp"
#include "../Model/Model3D/model3d.hpp"


using namespace std;
using ArgKey = Argument::ArgumentKey;
using ResKey = Response::ResponseKey;
class Controller;

void Viewer::HandleResponses(const vector<Response>& responses)
{
    if (responses[0].GetKey() == ResKey::EMPTY_PATH) {
        cout << "Empty path. Please enter a valid path." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::NOT_OBJ_PATH) {
        cout << "Not an obj file. Please enter a valid path." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::NOT_EXIST_PATH) {
        cout << "Path does not exist. Please enter a valid path." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::IMPORT_SUCCESS) {
        cout << "Import successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::IMPORT_FAILED) {
        cout << "Import failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::EXPORT_SUCCESS) {
        cout << "Export successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::EXPORT_FAILED) {
        cout << "Export failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DELETE_FACE_SUCCESS) {
        cout << "Delete face successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::ADD_FACE_SUCCESS) {
        cout << "Add face successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DELETE_LINE_SUCCESS) {
        cout << "Delete line successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::ADD_LINE_SUCCESS) {
        cout << "Add line successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::MODIFY_FACE_POINT_SUCCESS) {
        cout << "Modify face point successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::MODIFY_LINE_POINT_SUCCESS) {
        cout << "Modify line point successful." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DISPLAY_ALL_FACES) {
        cout << "Display all faces:" << endl;
        DisplayAllFaces(responses[0].GetValues());
        return;
    }
    if (responses[0].GetKey() == ResKey::DISPLAY_FACE_POINTS) {
        cout << "Display face points:" << endl;
        DisplayFacePoints(responses[0].GetValues());
        return;
    }
    if (responses[0].GetKey() == ResKey::DISPLAY_ALL_LINES) {
        cout << "Display all lines:" << endl;
        DisplayAllLines(responses[0].GetValues());
        return;
    }
    if (responses[0].GetKey() == ResKey::DISPLAY_LINE_POINTS) {
        cout << "Display line points:" << endl;
        DisplayLinePoints(responses[0].GetValues());
        return;
    }
    if (responses[0].GetKey() == ResKey::DISPLAY_STATISTICS) {
        cout << "Display statistics:" << endl;
        DisplayStatistics(responses[0].GetValues());
        return;
    }
    if (responses[0].GetKey() == ResKey::UNKNOWN_INVALID_ARGUMENT) {
        cout << "Please enter a valid argument." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::UNKNOWN_RUN_TIME_ERROR) {
        cout << "An unknown error occurred." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::ADD_FACE_FAILED) {
        cout << "Add face failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DELETE_FACE_FAILED) {
        cout << "Delete face failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::MODIFY_FACE_POINT_FAILED) {
        cout << "Modify face point failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::ADD_LINE_FAILED) {
        cout << "Add line failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DELETE_LINE_FAILED) {
        cout << "Delete line failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::MODIFY_LINE_POINT_FAILED) {
        cout << "Modify line point failed." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DUPLICATE_FACE) {
        cout << "Face already exists." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::DUPLICATE_LINE) {
        cout << "Line already exists." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::NOT_A_FACE) {
        cout << "Not a face." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::NOT_A_LINE) {
        cout << "Not a line." << endl;
        return;
    }
    if (responses[0].GetKey() == ResKey::INDEX_OUT_OF_RANGE) {
        cout << "Index out of range." << endl;
        return;
    }
    else {
        cout << "An unknown error occurred. Please try again." << endl;
        return;
    }
    
}
    

void Viewer::Start()
{
    bool IsRunning = true;
    while (IsRunning)
    {
        try {
            cout << endl;
            cout << string(50, '=') << endl;
            cout << "Welcome to the 3D Model Viewer" << endl;
            cout << "1. Import 3D Model" << endl;
            cout << "2. Export 3D Model" << endl;
            cout << "3. Modify 3D Model" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";

            string arg;
            cin >> arg;

            int input = GetIntegerInput(arg);

            switch (input)
            {
            case 1:
                ShowImportModel();
                break;

            case 2:
                ShowExportModel();
                break;

            case 3:
                ShowModifyModelMenu();
                break;

            case 4:
                IsRunning = false;
                break;
            
            default:
                cout << "Invalid choice" << endl;
                break;
            }
            
        }
        catch (const exception& e) {
            // handle exception here
            cout << "viewer.cpp line 63" << endl;
            cout << "catch exception" << e.what() << endl;
        }
    } // end while loop
    // 结束之后说一些话
    cout << "Thank you for using the 3D Model Viewer!" << endl;
}

//
void Viewer::ShowImportModel()
{
    try {
        // menu to add 3D model
        cout << endl;
        cout << string(50, '=') << endl;
        //参数传给controller，并获取response展示给用户
        cout << "Import 3D Model" << endl;
        cout << "Enter the path to the 3D model (or type 'exit' to exit): ";
        string path;
        cin >> path;
        
        if (path == "exit") {
            cout << "Exiting import model process." << endl;
            return;
        }
        Controller* controller = Controller::GetInstance();
        
        Argument arg(ArgKey::IMPORT_3D_MODEL, vector<string>{path});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 94" << endl;
        cout << "catch exception" << e.what() << endl;
    }
}

void Viewer::ShowExportModel()
{
    try {
        // menu to export 3D model
        cout << endl;
        cout << string(50, '=') << endl;
        //参数传给controller，并获取response展示给用户
        cout << "Export 3D Model" << endl;
        cout << "Enter the path to save the 3D model \
                (or type 'exit' to exit): ";
        string path;
        cin >> path;
        
        if (path == "exit") {
            cout << "Exiting export model process." << endl;
            return;
        }
        Controller* controller = Controller::GetInstance();

        Argument arg(ArgKey::EXPORT_3D_MODEL, vector<string>{path});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 116" << endl;
        cout << "catch exception" << e.what() << endl;
    }
}

void Viewer::ShowModifyModelMenu()
{
    try {
        while (true) {
            // menu to modify 3D model
            cout << endl;
            cout << string(50, '=') << endl;
            //参数传给controller，并获取response展示给用户
            cout << "Modify 3D Model" << endl;
            cout << "1. Display all faces" << endl;
            cout << "2. Delete face" << endl;
            cout << "3. Add face" << endl;
            cout << "4. Display face points" << endl;
            cout << "5. Modify face point" << endl;
            cout << "6. Display all lines" << endl;
            cout << "7. Add line" << endl;
            cout << "8. Delete line" << endl;
            cout << "9. Display line points" << endl;
            cout << "10. Modify line point" << endl;
            cout << "11. Display statistics" << endl;
            cout << "12. Exit" << endl;
            cout << "Enter your choice: ";

            string choice;
            cin >> choice;

            int input = GetIntegerInput(choice);

            switch (input)
            {
            case 1:
                ShowListAllFaces();
                break;

            case 2:
                ShowDeleteFace();
                break;

            case 3:
                ShowAddFace();
                break;

            case 4:
                ShowListAllPointsOfFace();
                break;

            case 5:
                ShowModifyPointOfFace();
                break;

            case 6:
                ShowListAllLines();
                break;

            case 7:
                ShowAddLine();
                break;

            case 8:
                ShowDeleteLine();
                break;

            case 9:
                ShowListAllPointsOfLine();
                break;

            case 10:
                ShowModifyPointOfLine();
                break;

            case 11:
                ShowShowStatistics();
                break;

            case 12:
                cout << "Exiting modify model process." << endl;
                return;

            default:
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 214" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllFaces() {
    try {
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DISPLAY_ALL_FACES, vector<string>());
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 229" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowDeleteFace() {
    try {
        cout << "Delete Face" << endl;
        cout << "Enter the face ID to delete: ";
        string face_id;
        cin >> face_id;
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DELETE_FACE, vector<string>{face_id});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 244" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowAddFace() {
    try {
        cout << "Add Face" << endl;
        cout << "Enter the coordinates of the first point: ";
        cin.sync();
        string coord1;
        getline(cin, coord1);
        cout << "Enter the coordinates of the second point: ";
        string coord2;
        getline(cin, coord2);
        cout << "Enter the coordinates of the third point: ";
        string coord3;
        getline(cin, coord3);
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::ADD_FACE, vector<string>{coord1, coord2, coord3});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 264" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllPointsOfFace() {
    try {
        cout << "List All Points of Face" << endl;
        cout << "Enter the face ID to list: ";
        string face_id;
        cin >> face_id;
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DISPLAY_FACE_POINTS, vector<string>{face_id});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 280" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowModifyPointOfFace() {
    try {
        cin.sync();
        cout << "Modify Point of Face" << endl;
        cout << "Enter the face ID to modify: ";
        string face_id;
        cin >> face_id;
        cout << "Enter the point ID to modify: ";
        string point_id;
        cin >> point_id;
        cout << "Enter the new coordinates of the point: ";
        cin.sync();
        string coord;
        getline(cin, coord);
        Argument arg(ArgKey::MODIFY_FACE_POINT, 
                vector<string>{face_id, point_id, coord});
        Controller* controller = Controller::GetInstance();
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 300" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllLines() {
    try {
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DISPLAY_ALL_LINES, vector<string>());
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 315" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowAddLine() {
    try {
        cout << "Add Line" << endl;
        cin.sync();
        cout << "Enter the coordinates of the first point: ";
        string coord1;
        getline(cin, coord1);
        cout << "Enter the coordinates of the second point: ";
        string coord2;
        getline(cin, coord2);
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::ADD_LINE, vector<string>{coord1, coord2});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 335" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowDeleteLine() {
    try {
        cout << "Delete Line" << endl;
        cout << "Enter the line ID to delete: ";
        string line_id;
        cin >> line_id;
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DELETE_LINE, vector<string>{line_id});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 351" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllPointsOfLine() {
    try {
        cout << "List All Points of Line" << endl;
        cout << "Enter the line ID to list: ";
        string line_id;
        cin >> line_id;
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DISPLAY_LINE_POINTS, vector<string>{line_id});
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 367" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowModifyPointOfLine() {
    try {
        cout << "Modify Point of Line" << endl;
        cout << "Enter the line ID to modify: ";
        string line_id;
        cin >> line_id;
        cout << "Enter the point ID to modify: ";
        string point_id;
        cin >> point_id;
        cout << "Enter the new coordinates of the point: ";
        cin.sync();
        string coord;
        getline(cin, coord);
        Argument arg(ArgKey::MODIFY_LINE_POINT, 
                vector<string>{line_id, point_id, coord});
        Controller* controller = Controller::GetInstance();
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 387" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowShowStatistics() {
    try {
        Controller* controller = Controller::GetInstance();
        Argument arg(ArgKey::DISPLAY_STATISTICS, vector<string>());
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 402" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::DisplayAllFaces(const vector<string>& values) const{
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Face " << i << endl;
        cout << values[i] << endl;
    }
}

void Viewer::DisplayFacePoints(const vector<string>& values) const{
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Point " << i << endl;
        cout << values[i] << endl;
    }
}

void Viewer::DisplayAllLines(const vector<string>& values) const{
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Line " << i << endl;
        cout << values[i] << " " << endl;
    }
}

void Viewer::DisplayLinePoints(const vector<string>& values) const{
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Point " << i << endl;
        cout << values[i] << endl;
    }
}

void Viewer::DisplayStatistics(const vector<string>& values) const{
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << values[i] << endl;
    }
}

int Viewer::GetIntegerInput(const string& InputString) const {
    // 使用正则表达式检查输入是否为正整数
    std::regex positive_integer_regex("^[1-9]\\d*$");
    if (!std::regex_match(InputString, positive_integer_regex)) {
        throw invalid_argument("Invalid input.");
    }

    try {
        int input = stoi(InputString); // 尝试将字符串转换为整数
        return input;
    } catch (const invalid_argument& e) {
        throw invalid_argument("Invalid input.");
    } catch (const out_of_range& e) {
        throw invalid_argument("Invalid input.");
    }
}