#include "ScriptLoader.h"

void loadScripts()
{
	// Creating a shared pointer to the script, then adding it to Root
	std::shared_ptr<Script> myScript(new MyScript);
	Root::addScript(myScript);
}
