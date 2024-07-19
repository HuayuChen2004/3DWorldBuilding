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
//
//
//
//
//
//
#include "controller.hpp"
#include <stdexcept>



Response Controller::HandleArguments(vector<Argument> arguments)
{
    //
    try {
        switch (1) {
            case 1:
                Import3DModel("ha");
                return Response();
                break;
            case 2:
                Import3DModel("ie");
                return Response();
                break;
        }
        
    }
    catch (const exception& e) {
        // handle exception here
        return Response();
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
    // ...
    // Import the 3D model
    // ...
}