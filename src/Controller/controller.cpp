// [file name] : controller.cpp
// [function] : implement the class controller
// [author] : Huayu Chen
// [date] : 2024/8/2

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: init handle argument
//       add some error catch
// reason: to support handling some error
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: add display handle argument
// reason: to support displaying faces, lines, points, and statistics
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add functions to handle face and line operations
// reason: to support face and line operations
// -----------------------------------------------------------

#include "controller.hpp"
#include <stdexcept>

#include "../Model/FileIO/model3dobjimporter.hpp"
#include "../Model/FileIO/model3dobjexporter.hpp"
#include "../Model/Element3D/face3d.hpp"
#include "../Model/Element3D/line3d.hpp"
#include "../Model/Element3D/point3d.hpp"
#include "../Model/Model3D/model3d.hpp"
#include "../Message/argument.hpp"
#include "../Message/response.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <regex>

using namespace std;
using ArgKey = Argument::ArgumentKey;
using ResKey = Response::ResponseKey;

// Singleton pattern
Controller* Controller::m_instance = nullptr;

// -----------------------------------------------------------
// [name] : GetInstance
// [function] : get the instance of the controller
// [input] : none
// [output] : the instance of the controller
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
Controller* Controller::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new Controller();
    }
    return m_instance;
}

// -----------------------------------------------------------
// [name] : HandleArguments
// [function] : handle the arguments passed from the viewer
// [input] : vector of arguments
// [output] : the response to the viewer
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: init handle argument
//       add some error catch
// reason: to support handling some error
// -----------------------------------------------------------
// date: 2024/8/2
// author: Huayu Chen
// edit: add display handle argument
// reason: to support displaying faces, lines, points, and statistics
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add functions to handle face and line operations
// reason: to support face and line operations
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: fix some bugs about exception handling
// reason: to support handling some error
// -----------------------------------------------------------
Response Controller::HandleArguments(vector<Argument> arguments)
{
    try {
        ArgKey key = arguments[0].GetKey();
        if (key == ArgKey::IMPORT_3D_MODEL) {
            // import 3D model
            Import3DModel(arguments[0].GetValues()[0]);
            return Response(ResKey::IMPORT_SUCCESS, {});
        }
        else if (key == ArgKey::EXPORT_3D_MODEL) {
            // export 3D model
            Export3DModel(arguments[0].GetValues()[0]);
            return Response(ResKey::EXPORT_SUCCESS, {});
        }
        else if (key == ArgKey::DISPLAY_ALL_FACES) {
            // get all faces
            if (!m_model) {
                throw runtime_error("There is no 3D model to display.");
            }
            vector<shared_ptr<Face3D>> faces = m_model->GetFaces();
            vector<string> face_strings;
            for (const shared_ptr<Face3D>& face_ptr : faces) {
                string one_face_strings = "";
                for (const Point3D& point : face_ptr->GetPoints()) {
                    one_face_strings += point.ToString();
                    // add a space between points
                    one_face_strings += " ";
                }
                face_strings.push_back(one_face_strings);
            }
            return Response(ResKey::DISPLAY_ALL_FACES, face_strings);
        }
        else if (key == ArgKey::DISPLAY_FACE_POINTS) {
            // check if model exists
            if (!m_model) {
                throw runtime_error("There is no 3D model to display.");
            }
            // get the face index
            int index = stoi(arguments[0].GetValues()[0]);
            if (index >= m_model->GetFaces().size() || index < 0) {
                return Response(ResKey::INDEX_OUT_OF_RANGE, {});
            }
            // get the face points
            vector<shared_ptr<Face3D>> faces = m_model->GetFaces();
            vector<string> point_strings;
            for (const Point3D& point : faces[index]->GetPoints()) {
                point_strings.push_back(point.ToString());
            }
            return Response(ResKey::DISPLAY_FACE_POINTS, point_strings);
        }
        else if (key == ArgKey::DISPLAY_ALL_LINES) {
            // check if model exists
            if (!m_model) {
                throw runtime_error("There is no 3D model to display.");
            }
            // get all lines
            vector<shared_ptr<Line3D>> lines = m_model->GetLines();
            vector<string> line_strings;
            for (const shared_ptr<Line3D>& line_ptr : lines) {
                string one_line_string = "";
                for (const Point3D& point : line_ptr->GetPoints()) {
                    one_line_string += point.ToString();
                    one_line_string += " ";
                }
                line_strings.push_back(one_line_string);
            }
            return Response(ResKey::DISPLAY_ALL_LINES, line_strings);
        }
        else if (key == ArgKey::DISPLAY_LINE_POINTS) {
            // check if model exists
            if (!m_model) {
                throw runtime_error("There is no 3D model to display.");
            }
            // get the line index
            int index = stoi(arguments[0].GetValues()[0]);
            if (index >= m_model->GetLines().size() || index < 0) {
                return Response(ResKey::INDEX_OUT_OF_RANGE, {});
            }
            // get the line points
            vector<shared_ptr<Line3D>> lines = m_model->GetLines();
            vector<string> point_strings;
            for (const Point3D& point : lines[index]->GetPoints()) {
                point_strings.push_back(point.ToString());
            }
            return Response(ResKey::DISPLAY_LINE_POINTS, point_strings);
        }
        else if (key == ArgKey::DISPLAY_STATISTICS) {
            if (!m_model) {
                throw runtime_error("There is no 3D model to display.");
            }
            // get the number of faces, lines, and points
            vector<shared_ptr<Face3D>> faces = m_model->GetFaces();
            vector<shared_ptr<Line3D>> lines = m_model->GetLines();
            vector<Point3D> points = m_model->GetPoints();
            // get the total area of the faces
            double total_area = 0.0;
            for (const shared_ptr<Face3D>& face_ptr : faces) {
                total_area += face_ptr->Area();
            }
            // get the total length of the lines
            double total_length = 0.0;
            for (const shared_ptr<Line3D>& line_ptr : lines) {
                total_length += line_ptr->Length();
            }
            // get minimum and maximum x, y, and z values of the points
            double min_x = numeric_limits<double>::max();
            double max_x = numeric_limits<double>::min();
            double min_y = numeric_limits<double>::max();
            double max_y = numeric_limits<double>::min();
            double min_z = numeric_limits<double>::max();
            double max_z = numeric_limits<double>::min();
            // get the minimum surrounding cube volume
            for (const Point3D& point : points) {
                if (point.X < min_x) {
                    min_x = point.X;
                }
                if (point.X > max_x) {
                    max_x = point.X;
                }
                if (point.Y < min_y) {
                    min_y = point.Y;
                }
                if (point.Y > max_y) {
                    max_y = point.Y;
                }
                if (point.Z < min_z) {
                    min_z = point.Z;
                }
                if (point.Z > max_z) {
                    max_z = point.Z;
                }
            }
            double minimum_surrounding_cube_volume = 
                (max_x - min_x) * (max_y - min_y) * (max_z - min_z);
            // create the statistics
            vector<string> statistics = {
                "Number of faces: " + to_string(faces.size()),
                "Total area: " + to_string(total_area),
                "Number of lines: " + to_string(lines.size()),
                "Total length: " + to_string(total_length),
                "Number of points: " + to_string(points.size()),
                "minimum_surrounding_cube_volume: " + 
                    to_string(minimum_surrounding_cube_volume)
            };
            return Response(ResKey::DISPLAY_STATISTICS, statistics);
        }
        else if (key == ArgKey::DELETE_FACE) {
            // get the face index
            int index = stoi(arguments[0].GetValues()[0]);
            DeleteFace(index);
            return Response(ResKey::DELETE_FACE_SUCCESS, {});
        }
        else if (key == ArgKey::ADD_FACE) {
            // get the face points
            try {
                vector<Point3D> points = StringsToPoints(
                                            arguments[0].GetValues());
                AddFace(Face3D(points));
            }
            // handle invalid argument exception
            catch (const invalid_argument& e) {
                if (string(e.what()) == "Invalid number format.") {
                    return Response(ResKey::INVALID_NUMBER_FORMAT, {});
                }
                else if (string(e.what()) == 
                        "Exactly three numbers are required.") {
                    return Response(ResKey::INPUT_NUMBER_ERROR, {});
                }
                else {
                    return Response(ResKey::UNKNOWN, {});
                }
            }
            
            return Response(ResKey::ADD_FACE_SUCCESS, {});
        }
        else if (key == ArgKey::MODIFY_FACE_POINT) {
            // get the face index
            int face_index = stoi(arguments[0].GetValues()[0]);
            // get the point index
            int point_index = stoi(arguments[0].GetValues()[1]);
            // get the new point
            if (face_index >= m_model->GetFaces().size() || face_index < 0) {
                return Response(ResKey::INDEX_OUT_OF_RANGE, {});
            }
            // check if the point index is valid
            if (point_index >= 
                m_model->GetFaces()[face_index]->GetPoints().size() 
                || point_index < 0) {
                return Response(ResKey::INDEX_OUT_OF_RANGE, {});
            }
            Point3D new_point = StringsToPoints(
                vector<string>{arguments[0].GetValues()[2]})[0];
            ModifyFacePoint(face_index, point_index, new_point);
            return Response(ResKey::MODIFY_FACE_POINT_SUCCESS, {});
        }
        else if (key == ArgKey::DELETE_LINE) {
            // get the line index
            int index = stoi(arguments[0].GetValues()[0]);
            DeleteLine(index);
            return Response(ResKey::DELETE_LINE_SUCCESS, {});
        }
        else if (key == ArgKey::ADD_LINE) {
            // get the line points
            vector<Point3D> points = StringsToPoints(
                arguments[0].GetValues());
            AddLine(Line3D(points));
            return Response(ResKey::ADD_LINE_SUCCESS, {});
        }
        else if (key == ArgKey::MODIFY_LINE_POINT) {
            // get the line index
            int line_index = stoi(arguments[0].GetValues()[0]);
            // get the point index
            int point_index = stoi(arguments[0].GetValues()[1]);
            // get the new point
            Point3D new_point = StringsToPoints(
                vector<string>{arguments[0].GetValues()[2]})[0];
            ModifyLinePoint(line_index, point_index, new_point);
            return Response(ResKey::MODIFY_LINE_POINT_SUCCESS, {});
        }
        else {
            return Response(ResKey::UNKNOWN, {});
        }
    }
    catch (const exception& e) {
        // handle exception here
        // invalid argument exception
        if (typeid(e) == typeid(invalid_argument)) {
            // empty path exception
            if (string(e.what()) == "Path should not be empty.") {
                return Response(Response::ResponseKey::EMPTY_PATH, {});
            }
            // invalid path exception
            if (string(e.what()) == "Path is not a valid OBJ file.") {
                return Response(Response::ResponseKey::NOT_OBJ_PATH, {});
            }
            // invalid path exception
            if (string(e.what()) == "Path does not exist.") {
                return Response(Response::ResponseKey::NOT_EXIST_PATH, {});
            }
            // index out of range exception
            if (string(e.what()) == "Index out of range") {
                return Response(Response::ResponseKey::INDEX_OUT_OF_RANGE, {});
            }
            // face already exists exception
            if (string(e.what()) == "Face already exists") {
                return Response(Response::ResponseKey::DUPLICATE_FACE, {});
            }
            // points are not distinct exception
            if (string(e.what()) == "The three points are not distinct") {
                return Response(Response::ResponseKey::NOT_A_FACE, {});
            }
            // line already exists exception
            if (string(e.what()) == "Line already exists") {
                return Response(Response::ResponseKey::DUPLICATE_LINE, {});
            }
            // points are the same exception
            if (string(e.what()) == "The two points are the same") {
                return Response(Response::ResponseKey::NOT_A_LINE, {});
            }
            // invalid input exception
            if (string(e.what()) == "Invalid input.") {
                return Response(Response::ResponseKey::INVALID_INPUT, {});
            }
            // parse failed exception
            if (string(e.what()) == "Failed to parse") {
                return Response(Response::ResponseKey::PARSE_FAILED, {});
            }
            // points are not distinct or other related exceptions
            if (string(e.what()) == "The three points are not distinct"
                || string(e.what()) == "The point is on the line"
                || string(e.what()) == "The two lines are not on the same plane"
                || string(e.what()) == "The two lines are coincident"
                || string(e.what()) == "Face3D must have 3 points") {
                return Response(Response::ResponseKey::NOT_A_FACE, {});
            }
            // invalid number format exception
            if (string(e.what()) == "Invalid number format.") {
                return Response(
                    Response::ResponseKey::INVALID_NUMBER_FORMAT, {});
            }
            // exactly three numbers required exception
            if (string(e.what()) == "Exactly three numbers are required.") {
                return Response(Response::ResponseKey::INPUT_NUMBER_ERROR, {});
            }
            // points are the same or other related exceptions
            if (string(e.what()) == "The two points are the same"
                || string(e.what()) == "Line3D must have 2 points"
                || string(e.what()) == "The two points are the same") {
                return Response(Response::ResponseKey::NOT_A_LINE, {});
            }
            // point must have 3 coordinates exception
            if (string(e.what()) == "Point3D must have 3 coordinates") {
                return Response(Response::ResponseKey::NOT_A_POINT, {});
            }
            // unknown invalid argument exception
            return Response(
                Response::ResponseKey::UNKNOWN_INVALID_ARGUMENT, {});
        }
        else if (typeid(e) == typeid(runtime_error)) {
            // failed to import the 3D model exception
            if (string(e.what()) == "Failed to import the 3D model.") {
                return Response(Response::ResponseKey::IMPORT_FAILED, {});
            }
            // failed to export the 3D model exception
            if (string(e.what()) == "Failed to export the 3D model.") {
                return Response(Response::ResponseKey::EXPORT_FAILED, {});
            }
            // failed to delete the face exception
            if (string(e.what()) == "Failed to delete the face.") {
                return Response(Response::ResponseKey::DELETE_FACE_FAILED, {});
            }
            // failed to add the face exception
            if (string(e.what()) == "Failed to add the face.") {
                return Response(Response::ResponseKey::ADD_FACE_FAILED, {});
            }
            // failed to modify the face point exception
            if (string(e.what()) == "Failed to modify the face point.") {
                return Response(
                    Response::ResponseKey::MODIFY_FACE_POINT_FAILED, {});
            }
            // failed to delete the line exception
            if (string(e.what()) == "Failed to delete the line.") {
                return Response(Response::ResponseKey::DELETE_LINE_FAILED, {});
            }
            // failed to add the line exception
            if (string(e.what()) == "Failed to add the line.") {
                return Response(Response::ResponseKey::ADD_LINE_FAILED, {});
            }
            // failed to modify the line point exception
            if (string(e.what()) == "Failed to modify the line point.") {
                return Response(
                    Response::ResponseKey::MODIFY_LINE_POINT_FAILED, {});
            }
            // failed to open the file exception
            if (string(e.what()) == "Failed to open the file") {
                return Response(Response::ResponseKey::OPEN_FILE_FAILED, {});
            }
            // no 3D model to export exception
            if (string(e.what()) == "There is no 3D model to export.") {
                return Response(Response::ResponseKey::NO_MODEL_TO_EXPORT, {});
            }
            // no 3D model for various operations exception
            if (string(e.what()) == 
                "There is no 3D model to delete the face from." || 
                string(e.what()) == 
                "There is no 3D model to add the face to." || 
                string(e.what()) == 
                "There is no 3D model to modify the face point." || 
                string(e.what()) == 
                "There is no 3D model to delete the line from." || 
                string(e.what()) == 
                "There is no 3D model to add the line to." || 
                string(e.what()) ==
                "There is no 3D model to modify the line point." ||
                string(e.what()) == 
                "There is no 3D model to display."){
                return Response(Response::ResponseKey::NO_3D_MODEL, {});
            }
            // unknown run time error exception
            else {
                return Response(
                    Response::ResponseKey::UNKNOWN_RUN_TIME_ERROR, {});
            }
        }
        else {
            return Response(Response::ResponseKey::UNKNOWN, {});
        }
    }
}

// -----------------------------------------------------------
// [name] : Import3DModel
// [function] : import a 3D model from a file
// [input] : the path of the file
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
void Controller::Import3DModel(const string& path)
{
    // Load the 3D model
    Model3DObjImporter importer;
    m_model = make_shared<Model3D>(importer.Load(path));

}

// -----------------------------------------------------------
// [name] : Export3DModel
// [function] : export a 3D model to a file
// [input] : the path of the file
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
void Controller::Export3DModel(const string& path)
{
    // Export the 3D model
    if (!m_model) {
        throw runtime_error("There is no 3D model to export.");
    }
    Model3DObjExporter exporter;
    exporter.Save(path, *m_model);
    // ...
}

// -----------------------------------------------------------
// [name] : DeleteFace
// [function] : delete a face from the 3D model
// [input] : the index of the face to delete
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
void Controller::DeleteFace(unsigned int FaceIndex)
{
    // Delete the face
    if (!m_model) {
        throw runtime_error("There is no 3D model to delete the face from.");
    }
    m_model->DeleteFace(FaceIndex);
}

// -----------------------------------------------------------
// [name] : AddFace
// [function] : add a face to the 3D model
// [input] : the face to add
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
void Controller::AddFace(const Face3D& face)
{
    if (!m_model) {
        throw runtime_error("There is no 3D model to add the face to.");
    }
    // Add the face
    m_model->AddFace(face);
}

// -----------------------------------------------------------
// [name] : ModifyFacePoint
// [function] : modify a point of a face in the 3D model
// [input] : the index of the face, the index of the point, 
//           and the new point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
void Controller::ModifyFacePoint(
    unsigned int FaceIndex, unsigned int PointIndex, const Point3D& NewPoint)
{
    if (!m_model) {
        throw runtime_error("There is no 3D model to modify the face point.");
    }
    // Modify the face point
    m_model->ModifyFacePoint(FaceIndex, PointIndex, NewPoint);
}

// -----------------------------------------------------------
// [name] : DeleteLine
// [function] : delete a line from the 3D model
// [input] : the index of the line to delete
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void Controller::DeleteLine(unsigned int LineIndex)
{
    if (!m_model) {
        throw runtime_error("There is no 3D model to delete the line from.");
    }
    
    // Delete the line
    m_model->DeleteLine(LineIndex);

}

// -----------------------------------------------------------
// [name] : AddLine
// [function] : add a line to the 3D model
// [input] : the line to add
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void Controller::AddLine(const Line3D& line)
{
    if (!m_model) {
        throw runtime_error("There is no 3D model to add the line to.");
    }
    // Add the line
    m_model->AddLine(line);
}

// -----------------------------------------------------------
// [name] : ModifyLinePoint
// [function] : modify a point of a line in the 3D model
// [input] : the index of the line, the index of the point, 
//           and the new point
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
void Controller::ModifyLinePoint(unsigned int LineIndex, 
                unsigned int PointIndex, const Point3D& NewPoint)
{
    if (!m_model) {
        throw runtime_error("There is no 3D model to modify the line point.");
    }
    // Modify the line point
    m_model->ModifyLinePoint(LineIndex, PointIndex, NewPoint);
}

// -----------------------------------------------------------
// [name] : StringsToPoints
// [function] : convert a vector of strings to a vector of points
// [input] : the vector of strings
// [output] : the vector of points
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
vector<Point3D> Controller::StringsToPoints(
            const vector<string>& pointStrings) {
    vector<Point3D> points;
    for (const string& pointString : pointStrings) {
        points.push_back(StringToPoint(pointString));
    }
    return points;
}

// -----------------------------------------------------------
// [name] : StringToPoint
// [function] : convert a string to a point
// [input] : the string
// [output] : the point
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Point3D Controller::StringToPoint(const string& pointString) {
    vector<double> numbers;
    string trimmedInput = pointString;

    // delete the leading and trailing spaces and parentheses
    trimmedInput.erase(trimmedInput.begin(), find_if(trimmedInput.begin(), 
        trimmedInput.end(), [](unsigned char ch) {  
        return !isspace(ch) && ch != '(';
    }));
    // delete the trailing spaces and parentheses
    trimmedInput.erase(find_if(trimmedInput.rbegin(), trimmedInput.rend(), 
            [](unsigned char ch) {
        return !isspace(ch) && ch != ')';
    }).base(), trimmedInput.end());

    // use regex to extract the numbers from the string
    regex re("\\s*([-+]?[0-9]*\\.?[0-9]+)(?:\\s+|\\s*,\\s*|\\s*$)");
    auto begin = sregex_iterator(trimmedInput.begin(), trimmedInput.end(), re);
    auto end = sregex_iterator();
    // convert the numbers to double
    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        try {
            double num = stod(match.str());
            numbers.push_back(num);
        } catch (const invalid_argument& e) {
            throw invalid_argument("Invalid number format.");
        }
    }
    // check if the number of coordinates is correct
    if (numbers.size() != 3) {
        throw invalid_argument("Exactly three numbers are required.");
    }
    return Point3D(numbers[0], numbers[1], numbers[2]);
}

// -----------------------------------------------------------
// [name] : ~Controller
// [function] : destructor of the Controller class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/2
// -----------------------------------------------------------
Controller::~Controller()
{
    if (m_instance)
    {
        delete m_instance;
    }
}




