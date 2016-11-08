#pragma once

#include <glm/glm.hpp>
#include "Bengine/SpriteBatch.h"
class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speedint, int lifeTime);
	~Bullet();

	void draw(Bengine::SpriteBatch& spriteBatch);

	//returns true when out of life
	bool update();

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};

