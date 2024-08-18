// [file name] : viewer.cpp
// [function] : implement the Viewer class
// [author] : Huayu Chen
// [date] : 2024/8/1

// [edit history] :
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

// -----------------------------------------------------------
// [name] : HandleResponses
// [function] : handle the responses from the controller
// [input] : a vector of responses
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void Viewer::HandleResponses(const vector<Response>& responses)
{
    // Check if the path is empty
    if (responses[0].GetKey() == ResKey::EMPTY_PATH) {
        cout << "Empty path. Please enter a valid path." << endl;
        return;
    }
    // Check if the path is not an obj file
    if (responses[0].GetKey() == ResKey::NOT_OBJ_PATH) {
        cout << "Not an obj file. Please enter a valid path." << endl;
        return;
    }
    // Check if the path does not exist
    if (responses[0].GetKey() == ResKey::NOT_EXIST_PATH) {
        cout << "Path does not exist. Please enter a valid path." << endl;
        return;
    }
    // Check if the import was successful
    if (responses[0].GetKey() == ResKey::IMPORT_SUCCESS) {
        cout << "Import successful." << endl;
        return;
    }
    // Check if the import failed
    if (responses[0].GetKey() == ResKey::IMPORT_FAILED) {
        cout << "Import failed." << endl;
        return;
    }
    // Check if the export was successful
    if (responses[0].GetKey() == ResKey::EXPORT_SUCCESS) {
        cout << "Export successful." << endl;
        return;
    }
    // Check if the export failed
    if (responses[0].GetKey() == ResKey::EXPORT_FAILED) {
        cout << "Export failed." << endl;
        return;
    }
    // Check if the face deletion was successful
    if (responses[0].GetKey() == ResKey::DELETE_FACE_SUCCESS) {
        cout << "Delete face successful." << endl;
        return;
    }
    // Check if the face addition was successful
    if (responses[0].GetKey() == ResKey::ADD_FACE_SUCCESS) {
        cout << "Add face successful." << endl;
        return;
    }
    // Check if the line deletion was successful
    if (responses[0].GetKey() == ResKey::DELETE_LINE_SUCCESS) {
        cout << "Delete line successful." << endl;
        return;
    }
    // Check if the line addition was successful
    if (responses[0].GetKey() == ResKey::ADD_LINE_SUCCESS) {
        cout << "Add line successful." << endl;
        return;
    }
    // Check if the face point modification was successful
    if (responses[0].GetKey() == ResKey::MODIFY_FACE_POINT_SUCCESS) {
        cout << "Modify face point successful." << endl;
        return;
    }
    // Check if the line point modification was successful
    if (responses[0].GetKey() == ResKey::MODIFY_LINE_POINT_SUCCESS) {
        cout << "Modify line point successful." << endl;
        return;
    }
    // Check if displaying all faces
    if (responses[0].GetKey() == ResKey::DISPLAY_ALL_FACES) {
        cout << "Display all faces:" << endl;
        DisplayAllFaces(responses[0].GetValues());
        return;
    }
    // Check if displaying face points
    if (responses[0].GetKey() == ResKey::DISPLAY_FACE_POINTS) {
        cout << "Display face points:" << endl;
        DisplayFacePoints(responses[0].GetValues());
        return;
    }
    // Check if displaying all lines
    if (responses[0].GetKey() == ResKey::DISPLAY_ALL_LINES) {
        cout << "Display all lines:" << endl;
        DisplayAllLines(responses[0].GetValues());
        return;
    }
    // Check if displaying line points
    if (responses[0].GetKey() == ResKey::DISPLAY_LINE_POINTS) {
        cout << "Display line points:" << endl;
        DisplayLinePoints(responses[0].GetValues());
        return;
    }
    // Check if displaying statistics
    if (responses[0].GetKey() == ResKey::DISPLAY_STATISTICS) {
        cout << "Display statistics:" << endl;
        DisplayStatistics(responses[0].GetValues());
        return;
    }
    // Check for unknown invalid argument
    if (responses[0].GetKey() == ResKey::UNKNOWN_INVALID_ARGUMENT) {
        cout << "Please enter a valid argument." << endl;
        return;
    }
    // Check for unknown run time error
    if (responses[0].GetKey() == ResKey::UNKNOWN_RUN_TIME_ERROR) {
        cout << "An unknown error occurred." << endl;
        return;
    }
    // Check if adding face failed
    if (responses[0].GetKey() == ResKey::ADD_FACE_FAILED) {
        cout << "Add face failed." << endl;
        return;
    }
    // Check if deleting face failed
    if (responses[0].GetKey() == ResKey::DELETE_FACE_FAILED) {
        cout << "Delete face failed." << endl;
        return;
    }
    // Check if modifying face point failed
    if (responses[0].GetKey() == ResKey::MODIFY_FACE_POINT_FAILED) {
        cout << "Modify face point failed." << endl;
        return;
    }
    // Check if adding line failed
    if (responses[0].GetKey() == ResKey::ADD_LINE_FAILED) {
        cout << "Add line failed." << endl;
        return;
    }
    // Check if deleting line failed
    if (responses[0].GetKey() == ResKey::DELETE_LINE_FAILED) {
        cout << "Delete line failed." << endl;
        return;
    }
    // Check if modifying line point failed
    if (responses[0].GetKey() == ResKey::MODIFY_LINE_POINT_FAILED) {
        cout << "Modify line point failed." << endl;
        return;
    }
    // Check if face is duplicated
    if (responses[0].GetKey() == ResKey::DUPLICATE_FACE) {
        cout << "Face already exists." << endl;
        return;
    }
    // Check if line is duplicated
    if (responses[0].GetKey() == ResKey::DUPLICATE_LINE) {
        cout << "Line already exists." << endl;
        return;
    }
    // Check if not a face
    if (responses[0].GetKey() == ResKey::NOT_A_FACE) {
        cout << "Not a face." << endl;
        return;
    }
    // Check if not a line
    if (responses[0].GetKey() == ResKey::NOT_A_LINE) {
        cout << "Not a line." << endl;
        return;
    }
    // Check if index is out of range
    if (responses[0].GetKey() == ResKey::INDEX_OUT_OF_RANGE) {
        cout << "Index out of range." << endl;
        return;
    }
    // Check for invalid number format
    if (responses[0].GetKey() == ResKey::INVALID_NUMBER_FORMAT) {
        cout << "Invalid number format." << endl;
        return;
    }
    // Check if not a point
    if (responses[0].GetKey() == ResKey::NOT_A_POINT) {
        cout << "Not a point." << endl;
        return;
    }
    // Check for input number error
    if (responses[0].GetKey() == ResKey::INPUT_NUMBER_ERROR) {
        cout << "Input number wrong." << endl;
        return;
    }
    // Check for invalid input
    if (responses[0].GetKey() == ResKey::INVALID_INPUT) {
        cout << "Invalid input." << endl;
        return;
    }
    // Check if parse failed
    if (responses[0].GetKey() == ResKey::PARSE_FAILED) {
        cout << "Parse failed." << endl;
        return;
    }
    // Check if opening file failed
    if (responses[0].GetKey() == ResKey::OPEN_FILE_FAILED) {
        cout << "Open file failed." << endl;
        return;
    }
    // Check if there is no model to export
    if (responses[0].GetKey() == ResKey::NO_MODEL_TO_EXPORT) {
        cout << "No model to export." << endl;
        return;
    }
    // Check if there is no 3D model
    if (responses[0].GetKey() == ResKey::NO_3D_MODEL) {
        cout << "Please import a 3D model first." << endl;
        return;
    }
    cout << "An unknown error occurred. Please try again." << endl;
    return;
}
    
// -----------------------------------------------------------
// [name] : Start
// [function] : display the start menu to start the program
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::Start()
{
    bool IsRunning = true;
    while (IsRunning)
    {
        try {
            // start menu
            cout << endl;
            cout << string(50, '=') << endl;
            cout << "Welcome to the 3D Model Viewer" << endl;
            cout << "1. Import 3D Model" << endl;
            cout << "2. Export 3D Model" << endl;
            cout << "3. Modify 3D Model" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";

            string arg;
            cin.sync();
            getline(cin, arg);
            cin.sync();
            // convert string to integer
            int input = GetIntegerInput(arg);

            switch (input)
            {
            case 1 :
                ShowImportModel();
                break;

            case 2 :
                ShowExportModel();
                break;

            case 3 :
                ShowModifyModelMenu();
                break;

            case 4 :
            // exit the program
                IsRunning = false;
                break;
            
            default :
            // invalid choice, try again
                cout << "Invalid choice" << endl;
                break;
            }
        }
        catch (const exception& e) {
            // handle exception here
            cout << "invalid choice" << endl;
        }
    } // end while loop
    // exit the program
    cout << "Thank you for using the 3D Model Viewer!" << endl;
}

// -----------------------------------------------------------
// [name] : ShowImportModel
// [function] : display the menu to import a 3D model
// [input] : path to the 3D model
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
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
        getline(cin, path);
        // exit the import model process    
        if (path == "exit") {
            cout << "Exiting import model process." << endl;
            return;
        }
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::IMPORT_3D_MODEL, vector<string>{path});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "invalid input" << endl;
    }
}

// -----------------------------------------------------------
// [name] : ShowExportModel
// [function] : display the menu to export a 3D model
// [input] : path to save the 3D model
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowExportModel()
{
    try {
        // menu to export 3D model
        cout << endl;
        cout << string(50, '=') << endl;
        //参数传给controller，并获取response展示给用户
        cout << "Export 3D Model" << endl;
        cout << "Enter the path to save the 3D model(or type 'exit' to exit): ";
        string path;
        getline(cin, path);
        // exit the export model process
        if (path == "exit") {
            cout << "Exiting export model process." << endl;
            return;
        }
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::EXPORT_3D_MODEL, vector<string>{path});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "invalid input" << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowModifyModelMenu
// [function] : display the menu to modify a 3D model
// [input] : user choice
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowModifyModelMenu()
{
    bool IsRunning = true;
    while (IsRunning) {
        try {
            // menu to modify 3D model
            cout << endl;
            cout << string(50, '=') << endl;
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
            // get user input
            cin.sync();
            string choice;
            getline(cin, choice);
            cin.sync();
            // convert string to integer
            int input = GetIntegerInput(choice);
 
            switch (input)
            {
            case 1 :
                ShowListAllFaces();
                break;
 
            case 2 :
                ShowDeleteFace();
                break;
 
            case 3 :
                ShowAddFace();
                break;
 
            case 4 :
                ShowListAllPointsOfFace();
                break;
 
            case 5 :
                ShowModifyPointOfFace();
                break;
 
            case 6 :
                ShowListAllLines();
                break;
 
            case 7 :
                ShowAddLine();
                break;
 
            case 8 :
                ShowDeleteLine();
                break;
 
            case 9 :
                ShowListAllPointsOfLine();
                break;
 
            case 10 :
                ShowModifyPointOfLine();
                break;
 
            case 11 :
                ShowShowStatistics();
                break;
 
            case 12 :
            // exit the modify model process
                cout << "Exiting modify model process." << endl;
                IsRunning = false;
 
            default :
            // let the user try again
                cout << "Invalid choice" << endl;
                break;
            }
        }
        catch (const exception& e) {
            // handle exception here
            cout << "invalid choice" << endl;
        }
    }
}
 
// -----------------------------------------------------------
// [name] : ShowListAllFaces
// [function] : display all faces of the 3D model
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowListAllFaces() {
    try {
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DISPLAY_ALL_FACES, vector<string>());
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "Error: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowDeleteFace
// [function] : display the menu to delete a face from the 3D model
// [input] : face ID
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowDeleteFace() {
    try {
        // display the menu to delete a face from the 3D model
        cout << "Delete Face" << endl;
        cout << "Enter the face ID to delete: ";
        string face_id;
        getline(cin, face_id);
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DELETE_FACE, vector<string>{face_id});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 244" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
  
// -----------------------------------------------------------
// [name] : ShowAddFace
// [function] : display the menu to add a face to the 3D model
// [input] : coordinates of the face points
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowAddFace() {
    try {
        // display the menu to add a face to the 3D model
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
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::ADD_FACE, vector<string>{coord1, coord2, coord3});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 264" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowListAllPointsOfFace
// [function] : display the list of all points of a face in the 3D model
// [input] : face ID
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowListAllPointsOfFace() {
    try {
        // display the list of all points of a face in the 3D model
        cout << "List All Points of Face" << endl;
        cout << "Enter the face ID to list: ";
        string face_id;
        getline(cin, face_id);
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DISPLAY_FACE_POINTS, vector<string>{face_id});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 280" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowModifyPointOfFace
// [function] : display the menu to modify a point of a face in the 3D model
// [input] : face ID, point ID, new coordinates of the point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowModifyPointOfFace() {
    try {
        cin.sync();
        // display the menu to modify a point of a face in the 3D model
        cout << "Modify Point of Face" << endl;
        cout << "Enter the face ID to modify: ";
        string face_id;
        getline(cin, face_id);
        cout << "Enter the point ID to modify: ";
        string point_id;
        getline(cin, point_id);
        cout << "Enter the new coordinates of the point: ";
        cin.sync();
        string coord;
        getline(cin, coord);
        // create an argument object
        Argument arg(ArgKey::MODIFY_FACE_POINT, 
                vector<string>{face_id, point_id, coord});
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 300" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

// -----------------------------------------------------------
// [name] : ShowListAllLines
// [function] : display the list of all lines in the 3D model
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowListAllLines() {
    try {
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DISPLAY_ALL_LINES, vector<string>());
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 315" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowAddLine
// [function] : display the menu to add a line to the 3D model
// [input] : coordinates of the first point, coordinates of the second point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowAddLine() {
    try {
        // display the menu to add a line
        cout << "Add Line" << endl;
        cin.sync();
        // get the coordinates of the first point
        cout << "Enter the coordinates of the first point: ";
        string coord1;
        getline(cin, coord1);
        // get the coordinates of the second point
        cout << "Enter the coordinates of the second point: ";
        string coord2;
        getline(cin, coord2);
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::ADD_LINE, vector<string>{coord1, coord2});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 335" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowDeleteLine
// [function] : display the menu to delete a line from the 3D model
// [input] : line ID
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowDeleteLine() {
    try {
        // display the menu to delete a line
        cout << "Delete Line" << endl;
        // get the line ID to delete
        cout << "Enter the line ID to delete: ";
        string line_id;
        getline(cin, line_id);
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DELETE_LINE, vector<string>{line_id});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 351" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowListAllPointsOfLine
// [function] : display the list of all points of a line in the 3D model
// [input] : line ID
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowListAllPointsOfLine() {
    try {
        // display the menu to list all points of a line
        cout << "List All Points of Line" << endl;
        // get the line ID to list
        cout << "Enter the line ID to list: ";
        string line_id;
        getline(cin, line_id);
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DISPLAY_LINE_POINTS, vector<string>{line_id});
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 367" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : ShowModifyPointOfLine
// [function] : display the menu to modify a point of a line in the 3D model
// [input] : line ID, point ID, new coordinates of the point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowModifyPointOfLine() {
    try {
        // display the menu to modify a point of a line
        cout << "Modify Point of Line" << endl;
        // get the line ID to modify
        cout << "Enter the line ID to modify: ";
        string line_id;
        getline(cin, line_id);
        // get the point ID to modify
        cout << "Enter the point ID to modify: ";
        string point_id;
        getline(cin, point_id);
        // get the new coordinates of the point
        cout << "Enter the new coordinates of the point: ";
        cin.sync();
        string coord;
        getline(cin, coord);
        // create an argument object
        Argument arg(ArgKey::MODIFY_LINE_POINT, 
                vector<string>{line_id, point_id, coord});
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 387" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

// -----------------------------------------------------------
// [name] : ShowShowStatistics
// [function] : display the statistics of the 3D model
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::ShowShowStatistics() {
    try {
        // get the controller instance
        Controller* controller = Controller::GetInstance();
        // create an argument object
        Argument arg(ArgKey::DISPLAY_STATISTICS, vector<string>());
        // get the response from the controller
        Response response = 
                (*controller).HandleArguments(vector<Argument>{arg});
        // handle the response
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 402" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : DisplayAllFaces
// [function] : display all faces of the 3D model
// [input] : vector of strings representing face data
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::DisplayAllFaces(const vector<string>& values) const{
    // iterate through the face data and display each face
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Face " << i << endl;
        cout << values[i] << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : DisplayFacePoints
// [function] : display points of a specific face
// [input] : vector of strings representing face point data
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::DisplayFacePoints(const vector<string>& values) const{
    // iterate through the face point data and display each point
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Point " << i << endl;
        cout << values[i] << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : DisplayAllLines
// [function] : display all lines of the 3D model
// [input] : vector of strings representing line data
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::DisplayAllLines(const vector<string>& values) const{
    // iterate through the line data and display each line
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Line " << i << endl;
        cout << values[i] << " " << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : DisplayLinePoints
// [function] : display points of a specific line
// [input] : vector of strings representing line point data
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::DisplayLinePoints(const vector<string>& values) const{
    // iterate through the line point data and display each point
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << "Point " << i << endl;
        cout << values[i] << " " << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : DisplayStatistics
// [function] : display statistics of the 3D model
// [input] : vector of strings representing statistics data
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
void Viewer::DisplayStatistics(const vector<string>& values) const{
    // iterate through the statistics data and display each statistic
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << values[i] << endl;
    }
}
 
// -----------------------------------------------------------
// [name] : GetIntegerInput
// [function] : get an integer input from a string
// [input] : string containing the input
// [output] : integer value extracted from the string
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------
int Viewer::GetIntegerInput(const string& InputString) const {
    // regex pattern to match an integer surrounded by optional whitespace
    regex pattern(R"(^\s*(\d+)\s*$)");
    smatch match;
 
    // check if the input string matches the pattern
    if (regex_match(InputString, match, pattern)) {
        // extract the matched integer and convert it to an int
        string number = match.str(1);
        return stoi(number);
    } else {
        // throw an exception if the input is invalid
        throw invalid_argument("Invalid input");
    }
}


