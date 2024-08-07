#ifndef ENEMY_H__
#define ENEMY_H__
#include <ASprite.h>
#include <vector>
#include <list>

class Command;
class Projectile;

class Enemy : public ASprite
{
	friend class Snail;
	friend class Stage;
protected:
	struct AnimData2
	{
		int numFrames{ };
		int index{ };
		float animDelay{};
		float pauseDelay{};
		bool playing{ true };
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
	bool facingLeft{ false };
	std::string currentAnim{ "idle" };
	float pauseElapsed{ 0.f };
	float elapsed{ 0.f };
	bool animPaused{ false };
	int index{ 0 };

	std::map<std::pair<std::string, bool>, AnimData2> animMap{};
	std::list<std::unique_ptr<Command>> cmdList{};
public:
	Enemy() = default;
	Enemy(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_ = SpriteType::Basic, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);
	virtual ~Enemy() override = default;
	Enemy(const Enemy&) = default;
	Enemy& operator=(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(Enemy&&) = default;

	void setup(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_ = SpriteType::Basic, olc::v_2d<float> pos_ = { 0.f,0.f }, AnimDirType animDir_ = AnimDirType::Uni, bool bAffectedByGravity_ = false);
	int loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol, int startRow, int pitchColBegin);
	void loadBBoxes(const std::string& filename);
	bool hasBBoxesSet(const std::string& animname, bool facingleft);
	bool isFacingLeft();

	virtual void input() = 0;
	virtual void update() = 0;

	void pushCommand(CmdType cmd_, void* data_);

};


#endif