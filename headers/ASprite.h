#ifndef ASPRITE_H__
#define ASPRITE_H__
#include <3rdParty/olcUTIL_Geometry2D.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Cfg.h>
#include <memory>

class Tile;
class Projectile;
class Tilemap;

class ASprite
{
	struct AnimData
	{
		std::string name{ "none" };
		std::string fallbackName{ "none" };
		int numFrames{ };
		int index{ };
		float animDelay{};
		float pauseDelay{};
		bool playing{ true };
		bool facingLeft{ true };
		bool onLastFrame{ false };
		bool looping{ true };
		int repeatTimes{ 1 };

		std::vector<sf::FloatRect> bboxes{};

		bool isOnLastFrame();

		int getIndex();
		sf::IntRect getBBox();
		void animate();
		void resetData();
		void play();
		void stop();
		void pause();
		void resume();

	};

	int health{ 10 };
	int healthMax{ 10 };

	olc::v_2d<float> bbPos{};
	olc::v_2d<float> prevPos{};
	olc::v_2d<float> vel{};

	float accelY{};
	SpriteType eType{ SpriteType::Basic };
	Cfg::Textures tex{Cfg::Textures::Count};
	bool bAffectedByGravity{};
	bool bControlledByScript{false};
	bool showBoundingBox{ false };
	AnimDirType animDir{ AnimDirType::NotSet };
	std::vector<Projectile> projectiles{};




public:
	// these will be changed to a heinous animation map from the depths of hell
	sf::IntRect texRect{};
	sf::FloatRect bbox{};
public:
	ASprite() = default;
	virtual ~ASprite() = default;
	ASprite(const ASprite&) = default;
	ASprite& operator=(const ASprite&) = default;
	ASprite(ASprite&&) = default;
	ASprite& operator=(ASprite&&) = default;
	
	inline std::vector<Projectile>& getProjectiles() { return projectiles; }

	void shoot(ProjectileType type_, bool friendly_);


	ASprite(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_ = SpriteType::Basic, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);
	void setup(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_ = SpriteType::Basic,  olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);

	olc::vi2d getActualCollisionPt(olc::vf2d collPt_);

	bool isAffectedByGravity();
	void setAffectedByGravity(bool cond_);
	AnimDirType getAnimDirType();
	void setAnimDirType(AnimDirType type_);
	sf::IntRect getTexRect();
	sf::FloatRect getBBox_local();
	olc::utils::geom2d::rect<float> bbRect();
	olc::utils::geom2d::rect<float> bbPrevRect();
	bool prevOverlapIsY(ASprite& other);
	bool prevOverlapIsX(ASprite& other);

	virtual bool isFacingLeft(); 
	olc::v_2d<float> getPos();
	olc::v_2d<float> getBBCenter();
	olc::v_2d<float> getPrevPos();
	olc::v_2d<float> getNextPos();
	olc::utils::geom2d::rect<float> getBroadRect();
	olc::utils::geom2d::rect<float> getNextRect();

	void setPrevPos(olc::v_2d<float> pos_);
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
	void render();
	void applyExternalForces();
	void tickMovement();

	void setControlledByScript(bool cond_);
	bool isControlledByScript();

	olc::utils::geom2d::ray<float> castRay(OriginPtType oType_, RayDirType dirType, olc::v_2d<float> target = { 0.f,0.f });
	std::unique_ptr<sf::Sprite> getSpr();

	void takeDamage(int dmg);

};

#endif