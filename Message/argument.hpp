// this is the header file for the Argument class
// this class is used to store the arguments 
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: init Argument class
//       add key-value pair for arguments
//       add functions to get key and values
// reason: to support storing the arguments passed
//         from the viewer to the controller
// -----------------------------------------------------------




#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>
#include <vector>


using namespace std;


class Argument
{
public:
    enum class ArgumentKey {
        IMPORT_3D_MODEL,
        EXPORT_3D_MODEL,
        DISPLAY_ALL_FACES,
        DELETE_FACE,
        ADD_FACE,
        DISPLAY_FACE_POINTS,
        MODIFY_FACE_POINT,
        DISPLAY_ALL_LINES,
        ADD_LINE,
        DELETE_LINE,
        DISPLAY_LINE_POINTS,
        MODIFY_LINE_POINT,
        DISPLAY_STATISTICS,
        UNKNOWN
    };
    Argument(ArgumentKey key, vector<string> values);
    virtual ~Argument();
    ArgumentKey GetKey() const;
    vector<string> GetValues() const;
private:
    ArgumentKey m_key;
    vector<string> m_values;

};

#endif // ARGUMENT_HPP