#pragma once

#include <rootgui/RootGUI.h>
#include <rootgui/Rectangle.h>
#include <Root/Root.h>

class GUIScript : public Script
{
public:
	GUIScript();
	~GUIScript();

	void start() override;

	void update() override;
};

