#pragma once

#include "ScriptLoader.h"

#include <Root/Root.h>

// Window size
const int WIDTH = 1280, HEIGHT = 720;

int main()
{
	loadScripts();
	Root::Start(WIDTH, HEIGHT);
}
