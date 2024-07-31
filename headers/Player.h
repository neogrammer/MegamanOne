#ifndef PLAYER_H__
#define PLAYER_H__
#include <ASprite.h>
class Player : public ASprite
{
	bool right_down{};
	bool left_down{};
	bool right_pressed{};
	bool left_pressed{};
	bool jump_down{};
	bool jump_pressed{};
	bool canJump{};
	const float MaxSpeed{ 400.f };
	const float JumpForce{ -600.f };

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
	void handleMapCollisions(std::vector<ASprite>& tiles);
	bool isTileBelow(std::vector<ASprite>& tiles);
};

#endif