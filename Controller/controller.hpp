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
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP



#include <string>
#include <vector>
#include <memory>
#include "../Model/Storage/storage.hpp"

using namespace std;
//
//
//
//
//
//
//从viewer传到controller的参数
//
class Argument
{
};
//
//
//
class Response
{
};

//
//
//
class Controller
{
public:
    //
    //
    //
    //操作model的函数
    //
    //
    void Import3DModel(const string& path);
    //
    //word里面2.几那些功能最好每一个写一个函数
    //实现里面的功能
    //
    //
    //
    //
    //和viewer交互
    //
    //
    //
    //
    //
    //
    Response HandleArguments(vector<Argument> arguments);
    //
    //
    //
    //
    //
    //
    //
    //
    //
private:
    //
    //
    shared_ptr<Storage> m_pStorage;
    //
    //




};
















#endif // CONTROLLER_HPP