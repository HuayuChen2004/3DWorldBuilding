// [file name] : viewer.hpp
// [function] : implement the Viewer class
// [author] : Huayu Chen
// [date] : 2024/8/1

// [edit history] :
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

//// this is the header file of the Viewer class
// the class Viewer is a class that interacts with the user
// the class Viewer has functions to show the user interface
// and functions to get user input

#ifndef VIEWER_HPP
#define VIEWER_HPP


#include <string>
#include <vector>
#include <iostream>
#include "../Controller/controller.hpp"
#include "../Message/argument.hpp"
#include "../Message/response.hpp"

using namespace std;

// notes on the class Viewer
// -----------------------------------------------------------
// [class name] : Viewer
// [function] : interact with the user
// [notes on interface] :
// 1. the viewer class is a class that interacts with the user
// 2. the public function Start is the entry point of the viewer
//    and the only function that should be called from outside the class
// 3. the private function HandleResponses is used to handle the responses
//    from the controller
// 4. other private functions are used to show the user interface
//    and get user input
// [author] : Huayu Chen
// [date] : 2024/8/1
// -----------------------------------------------------------


class Viewer
{

public:
    // display the start menu to start the program
    void Start();
private:
    // handle the responses from the controller
    void HandleResponses(const vector<Response>& responses);
    // list all the interfaces
    // interface 1: start menu
    void ShowStartMenu();
    // interface 2: import model menu
    void ShowImportModel();
    // interface 3: export model menu
    void ShowExportModel();
    // interface 4: modify model menu
    void ShowModifyModelMenu();    
    // interface 5: show all faces
    void ShowListAllFaces();
    // interface 6: delete face
    void ShowDeleteFace();
    // interface 7: add face
    void ShowAddFace();
    // interface 8: show all points of a face
    void ShowListAllPointsOfFace();
    // interface 9: modify point of a face
    void ShowModifyPointOfFace();
    // interface 10: show all lines
    void ShowListAllLines();
    // interface 11: delete line
    void ShowDeleteLine();
    // interface 12: add line
    void ShowAddLine();
    // interface 13: show all points of a line
    void ShowListAllPointsOfLine();
    // interface 14: modify point of a line
    void ShowModifyPointOfLine();
    // interface 15: show statistics
    void ShowShowStatistics();

    // display functions
    // display all faces
    void DisplayAllFaces(const vector<string>& FaceStrings) const;
    // display all points of a face
    void DisplayFacePoints(const vector<string>& PointStrings) const;
    // display all lines
    void DisplayAllLines(const vector<string>& LineStrings) const;
    // display all points of a line
    void DisplayLinePoints(const vector<string>& PointStrings) const;
    // display statistics
    void DisplayStatistics(const vector<string>& StatsStrings) const;
    // convert string input to integer
    int GetIntegerInput(const string& InputString) const;
};



















#endif // VIEWER_HPP    