#ifndef PROJECTILE_H__
#define PROJECTILE_H__
#include <3rdParty/olcUTIL_Geometry2D.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Cfg.h>
#include <memory>
#include <string>
class Player;
class ASprite;
class Tile;


class Projectile
{
	olc::v_2d<float> pos{};
	float speed{};

	ProjectileType type{ProjectileType::Base};
	TravelDir tDir{ TravelDir::NotSet };

	Cfg::Textures tex{ Cfg::Textures::Count };
	sf::IntRect texRect{};
	sf::IntRect bboxLocal{};

	int damage{ 1 };
	const float maxDistance{ 1600.f };
	float distanceTravelled{ 0.f };

	bool markedForDeletion{ false };

	bool isFriendly{ true };

	float animTimeElapsed{ 0.f };
	float animDelay{ 0.05f };
	int numFrames{ 1 };
	int index{ 0 };

	std::vector<sf::IntRect> frames_{};
	std::vector<sf::IntRect> bboxes_{};


public:
	Projectile() = default;
	virtual ~Projectile() = default;
	Projectile(const Projectile& o);
	Projectile& operator=(const Projectile& o);
	Projectile(Projectile&& o) noexcept;
	Projectile& operator=(Projectile&& o) noexcept;

	Projectile(Cfg::Textures tex_,const std::string& aabbFile, olc::v_2d<float> pos_, float speed_ = 10.f, TravelDir dir_ = TravelDir::Horizontal, ProjectileType type_ = ProjectileType::Base, int damage_ = 1);
	void setup(Cfg::Textures tex_,const  std::string& aabbFile, olc::v_2d<float> pos_, float speed_ = 10.f, TravelDir dir_ = TravelDir::Horizontal, ProjectileType type_ = ProjectileType::Base, int damage_ = 1);

	inline olc::utils::geom2d::rect<float> aabb() {
		return { {pos.x,pos.y},{(float)bboxLocal.width,(float)bboxLocal.height} };
	};

	std::unique_ptr<sf::Sprite> getSpr();

	inline bool isMarkedForDeletion() { return markedForDeletion; }
	inline void setMarkedForDeletion(bool cond_) { markedForDeletion = cond_; }
	void destoryAndDOT(ASprite& aSpr_);
	void destroyAndAOE(ASprite& aSpr_);
	void destroyAndHit(ASprite& aSpr_);
	inline void destroy() { markedForDeletion = true; }

	bool collide(ASprite& aSpr_);

	void updateCheckHandle(Player& player_, std::vector<ASprite*>& sprites_, std::vector<Tile>& tiles_);

	void tickMovement();
	void render();
	void animate();


	void LoadAABB(const std::string& aabbFile);
};

#endif