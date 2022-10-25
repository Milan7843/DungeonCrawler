#include "ScriptLoader.h"

void loadScripts()
{
	// Creating a shared pointer to the script, then adding it to Root
	std::shared_ptr<Script> gameManager(new GameManager);
	Root::addScript(gameManager);

	// Creating a shared pointer to the script, then adding it to Root
	std::shared_ptr<Script> guiScript(new GUIScript);
	Root::addScript(guiScript);
}
