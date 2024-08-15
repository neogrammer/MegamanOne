#include <pch.h>
#include <DynoPlayer.h>
#include <BusterProj.h>
#include <DynoEnemy.h>
#include <DynoPlat.h>
#include <iostream>
DynoPlayer::DynoPlayer()
	: DynoSprite{}, ActionTarget<int>{Cfg::playerInputs}
	, texCopy{ Cfg::Textures::Count }
	, texRecPosCopy{ olc::vi2d{0,0} }
	, tex{ Cfg::Textures::PlayerAtlas }
	, liveBullets{ std::list<std::unique_ptr<SProj>>{} }
	, animElapsed{0.f}
		, jumpSnd{}
		, landSnd{}
		, shootSnd{}
{
	this->currentAnim = "none";
	std::cout << "current state is none"  << std::endl;
}

DynoPlayer::DynoPlayer(Cfg::Textures tex_, olc::vi2d texRecPos_, olc::vf2d pos)
	: DynoSprite{pos}, ActionTarget<int>{Cfg::playerInputs}
	, texCopy{ tex_ }
	, texRecPosCopy{ texRecPos_ }
	, tex { Cfg::Textures::PlayerAtlas }
	, liveBullets{ std::list<std::unique_ptr<SProj>>{} }
	, animElapsed{ 0.f }
		, jumpSnd{}
		, landSnd{}
		, shootSnd{}
{
	build(pos);
	std::cout << "current state is now " << currentAnim << std::endl;
	liveBullets.clear();
	loadAnimations();

	fsmHandler = std::make_unique<MachineHandler>(MachineType::Player);
	fsmHandler->getMachine().setJustChanged(false);
	this->animMap[std::pair(this->currentAnim, this->facingLeft)]->data.index = 0;
	this->animMap[std::pair(this->currentAnim, !this->facingLeft)]->data.index = 0;
	dispatch(fsmHandler->getMachine(), evt_Fell{}, evt_Landed{}, evt_AnimationFinished{});
	currentAnim = fsmHandler->getMachine().getCurrentState();
	fsmHandler->getMachine().setJustChanged(false);
	this->animMap[std::pair(this->currentAnim, this->facingLeft)]->data.index = 0;
	this->animMap[std::pair(this->currentAnim, !this->facingLeft)]->data.index = 0;

	// setup sounds
	jumpSnd.setVolume(45);
	jumpSnd.setBuffer(Cfg::sounds.get((int)Cfg::Sounds::Jump));
	landSnd.setBuffer(Cfg::sounds.get((int)Cfg::Sounds::Land));
	shootSnd.setBuffer(Cfg::sounds.get((int)Cfg::Sounds::BusterShotNormal));

	setupBindings();
}

DynoPlayer::~DynoPlayer()
{

}


void DynoPlayer::setPreBuild(Cfg::Textures texCopy_, olc::vi2d texRecPosCopy_)
{
	texCopy = texCopy_;
	texRecPosCopy = texRecPosCopy_;
}

void DynoPlayer::build(olc::vf2d pos)
{
	pos.x += 300.f;
	pos.y = 600.f;

	auto& r = this->getRec();
	r.set(pos, { 80.f, 83.f }, texCopy, texRecPosCopy, { 130,160 }, { 22,45 }, {0.f,0.f});
	this->animElapsed = 0.f;
}

void DynoPlayer::setupBindings()
{
	bind(Cfg::PlayerInputs::DPadX, [this](const sf::Event& e) {
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > 50.f)
		{
			rightBtnPressed = true;
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < -50.f)
		{
			leftBtnPressed = true;
		}
			

		});

	bind(Cfg::PlayerInputs::AxisX, [this](const sf::Event& e) {
		
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50.f)
		{
			rightBtnPressed = true;
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50.f)
		{
			leftBtnPressed = true;
		}

		});

	bind(Cfg::PlayerInputs::JoyX, [this](const sf::Event& e) {
			shootBtnPressed = true;
		});

	bind(Cfg::PlayerInputs::JoyB, [this](const sf::Event& e) {
			jumpBtnPressed = true;
		});

}

DynoPlayer& DynoPlayer::operator()()
{
	return *dynamic_cast<DynoPlayer*>(this);
}

rec& DynoPlayer::getRec()
{
	return DynoSprite::getRec();
}



void DynoPlayer::loadAnimations()
{

	this->currentAnim = "idle";
	this->facingLeft = false;
	// right animations
	this->animMap.emplace( std::pair{"idle", false} , std::make_unique<Animation>());
	this->animMap[std::pair("idle", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("idle", false)]->data.frames, 3, 3, 0, 1, 0);
	this->animMap[std::pair("idle", false)]->data.animDelay = 0.3f;
	this->animMap[std::pair("idle", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("idle", false)]->data.looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "idle", true }, std::make_unique<Animation>());
	this->animMap[std::pair("idle", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("idle", true)]->data.frames, 3, 3, 0, 14, 0);
	this->animMap[std::pair("idle", true)]->data.animDelay = 0.3f;
	this->animMap[std::pair("idle", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("idle", true)]->data.looping = true;

	this->animMap.emplace(std::pair{ "falling", false }, std::make_unique<Animation>());
	this->animMap[std::pair("falling", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("falling", false)]->data.frames, 3, 3, 0, 5, 9);
	this->animMap[std::pair("falling", false)]->data.animDelay = 0.1f;
	this->animMap[std::pair("falling", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("falling", false)]->data.looping = false;

	// left animations
	this->animMap.emplace(std::pair{ "falling", true }, std::make_unique<Animation>());
	this->animMap[std::pair("falling", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("falling", true)]->data.frames, 3, 3, 0, 18, 9);
	this->animMap[std::pair("falling", true)]->data.animDelay = 0.1f;
	this->animMap[std::pair("falling", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("falling", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "landing", false }, std::make_unique<Animation>());
	this->animMap[std::pair("landing", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("landing", false)]->data.frames, 1, 1, 0, 5, 14);
	this->animMap[std::pair("landing", false)]->data.animDelay = 0.01f;
	this->animMap[std::pair("landing", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("landing", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "landing", true }, std::make_unique<Animation>());
	this->animMap[std::pair("landing", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("landing", true)]->data.frames, 1, 1, 0, 18, 14);
	this->animMap[std::pair("landing", true)]->data.animDelay = 0.01f;
	this->animMap[std::pair("landing", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("landing", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "startingRun", false }, std::make_unique<Animation>());
	this->animMap[std::pair("startingRun", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("startingRun", false)]->data.frames, 2, 2, 0, 2, 0);
	this->animMap[std::pair("startingRun", false)]->data.animDelay = 0.01f;
	this->animMap[std::pair("startingRun", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("startingRun", false)]->data.looping = false;
	// left anim->dataations
	this->animMap.emplace(std::pair{ "startingRun", true }, std::make_unique<Animation>());
	this->animMap[std::pair("startingRun", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("startingRun", true)]->data.frames, 2, 2, 0, 15, 0);
	this->animMap[std::pair("startingRun", true)]->data.animDelay = 0.01f;
	this->animMap[std::pair("startingRun", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("startingRun", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "running", false }, std::make_unique<Animation>());
	this->animMap[std::pair("running", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("running", false)]->data.frames, 10, 10, 0, 2, 3);
	this->animMap[std::pair("running", false)]->data.animDelay = 0.05f;
	this->animMap[std::pair("running", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("running", false)]->data.looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "running", true }, std::make_unique<Animation>());
	this->animMap[std::pair("running", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("running", true)]->data.frames, 10, 10, 0, 15, 3);
	this->animMap[std::pair("running", true)]->data.animDelay = 0.05f;
	this->animMap[std::pair("running", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("running", true)]->data.looping = true;

	this->animMap.emplace(std::pair{ "jumping", false }, std::make_unique<Animation>());
	this->animMap[std::pair("jumping", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("jumping", false)]->data.frames, 4, 4, 0, 5, 0);
	this->animMap[std::pair("jumping", false)]->data.animDelay = 0.01f;
	this->animMap[std::pair("jumping", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("jumping", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "jumping", true }, std::make_unique<Animation>());
	this->animMap[std::pair("jumping", true)]->data. numFrames = loadAnimation(this->animMap[std::pair("jumping", true)]->data.frames, 4, 4, 0, 18, 0);
	this->animMap[std::pair("jumping", true)]->data. animDelay = 0.01f;
	this->animMap[std::pair("jumping", true)]->data. pauseDelay = 0.f;
	this->animMap[std::pair("jumping", true)]->data. looping = false;

	this->animMap.emplace(std::pair{ "peakingJump", false }, std::make_unique<Animation>());
	this->animMap[std::pair("peakingJump", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("peakingJump", false)]->data.frames, 1, 1, 0, 5, 5);
	this->animMap[std::pair("peakingJump", false)]->data.animDelay = 0.01f;
	this->animMap[std::pair("peakingJump", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("peakingJump", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "peakingJump", true }, std::make_unique<Animation>());
	this->animMap[std::pair("peakingJump", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("peakingJump", true)]->data.frames, 1, 1, 0, 18, 5);
	this->animMap[std::pair("peakingJump", true)]->data.animDelay = 0.01f;
	this->animMap[std::pair("peakingJump", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("peakingJump", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "brandishing", false }, std::make_unique<Animation>());
	this->animMap[std::pair("brandishing", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("brandishing", false)]->data.frames, 3, 3, 0, 1, 8);
	this->animMap[std::pair("brandishing", false)]->data.animDelay = 0.01f;
	this->animMap[std::pair("brandishing", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("brandishing", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "brandishing", true }, std::make_unique<Animation>());
	this->animMap[std::pair("brandishing", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("brandishing", true)]->data.frames, 3, 3, 0, 14, 8);
	this->animMap[std::pair("brandishing", true)]->data.animDelay = 0.01f;
	this->animMap[std::pair("brandishing", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("brandishing", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "shooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("shooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("shooting", false)]->data.frames, 1, 1, 0, 1, 12);
	this->animMap[std::pair("shooting", false)]->data.animDelay = 0.05f;
	this->animMap[std::pair("shooting", false)]->data.pauseDelay = 1.f;
	this->animMap[std::pair("shooting", false)]->data.looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "shooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("shooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("shooting", true)]->data.frames, 1, 1, 0, 14, 12);
	this->animMap[std::pair("shooting", true)]->data.animDelay = 0.05f;
	this->animMap[std::pair("shooting", true)]->data.pauseDelay = 1.f;
	this->animMap[std::pair("shooting", true)]->data.looping = true;

	this->animMap.emplace(std::pair{ "startRunAndShooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("startRunAndShooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("startRunAndShooting", false)]->data.frames, 2, 2, 0, 3, 0);
	this->animMap[std::pair("startRunAndShooting", false)]->data.animDelay = 0.05f;
	this->animMap[std::pair("startRunAndShooting", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("startRunAndShooting", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "startRunAndShooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("startRunAndShooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("startRunAndShooting", true)]->data.frames, 2, 2, 0, 16, 0);
	this->animMap[std::pair("startRunAndShooting", true)]->data.animDelay = 0.05f;
	this->animMap[std::pair("startRunAndShooting", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("startRunAndShooting", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "runningAndShooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("runningAndShooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("runningAndShooting", false)]->data.frames, 10, 10, 0, 3, 3);
	this->animMap[std::pair("runningAndShooting", false)]->data.animDelay = 0.05f;
	this->animMap[std::pair("runningAndShooting", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("runningAndShooting", false)]->data.looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "runningAndShooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("runningAndShooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("runningAndShooting", true)]->data.frames, 10, 10, 0, 16, 3);
	this->animMap[std::pair("runningAndShooting", true)]->data.animDelay = 0.05f;
	this->animMap[std::pair("runningAndShooting", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("runningAndShooting", true)]->data.looping = true;


	this->animMap.emplace(std::pair{ "jumpingAndShooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("jumpingAndShooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("jumpingAndShooting", false)]->data.frames, 4, 4, 0, 6, 0);
	this->animMap[std::pair("jumpingAndShooting", false)]->data.animDelay = 0.16f;
	this->animMap[std::pair("jumpingAndShooting", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("jumpingAndShooting", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "jumpingAndShooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("jumpingAndShooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("jumpingAndShooting", true)]->data.frames, 4, 4, 0, 19, 0);
	this->animMap[std::pair("jumpingAndShooting", true)]->data.animDelay = 0.16f;
	this->animMap[std::pair("jumpingAndShooting", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("jumpingAndShooting", true)]->data.looping = false;


	this->animMap.emplace(std::pair{ "jumpPeakShooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("jumpPeakShooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("jumpPeakShooting", false)]->data.frames, 1, 1, 0, 6, 5);
	this->animMap[std::pair("jumpPeakShooting", false)]->data.animDelay = 0.16f;
	this->animMap[std::pair("jumpPeakShooting", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("jumpPeakShooting", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "jumpPeakShooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("jumpPeakShooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("jumpPeakShooting", true)]->data.frames, 1, 1, 0, 19, 5);
	this->animMap[std::pair("jumpPeakShooting", true)]->data.animDelay = 0.16f;
	this->animMap[std::pair("jumpPeakShooting", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("jumpPeakShooting", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "fallingAndShooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("fallingAndShooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("fallingAndShooting", false)]->data.frames, 3, 3, 0, 6, 9);
	this->animMap[std::pair("fallingAndShooting", false)]->data.animDelay = 0.16f;
	this->animMap[std::pair("fallingAndShooting", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("fallingAndShooting", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "fallingAndShooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("fallingAndShooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("fallingAndShooting", true)]->data.frames, 3, 3, 0, 19, 9);
	this->animMap[std::pair("fallingAndShooting", true)]->data.animDelay = 0.16f;
	this->animMap[std::pair("fallingAndShooting", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("fallingAndShooting", true)]->data.looping = false;

	this->animMap.emplace(std::pair{ "landingAndShooting", false }, std::make_unique<Animation>());
	this->animMap[std::pair("landingAndShooting", false)]->data.numFrames = loadAnimation(this->animMap[std::pair("landingAndShooting", false)]->data.frames, 1, 1, 0, 6, 14);
	this->animMap[std::pair("landingAndShooting", false)]->data.animDelay = 0.05f;
	this->animMap[std::pair("landingAndShooting", false)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("landingAndShooting", false)]->data.looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "landingAndShooting", true }, std::make_unique<Animation>());
	this->animMap[std::pair("landingAndShooting", true)]->data.numFrames = loadAnimation(this->animMap[std::pair("landingAndShooting", true)]->data.frames, 1, 1, 0, 19, 14);
	this->animMap[std::pair("landingAndShooting", true)]->data.animDelay = 0.05f;
	this->animMap[std::pair("landingAndShooting", true)]->data.pauseDelay = 0.f;
	this->animMap[std::pair("landingAndShooting", true)]->data.looping = false;

	this->loadBBoxes();

	this->currentAnim = "falling";
	this->facingLeft = false;

}

int DynoPlayer::loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol, int startRow, int pitchColBegin)
{
	sf::IntRect texRect = { {0,0},{130,160} };

	int colsFirst = pitch - startCol;
	float rowsAfter = ((float)numFrames - (float)colsFirst) / (float)pitch;
	int rowsBetween = static_cast<int>(rowsAfter);
	int colsLast = static_cast<int>(round((rowsAfter * (float)pitch) / texRect.getSize().x));


	if (correctVec.size() > 0)
	{
		std::cout << "frames already exist in structure you are about to wipe, check that" << std::endl;
		throw std::runtime_error("IntRect vector in animation already loaded bout to wipe");
	}

	correctVec.clear();
	correctVec.reserve(numFrames);
	int numFramesCreated = 0;
	// first row
	for (int x = pitchColBegin; x < pitchColBegin + colsFirst; x++)
	{
		correctVec.emplace_back(sf::IntRect{ {x * (int)texRect.getSize().x, startRow * (int)texRect.getSize().y},{(int)texRect.getSize().x,(int)texRect.getSize().y} });
		numFramesCreated++;
	}
	//  middle full rows
	for (int y = 1; y < rowsBetween; y++)
	{
		for (int x = pitchColBegin; x < pitch; x++)
		{
			correctVec.emplace_back(sf::IntRect{ {x * (int)texRect.getSize().x, (startRow + y) * (int)texRect.getSize().y},{(int)texRect.getSize().x,(int)texRect.getSize().y} });
		}
	}
	// final partial row
	for (int x = pitchColBegin; x < colsLast; x++)
	{
		correctVec.emplace_back(sf::IntRect{ {x * (int)texRect.getSize().x, (startRow + rowsBetween + 1) * (int)texRect.getSize().y },{ (int)texRect.getSize().x,(int)texRect.getSize().y} });
	}
	//handled like a pimp
	this->numAnims++;

	if (numFrames != numFramesCreated)
	{
		std::cout << "frames created do not match the number of frames that were passed into the loadAnimation function" << std::endl;
		throw std::runtime_error("Check frames");
	}

	return numFramesCreated;
}

void DynoPlayer::loadBBoxes()
{
	std::ifstream file;
	file.open("assets/data/bboxes/player/player.bbox");
	if (!file.is_open() || !file.good()) { throw std::runtime_error("File opened for loadin bboxes is no bueno!"); }
	int numberOfFrames;

	while (file >> numberOfFrames) // any more left in the file to read?
	{
		std::string animname{}, facingleft{};
		file >> animname >> facingleft;
		bool left = ((facingleft == "left") ? true : false);

		if (this->animMap[std::pair(animname, left)]->data.numFrames == this->animMap[std::pair(animname, left)]->data.bboxes.size() && this->animMap[std::pair(animname, left)]->data.bboxes.size() > (size_t)0)
		{
			std::cout << "animMap : " << animname << " , " << facingleft << " bboxes already has a size equal to the amount of frames you are about to clear and reserve, this must be an oversight, check your .bbox file" << std::endl;
			throw std::runtime_error("Check bboxes");
		}

		this->animMap[std::pair(animname, left)]->data.bboxes.clear();
		this->animMap[std::pair(animname, left)]->data.bboxes.reserve(numberOfFrames);
		for (int i = 0; i < numberOfFrames; i++)
		{
			int l{}, t{}, w{}, h{};
			file >> l >> t >> w >> h;
			this->animMap[std::pair(animname, left)]->data.bboxes.emplace_back(sf::IntRect{ {l,t},{w,h} });
		}
		if (!hasBBoxesSet(animname, left))
		{
			throw std::runtime_error("BBoxes for " + animname + facingleft + " is not adequate for its corresponding animation!");
		}
	}
	// bounding boxes loaded successfully for all animations depicted in filename

}
sf::IntRect DynoPlayer::getFrame()
{
	auto itr = animMap.find(std::pair(currentAnim, facingLeft));
	if (itr == animMap.end()) return { {0,0},{0,0} };
	return itr->second->data.frames.at(itr->second->data.index);
}
void DynoPlayer::resetAnim()
{
	animMap[std::pair(currentAnim, facingLeft)]->data.index = 0;
    currentAnim = fsmHandler->getMachine().getCurrentState();
    animElapsed = 0.f;
}
void DynoPlayer::render()
{
	
	//phys::sprAnim(this->getRec(), getFrame(), *this);
	gWnd.draw(*phys::sprAnim(getRec(), getFrame(), *this));

	for (auto& b : liveBullets)
	{
		b->render();
	}
	
}

void DynoPlayer::input()
{
	rightBtnPressed = false;
	leftBtnPressed = false;
	jumpBtnPressed = false;
	shootBtnPressed = false;
	sf::Joystick::update();
	ActionTarget<int>::processEvents();



	for (auto& b : liveBullets)
	{
		b->input();
	}

	//input();
			// add keybased updates to playere here
	getRec().vel.x = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || rightBtnPressed)
	{
		
		if (facingLeft == true)
		{
			facingOtherWay = true;
		}
		else
		{
			facingOtherWay = false;
		}

		getRec().vel.x += 300.f;
		if (!facingOtherWay)
		{

			if (currentAnim != "startingRun" && currentAnim != "running" && currentAnim != "runningAndShooting" && currentAnim != "shooting" && currentAnim != "landing" && currentAnim != "peakingJump" && currentAnim != "jumping" && currentAnim != "falling")
			{
				dispatch(fsmHandler->getMachine(), evt_StartedMoving{});

				fsmHandler->getMachine().setJustChanged(false);
				currentAnim = fsmHandler->getMachine().getCurrentState();
				resetAnim();
			}
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || leftBtnPressed)
	{
		if (facingLeft == false)
		{
			facingOtherWay = true;
		}
		else
		{
			facingOtherWay = false;
		}

		getRec().vel.x -= 300.f;
		
		if (!facingOtherWay)
		{
			if (currentAnim != "startingRun" && currentAnim != "running" && currentAnim != "runningAndShooting" && currentAnim != "shooting"  && currentAnim != "landing" && currentAnim != "peakingJump" && currentAnim != "jumping" && currentAnim != "falling")
			{

				dispatch(fsmHandler->getMachine(), evt_StartedMoving{});

				fsmHandler->getMachine().setJustChanged(false);
				currentAnim = fsmHandler->getMachine().getCurrentState();
				resetAnim();
			}

		}
	}
	if (facingOtherWay)
	{
		facingOtherWay = false;

		if (currentAnim != "startingRun" && currentAnim != "running" && currentAnim != "runningAndShooting" && currentAnim != "shooting" && currentAnim != "landing" && currentAnim != "peakingJump" && currentAnim != "jumping" && currentAnim != "falling" && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		{
			
			dispatch(fsmHandler->getMachine(), evt_StartedMoving{});

			fsmHandler->getMachine().setJustChanged(false);
			currentAnim = fsmHandler->getMachine().getCurrentState();
			resetAnim();
		}
	}

	if (getRec().vel.x > 0.f)
	{
		facingLeft = false;
	}
	else if (getRec().vel.x < 0.f)
	{
		facingLeft = true;

	}
	else if (getRec().vel.x == 0.f && currentAnim != "idle" && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))))
	{
		dispatch(fsmHandler->getMachine(), evt_StoppedMoving{});
		if (fsmHandler->getMachine().wasJustChanged())
		{
			fsmHandler->getMachine().setJustChanged(false);
			currentAnim = fsmHandler->getMachine().getCurrentState();
			resetAnim();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || jumpBtnPressed)
	{
		jumpPressed = true;
		if (playerGrounded == true && getRec().vel.y == 0.f)
		{
			
		
			jumpSnd.play();

			dispatch(fsmHandler->getMachine(), evt_Jumped{});
			currentAnim = fsmHandler->getMachine().getCurrentState();
			resetAnim();

			playerGrounded = false;

			if (standingOnAPlatform)
			{
				standingOnAPlatform = false;
				getRec().pos.y += -1208.81f * gTime;
			}
			getRec().vel.y = -1208.81f;
		}
	}
	else
	{
		jumpPressed = false;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !shootBtnPressed)
	{
	
			firstShot = true;

	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || shootBtnPressed)
	{
		shootPressed = true;
		if (liveBullets.size() < 5)
		{
			if (shootElapsed > shootDelay || firstShot == true)
			{
				firstShot = false;
				shootElapsed = 0.f;
				shoot(ProjectileType::BusterBullet, true);
			}
		}
	}
	else
	{
		shootPressed = false;
		if (shootElapsed > shootDelay)
		{
			shootElapsed = 0.f;
			firstShot = true;
		}
	}
}

void DynoPlayer::update()
{
	if (liveBullets.size() < 5)
	{
		shootElapsed += gTime;
	}
	if (shootPressed)
	{
		shootStanceElapsed = 0.f;
		shootStanceHold = true;

		if (currentAnim != "shooting" && currentAnim != "brandishing" && currentAnim != "runningAndShooting")
		{
			dispatch(this->fsmHandler->getMachine(), evt_StartedShooting{});
			currentAnim = this->fsmHandler->getMachine().getCurrentState();
			resetAnim();
		}
	}
	if (shootStanceHold)
	{
		shootStanceElapsed += gTime;
		if (currentAnim == "brandishing" && animMap[std::pair(currentAnim,facingLeft)]->data.onLastFrame)
		{
			dispatch(this->fsmHandler->getMachine(), evt_AnimationFinished{});
			currentAnim = this->fsmHandler->getMachine().getCurrentState();
			resetAnim();
		}
		if (shootStanceElapsed > shootStanceDelay)
		{
			shootStanceElapsed = 0.f;
			shootStanceHold = false;

			dispatch(this->fsmHandler->getMachine(), evt_StoppedShooting{});
			currentAnim = this->fsmHandler->getMachine().getCurrentState();
			resetAnim();

		}

		if ((getRec().vel.x > 0.f || getRec().vel.x < 0.f) && getRec().vel.y == 0.f && currentAnim != "runningAndShooting")
		{
			dispatch(this->fsmHandler->getMachine(), evt_StartedMoving{});
			currentAnim = this->fsmHandler->getMachine().getCurrentState();
			resetAnim();
		}
	}
	
	std::list< std::unique_ptr<SProj> >::iterator iter = liveBullets.begin();
	std::list<  std::unique_ptr<SProj>>::iterator end = liveBullets.end();

	while (iter != end)
	{
		std::unique_ptr<SProj>& pItem = *iter;

		if (pItem->getRec().pos.x < this->getRec().pos.x - 1600 || pItem->getRec().pos.x > this->getRec().pos.x + 1600 || pItem->marked)
		{
			std::cout << "Erasing one bullet, there are " << liveBullets.size() << " left alive" << std::endl;
			iter = liveBullets.erase(iter);
		}
		else
		{
			pItem->update();
			++iter;
		}
	}
	


	
	
	
	
	for (auto& b : liveBullets)
	{
		b->update();
	}

	auto& r = getRec();
	currentAnim = fsmHandler->getMachine().getCurrentState();

	this->animElapsed += gTime;

	if (currentAnim == "landing" || currentAnim == "startingRun" || currentAnim == "peakingJump" || currentAnim == "jumpPeakShooting" || currentAnim == "shootingAndLanding")
	{
		if (animElapsed >= animMap[std::pair(currentAnim, facingLeft)]->data.animDelay)
		{
			animElapsed = 0.f;
			dispatch(fsmHandler->getMachine(),  evt_AnimationFinished{});
			currentAnim = fsmHandler->getMachine().getCurrentState();
			resetAnim();
		}
	}
	if (r.vel.y > 0.f && (currentAnim == "jumping" || currentAnim == "jumpingAndShooting"))
	{
		dispatch(fsmHandler->getMachine(), evt_ReachedJumpPeak{});
		currentAnim = fsmHandler->getMachine().getCurrentState();
		resetAnim();
	}

	if (r.vel.y > 0.f && (currentAnim == "jumpPeakShooting" || currentAnim == "peakingJump"))
	{
		dispatch(fsmHandler->getMachine(), evt_Fell{});
		currentAnim = fsmHandler->getMachine().getCurrentState();
		resetAnim();
	}

	

	if (animElapsed >= animMap[std::pair(currentAnim, facingLeft)]->data.animDelay)
	{
		animElapsed = 0.f;
		animMap[std::pair(currentAnim, facingLeft)]->animate();
	}

	getRec().vel.y += powf(59.8f, 2) * gTime;




}
void DynoPlayer::handleSpriteCollisions(std::vector<std::shared_ptr<DynoEnemy> >& sprites)
{
	// first check bullets	
	for (auto& b : liveBullets)
	{
		for (auto& spr : sprites)
		{

			if (phys::RectVsRect(b->getRec(), spr->getRec()))
			{
				spr->hit(1);
				spr->wasHit = true;
				b->marked = true;
			}
		}
	}

}

void DynoPlayer::handleSpriteCollisions(std::vector<StatTile>& tiles)
{
	// first check bullets	
	for (auto& b : liveBullets)
	{
		for (auto& tile : tiles)
		{
			if (phys::RectVsRect(b->getRec(), tile.getRec()))
			{
				b->marked = true;
			}
		}
	}

	// check collisions
	olc::vf2d cp;
	olc::vi2d cn;
	float ct;

	std::vector<std::pair<int, float> > z;
	for (int i = 0; i < tiles.size(); i++)
	{
		rec target;
		target.set({ tiles[i].getRec().pos.x, tiles[i].getRec().pos.y }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0, 0 }, { 0.f,0.f });
		if (phys::DynamicRectVsRect(getRec(), target, cp, cn, ct, gTime))
		{
			if (cn.y == -1 && getRec().vel.y > 20.f && currentAnim != "running" && currentAnim != "peakingJump" && currentAnim != "jumping" && currentAnim != "idle" && currentAnim != "jumpPeakShooting"
				&& currentAnim != "runningAndShooting")
			{
				dispatch(fsmHandler->getMachine(), evt_Landed{});
				currentAnim = fsmHandler->getMachine().getCurrentState();
				resetAnim();
				playerGrounded = true;
			}
			z.push_back({ i, ct });

		}
	}

	// sort
	std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{
			return a.second < b.second;
		});


	// resolve in correct order
	for (auto j : z)
	{
		rec target;
		target.set({ tiles[j.first].getRec().pos.x, tiles[j.first].getRec().pos.y }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0, 0 }, { 0.f,0.f });
		if (phys::DynamicRectVsRect(getRec(), target, cp, cn, ct, gTime))
		{
			getRec().vel += cn * olc::vf2d{ std::abs(getRec().vel.x), std::abs(getRec().vel.y) } *(1 - ct);
		}
	}

}

void DynoPlayer::handleSpriteCollisions(std::vector<DynoPlat*>& plats)
{
	/*standingOnAPlatform = false;
	platOn = nullptr;
	platVel = { 0.f,0.f };*/

	// check collisions
	olc::vf2d cp;
	olc::vi2d cn;
	float ct;

	std::vector<std::pair<int, float> > z;
	for (int i = 0; i < plats.size(); i++)
	{
	

		rec target;
		target.set({ plats[i]->getRec().pos.x, plats[i]->getRec().pos.y }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0, 0 }, { 0.f,0.f });
		if (phys::DynamicRectVsRect(getRec(), target, cp, cn, ct, gTime))
		{
			if (cn.y == -1 && getRec().vel.y > 20.f && currentAnim != "running" && currentAnim != "peakingJump" && currentAnim != "jumping" && currentAnim != "idle" && currentAnim != "jumpPeakShooting"
				&& currentAnim != "runningAndShooting")
			{
				dispatch(fsmHandler->getMachine(), evt_Landed{});
				currentAnim = fsmHandler->getMachine().getCurrentState();
				resetAnim();
				playerGrounded = true;
				standingOnAPlatform = true;
				platVel = plats[i]->getRec().vel;
				platOn = plats[i];
			}
			z.push_back({ i, ct });

		}
	}

	// sort
	std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{
			return a.second < b.second;
		});


	// resolve in correct order
	for (auto j : z)
	{
		rec target;
		target.set({ plats[j.first]->getRec().pos.x, plats[j.first]->getRec().pos.y }, { 50.f,50.f }, Cfg::Textures::Tileset1, { 9, 3 }, { 50,50 }, { 0, 0 }, { 0.f,0.f });
		if (phys::DynamicRectVsRect(getRec(), target, cp, cn, ct, gTime))
		{
			getRec().vel += cn * olc::vf2d{ std::abs(getRec().vel.x), std::abs(getRec().vel.y) } *(1 - ct);
		}
	}
}

void DynoPlayer::shoot(ProjectileType type_, bool friendly_)
{
	auto& p = getRec().pos;

	switch (type_)
	{
		case ProjectileType::BusterBullet:
		{
			if (currentAnim == "shooting" || currentAnim == "brandishing" || currentAnim == "idle")
				liveBullets.push_back(std::move(std::make_unique<BusterProj>(olc::vf2d{ (facingLeft) ? p.x - getRec().texPosOffset.x + 23 : p.x - getRec().texPosOffset.x + 83 , p.y - getRec().texPosOffset.y + 57 }, facingLeft)));  //{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
			else if (currentAnim == "jumpingAndShooting" || currentAnim == "jumping")
				liveBullets.push_back(std::move(std::make_unique<BusterProj>(olc::vf2d{ (facingLeft) ? p.x - getRec().texPosOffset.x + 20 : p.x - getRec().texPosOffset.x + 87 , p.y - getRec().texPosOffset.y + 53 }, facingLeft)));  //{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
			else if (currentAnim == "fallingAndShooting" || currentAnim == "falling")
				liveBullets.push_back(std::move(std::make_unique<BusterProj>(olc::vf2d{ (facingLeft) ? p.x - getRec().texPosOffset.x + 20 : p.x - getRec().texPosOffset.x + 87 , p.y - getRec().texPosOffset.y + 53 }, facingLeft)));  //{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
			else if (currentAnim == "landingAndShooting" || currentAnim == "landing")
				liveBullets.push_back(std::move(std::make_unique<BusterProj>(olc::vf2d{ (facingLeft) ? p.x - getRec().texPosOffset.x + 23 : p.x - getRec().texPosOffset.x + 83 , p.y - getRec().texPosOffset.y + 57 }, facingLeft)));  //{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
			else if (currentAnim == "runningAndShooting" || currentAnim == "running")
				liveBullets.push_back(std::move(std::make_unique<BusterProj>(olc::vf2d{ (facingLeft) ? p.x - getRec().texPosOffset.x + 5 : p.x - getRec().texPosOffset.x + 95 , p.y - getRec().texPosOffset.y + 53 }, facingLeft)));  //{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
			else if (currentAnim == "jumpPeakShooting" || currentAnim == "peakingJump")
				liveBullets.push_back(std::move(std::make_unique<BusterProj>(olc::vf2d{ (facingLeft) ? p.x - getRec().texPosOffset.x + 20 : p.x - getRec().texPosOffset.x + 87 , p.y - getRec().texPosOffset.y + 53 }, facingLeft)));  //{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
			else
			{
				break;
			}
			shootSnd.play();
		}
			break;
		default:
			break;
	}
}

bool DynoPlayer::hasBBoxesSet(const std::string& animname, bool facingleft)
{
	if (animMap[std::pair(animname, facingleft)]->data.bboxes.size() > 0)
	{
		if (animMap[std::pair(animname, facingleft)]->data.bboxes.size() != animMap[std::pair(animname, facingleft)]->data.numFrames)
		{
			throw std::runtime_error("animation " + animname + (facingleft ? " left " : " right ") + " exists, but does not have enough bboxes for the frames of animation set!");
		}
		else
		{
			return true;
		}
	}

	return false;
}


