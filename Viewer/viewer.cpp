//
//
//
#include "viewer.hpp"
#include <iostream>
#include <exception>

using namespace std;



void Viewer::Start(Controller& controller)
{
    bool IsRunning = true;
    while (IsRunning)
    {
        try {
            system("cls");
            cout << "Welcome to the 3D Model Viewer" << endl;
            cout << "1. Add 3D Model" << endl;
            cout << "2. Export 3D Model" << endl;
            cout << "3. Render 3D Model" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";

            string arg;
            cin >> arg;

            switch (atoi(arg.c_str()))
            {
            case 1:
                ShowAddModel();
                break;

            case 2:
                controller.HandleArguments(vector<Argument>());
                break;

            
            default:
                cout << "Invalid choice" << endl;
                break;
            }


            
        }
        catch (const exception& e) {
            // handle exception here
        }
    } // end while loop
    // 结束之后说一些话
    cout << "Thank you for using the 3D Model Viewer!" << endl;
}


//
void Viewer::ShowAddModel()
{
    try {
        // menu to add 3D model
        // clear screen
        system("cls");
        //参数传给controller，并获取response展示给用户
        cout << "Add 3D Model" << endl;
        cout << "Enter the path to the 3D model: ";
        string path;
        cin >> path;
        //controller.Import3DModel(path);
    }
    catch (const exception& e) {
        // handle exception here
    }
}