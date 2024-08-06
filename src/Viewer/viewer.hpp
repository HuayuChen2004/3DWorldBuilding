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
// date: 2024/8/3
// author: Huayu Chen
// edit: add functions that display the model
// reason: to support displaying the model
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
#ifndef VIEWER_HPP
#define VIEWER_HPP


#include <string>
#include <vector>
#include <iostream>
#include "../Controller/controller.hpp"
#include "../Message/argument.hpp"
#include "../Message/response.hpp"

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


    void HandleResponses(const vector<Response>& responses);
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

    void DisplayAllFaces(const vector<string>& FaceStrings) const;
    void DisplayFacePoints(const vector<string>& PointStrings) const;
    void DisplayAllLines(const vector<string>& LineStrings) const;
    void DisplayLinePoints(const vector<string>& PointStrings) const;
    void DisplayStatistics(const vector<string>& StatsStrings) const;
};



















#endif // VIEWER_HPP    