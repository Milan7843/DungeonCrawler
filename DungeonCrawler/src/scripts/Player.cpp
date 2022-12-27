#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::start()
{
	crossbow = std::shared_ptr<Crossbow>(new Crossbow(this->getTransform()));

	weapon = transform->getChildren()[0];

	firePoint = Transform::create(glm::vec2(0.6f, 0.0f));
	firePoint->setParent(weapon);

	bulletCollider = BoxCollider::create(0.1f, 0.1f, LAYER_1, LAYER_ALL - LAYER_1);
}

void Player::update()
{
	AnimationHandler::setAnimationWebParameter("player_sprite", "up", Input::getKey(KEY_W));
	AnimationHandler::setAnimationWebParameter("player_sprite", "down", Input::getKey(KEY_S));
	AnimationHandler::setAnimationWebParameter("player_sprite", "left", Input::getKey(KEY_A));
	AnimationHandler::setAnimationWebParameter("player_sprite", "right", Input::getKey(KEY_D));

	if (Input::getKey(KEY_W))
	{
		transform->movePosition(glm::vec2(0.0f, 1.0f) * Time::getDeltaTime() * playerSpeed);
	}
	if (Input::getKey(KEY_S))
	{
		transform->movePosition(glm::vec2(0.0f, -1.0f) * Time::getDeltaTime() * playerSpeed);
	}
	if (Input::getKey(KEY_A))
	{
		transform->movePosition(glm::vec2(-1.0f, 0.0f) * Time::getDeltaTime() * playerSpeed);
	}
	if (Input::getKey(KEY_D))
	{
		transform->movePosition(glm::vec2(1.0f, 0.0f) * Time::getDeltaTime() * playerSpeed);
	}

	if (Input::getMouseButton(MOUSE_LEFT) && timeSinceShot >= fireDelay)
	{
		crossbow->shoot();
		timeSinceShot = glm::mod(timeSinceShot, fireDelay);
	}

	timeSinceShot += Time::getDeltaTime();

	float requestedRotation = weapon->lookAt(weapon->worldPointToParentLocalPoint(Input::getMouseWorldPosition()));
	weapon->setRotation(Math::smoothRotate(weapon->getRotation(), requestedRotation, 5.0f, 400.0f));
}

void Player::shoot()
{
	Audio::playSound("shoot");

	Transform* bullet = Transform::create(firePoint->getPosition(), firePoint->getRotation(), glm::vec2(0.6f));
	bullet->setName("bullet");
	bullet->setTag("bullet");
	Rigidbody::create(bullet, bulletCollider, DYNAMIC, 0.0f, true);

	bullet->getComponent<Rigidbody>()->setLinearVelocity(bullet->getLocalRightVector() * 5.0f);

	SpriteRenderer::create(bullet, "src/sprites/cutie_cat.png", glm::vec2(0.0f), true);

	std::shared_ptr<Bullet> bulletScript = std::shared_ptr<Bullet>(new Bullet());
	bullet->addComponent(bulletScript);
}
