#pragma once

#include "Application.h"

// Window size
const int WIDTH = 1200, HEIGHT = 700;

int main()
{
	Application application(WIDTH, HEIGHT);
	return application.Start();
}
