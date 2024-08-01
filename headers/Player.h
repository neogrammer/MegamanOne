#ifndef PLAYER_H__
#define PLAYER_H__
#include <ASprite.h>
#include <Tile.h>
class Platform;
class Player : public ASprite
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

	void loadAnimations();
	std::vector<sf::IntRect> loadAnimation(int numFrames, int  pitch, int startCol = 0, int startRow = 0, int pitchColBegin = 0);
	void loadBBoxes();
	bool hasBBoxesSet(const std::string& animname, bool facingleft);
	std::map<std::pair<std::string, bool>, AnimData> animMap{};
public:
	Player() = default;
	Player(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);
	~Player() override = default;

	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	Player(Player&&) = default;
	Player& operator=(Player&&) = default;

	void input();
	void update();

	void handleMapCollisions(std::vector<Tile>& tiles);

	void handleMapCollisions(std::vector<Platform>& plats_);

	bool isTileBelow(std::vector<Tile>& tiles);
	bool isTileBelow(std::vector<Platform>& plats);
	void setCanJump(bool cond_);
};

#endif