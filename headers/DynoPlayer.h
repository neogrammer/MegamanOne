#ifndef DYNOPLAYER_H__
#define DYNOPLAYER_H__
#include <DynoSprite.h>
#include <memory>
#include <MachineHandler.h>
#include <duck_fold.h>
#include <assert.h>
#include <algorithm>
#include <string>
#include <Animation.h>
#include <map>


class DynoPlayer : public DynoSprite
{
	Cfg::Textures texCopy;
	olc::vi2d texRecPosCopy;
	std::map<std::pair<std::string, bool>, std::unique_ptr<Animation>> animMap;

	float animElapsed;

public:
	DynoPlayer();
	explicit DynoPlayer(Cfg::Textures tex_, olc::vi2d texRecPos_, olc::vf2d pos);

	virtual ~DynoPlayer() override;
	DynoPlayer(const DynoPlayer&) = default;
	DynoPlayer& operator=(const DynoPlayer&) = default;
	DynoPlayer(DynoPlayer&&) = default;
	DynoPlayer& operator=(DynoPlayer&&) = default;
	void setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_);
	void build(olc::vf2d pos = { 0.f,0.f }) override final;

	DynoPlayer&operator()() override final;

	rec& getRec();

	std::unique_ptr<MachineHandler> fsmHandler{};
	std::string currentAnim{ "idle" };
	bool facingLeft{ false };
	int numAnims{ 0 };
	const Cfg::Textures tex;

	void loadAnimations();
	bool hasBBoxesSet(const std::string& animname, bool facingleft);
	int loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol = 0, int startRow = 0, int pitchColBegin = 0);
	void loadBBoxes();

	sf::IntRect getFrame();
	void resetAnim();
	void render() override;
	void update() override;

};

#endif