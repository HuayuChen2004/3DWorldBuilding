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
// edit: implement the rest of the functions about the diaplay and modification of the 3D model
// reason: to add various functions of the interface
// -----------------------------------------------------------





#include "viewer.hpp"
#include <iostream>
#include <exception>

using namespace std;
using ArgKey = Argument::ArgumentKey;
class Controller;

void Viewer::Start(Controller& controller)
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

            switch (atoi(arg.c_str()))
            {
            case 1:
                ShowImportModel(controller);
                break;

            case 2:
                ShowExportModel(controller);
                break;

            case 3:
                ShowModifyModelMenu(controller);
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
void Viewer::ShowImportModel(Controller& controller)
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

        Argument arg(ArgKey::IMPORT_3D_MODEL, vector<string>{path});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 94" << endl;
        cout << "catch exception" << e.what() << endl;
    }
}

void Viewer::ShowExportModel(Controller& controller)
{
    try {
        // menu to export 3D model
        cout << endl;
        cout << string(50, '=') << endl;
        //参数传给controller，并获取response展示给用户
        cout << "Export 3D Model" << endl;
        cout << "Enter the path to save the 3D model (or type 'exit' to exit): ";
        string path;
        cin >> path;
        
        if (path == "exit") {
            cout << "Exiting export model process." << endl;
            return;
        }

        Argument arg(ArgKey::EXPORT_3D_MODEL, vector<string>{path});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 116" << endl;
        cout << "catch exception" << e.what() << endl;
    }
}

void Viewer::ShowModifyModelMenu(Controller& controller)
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
            switch (atoi(choice.c_str()))
            {
            case 1:
                ShowListAllFaces(controller);
                break;

            case 2:
                ShowDeleteFace(controller);
                break;

            case 3:
                ShowAddFace(controller);
                break;

            case 4:
                ShowListAllPointsOfFace(controller);
                break;

            case 5:
                ShowModifyPointOfFace(controller);
                break;

            case 6:
                ShowListAllLines(controller);
                break;

            case 7:
                ShowAddLine(controller);
                break;

            case 8:
                ShowDeleteLine(controller);
                break;

            case 9:
                ShowListAllPointsOfLine(controller);
                break;

            case 10:
                ShowModifyPointOfLine(controller);
                break;

            case 11:
                ShowShowStatistics(controller);
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

void Viewer::ShowListAllFaces(Controller& controller) {
    try {
        Argument arg(ArgKey::DISPLAY_ALL_FACES, vector<string>());
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 229" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowDeleteFace(Controller& controller) {
    try {
        cout << "Delete Face" << endl;
        cout << "Enter the face ID to delete: ";
        string face_id;
        cin >> face_id;
        Argument arg(ArgKey::DELETE_FACE, vector<string>{face_id});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 244" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowAddFace(Controller& controller) {
    try {
        cout << "Add Face" << endl;
        cout << "Enter the coordinates of the first point: ";
        string coord1;
        cin >> coord1;
        cout << "Enter the coordinates of the second point: ";
        string coord2;
        cin >> coord2;
        cout << "Enter the coordinates of the third point: ";
        string coord3;
        cin >> coord3;
        Argument arg(ArgKey::ADD_FACE, vector<string>{coord1, coord2, coord3});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 264" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllPointsOfFace(Controller& controller) {
    try {
        cout << "List All Points of Face" << endl;
        cout << "Enter the face ID to list: ";
        string face_id;
        cin >> face_id;
        Argument arg(ArgKey::DISPLAY_FACE_POINTS, vector<string>{face_id});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 280" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowModifyPointOfFace(Controller& controller) {
    try {
        cout << "Modify Point of Face" << endl;
        cout << "Enter the face ID to modify: ";
        string face_id;
        cin >> face_id;
        cout << "Enter the point ID to modify: ";
        string point_id;
        cin >> point_id;
        cout << "Enter the new coordinates of the point: ";
        string coord;
        cin >> coord;
        Argument arg(ArgKey::MODIFY_FACE_POINT, vector<string>{face_id, point_id, coord});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 300" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllLines(Controller& controller) {
    try {
        Argument arg(ArgKey::DISPLAY_ALL_LINES, vector<string>());
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 315" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowAddLine(Controller& controller) {
    try {
        cout << "Add Line" << endl;
        cout << "Enter the coordinates of the first point: ";
        string coord1;
        cin >> coord1;
        cout << "Enter the coordinates of the second point: ";
        string coord2;
        cin >> coord2;
        Argument arg(ArgKey::ADD_LINE, vector<string>{coord1, coord2});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 335" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowDeleteLine(Controller& controller) {
    try {
        cout << "Delete Line" << endl;
        cout << "Enter the line ID to delete: ";
        string line_id;
        cin >> line_id;
        Argument arg(ArgKey::DELETE_LINE, vector<string>{line_id});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 351" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowListAllPointsOfLine(Controller& controller) {
    try {
        cout << "List All Points of Line" << endl;
        cout << "Enter the line ID to list: ";
        string line_id;
        cin >> line_id;
        Argument arg(ArgKey::DISPLAY_LINE_POINTS, vector<string>{line_id});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 367" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowModifyPointOfLine(Controller& controller) {
    try {
        cout << "Modify Point of Line" << endl;
        cout << "Enter the line ID to modify: ";
        string line_id;
        cin >> line_id;
        cout << "Enter the point ID to modify: ";
        string point_id;
        cin >> point_id;
        cout << "Enter the new coordinates of the point: ";
        string coord;
        cin >> coord;
        Argument arg(ArgKey::MODIFY_LINE_POINT, vector<string>{line_id, point_id, coord});
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 387" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}

void Viewer::ShowShowStatistics(Controller& controller) {
    try {
        Argument arg(ArgKey::DISPLAY_STATISTICS, vector<string>());
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
        cout << "viewer.cpp line 402" << endl;
        cout << "catch exception: " << e.what() << endl;
    }
}