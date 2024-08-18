// [file name] : argument.hpp
// [function] : declare the class argument
// [author] : Huayu Chen
// [date] : 2024/8/3

// [edit history] :
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

// notes for the Argument class
// -----------------------------------------------------------
// [class name] : Argument
// [function] : store the arguments passed from the viewer to the controller
// [notes on interface] :
// 1. the arguments are stored as a key-value pair, where the key is the
//    argument name and the value is a vector of strings that contains the
//    arguments passed
// 2. there are constant getters to get the key and values
// 3. the key is an enum class that defines all the possible argument names
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------

class Argument
{
public:
    // notes for the ArgumentKey enum class
    // -----------------------------------------------------------
    // [enum class name] : ArgumentKey
    // [function] : define all the possible argument names
    // [author] : Huayu Chen
    // [notes on interface] :
    // 1. this is an enum class that defines all the possible argument names
    //    so there are no member variables or functions
    // 2. add new argument names if the program needs to support more commands
    // [date] : 2024/8/3
    // -----------------------------------------------------------
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
    // constructor, argument key: the type of command, 
    // values: the arguments passed
    Argument(ArgumentKey key, vector<string> values);
    // virtual destructor
    virtual ~Argument();
    // getter for the key
    ArgumentKey GetKey() const;
    // getter for the values
    vector<string> GetValues() const;
private:
    // private member variables, key and values
    ArgumentKey m_key;
    vector<string> m_values;
};

#endif // ARGUMENT_HPP