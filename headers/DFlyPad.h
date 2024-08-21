#ifndef DFLYPAD_H__
#define DFLYPAD_H__
#include <DynoPlat.h>
#include <Animation.h>

class DFlyPad : public DynoPlat
{
	float animElapsed{ 0.f };
	olc::vf2d pathStart{ 0.f,0.f };
	olc::vf2d pathEnd{ 0.f,0.f };
	bool toEnd{ true };
	float speed{ 0.f };
	float currentT{ 0.f };
	float timeToComplete{ 3.0f };

	Animation anim{};
public:
	DFlyPad();
	explicit DFlyPad(olc::vf2d pos_, olc::vf2d pathEnd_, float speed_);

	~DFlyPad();
	DFlyPad(const DFlyPad&) = default;
	DFlyPad& operator=(const DFlyPad&) = default;
	DFlyPad(DFlyPad&&) = default;
	DFlyPad& operator=(DFlyPad&&) = default;

	void build(olc::vf2d pos) override final;
	sf::IntRect getFrame();
	DFlyPad& operator()() override final;

	rec& getRec() override final;
	void render() override final;
	void update() override final;
	void input() override final;
};

#endif