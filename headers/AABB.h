#ifndef AABB_H__
#define AABB_H__
#include <3rdParty/olcUTIL_Geometry2D.h>

class AABB
{
public:
	AABB();
	AABB(Cfg::Textures texType_,  sf::IntRect texRect_, int imgOx_, int imgOy_, sf::FloatRect bboxRect_);
	olc::utils::geom2d::rect<float> current{};
	olc::utils::geom2d::rect<float> previous{};
	sf::IntRect imgRect{};
	int imgOffsetX;
	int imgOffsetY;

	float velx;
	float vely;
	Cfg::Textures tex;
	sf::IntRect* currFrame;
	float& posx();
	float& posy();
	float& oldPosx();
	float& oldPosy();
	float width();
	float height();
	float hHeight();
	float hWidth();
	olc::utils::geom2d::ray<float> dir();
	olc::utils::geom2d::line<float> fromTo(olc::v_2d<float>  point_);
	olc::utils::geom2d::line<float> toFrom(olc::v_2d<float>  point_);
	olc::utils::geom2d::rect<float> broadBox();
	void staticCollide(olc::utils::geom2d::rect<float> statObj_);
	int imgXOffset();
	int imgYOffset();
	int imgX();
	int imgY();
	int imgRectW();
	int imgRectHW();
	int imgRectH();
	int imgRectHH();
	std::unique_ptr<sf::Sprite> mkSpr();
	void setup(Cfg::Textures texType_, sf::IntRect texRect_, sf::FloatRect bboxRect_);
	void applyVelocity();
	void setPos(sf::Vector2f pos_);
	void move(sf::Vector2f pos_);
	void setVelocity(sf::Vector2f vel_);
	void accelerate(sf::Vector2f acc_);
	void applyGravity();
};

#endif