#include "MyComponentScript.h"

MyComponentScript::MyComponentScript()
{
}

MyComponentScript::~MyComponentScript()
{

}

void MyComponentScript::start()
{
	Logger::log("We called the start function from a component script!");
}

void MyComponentScript::update()
{
	Logger::log("We called the update function from a component script!");
}
