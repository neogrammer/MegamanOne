#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Cfg.h>

#ifndef DYNAMIC_H__
#define DYNAMIC_H__

class Dynamic
{
public:
	Cfg::Textures texType;
	sf::Vector2f pos{};
	sf::Vector2f imgOrigin{};
	sf::Vector2f vel{};
	sf::IntRect texRect{};
	sf::IntRect bbox{};

	sf::Vector2f getImgSize();
	sf::Vector2f getImgHSize();
	sf::Vector2f getBBoxSize();
	sf::Vector2f getBBoxHSize();
	sf::FloatRect getAABB();
	sf::Vector2f getAABBCenter();
	void setup(Cfg::Textures texType_, sf::Vector2f pos_, sf::Vector2f orig_, sf::IntRect texRect_, sf::IntRect bboxRect_, sf::Vector2f vel_);
	void applyVelocity();
	void setPos(sf::Vector2f pos_);
	void move(sf::Vector2f pos_);
	void setVelocity(sf::Vector2f vel_);
	void accelerate(sf::Vector2f acc_);
	void applyGravity();
	std::unique_ptr<sf::Sprite> spr();
};

#endif