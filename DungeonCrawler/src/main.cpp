#pragma once

#include "ScriptLoader.h"

#include <Root/Root.h>

// Window size
const int WIDTH = 1200, HEIGHT = 700;

int main()
{
	loadScripts();
	Root::Start(WIDTH, HEIGHT);
}
