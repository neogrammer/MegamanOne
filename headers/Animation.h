#ifndef ANIMATION_H__
#define ANIMATION_H__
#include <vector>
#include <string>
#include <SFML/Graphics/Rect.hpp>
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

	AnimData();
};

struct Animation
{
	AnimData data;
	void addFrame(const sf::IntRect& iRect_);
	void addFrameSheet(const std::string& filename_, const std::string& cfgFile_);


	bool isOnLastFrame();

	int getIndex();
	void animate();
	void resetData();
	void play();
	void stop();
	void pause();
	void resume();

	Animation();

};

#endif
