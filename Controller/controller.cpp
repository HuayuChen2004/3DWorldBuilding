// this is 
//
// edit logging:
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
//
#include "controller.hpp"
#include <stdexcept>
#include <filesystem>

#include "../Model/FileIO/model3dobjimporter.hpp"
#include "../Model/FileIO/model3dobjexporter.hpp"
#include "../Model/Element3D/face3d.hpp"
#include "../Model/Element3D/line3d.hpp"
#include "../Model/Element3D/point3d.hpp"
#include "../Message/argument.hpp"
#include "../Message/response.hpp"


using ArgKey = Argument::ArgumentKey;
using ResKey = Response::ResponseKey;

Controller* Controller::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new Controller();
    }
    return m_instance;
}


Response Controller::HandleArguments(vector<Argument> arguments)
{
    //
    try {
        ArgKey key = arguments[0].GetKey();
        if (key == ArgKey::IMPORT_3D_MODEL) {
            Import3DModel(arguments[0].GetValues()[0]);
            return Response(ResKey::IMPORT_SUCCESS, {});
        }
        else if (key == ArgKey::EXPORT_3D_MODEL) {
            Export3DModel(arguments[0].GetValues()[0]);
            return Response(ResKey::EXPORT_SUCCESS, {});
        }
        else if (key == ArgKey::DISPLAY_ALL_FACES) {
            // get all faces
            vector<shared_ptr<Face3D>> faces = m_model->GetFaces();
            vector<string> face_strings;
            for (const shared_ptr<Face3D>& face_ptr : faces) {
                face_strings.push_back(face_ptr->ToString());
            }
            return Response(ResKey::DISPLAY_ALL_FACES, face_strings);
        }
        else if (key == ArgKey::DISPLAY_FACE_POINTS) {
            // get the face index
            int index = stoi(arguments[0].GetValues()[0]);
            // get the face points
            vector<shared_ptr<Face3D>> faces = m_model->GetFaces();
            vector<string> point_strings;
            for (const Point3D& point : faces[index]->GetPoints()) {
                point_strings.push_back(point.ToString());
            }
            return Response(ResKey::DISPLAY_FACE_POINTS, point_strings);
        }
        else if (key == ArgKey::DISPLAY_ALL_LINES) {
            // get all lines
            vector<shared_ptr<Line3D>> lines = m_model->GetLines();
            vector<string> line_strings;
            for (const shared_ptr<Line3D>& line_ptr : lines) {
                line_strings.push_back(line_ptr->ToString());
            }
            return Response(ResKey::DISPLAY_ALL_LINES, line_strings);
        }
        else if (key == ArgKey::DISPLAY_LINE_POINTS) {
            // get the line index
            int index = stoi(arguments[0].GetValues()[0]);
            // get the line points
            vector<shared_ptr<Line3D>> lines = m_model->GetLines();
            vector<string> point_strings;
            for (const Point3D& point : lines[index]->GetPoints()) {
                point_strings.push_back(point.ToString());
            }
            return Response(ResKey::DISPLAY_LINE_POINTS, point_strings);
        }
        else if (key == ArgKey::DISPLAY_STATISTICS) {
            // get the number of faces, lines, and points
            vector<shared_ptr<Face3D>> faces = m_model->GetFaces();
            vector<shared_ptr<Line3D>> lines = m_model->GetLines();
            vector<shared_ptr<Point3D>> points = m_model->GetPoints();
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
            for (const shared_ptr<Point3D>& point_ptr : points) {
                if (point_ptr->X < min_x) {
                    min_x = point_ptr->X;
                }
                if (point_ptr->X > max_x) {
                    max_x = point_ptr->X;
                }
                if (point_ptr->Y < min_y) {
                    min_y = point_ptr->Y;
                }
                if (point_ptr->Y > max_y) {
                    max_y = point_ptr->Y;
                }
                if (point_ptr->Z < min_z) {
                    min_z = point_ptr->Z;
                }
                if (point_ptr->Z > max_z) {
                    max_z = point_ptr->Z;
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
            vector<Point3D> points = FixedSizePoint3DContainer::StringsToPoints(
                arguments[0].GetValues());
            AddFace(Face3D(points));
            return Response(ResKey::ADD_FACE_SUCCESS, {});
        }
        else if (key == ArgKey::MODIFY_FACE_POINT) {
            // get the face index
            int face_index = stoi(arguments[0].GetValues()[0]);
            // get the point index
            int point_index = stoi(arguments[0].GetValues()[1]);
            // get the new point
            Point3D new_point = FixedSizePoint3DContainer::StringsToPoints(
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
            vector<Point3D> points = FixedSizePoint3DContainer::StringsToPoints(
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
            Point3D new_point = FixedSizePoint3DContainer::StringsToPoints(
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
            else if (string(e.what()) == "Path is not a valid OBJ file.") {
                return Response(Response::ResponseKey::NOT_OBJ_PATH, {});
            }
            // invalid path exception
            else if (string(e.what()) == "Path does not exist.") {
                return Response(Response::ResponseKey::NOT_EXIST_PATH, {});
            }
        }

        else if (typeid(e) == typeid(runtime_error)) {
            // failed to import the 3D model
            if (string(e.what()) == "Failed to import the 3D model.") {
                return Response(Response::ResponseKey::IMPORT_FAILED, {});
            }
            // failed to export the 3D model
            if (string(e.what()) == "Failed to export the 3D model.") {
                return Response(Response::ResponseKey::EXPORT_FAILED, {});
            }
        }

        
    }
}

//
void Controller::Import3DModel(const string& path)
{
    // Check if the path is empty
    if (path.empty())
    {
        throw invalid_argument("Path should not be empty.");
    }
    // Check if the path is valid
    if (path.find(".obj") == string::npos)
    {
        throw invalid_argument("Path is not a valid OBJ file.");
    }

    // Load the 3D model
    try {
        Model3DObjImporter importer;
        importer.Load(path);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to import the 3D model.");
    }
    // Import the 3D model
    // ...
}

void Controller::Export3DModel(const string& path)
{
    // Check if the path is empty
    if (path.empty())
    {
        throw invalid_argument("Path should not be empty.");
    }
    // Check if the path is valid
    if (path.find(".obj") == string::npos)
    {
        throw invalid_argument("Path is not a valid OBJ file.");
    }
    // Check if the path exists
    if (!filesystem::exists(path))
    {
        throw invalid_argument("Path does not exist.");
    }

    // Export the 3D model
    try {
        Model3DObjExporter exporter;
        exporter.Save(path, *m_model);
    }
    catch (const exception& e) {
        throw runtime_error("Failed to export the 3D model.");
    }
    // ...
}

void Controller::DeleteFace(unsigned int FaceIndex)
{
    if (FaceIndex >= m_model->GetFaces().size())
    {
        throw invalid_argument("Face index out of range.");
    }
    // Delete the face
    try {
        m_model->DeleteFace(FaceIndex);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to delete the face.");
    }
}

void Controller::AddFace(const Face3D& face)
{
    // Add the face
    try {
        m_model->AddFace(face);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to add the face.");
    }
}

void Controller::ModifyFacePoint(unsigned int FaceIndex, unsigned int PointIndex, const Point3D& NewPoint)
{
    if (FaceIndex >= m_model->GetFaces().size())
    {
        throw invalid_argument("Face index out of range.");
    }
    if (PointIndex >= m_model->GetFaces()[FaceIndex]->GetPoints().size())
    {
        throw invalid_argument("Point index out of range.");
    }
    // Modify the face point
    try {
        m_model->ModifyFacePoint(FaceIndex, PointIndex, NewPoint);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to modify the face point.");
    }
}

void Controller::DeleteLine(unsigned int LineIndex)
{
    if (LineIndex >= m_model->GetLines().size())
    {
        throw invalid_argument("Line index out of range.");
    }
    // Delete the line
    try {
        m_model->DeleteLine(LineIndex);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to delete the line.");
    }
}

void Controller::AddLine(const Line3D& line)
{
    // Add the line
    try {
        m_model->AddLine(line);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to add the line.");
    }
}

void Controller::ModifyLinePoint(unsigned int LineIndex, 
                unsigned int PointIndex, const Point3D& NewPoint)
{
    if (LineIndex >= m_model->GetLines().size())
    {
        throw invalid_argument("Line index out of range.");
    }
    if (PointIndex >= m_model->GetLines()[LineIndex]->GetPoints().size())
    {
        throw invalid_argument("Point index out of range.");
    }
    // Modify the line point
    try {
        m_model->ModifyLinePoint(LineIndex, PointIndex, NewPoint);
    }
    catch (const exception& e) {
        // Handle the exception
        throw runtime_error("Failed to modify the line point.");
    }
}






