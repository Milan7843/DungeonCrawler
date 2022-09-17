#pragma once

/**
 * Class which all components must inherit from.
 */
class Component
{
public:

	/**
	 * The start function of this component, gets called automatically at the start of the game.
	 */
	virtual void start();

	/**
	 * The update function of this component, gets called automatically every frame.
	 */
	virtual void update();

private:

};
