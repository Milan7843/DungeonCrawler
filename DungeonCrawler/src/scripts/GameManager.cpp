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
	SpriteRenderer::create(backgroundTransform, "src/sprites/background.png", glm::vec2(0, 0), true);
	backgroundTransform->setName("wall");
	backgroundTransform->setTag("wall");
	// Creating the level border collider
	std::vector<glm::vec2> backgroundColliderPoints{
		glm::vec2(4.0f * (16.0f / 9.0f), 4.0f),
		glm::vec2(4.0f * (16.0f / 9.0f), -4.0f),
		glm::vec2(-4.0f * (16.0f / 9.0f), -4.0f),
		glm::vec2(-4.0f * (16.0f / 9.0f), 4.0f)
	};
	ColliderPointer backgroundCollider = LoopCollider::create(backgroundColliderPoints);
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

	EnemySpawner::spawnEnemy();

	Physics::enableDebugMode();

	RootGUI::loadFont("src/fonts/arial.ttf", "arial", 0.7f, 0.8f);
	RootGUI::loadFont("src/fonts/ROCKB.TTF", "rockb", 0.4f, 1.0f);
	RootGUI::enableDebugMode();

	//RootGUIComponent::Text::create("test", "arial");
	//RootGUIComponent::Text::create("abcdefghijklmnopqrstuvwxyz", "arial", 0.01f);



	RectanglePointer pauseRect = RootGUIComponent::Rectangle::create(
		glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 0.4f), 0.0f);
	
	TextPointer text = RootGUIComponent::Text::create(
		"PLAY",
		"rockb", 0.8f, glm::vec2(0.0f, 0.0f), glm::vec2(0.4f, 0.2f), 0.0f);

	text->setParent(pauseRect);

	text->setCenterHorizontally(true);
	text->setCenterVertically(true);

	text->setColor(glm::vec3(0.4f));
	text->setColorOnHover(glm::vec3(0.2f));
	text->setColorOnPress(glm::vec3(0.0f));

	text->setTextColor(glm::vec3(1.0f));
	text->setTextColorOnHover(glm::vec3(1.0f, 0.3f, 0.8f));
	text->setTextColorOnPress(glm::vec3(0.5f, 0.7f, 1.0f));

	text->setScaleOnHover(glm::vec2(1.05f));
	text->setScaleOnPress(glm::vec2(0.96f));

	text->setTransitionDuration(0.09f);
	
	/*
	TextPointer text2 = RootGUIComponent::Text::create(
		"If the code is working correctly, we should have a different font here.",
		"rockb", 0.8f, glm::vec2(-0.5f, 0.0f), glm::vec2(1.0f, 1.0f));
	*/
	/*
	RectanglePointer rect = RootGUIComponent::Rectangle::create(glm::vec2(-0.1f, 0.1f), glm::vec2(0.1f, 0.1f));
	rect->setHorizontalScreenAnchorPoint(HorizontalAnchorPoint::Right);
	rect->setVerticalScreenAnchorPoint(VerticalAnchorPoint::Bottom);
	rect->setScaleReference(ScaleReference::Height);*/


	//TileSet::create("src/tile grids/grass.tileset", "ground");
	TileMapCreator::createTileSets();

	TransformPointer tileGridTransform = Transform::create();
	tileGridTransform->setRenderDepth(4000.0f);
	TileGrid* tileGrid = TileGrid::create(tileGridTransform,
			"src/sprites/test_tileset.png",
			true,
			glm::ivec2(6, 3),
			"src/tile grids/tile_grid_example.tilegrid",
			"ground",
			1.4f);


	ColliderPointer tileGridCollider = TileGridCollider::create(tileGrid, LAYER_0, LAYER_ALL - LAYER_1, CollisionType::INSIDE, 1);
	Rigidbody::create(tileGridTransform, tileGridCollider, KINEMATIC, 1.0f);
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
	player->setTag("player");

	// Adding a script to this object
	std::shared_ptr<Player> playerScript = std::shared_ptr<Player>(new Player());
	player->addComponent(playerScript);

	ColliderPointer fullBoxCollider{ BoxCollider::create(1.0f, 1.0f, LAYER_0, LAYER_ALL - LAYER_1 - LAYER_0) };
	ColliderPointer lowerBoxCollider{ BoxCollider::create(1.0f, 0.5f, LAYER_0, LAYER_ALL - LAYER_1, glm::vec2(0.0f, -0.25f)) };

	std::vector<ColliderPointer> colliders{
		fullBoxCollider, lowerBoxCollider
	};

	// Giving the player a rigidbody so that it can collide
	Rigidbody::create(player, colliders, DYNAMIC, 0.0f, false, true, false);

	// Adding a sprite renderer to the object
	playerSpriteRenderer = SpriteRenderer::create(player, "src/sprites/test_sprite_sheet_directions.png", glm::vec2(0, 0), true, 4, 4);
	player->setRenderDepth(100.0f);

	// Creating an animator for the player
	PlayerAnimator::create(player, "player_sprite");
}

