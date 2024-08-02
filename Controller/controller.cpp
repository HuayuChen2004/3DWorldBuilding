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
//
//
#include "controller.hpp"
#include <stdexcept>
#include <filesystem>

#include "../Model/FileIO/model3dobjimporter.hpp"
#include "../Model/FileIO/model3dobjexporter.hpp"

using ArgKey = Argument::ArgumentKey;
using ResKey = Response::ResponseKey;


Response Controller::HandleArguments(vector<Argument> arguments)
{
    //
    try {
        ArgKey key = arguments[0].GetKey();
        if (key == ArgKey::IMPORT_3D_MODEL) {
            Import3DModel(arguments[0].GetValue());
            return Response(ResKey::IMPORT_SUCCESS, {});
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

void Controller::DisplayAllFaces() const {

}
