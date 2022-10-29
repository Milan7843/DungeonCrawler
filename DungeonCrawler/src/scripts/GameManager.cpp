#include "GameManager.h"

#include <functional>

GameManager::GameManager()
	: collisionCallbackListener()
{
	Physics::setCollisionListener(&collisionCallbackListener);
}

GameManager::~GameManager()
{

}

void GameManager::start()
{
	initialisePlayer();
	
	// Adding a camera to the scene
	cameraTransform = Transform::create();
	CameraPointer camera = Camera::create(cameraTransform, 8.0f);

	Transform* backgroundTransform = Transform::create(glm::vec2(0.0f), 0.0f, glm::vec2(8.0f * (16.0f / 9.0f), 8.0f), 10000.0f);
	SpriteRenderer::create(backgroundTransform, "src/sprites/background.png", true);
	backgroundTransform->setName("wall");
	// Creating the level border collider
	std::vector<glm::vec2> backgroundColliderPoints{
		glm::vec2(4.0f * (16.0f / 9.0f), 4.0f),
		glm::vec2(4.0f * (16.0f / 9.0f), -4.0f),
		glm::vec2(-4.0f * (16.0f / 9.0f), -4.0f),
		glm::vec2(-4.0f * (16.0f / 9.0f), 4.0f)
	};
	LoopCollider backgroundCollider(backgroundColliderPoints);
	Rigidbody::create(backgroundTransform, backgroundCollider, STATIC);

	/*
	particleSystemTransform = Transform::create(glm::vec2(2.0f, 1.0f));
	particleSystem = ParticleSystem::create(particleSystemTransform);
	Gradient<glm::vec3> colorGradient = Gradient<glm::vec3>(std::vector<GradientPoint<glm::vec3>>{ 
		{ 0.0f, glm::vec3(1.0f) },
		{ 0.5f, glm::vec3(0.1f, 0.9f, 0.6f) },
		{ 0.9f, glm::vec3(0.9f, 0.2f, 0.8f) } });
	Gradient<glm::vec2> sizeGradient = Gradient<glm::vec2>(std::vector<GradientPoint<glm::vec2>>{
		{ 0.0f, glm::vec2(0.0f) },
		{ 0.1f, glm::vec2(1.0f) },
		{ 0.8f, glm::vec2(1.0f) },
		{ 1.0f, glm::vec2(0.0f) } 
	});
	particleSystem->setColorOverLifeTimeGradient(colorGradient);
	particleSystem->setSizeOverLifeTimeGradient(sizeGradient);
	particleSystem->setSprite("src/sprites/cutie_cat.png");
	particleSystem->setOnFinish(REPEAT);
	particleSystem->play();
	*/

	Renderer::addScreenSpaceEffect(ScreenSpaceEffect::create("src/shaders/screenSpaceFragment.shader"));
	//Renderer::Bloom::setEnabled(true);
	Renderer::Bloom::setThreshold(0.7f);
	Renderer::Bloom::setIntensity(0.5f);
	Renderer::setMSAAQualityLevel(2);

	Audio::loadSound("src/soundfx/shoot.wav", "shoot");
}

void GameManager::update()
{
	/*
	std::cout
		<< r[0][0] << " " << r[1][0] << " " << r[2][0] << " " << r[3][0] << "\n"
		<< r[0][1] << " " << r[1][1] << " " << r[2][1] << " " << r[3][1] << "\n"
		<< r[0][2] << " " << r[1][2] << " " << r[2][2] << " " << r[3][2] << "\n"
		<< r[0][3] << " " << r[1][3] << " " << r[2][3] << " " << r[3][3] << std::endl;
	*/
}

void GameManager::initialisePlayer()
{
	// Adding an object to the scene
	player = Transform::create();
	player->setName("player");

	// Adding a script to this object
	std::shared_ptr<Player> playerScript = std::shared_ptr<Player>(new Player());
	player->addComponent(playerScript);

	BoxCollider boxCollider(1.0f, 1.0f);

	// Giving the player a rigidbody so that it can collide
	Rigidbody::create(player, boxCollider, DYNAMIC, LAYER_0, LAYER_ALL - LAYER_1, 0.0f, false, true, false);

	// Adding a sprite renderer to the object
	playerSpriteRenderer = SpriteRenderer::create(player, "src/sprites/test_sprite_sheet_directions.png", true, 4, 4);
	player->setRenderDepth(100.0f);

	// Creating an animator for the player
	PlayerAnimator::create(player, "player_sprite");

	// Creating a weapon for the player to hold
	TransformPointer weapon = Transform::create(glm::vec2(0.0f, -0.1f));
	weapon->setScale(glm::vec2(0.8f, 0.4f));
	weapon->setParent(player);

	// Adding a sprite renderer to the object
	SpriteRendererPointer weaponSpriteRenderer = SpriteRenderer::create(weapon, "src/sprites/weapon.png", true);
}

