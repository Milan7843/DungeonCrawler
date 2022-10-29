#include "EnemySpawner.h"

namespace EnemySpawner
{
	void spawnEnemy()
	{
		// Adding an object to the scene
		TransformPointer enemy = Transform::create();
		enemy->setName("enemy");

		// Adding a script to this object
		std::shared_ptr<SimpleEnemy> simpleEnemyScript = std::shared_ptr<SimpleEnemy>(new SimpleEnemy());
		enemy->addComponent(simpleEnemyScript);

		BoxCollider boxCollider(1.0f, 1.0f);

		// Giving the player a rigidbody so that it can collide
		Rigidbody::create(enemy, boxCollider, DYNAMIC, LAYER_0, LAYER_ALL - LAYER_1, 0.0f, false, true, false);

		// Adding a sprite renderer to the object
		SpriteRenderer::create(enemy, "src/sprites/monster_sprite_sheet.png", true, 3, 4);
		enemy->setRenderDepth(200.0f);

		// Creating an animator for the player
		SimpleEnemyAnimator::create(enemy, "enemy_sprite");
	}
};
