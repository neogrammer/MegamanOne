#ifndef ASPRITE_H__
#define ASPRITE_H__
#include <3rdParty/olcUTIL_Geometry2D.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Cfg.h>
#include <memory>

class ASprite
{
	olc::v_2d<float> bbPos{};
	olc::v_2d<float> vel{};
	float accelY{};
	Cfg::Textures tex{Cfg::Textures::Count};
	bool bAffectedByGravity{};
	AnimDirType animDir{ AnimDirType::NotSet };
public:
	// these will be changed to a heinous animation map from the depths of hell
	sf::IntRect texRect{};
	sf::FloatRect bbox{};
public:
	ASprite() = default;
	~ASprite() = default;
	ASprite(const ASprite&) = default;
	ASprite& operator=(const ASprite&) = default;
	ASprite(ASprite&&) = default;
	ASprite& operator=(ASprite&&) = default;

	ASprite(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);
	void setup(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);

	bool isAffectedByGravity();
	void setAffectedByGravity(bool cond_);
	AnimDirType getAnimDirType();
	void setAnimDirType(AnimDirType type_);
	sf::IntRect getTexRect();
	sf::FloatRect getBBox();
	olc::utils::geom2d::rect<float> bbRect();
	olc::v_2d<float> getPos();
	olc::v_2d<float> getBBOffset();
	olc::v_2d<float> getBBSize();
	olc::vi2d getFrameSize();
	olc::v_2d<float> getVelocity();
	void setVelocity(olc::v_2d<float> vel_);
	void adjustSpeed(olc::v_2d<float> vel_);
	void setPos(olc::v_2d<float> pos_);
	void displace(olc::v_2d<float> disp_);
	void switchDirection();
	void changeDirection(AnimDirType animDir_);
	void  applyGravity(float grav_);
	void tickMovement();

	olc::utils::geom2d::ray<float> castRay(OriginPtType oType_, RayDirType dirType, olc::v_2d<float> target = { 0.f,0.f });
	std::unique_ptr<sf::Sprite> getSpr();

};

#endif