#include "EnemySpawner.h"

namespace EnemySpawner
{
	void spawnEnemy()
	{
		// Adding an object to the scene
		TransformPointer enemy = Transform::create();
		enemy->setScale(glm::vec2(0.75f, 1.0f));
		enemy->setName("enemy");
		enemy->setTag("enemy");

		// Adding a script to this object
		std::shared_ptr<SimpleEnemy> simpleEnemyScript = std::shared_ptr<SimpleEnemy>(new SimpleEnemy());
		enemy->addComponent(simpleEnemyScript);

		ColliderPointer boxCollider{ BoxCollider::create(1.0f, 1.0f, LAYER_2, LAYER_ALL) };

		// Giving the player a rigidbody so that it can collide
		Rigidbody::create(enemy, boxCollider, DYNAMIC, 0.0f, false, true, false);

		// Adding a sprite renderer to the object
		SpriteRenderer::create(enemy, "src/sprites/monster_sprite_sheet.png", glm::vec2(0.0f), true, 3, 4);
		enemy->setRenderDepth(200.0f);

		// Creating an animator for the player
		SimpleEnemyAnimator::create(enemy, "enemy_sprite");
	}
};
