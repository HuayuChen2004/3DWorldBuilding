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

using ArgKey = Argument::ArgumentKey;


Response Controller::HandleArguments(vector<Argument> arguments)
{
    //
    try {
        ArgKey key = arguments[0].GetKey();
        if (key == ArgKey::IMPORT_3D_MODEL) {

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
            else if (string(e.what()) == "Path is invalid.") {
                return Response(Response::ResponseKey::INVALID_PATH, {});
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
    
    // Import the 3D model
    // ...
}