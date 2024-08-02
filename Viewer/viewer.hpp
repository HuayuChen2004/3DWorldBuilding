// this is the header file of the Viewer class
// the class Viewer is a class that interacts with the user
// the class Viewer has functions to show the user interface
// and functions to get user input
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/1
// author: Huayu Chen
// edit: init viewer class
//      add functions to show user interface
//      add functions to get user input
// reason: to support various user interactions
// -----------------------------------------------------------
// date: 2024/8/1
// author: Huayu Chen
// edit: add HandleResponses function
//       add functions that show user interface
// reason: improve the viewer class
// -----------------------------------------------------------
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
#ifndef VIEWER_HPP
#define VIEWER_HPP


#include <string>
#include <iostream>
#include "../Controller/controller.hpp"
using namespace std;




//
//
//
//
//
//
//
//
//
//
//
//
class Viewer
{

//
//
public:
    //
    //
    //
    //
    //
    //
    //
    void Start();
    //
    //
    //
    //







private:


    void HandleResponses(vector<Response> responses);
    // list all the interfaces
    void ShowStartMenu();
    void ShowImportModel();
    void ShowExportModel();
    void ShowModifyModelMenu();    
    void ShowListAllFaces();
    void ShowDeleteFace();
    void ShowAddFace();
    void ShowListAllPointsOfFace();
    void ShowModifyPointOfFace();
    void ShowListAllLines();
    void ShowDeleteLine();
    void ShowAddLine();
    void ShowListAllPointsOfLine();
    void ShowModifyPointOfLine();
    void ShowShowStatistics();

};



















#endif // VIEWER_HPP    