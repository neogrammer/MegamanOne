#ifndef PLATFORM_H__
#define PLATFORM_H_
#include <ASprite.h>
class Platform : public ASprite
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


	int numAnims{ 0 };
	bool facingLeft{ true };
	std::string currentAnim{ "idle" };
	float pauseElapsed{ 0.f };
	float elapsed{ 0.f };
	bool animPaused{ false };
	int index{ 0 };
	float minY{ 0.f };
	float maxY{ 0.f };
	float minX{ 0.f };
	float maxX{ 0.f };

	void loadAnimations();
	std::vector<sf::IntRect> loadAnimation(int numFrames, int  pitch, int startCol = 0, int startRow = 0, int pitchColBegin = 0);
	void loadBBoxes();
	bool hasBBoxesSet(const std::string& animname, bool facingleft);
	std::map<std::pair<std::string, bool>, AnimData> animMap{};
public:
	float platDisp{ 0.f };
	bool goingUp{ false };
	int id{ 1 };
	Platform() = default;
	Platform(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_);
	~Platform() override = default;

	Platform(const Platform&) = default;
	Platform& operator=(const Platform&) = default;
	Platform(Platform&&) = default;
	Platform& operator=(Platform&&) = default;

	void input();
	void update();

	float getMinY();
	void setMinY(float val_);
	bool isAtTopOfPath();
};

#endif