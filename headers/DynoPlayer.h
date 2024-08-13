#ifndef DYNOPLAYER_H__
#define DYNOPLAYER_H__
#include <DynoSprite.h>
#include <memory>
#include <MachineHandler.h>
#include <duck_fold.h>
#include <assert.h>
#include <algorithm>
#include <string>
#include <StatTile.h>
#include <Animation.h>
#include <ActionTarget.h>
#include <list>

#include <map>
class SProj;
class DynoPlat;
class DynoPlayer : public DynoSprite, public ActionTarget<int>
{
	Cfg::Textures texCopy;
	olc::vi2d texRecPosCopy;
	std::map<std::pair<std::string, bool>, std::unique_ptr<Animation>> animMap;

	std::list<std::unique_ptr<SProj> > liveBullets;


	float animElapsed;

	bool rightBtnPressed{ false };
	bool leftBtnPressed{ false };
	bool jumpBtnPressed{ false };
	bool shootBtnPressed{ false };



public:
	DynoPlayer();
	explicit DynoPlayer(Cfg::Textures tex_, olc::vi2d texRecPos_, olc::vf2d pos);

	virtual ~DynoPlayer() override;
	DynoPlayer(const DynoPlayer&) = default;
	DynoPlayer& operator=(const DynoPlayer&) = default;
	DynoPlayer(DynoPlayer&&) = default;
	DynoPlayer& operator=(DynoPlayer&&) = default;
	void setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_);
	void build(olc::vf2d pos) override final;
	void setupBindings();
	DynoPlayer&operator()() override final;

	rec& getRec() override final;

	std::unique_ptr<MachineHandler> fsmHandler{};
	std::string currentAnim{ "idle" };
	bool facingLeft{ false };
	bool facingOtherWay{ false };
	int numAnims{ 0 };
	const Cfg::Textures tex;
	bool playerGrounded{ true };
	bool jumpPressed{ false };
	bool shootPressed{ false };
	bool shootStanceHold{ false };
	float shootStanceDelay = 0.2f;
	float shootStanceElapsed = 0.f;
	bool standingOnAPlatform{ false };
	olc::vf2d platVel{ 0.0f, 0.f };
	DynoPlat* platOn{ nullptr };
	float shootElapsed{ 0.f };
	float shootDelay{ 0.15f };

	//std::vector<Projectile> projectiles{};
	/*int numLiveBullets{ 0 };
	int maxLiveBullets{ 5 };
	bool justShot{ false };
	bool shooting{ false };
	float shootWaitElapsed{ 0.f };
	float shootAnimHoldElapsed{ 0.f };
	float shootAnimDelay{ 0.15f };
	float shootWaitDelay{ 0.15f };
	bool canShoot{ true };
	bool shootAnimHolding{ false };*/

	void loadAnimations();
	bool hasBBoxesSet(const std::string& animname, bool facingleft);
	int loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol = 0, int startRow = 0, int pitchColBegin = 0);
	void loadBBoxes();

	sf::IntRect getFrame();
	void resetAnim();
	void input() override;
	void render() override;
	void update() override;
	void handleSpriteCollisions(std::vector<StatTile>& tiles);
	void handleSpriteCollisions(std::vector<DynoPlat*>& plats);

	void handleSpriteCollisions(std::vector<std::shared_ptr<BaseSprite> >& sprites);
   inline std::list<std::unique_ptr<SProj> >& getProjectiles() { return liveBullets; }
  	void shoot(ProjectileType type_, bool friendly_);
};

#endif