#include "MyScript.h"

MyScript::MyScript()
{
}

MyScript::~MyScript()
{

}

void MyScript::start()
{
	Logger::log("We called the start function from a script!");
}

void MyScript::update()
{
	Logger::log("We called the update function from a script!");
}
