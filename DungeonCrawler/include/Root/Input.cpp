#include "Input.h"

#include "Root/engine/InputEngine.h"

namespace Input
{
	bool getKey(int key)
	{
		return InputEngine::getKey(key);
	}

	bool getKeyPressed(int key)
	{
		return InputEngine::getKeyPressed(key);
	}
	bool getKeyReleased(int key)
	{
		return InputEngine::getKeyReleased(key);
	}
};
