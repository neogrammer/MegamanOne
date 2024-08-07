#ifndef PLAYER_H__
#define PLAYER_H__
#include <ASprite.h>

#include <memory>
#include <MachineHandler.h>

class Tile;
class Tilemap;
class Platform;
class Projectile;
class Player : public ASprite
{
	std::unique_ptr<MachineHandler> fsmHandler{};

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
		std::vector<sf::IntRect> frames{};
		std::vector<sf::FloatRect> bboxes{};

		bool isOnLastFrame();

		int getIndex();
		void animate();
		void resetData();
		void play();
		void stop();
		void pause();
		void resume();
	};

	float pOffsetX{ 0.f };
	bool landed{ false };
	bool right_down{};
	bool left_down{};
	bool right_pressed{};
	bool left_pressed{};
	bool jump_down{};
	bool jump_pressed{};
	bool canJump{};
	const float MaxSpeed{ 400.f };
	const float JumpForce{ -625.f };
	int numAnims{ 0 };
	bool facingLeft{ false };
	std::string currentAnim{ "idle" };
	float pauseElapsed{ 0.f };
	float elapsed{ 0.f };
	bool animPaused{false};
	int index{ 0 };
	bool onPlatform{ false };
	float platPlayerOffsetX{ 0.f };
	float initialLandedXPlatDisp{ 0.f };



	void loadAnimations();
    int loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol = 0, int startRow = 0, int pitchColBegin = 0);
	void loadBBoxes();
	bool hasBBoxesSet(const std::string& animname, bool facingleft);
	std::map<std::pair<std::string, bool>, AnimData> animMap{};
public:
	bool isFacingLeft() override;
	bool wasFacingLeft{ false };
	int numLiveBullets{ 0 };
	int maxLiveBullets{ 5 };
	bool justShot{ false };
	bool shooting{ false };
	float shootWaitElapsed{0.f};
	float shootAnimHoldElapsed{ 0.f };
	float shootAnimDelay{ 0.15f };
	float shootWaitDelay{ 0.15f };
	bool canShoot{ true };
	bool shootAnimHolding{ false };
	bool jumping{ false };
	bool falling{ false };
	bool riding{ false };
	Player() = default;
	Player(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);
	~Player() override = default;
	bool tmpFlag{ false };
	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	Player(Player&&) = default;
	Player& operator=(Player&&) = default;
	olc::vf2d storedVel{ 0.f,0.f };
	bool mapMoved{ false };
	bool mapMovedLeft{ false };
	bool mapMovedRight{ false };

	
	std::vector<std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> > > resVec{};

	void input(sf::View& gview_);
	void update();

	void handleMapCollisions(std::vector<Tile>& tiles);

	void handleMapCollisions(std::vector<Platform>& plats_);

	bool isTileBelow(std::vector<Tile>& tiles);
	bool isTileBelow(std::vector<Platform>& plats);
	void setCanJump(bool cond_);
};

#endif