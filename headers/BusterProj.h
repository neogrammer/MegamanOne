#ifndef BUSTERPROJ_H__
#define BUSTERPROJ_H__
#include <SProj.h>
#include <string>
class BusterProj : public SProj
{
	std::string dirStr{ "" };
public:
	BusterProj();
	BusterProj(olc::vf2d pos_ , bool rightDir_);

	~BusterProj() override final;
	BusterProj& operator()() override final;
	void build(olc::vf2d pos_) override final;
	rec& getRec() override final;
	void update() override final;
	void render() override final;
	void input() override final;
};
#endif