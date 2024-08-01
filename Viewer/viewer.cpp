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
//
//
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

            Response response;

            switch (atoi(arg.c_str()))
            {
            case 1:
                ShowImportModel(controller);
                break;

            case 2:
                ShowExportModel(controller);
                break;

            case 3:
                ShowModifyModel(controller);
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
        cout << "Enter the path to the 3D model: ";
        string path;
        cin >> path;
        Argument arg(ArgKey::IMPORT_3D_MODEL, path);
        Response response = controller.HandleArguments(vector<Argument>{arg});
        HandleResponses(vector<Response>{response});
    }
    catch (const exception& e) {
        // handle exception here
    }
}