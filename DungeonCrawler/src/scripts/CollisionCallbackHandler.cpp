#include "CollisionCallbackHandler.h"

void CollisionCallbackHandler::BeginContact(b2Contact* contact)
{
	Logger::log("Began contact!");
}

void CollisionCallbackHandler::EndContact(b2Contact* contact)
{
}
