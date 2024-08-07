#include <pch.h>
#include <Player.h>
#include <Physics.h>
#include <Platform.h>
#include <duck_fold.h>
#include <assert.h>
#include <algorithm>
#include <Tilemap.h>
#include <Projectile.h>
#include <Tile.h>
#include <Projectile.h>

using namespace olc::utils::geom2d;

void Player::loadAnimations()
{

	this->currentAnim = "idle";
	this->facingLeft = false;
	// right animations
	this->animMap.emplace(std::pair{ "idle", false }, AnimData{});
	this->animMap[std::pair("idle", false)].numFrames = loadAnimation(this->animMap[std::pair("idle", false)].frames, 3, 3, 0, 1, 0);
	this->animMap[std::pair("idle", false)].animDelay = 0.3f;
	this->animMap[std::pair("idle", false)].pauseDelay = 0.f;
	// left animations
	this->animMap.emplace(std::pair{ "idle", true }, AnimData{});
	this->animMap[std::pair("idle", true)].numFrames = loadAnimation(this->animMap[std::pair("idle", true)].frames, 3, 3, 0, 14, 0);
	this->animMap[std::pair("idle", true)].animDelay = 0.3f;
	this->animMap[std::pair("idle", true)].pauseDelay = 0.f;
	
	this->animMap.emplace(std::pair{ "falling", false }, AnimData{});
	this->animMap[std::pair("falling", false)].numFrames = loadAnimation(this->animMap[std::pair("falling", false)].frames, 3, 3, 0, 5, 9);
	this->animMap[std::pair("falling", false)].animDelay = 0.1f;
	this->animMap[std::pair("falling", false)].pauseDelay = 0.f;
	this->animMap[std::pair("falling", false)].looping = false;

	// left animations
	this->animMap.emplace(std::pair{ "falling", true }, AnimData{});
	this->animMap[std::pair("falling", true)].numFrames = loadAnimation(this->animMap[std::pair("falling", true)].frames, 3, 3, 0, 18, 9);
	this->animMap[std::pair("falling", true)].animDelay = 0.1f;
	this->animMap[std::pair("falling", true)].pauseDelay = 0.f;
	this->animMap[std::pair("falling", true)].looping = false;

	this->animMap.emplace(std::pair{ "landing", false }, AnimData{});
	this->animMap[std::pair("landing", false)].numFrames = loadAnimation(this->animMap[std::pair("landing", false)].frames, 1, 1, 0, 5, 14);
	this->animMap[std::pair("landing", false)].animDelay = 0.05f;
	this->animMap[std::pair("landing", false)].pauseDelay = 0.f;
	this->animMap[std::pair("landing", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "landing", true }, AnimData{});
	this->animMap[std::pair("landing", true)].numFrames = loadAnimation(this->animMap[std::pair("landing", true)].frames, 1, 1, 0, 18, 14);
	this->animMap[std::pair("landing", true)].animDelay = 0.05f;
	this->animMap[std::pair("landing", true)].pauseDelay = 0.f;
	this->animMap[std::pair("landing", true)].looping = false;

	this->animMap.emplace(std::pair{ "startingRun", false }, AnimData{});
	this->animMap[std::pair("startingRun", false)].numFrames = loadAnimation(this->animMap[std::pair("startingRun", false)].frames, 2, 2, 0, 2, 0);
	this->animMap[std::pair("startingRun", false)].animDelay = 0.05f;
	this->animMap[std::pair("startingRun", false)].pauseDelay = 0.f;
	this->animMap[std::pair("startingRun", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "startingRun", true }, AnimData{});
	this->animMap[std::pair("startingRun", true)].numFrames = loadAnimation(this->animMap[std::pair("startingRun", true)].frames, 2, 2, 0, 15, 0);
	this->animMap[std::pair("startingRun", true)].animDelay = 0.05f;
	this->animMap[std::pair("startingRun", true)].pauseDelay = 0.f;
	this->animMap[std::pair("startingRun", true)].looping = false;

	this->animMap.emplace(std::pair{ "running", false }, AnimData{});
	this->animMap[std::pair("running", false)].numFrames = loadAnimation(this->animMap[std::pair("running", false)].frames, 10, 10, 0, 2, 3);
	this->animMap[std::pair("running", false)].animDelay = 0.05f;
	this->animMap[std::pair("running", false)].pauseDelay = 0.f;
	this->animMap[std::pair("running", false)].looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "running", true }, AnimData{});
	this->animMap[std::pair("running", true)].numFrames = loadAnimation(this->animMap[std::pair("running", true)].frames, 10, 10, 0, 15, 3);
	this->animMap[std::pair("running", true)].animDelay = 0.05f;
	this->animMap[std::pair("running", true)].pauseDelay = 0.f;
	this->animMap[std::pair("running", true)].looping = true;

	this->animMap.emplace(std::pair{ "jumping", false }, AnimData{});
	this->animMap[std::pair("jumping", false)].numFrames = loadAnimation(this->animMap[std::pair("jumping", false)].frames, 4, 4, 0, 5, 0);
	this->animMap[std::pair("jumping", false)].animDelay = 0.16f;
	this->animMap[std::pair("jumping", false)].pauseDelay = 0.f;
	this->animMap[std::pair("jumping", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "jumping", true }, AnimData{});
	this->animMap[std::pair("jumping", true)].numFrames = loadAnimation(this->animMap[std::pair("jumping", true)].frames, 4, 4, 0, 18, 0);
	this->animMap[std::pair("jumping", true)].animDelay = 0.16f;
	this->animMap[std::pair("jumping", true)].pauseDelay = 0.f;
	this->animMap[std::pair("jumping", true)].looping = false;

	this->animMap.emplace(std::pair{ "peakingJump", false }, AnimData{});
	this->animMap[std::pair("peakingJump", false)].numFrames = loadAnimation(this->animMap[std::pair("peakingJump", false)].frames, 1, 1, 0, 5, 5);
	this->animMap[std::pair("peakingJump", false)].animDelay = 0.3f;
	this->animMap[std::pair("peakingJump", false)].pauseDelay = 0.f;
	this->animMap[std::pair("peakingJump", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "peakingJump", true }, AnimData{});
	this->animMap[std::pair("peakingJump", true)].numFrames = loadAnimation(this->animMap[std::pair("peakingJump", true)].frames, 1, 1, 0, 18, 5);
	this->animMap[std::pair("peakingJump", true)].animDelay = 0.3f;
	this->animMap[std::pair("peakingJump", true)].pauseDelay = 0.f;
	this->animMap[std::pair("peakingJump", true)].looping = false;

	this->animMap.emplace(std::pair{ "brandishing", false }, AnimData{});
	this->animMap[std::pair("brandishing", false)].numFrames = loadAnimation(this->animMap[std::pair("brandishing", false)].frames, 3, 3, 0, 1, 8);
	this->animMap[std::pair("brandishing", false)].animDelay = 0.05f;
	this->animMap[std::pair("brandishing", false)].pauseDelay = 0.f;
	this->animMap[std::pair("brandishing", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "brandishing", true }, AnimData{});
	this->animMap[std::pair("brandishing", true)].numFrames = loadAnimation(this->animMap[std::pair("brandishing", true)].frames, 3, 3, 0, 14, 8);
	this->animMap[std::pair("brandishing", true)].animDelay = 0.05f;
	this->animMap[std::pair("brandishing", true)].pauseDelay = 0.f;
	this->animMap[std::pair("brandishing", true)].looping = false;

	this->animMap.emplace(std::pair{ "shooting", false }, AnimData{});
	this->animMap[std::pair("shooting", false)].numFrames = loadAnimation(this->animMap[std::pair("shooting", false)].frames, 1, 1, 0, 1, 12);
	this->animMap[std::pair("shooting", false)].animDelay = 0.05f;
	this->animMap[std::pair("shooting", false)].pauseDelay = 1.f;
	this->animMap[std::pair("shooting", false)].looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "shooting", true }, AnimData{});
	this->animMap[std::pair("shooting", true)].numFrames = loadAnimation(this->animMap[std::pair("shooting", true)].frames, 1, 1, 0, 14, 12);
	this->animMap[std::pair("shooting", true)].animDelay = 0.05f;
	this->animMap[std::pair("shooting", true)].pauseDelay = 1.f;
	this->animMap[std::pair("shooting", true)].looping = true;

	this->animMap.emplace(std::pair{ "startRunAndShooting", false }, AnimData{});
	this->animMap[std::pair("startRunAndShooting", false)].numFrames = loadAnimation(this->animMap[std::pair("startRunAndShooting", false)].frames, 2, 2, 0, 3, 0);
	this->animMap[std::pair("startRunAndShooting", false)].animDelay = 0.05f;
	this->animMap[std::pair("startRunAndShooting", false)].pauseDelay = 0.f;
	this->animMap[std::pair("startRunAndShooting", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "startRunAndShooting", true }, AnimData{});
	this->animMap[std::pair("startRunAndShooting", true)].numFrames = loadAnimation(this->animMap[std::pair("startRunAndShooting", true)].frames, 2, 2, 0, 16, 0);
	this->animMap[std::pair("startRunAndShooting", true)].animDelay = 0.05f;
	this->animMap[std::pair("startRunAndShooting", true)].pauseDelay = 0.f;
	this->animMap[std::pair("startRunAndShooting", true)].looping = false;

	this->animMap.emplace(std::pair{ "runningAndShooting", false }, AnimData{});
	this->animMap[std::pair("runningAndShooting", false)].numFrames = loadAnimation(this->animMap[std::pair("runningAndShooting", false)].frames, 10, 10, 0, 3, 3);
	this->animMap[std::pair("runningAndShooting", false)].animDelay = 0.05f;
	this->animMap[std::pair("runningAndShooting", false)].pauseDelay = 0.f;
	this->animMap[std::pair("runningAndShooting", false)].looping = true;
	// left animations
	this->animMap.emplace(std::pair{ "runningAndShooting", true }, AnimData{});
	this->animMap[std::pair("runningAndShooting", true)].numFrames = loadAnimation(this->animMap[std::pair("runningAndShooting", true)].frames, 10, 10, 0, 16, 3);
	this->animMap[std::pair("runningAndShooting", true)].animDelay = 0.05f;
	this->animMap[std::pair("runningAndShooting", true)].pauseDelay = 0.f;
	this->animMap[std::pair("runningAndShooting", true)].looping = true;


	this->animMap.emplace(std::pair{ "jumpingAndShooting", false }, AnimData{});
	this->animMap[std::pair("jumpingAndShooting", false)].numFrames = loadAnimation(this->animMap[std::pair("jumpingAndShooting", false)].frames, 4, 4, 0, 6, 0);
	this->animMap[std::pair("jumpingAndShooting", false)].animDelay = 0.16f;
	this->animMap[std::pair("jumpingAndShooting", false)].pauseDelay = 0.f;
	this->animMap[std::pair("jumpingAndShooting", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "jumpingAndShooting", true }, AnimData{});
	this->animMap[std::pair("jumpingAndShooting", true)].numFrames = loadAnimation(this->animMap[std::pair("jumpingAndShooting", true)].frames, 4, 4, 0, 19, 0);
	this->animMap[std::pair("jumpingAndShooting", true)].animDelay = 0.16f;
	this->animMap[std::pair("jumpingAndShooting", true)].pauseDelay = 0.f;
	this->animMap[std::pair("jumpingAndShooting", true)].looping = false;


	this->animMap.emplace(std::pair{ "jumpPeakShooting", false }, AnimData{});
	this->animMap[std::pair("jumpPeakShooting", false)].numFrames = loadAnimation(this->animMap[std::pair("jumpPeakShooting", false)].frames, 1, 1, 0, 6, 5);
	this->animMap[std::pair("jumpPeakShooting", false)].animDelay = 0.16f;
	this->animMap[std::pair("jumpPeakShooting", false)].pauseDelay = 0.f;
	this->animMap[std::pair("jumpPeakShooting", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "jumpPeakShooting", true }, AnimData{});
	this->animMap[std::pair("jumpPeakShooting", true)].numFrames = loadAnimation(this->animMap[std::pair("jumpPeakShooting", true)].frames, 1, 1, 0, 19, 5);
	this->animMap[std::pair("jumpPeakShooting", true)].animDelay = 0.16f;
	this->animMap[std::pair("jumpPeakShooting", true)].pauseDelay = 0.f;
	this->animMap[std::pair("jumpPeakShooting", true)].looping = false;

	this->animMap.emplace(std::pair{ "fallingAndShooting", false }, AnimData{});
	this->animMap[std::pair("fallingAndShooting", false)].numFrames = loadAnimation(this->animMap[std::pair("fallingAndShooting", false)].frames, 3, 3, 0, 6, 9);
	this->animMap[std::pair("fallingAndShooting", false)].animDelay = 0.16f;
	this->animMap[std::pair("fallingAndShooting", false)].pauseDelay = 0.f;
	this->animMap[std::pair("fallingAndShooting", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "fallingAndShooting", true }, AnimData{});
	this->animMap[std::pair("fallingAndShooting", true)].numFrames = loadAnimation(this->animMap[std::pair("fallingAndShooting", true)].frames, 3, 3, 0, 19, 9);
	this->animMap[std::pair("fallingAndShooting", true)].animDelay = 0.16f;
	this->animMap[std::pair("fallingAndShooting", true)].pauseDelay = 0.f;
	this->animMap[std::pair("fallingAndShooting", true)].looping = false;

	this->animMap.emplace(std::pair{ "landingAndShooting", false }, AnimData{});
	this->animMap[std::pair("landingAndShooting", false)].numFrames = loadAnimation(this->animMap[std::pair("landingAndShooting", false)].frames, 1, 1, 0, 6, 14);
	this->animMap[std::pair("landingAndShooting", false)].animDelay = 0.05f;
	this->animMap[std::pair("landingAndShooting", false)].pauseDelay = 0.f;
	this->animMap[std::pair("landingAndShooting", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "landingAndShooting", true }, AnimData{});
	this->animMap[std::pair("landingAndShooting", true)].numFrames = loadAnimation(this->animMap[std::pair("landingAndShooting", true)].frames, 1, 1, 0, 19, 14);
	this->animMap[std::pair("landingAndShooting", true)].animDelay = 0.05f;
	this->animMap[std::pair("landingAndShooting", true)].pauseDelay = 0.f;
	this->animMap[std::pair("landingAndShooting", true)].looping = false;

	this->loadBBoxes();

	this->currentAnim = "falling";

}

int Player::loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol, int startRow, int pitchColBegin)
{
	int colsFirst = pitch - startCol;
	float rowsAfter = ((float)numFrames - (float)colsFirst) / (float)pitch;
	int rowsBetween = static_cast<int>(rowsAfter);
	int colsLast = static_cast<int>(round((rowsAfter * (float)pitch) / this->texRect.getSize().x));


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

void Player::loadBBoxes()
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

			if (this->animMap[std::pair(animname, left)].numFrames == this->animMap[std::pair(animname, left)].bboxes.size() && this->animMap[std::pair(animname, left)].bboxes.size() > (size_t)0)
			{
				std::cout << "animMap : " << animname << " , " << facingleft << " bboxes already has a size equal to the amount of frames you are about to clear and reserve, this must be an oversight, check your .bbox file" << std::endl;
				throw std::runtime_error("Check bboxes");
			}

			this->animMap[std::pair(animname, left)].bboxes.clear();
			this->animMap[std::pair(animname, left)].bboxes.reserve(numberOfFrames);
			for (int i = 0; i < numberOfFrames; i++)
			{
				int l{}, t{}, w{}, h{};
				file >> l >> t >> w >> h;
				this->animMap[std::pair(animname, left)].bboxes.emplace_back(sf::IntRect{ {l,t},{w,h} });
			}
			if (!hasBBoxesSet(animname, left))
			{
				throw std::runtime_error("BBoxes for " + animname + facingleft + " is not adequate for its corresponding animation!");
			}
		}
		// bounding boxes loaded successfully for all animations depicted in filename

}
bool Player::hasBBoxesSet(const std::string& animname, bool facingleft)
{
	if (animMap[std::pair(animname, facingleft)].bboxes.size() > 0)
	{
		if (animMap[std::pair(animname, facingleft)].bboxes.size() != animMap[std::pair(animname, facingleft)].numFrames)
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

bool Player::isFacingLeft()
{
	return facingLeft;
}

Player::Player(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
	: ASprite{ tex_, texRect_, bbox_, SpriteType::Player, pos_, animDir_, bAffectedByGravity_ }
{
	loadAnimations();

	fsmHandler = std::make_unique<MachineHandler>(MachineType::Player);
	dispatch(fsmHandler->getMachine(), evt_Fell{});

	if (fsmHandler->getMachine().wasJustChanged())
	{
		fsmHandler->getMachine().setJustChanged(false);
		this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
		this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
		currentAnim = fsmHandler->getMachine().getCurrentState();
		this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
		this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
		this->index = 0;
		elapsed = 0.f;
		pauseElapsed = 0.f;
		animPaused = true;
	}

	setPos({800.f + (this->getBBSize().x / 2.f), 0.f});
	
}

void Player::input(sf::View& gview_)
{
	mapMoved = false;
	mapMovedLeft = false;
	mapMovedRight = false;
	wasFacingLeft = facingLeft;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!right_down)
		{
			// first moment of push
			right_pressed = true;
			
		}
		else
		{
			right_pressed = false;
		}

		right_down = true;

		dispatch(this->fsmHandler->getMachine(), evt_StartedMoving{});

		if (fsmHandler->getMachine().wasJustChanged())
		{
			fsmHandler->getMachine().setJustChanged(false);
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			currentAnim = fsmHandler->getMachine().getCurrentState();
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			this->index = 0;
			elapsed = 0.f;
			pauseElapsed = 0.f;
			animPaused = true;
		}

		facingLeft = false;
		if (this->getVelocity().x <= MaxSpeed)
		{

			if (gWnd.mapCoordsToPixel({ this->getPos().x, this->getPos().y }).x >= gWnd.mapPixelToCoords({ 800 + (int)(this->getBBSize().x / 2.f), 0 }).x + this->getVelocity().x * gTime || this->getPos().x + (this->getBBSize().x / 2.f) < 800.f)
			{
				this->setVelocity({ 250.f, this->getVelocity().y });
				storedVel = { 0.f, 0.f };
				mapMoved = false;
			}
			else
			{

				if (gameView.getCenter().x < 2400.f - (this->getBBSize().x / 2.f))
				{
					gview_.move({ 250.f * gTime,0.f });
					mapMoved = true;
					mapMovedLeft = true;
					storedVel = { 250.f, 0.f };
					sf::Vector2f tmp = { this->getPos().x, this->getPos().y };
					sf::Vector2i tmpI = gWnd.mapCoordsToPixel({ this->getPos().x, this->getPos().y });
					sf::Vector2f centerIX = gWnd.mapPixelToCoords({ 800 - (int)((float)this->getBBSize().x / 2.f) ,tmpI.y });
					this->setPos({ centerIX.x, this->getPos().y});
					this->setVelocity({ 0.f, this->getVelocity().y });
				}
				else
				{
					storedVel = { 0.f, 0.f };
					mapMoved = false;

					this->setVelocity({ 250.f, this->getVelocity().y });
				}
			/*	if (gWnd.mapCoordsToPixel(sf::Vector2f{ this->getPos().x, this->getPos().y }).x  > 800.f)
				{
					this->setVelocity({ -250.f, this->getVelocity().y });
				}*/
			/*	if (gameView.getCenter().x < )
				{
					gview_.move({ 250.f * gTime,0.f });
					sf::Vector2f tmp = { this->getPos().x, this->getPos().y };
					sf::Vector2i tmpI = gWnd.mapCoordsToPixel({ this->getPos().x + this->getVelocity().x * gTime, this->getPos().y });
					sf::Vector2f centerIX = gWnd.mapPixelToCoords({ 800 ,tmpI.y });
					this->setPos({ centerIX.x , centerIX.y });

					this->setVelocity({ 0.f, this->getVelocity().y });
				}
				else
				{
					

				}*/
			}

			/*if (gWnd.mapCoordsToPixel({ this->getPos().x, this->getPos().y }).x < gWnd.mapPixelToCoords({ 800, 0 }).x)
			{
				this->setVelocity({ 250.f, this->getVelocity().y });
			}
			else
			{
				gview_.move({250.f * gTime,0.f });
				sf::Vector2f tmp = { this->getPos().x, this->getPos().y };
				sf::Vector2i tmpI = gWnd.mapCoordsToPixel({ this->getPos().x, this->getPos().y });
				sf::Vector2f centerIX = gWnd.mapPixelToCoords({ 800 ,tmpI.y });
				this->setPos({ centerIX.x, centerIX.y });
			}*/

		}
		onPlatform = false;
	}
	else
	{
		right_down = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!left_down)
		{
			// first moment of push
			left_pressed = true;
			
		}
		else
		{
			left_pressed = false;
		}
		left_down = true;


		dispatch(this->fsmHandler->getMachine(), evt_StartedMoving{});

		if (fsmHandler->getMachine().wasJustChanged())
		{
			fsmHandler->getMachine().setJustChanged(false);
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			currentAnim = fsmHandler->getMachine().getCurrentState();
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			this->index = 0;
			elapsed = 0.f;
			pauseElapsed = 0.f;
			animPaused = true;
		}
		facingLeft = true;
		
			if (this->getVelocity().x >= -MaxSpeed)
			{
				
				if (gWnd.mapCoordsToPixel({ this->getPos().x, this->getPos().y }).x > gWnd.mapPixelToCoords({ 800 + (int)(this->getBBSize().x / 2.f) , 0 }).x || this->getPos().x + (this->getBBSize().x / 2.f) > 2400)
				{
					this->setVelocity({ -250.f, this->getVelocity().y });
					storedVel = { 0.f,0.f };
					mapMoved = false;
				}
				else
				{
					if (gameView.getCenter().x > 800.f + (this->getBBSize().x / 2.f))
					{
						storedVel = { -250.f, 0.f };
						gview_.move({ -250.f * gTime,0.f });
						mapMoved = true;
						mapMovedRight = true;
						sf::Vector2f tmp = { this->getPos().x, this->getPos().y };
						sf::Vector2i tmpI = gWnd.mapCoordsToPixel({ this->getPos().x, this->getPos().y });
						sf::Vector2f centerIX = gWnd.mapPixelToCoords({ 800 - (int)((float)this->getBBSize().x / 2.f) ,tmpI.y });
						this->setPos({ centerIX.x, this->getPos().y });
						this->setVelocity({ 0.f, this->getVelocity().y });
					}
					else
					{
						storedVel = { 0.f,0.f };
						this->setVelocity({ -250.f, this->getVelocity().y });
						mapMoved = false;
					}
				}

				//nowFacingLeft
			}
			onPlatform = false;
	}
	else
	{
		left_down = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!jump_down && canJump)
		{
			// first moment of push
			jump_pressed = true;
			canJump = false;
			onPlatform = false;
			setVelocity({ getVelocity().x, JumpForce });
			this->setAffectedByGravity(true);
			this->tickMovement();
			dispatch(fsmHandler->getMachine(), evt_Jumped{});

			if (fsmHandler->getMachine().wasJustChanged())
			{
				snd::Play("jump");

				
				fsmHandler->getMachine().setJustChanged(false);
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				currentAnim = fsmHandler->getMachine().getCurrentState();
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				this->index = 0;
				elapsed = 0.f;
				pauseElapsed = 0.f;
				animPaused = true;
			}
			jumping = true;
			falling = false;
		}
		else
		{
			jump_pressed = false;
		}
		jump_down = true;
		
	}
	else
	{
		jump_down = false;
	}

	if (left_down == false && right_down == false)
	{
		setVelocity({ 0.f, getVelocity().y });
		dispatch(this->fsmHandler->getMachine(), evt_StoppedMoving{});

		if (fsmHandler->getMachine().wasJustChanged())
		{
			fsmHandler->getMachine().setJustChanged(false);
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			currentAnim = fsmHandler->getMachine().getCurrentState();
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			this->index = 0;
			elapsed = 0.f;
			pauseElapsed = 0.f;
			animPaused = true;
		}
	}

	if (shooting || justShot)
	{
		shootWaitElapsed += gTime;
		if (shootWaitElapsed >= shootWaitDelay)
		{
			shooting = false;
		}
	}
	if (!shooting)
	{
		if (!shootAnimHolding)
		{
			canShoot = true;
		}
	}

	if (!shootAnimHolding)
	{
		dispatch(this->fsmHandler->getMachine(), evt_StoppedShooting{});

		if (fsmHandler->getMachine().wasJustChanged())
		{
			fsmHandler->getMachine().setJustChanged(false);
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			currentAnim = fsmHandler->getMachine().getCurrentState();
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			this->index = 0;
			elapsed = 0.f;
			pauseElapsed = 0.f;
			animPaused = true;
		}
	}

	if (shootAnimHolding)
	{
		shootAnimHoldElapsed += gTime;
		if (shootAnimHoldElapsed >= shootAnimDelay)
		{
			shootAnimHolding = false;
			
		}
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shootAnimHolding = true;
		shootAnimHoldElapsed = 0.f;

		if (canShoot)
		{
			if (!shooting)
			{
				if (!justShot)
				{
					shootWaitElapsed = 0.f;
					justShot = true;
					canShoot = false;
					shooting = true;
				}
				
				
				
			
			
				dispatch(this->fsmHandler->getMachine(), evt_StartedShooting{});
				
				if (fsmHandler->getMachine().wasJustChanged())
				{
					fsmHandler->getMachine().setJustChanged(false);
					this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
					this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
					currentAnim = fsmHandler->getMachine().getCurrentState();
					this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
					this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
					this->index = 0;
					elapsed = 0.f;
					pauseElapsed = 0.f;
					animPaused = true;
				}
			}
		}

	}
	else
	{

		

	}

	//if (jump_down == false && getVelocity().y < -50.f && jumping)
	//{

	//	setVelocity({ getVelocity().x, -50.f });
	//	dispatch(fsmHandler->getMachine(), evt_ReachedJumpPeak{});

	//	if (fsmHandler->getMachine().wasJustChanged())
	//	{
	//		fsmHandler->getMachine().setJustChanged(false);
	//		currentAnim = fsmHandler->getMachine().getCurrentState();
	//		this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
	//		this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
	//		this->index = 0;
	//		elapsed = 0.f;
	//		pauseElapsed = 0.f;
	//		animPaused = true;
	//	}
	//	jumping = false;
	//	falling = false;

	//}

}

void Player::update()
{
	if (justShot && (fsmHandler->getMachine().getCurrentState() == "shooting" || fsmHandler->getMachine().getCurrentState() == "jumpingAndShooting" || fsmHandler->getMachine().getCurrentState() == "startRunAndShooting" || fsmHandler->getMachine().getCurrentState() == "jumpPeakShooting" || fsmHandler->getMachine().getCurrentState() == "landingAndShooting" || fsmHandler->getMachine().getCurrentState() == "fallingAndShooting"  || fsmHandler->getMachine().getCurrentState() == "runningAndShooting") && shootWaitElapsed >= shootWaitDelay)
	{
		canShoot = true;
		
		if (numLiveBullets < maxLiveBullets)
		{
			shoot(ProjectileType::BusterBullet, true);
			snd::Play("shoot");

			numLiveBullets++;
		}
		justShot = false;
	}

	if (numLiveBullets > 0)
	{
		for (auto& b : getProjectiles())
		{
			if (b.isMarkedForDeletion())
			{
				continue;
			}

			if (b.aabb().top().end.x < 0.f || b.aabb().top().start.x > 1600.f)
			{
				b.setMarkedForDeletion(true);
			}
		}
	}

	auto erased = std::erase_if(getProjectiles(),  [](Projectile& p) { return p.isMarkedForDeletion() == true; });
	numLiveBullets -= (int)erased;

	currentAnim = fsmHandler->getMachine().getCurrentState();
	if (fsmHandler->getMachine().wasJustChanged())
	{
		fsmHandler->getMachine().setJustChanged(false);
		this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
		this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
		currentAnim = fsmHandler->getMachine().getCurrentState();
		this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
		this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
		this->index = 0;
		elapsed = 0.f;
		pauseElapsed = 0.f;
		animPaused = true;
	}

	if (jumping == true)
	{
		if (getVelocity().y > -50)
		{
			jumping = false;
			falling = false;
			dispatch(fsmHandler->getMachine(), evt_ReachedJumpPeak{});

			if (fsmHandler->getMachine().wasJustChanged())
			{
				fsmHandler->getMachine().setJustChanged(false);
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				currentAnim = fsmHandler->getMachine().getCurrentState();
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				this->index = 0;
				elapsed = 0.f;
				pauseElapsed = 0.f;
				animPaused = true;
			}
		}
	}

	if (currentAnim == "peakingJump" || currentAnim == "jumpPeakShooting")
	{
		if (getVelocity().y > 50.f)
		{
			falling = true;
			jumping = false;
			dispatch(fsmHandler->getMachine(), evt_Fell{});

			if (fsmHandler->getMachine().wasJustChanged())
			{
				fsmHandler->getMachine().setJustChanged(false);
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				currentAnim = fsmHandler->getMachine().getCurrentState();
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				this->index = 0;
				elapsed = 0.f;
				pauseElapsed = 0.f;
				animPaused = true;
			}
		}
	}



	if (!fsmHandler->getMachine().wasJustChanged() && elapsed > this->animMap[std::pair(this->currentAnim, this->facingLeft)].animDelay)
	{
		if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].isOnLastFrame())
		{
			dispatch(this->fsmHandler->getMachine(), evt_AnimationFinished{});

			if (fsmHandler->getMachine().wasJustChanged())
			{
				fsmHandler->getMachine().setJustChanged(false);
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				currentAnim = fsmHandler->getMachine().getCurrentState();
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
				this->index = 0;
				elapsed = 0.f;
				pauseElapsed = 0.f;
				animPaused = true;
			}
		}
	}


	// Handle animation frame switching and pause at the start of an animation if it has a pause delay of more than 0.f
	this->pauseElapsed += gTime;
	if (this->pauseElapsed >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].pauseDelay && this->animPaused == true)
	{
		this->elapsed = std::min(this->pauseElapsed - gTime, 0.f);
		this->animPaused = false;
	}
	//if (this->animPaused)
	//{
	//	if (pauseElapsed > this->animMap[std::pair(this->currentAnim, this->facingLeft)].pauseDelay)
	//	{
	//		if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].looping)
	//		{
	//			index = 0;
	//			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
	//			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
	//			elapsed = 0.f;
	//			pauseElapsed = 0.f;
	//			animPaused = true;
	//		}
	//	}
	//}

	if (this->animPaused == false)
	{
		this->elapsed += gTime;
		//if (this->index < 0 || this->index >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].numFrames)
		//{
		//	this->index = this->animMap[std::pair(this->currentAnim, this->facingLeft)].index;
		//	this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = index;
		//	elapsed = 0.f;
		//	pauseElapsed = 0.f;
		//	animPaused = true;
		//	fsmHandler->getMachine().setJustChanged(false);
		//	//throw std::runtime_error("Oh no! index for dynamic is out of range of the current animation selected to run");
		//}

		if (this->elapsed >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].animDelay)
		{
				this->elapsed = 0.f;
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].animate();

				if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].isOnLastFrame())
				{
					dispatch(fsmHandler->getMachine(), evt_AnimationFinished{});
					currentAnim = fsmHandler->getMachine().getCurrentState();
				}
				if (fsmHandler->getMachine().wasJustChanged())
				{
					this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
				}
				this->index = this->animMap[std::pair(this->currentAnim, this->facingLeft)].index;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = this->index;
				if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].onLastFrame)
				{
					this->animPaused = true;
					this->pauseElapsed = 0.f;
				}
			
		}
	}

//	index = animMap[std::pair(currentAnim, facingLeft)].index;

	bbox = animMap[std::pair(currentAnim, facingLeft)].bboxes[index];
	texRect = animMap[std::pair(currentAnim, facingLeft)].frames[index];

	

}

void Player::handleMapCollisions(std::vector<Platform>& plats_)
{
	ResolutionDir resDir = ResolutionDir::None;
	olc::vf2d tmpPos = this->getPos();
	if (this->onPlatform && !this->riding)
	{
		this->setPos({ this->getPos().x, this->getPrevPos().y });
	}
	else if (this->onPlatform && this->riding)
	{
		this->setPos({ this->getPos().x, this->getPrevPos().y + 1.f });
	}
	else
	{
		
			//this->setPos({ this->getPos().x, this->getPos().y + 3.f });
	}
	for (auto& plat : plats_)
	{
		if (Physics::RectVsRect(plat.bbRect(), this->bbRect()))
		{

			rect<float> bbRect = plat.bbRect();
			rect<float> playerBBRect = this->bbRect();
			auto aVec = intersects(bbRect, playerBBRect);

		

			if (aVec.size() > 0)
			{
				int num{ 0 };
				for (int i = 0; i < aVec.size(); i++)
				{
					if (this->prevOverlapIsX(plat))
					{
						// this is the point we want to shoot a ray through
						// resolve on the y
						num = i;
						if (this->getVelocity().y < 0.f)
						{
							if (plat.getPos().y < this->getPos().y)
							{
								// collision happened above
								std::cout << "Collision happened above" << std::endl;
								resDir = ResolutionDir::Down;
							}
							else
							{
								// collision happened above
								std::cout << "Collision happened below.. the platform is moving upward and the player is standing on it" << std::endl;
								resDir = ResolutionDir::Up;
							}
							break;
						}
						else if (this->getVelocity().y > 0.f)
						{
							// collision happened below
							std::cout << "Collision happened below need to push up " << std::endl;
							resDir = ResolutionDir::Up;
							break;
						}
					}
					else if (this->prevOverlapIsY(plat))
					{
						// this is the point we want to shoot a ray through
						// resolve on the x
						num = i;
						if (this->getVelocity().x < 0.f || storedVel.x < 0.f)
						{
							// collision happened on the left side
							std::cout << "Collision happened on the left" << std::endl;
							resDir = ResolutionDir::Right;
							break;
						}
						else if (this->getVelocity().x > 0.f || storedVel.x > 0.f)
						{
							// collision happened on the right side
							std::cout << "Collision happened on the right" << std::endl;
							resDir = ResolutionDir::Left;
							break;
						}
					}
				}
				
				this->setPos({ this->getPos().x, tmpPos.y });

				if (resDir == ResolutionDir::Up)
				{
					if (currentAnim == "falling" || currentAnim == "fallingAndShooting")
					{
						
						dispatch(this->fsmHandler->getMachine(), evt_Landed{});
						if (fsmHandler->getMachine().wasJustChanged())
						{
							
							snd::Play("land");

							fsmHandler->getMachine().setJustChanged(false);
							this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
							this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
							currentAnim = fsmHandler->getMachine().getCurrentState();
							this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
							this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
							this->index = 0;
							elapsed = 0.f;
							pauseElapsed = 0.f;
							animPaused = true;
						}
					}
					//this->setPos({ this->getPos().x,  plat.getPos().y - this->getBBSize().y - 0.1f });
					//this->setVelocity({ this->getVelocity().x, (plat.getPos().y - plat.getPrevPos().y) / gTime });
					if (plat.getPos().y > plat.getPrevPos().y && plat.getVelocity().y >= 0.f)
					{
						plat.goingUp = false;
						canJump = true;

					}
					 //this section collides like landing on a tile, eventually remove this completely
					if (plat.getPos().y < plat.getPrevPos().y && plat.getVelocity().y <= 0.f && plat.goingUp == false)
					{
						plat.goingUp = true;
						this->setPos({ this->getPrevPos().x , this->getPrevPos().y });
						this->setPos({ this->getPos().x, this->getPos().y + ((plat.getPos().y - (this->getPos().y + this->getBBSize().y)) - 0.1f) });
						//this->setVelocity({this->getVelocity().x,  this->getVelocity().y + plat.getVelocity().y});
						this->onPlatform = true;
						this->canJump = true;
						this->setAffectedByGravity(true);
						tmpFlag = true;
					}
					else
					{
						if (tmpFlag)
						{
							tmpFlag = false;
						}


						if (plat.getVelocity().y > 0.f)
						{
							this->setPos({ this->getPos().x,  (plat.getPos().y - this->getBBSize().y - 0.1f + 1.f) });
							this->setVelocity({ this->getVelocity().x + plat.getVelocity().x,0.f });
							this->setAffectedByGravity(true);
						}
						else
						{

							if (plat.isAtTopOfPath())
							{
								this->setPos({ this->getPos().x,  (plat.getPos().y - this->getBBSize().y - 0.1f) + 5.f });
								this->setVelocity({ this->getVelocity().x + plat.getVelocity().x, 74.f });
								this->setAffectedByGravity(true);

								this->onPlatform = true;
								this->canJump = true;
							}
							else
							{
								this->setPos({ this->getPos().x,  (plat.getPos().y - this->getBBSize().y - 0.1f) });
								// platform moving up
								this->setVelocity({ this->getVelocity().x + plat.getVelocity().x,plat.getVelocity().y });
								this->setAffectedByGravity(false);

								this->onPlatform = true;
								this->canJump = true;
							}

						}


						this->setAffectedByGravity(true);
					}
						if (plat.getVelocity().x < 0.f && left_down)
						{
							// platform player is standing on moving horizontally
							this->setVelocity({(this->getVelocity().x + plat.getVelocity().x) / 2.f , this->getVelocity().y});
							this->riding = true;
						}
						else if (plat.getVelocity().x > 0.f && left_down)
						{
							this->setVelocity({ (this->getVelocity().x - plat.getVelocity().x) / 2.f , this->getVelocity().y });
							this->riding = true;
						}
						else if (plat.getVelocity().x < 0.f && right_down)
						{
							// platform player is standing on moving horizontally
							this->setVelocity({ (this->getVelocity().x + plat.getVelocity().x) / 2.f , this->getVelocity().y });
							this->riding = true;
						}
						else if (plat.getVelocity().x > 0.f && right_down)
						{
							this->setVelocity({ (this->getVelocity().x - plat.getVelocity().x) / 2.f , this->getVelocity().y });
							this->riding = true;
						}
						else if (plat.getVelocity().x != 0 && !left_down && !right_down)
						{
							this->setVelocity({ plat.getVelocity().x , plat.getVelocity().y});
							this->riding = true;
						}


					
					 //mini section end

					//float offsetX = plat.getPos().x - plat.getPrevPos().x;
					//if (!landed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					//{
					//	pOffsetX = (this->getPos().x + this->getBBSize().x / 2.f) - (plat.getPos().x + this->getBBSize().x / 2.f);
					//	this->setPos({ this->getPos().x,  plat.getPos().y - this->getBBSize().y - 0.1f});
					//	landed = true;
					//}
					//else if (!landed)
					//{
					//	this->setPos({ this->getPos().x,  plat.getPos().y - this->getBBSize().y - 0.1f });
					//	landed = true;
					//}
					//else
					//{
					//	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					//	{
					//		this->setPos({ plat.getPos().x + offsetX + pOffsetX + this->getVelocity().x * gTime,  plat.getPos().y - this->getBBSize().y - 0.1f});
					//	}
					//	else
					//	{
					//		landed = false;
					//		this->setPos({ this->getPos().x,  plat.getPos().y - this->getBBSize().y - 0.1f});	
					//	}
					//}
					//this->setVelocity({ this->getVelocity().x , -1 * (this->getPos().y + this->getBBSize().y - plat.getPos().y)});//plat.getVelocity().y });
				}
				else if (resDir == ResolutionDir::Down)
				{
					this->setPos({ this->getPos().x,  plat.getPos().y + plat.getBBSize().y + 0.1f });
					this->setVelocity({ this->getVelocity().x, plat.getVelocity().y });
					this->onPlatform = false;
					this->setAffectedByGravity(true);
					this->canJump = false;

					if (this->fsmHandler->getMachine().getCurrentState() == "peakingJump" || this->jumping || this->fsmHandler->getMachine().getCurrentState() == "jumping" || this->fsmHandler->getMachine().getCurrentState() == "jumpingAndShooting" || this->fsmHandler->getMachine().getCurrentState() == "jumpPeakShooting")
					{
							falling = true;
							jumping = false;
							dispatch(fsmHandler->getMachine(), evt_ReachedJumpPeak{}, evt_Fell{});

							if (fsmHandler->getMachine().wasJustChanged())
							{
								fsmHandler->getMachine().setJustChanged(false);
								this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
								this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
								currentAnim = fsmHandler->getMachine().getCurrentState();
								this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
								this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
								this->index = 0;
								elapsed = 0.f;
								pauseElapsed = 0.f;
								animPaused = true;
							}
					}

				}
				else if (resDir == ResolutionDir::Left)
				{
					this->setPos({ plat.getPos().x - this->getBBSize().x - 0.1f , this->getPos().y });
					this->setVelocity({ plat.getVelocity().x, this->getVelocity().y });
					this->onPlatform = false;
					this->setAffectedByGravity(true);
					this->canJump = false;

					
				}
				else if (resDir == ResolutionDir::Right)
				{
					this->setPos({ plat.getPos().x + plat.getBBSize().x + 0.1f,  this->getPos().y });
					this->setVelocity({ plat.getVelocity().x, this->getVelocity().y });
					this->onPlatform = false;
					this->setAffectedByGravity(true);
					this->canJump = false;


				}
			}
		}
	}
}


bool Player::isTileBelow(std::vector<Platform>& plats)
	{
	rect<float> tmp{ bbRect() };
	tmp.pos.y += 10.f;

	bool collided = false;
	for (auto& plat : plats)
	{
		if (Physics::RectVsRect(tmp, plat.bbRect()))
		{
			if (this->prevOverlapIsX(plat) && !this->prevOverlapIsY(plat))
			{
				collided = true;
				break;


			}
		}
	}
	return collided;
}


void Player::handleMapCollisions(std::vector<Tile>& tiles)
{
	ResolutionDir resDir = ResolutionDir::None;



	resVec.clear();
	std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> > toAdd{};
	Tile* firstTile = nullptr;
	ResolutionDir firstResDir = ResolutionDir::None;

	for (auto& tile : tiles)
	{
 		if (Physics::RectVsRect(tile.bbRect(), this->bbRect()))
		{
			firstTile = &tile;
			sf::FloatRect tileFloatRect = { {tile.getPos().x, tile.getPos().y},{tile.getBBSize().x,tile.getBBSize().y} };
			sf::FloatRect playerFloatRect = { {this->getPos().x, this->getPos().y},{this->getBBSize().x,this->getBBSize().y} };
			sf::FloatRect overlapRect{};
			tileFloatRect.intersects(playerFloatRect, overlapRect);

			auto aVec = intersects(tile.bbRect(), this->bbRect());
			if (aVec.size() > 0)
			{


				int num{ 0 };
				for (int i = 0; i < aVec.size(); i++)
				{
					if (this->prevOverlapIsX(tile))
					{
						// this is the point we want to shoot a ray through
						// resolve on the y
						num = i;
						if (this->getVelocity().y < 0.f)
						{
							// collision happened above
							std::cout << "Collision happened above" << std::endl;
							resDir = ResolutionDir::Down;
							if (firstResDir == ResolutionDir::None)
							{
								firstResDir = resDir;
							}
							toAdd = std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> >{ &tile, {overlapRect, ResolutionDir::Down} };
							resVec.push_back(toAdd);
							
						}
						else if (this->getVelocity().y > 0.f)
						{
							// collision happened below
							std::cout << "Collision happened below need to push up " << std::endl;
							resDir = ResolutionDir::Up;
							if (firstResDir == ResolutionDir::None)
							{
								firstResDir = resDir;
							}
							toAdd = std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> >{ &tile, {overlapRect, ResolutionDir::Up} };
							resVec.push_back(toAdd);
							

						}
					}
					else if (this->prevOverlapIsY(tile))
					{
						// this is the point we want to shoot a ray through
						// resolve on the x
						num = i;
						if (this->getVelocity().x < 0.f || storedVel.x < 0.f)
						{
							if (!wasFacingLeft)
							{
								//player up against wall and turned around collision on the other side
								// collision happened on the left side
								std::cout << "Collision happened on the left" << std::endl;
								resDir = ResolutionDir::Left;
								if (firstResDir == ResolutionDir::None)
								{
									firstResDir = resDir;
								}
								toAdd = std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> >{ &tile, {overlapRect, ResolutionDir::Left} };
								resVec.push_back(toAdd);
							}
							else
							{
								// collision happened on the left side
								std::cout << "Collision happened on the left" << std::endl;
								resDir = ResolutionDir::Right;
								if (firstResDir == ResolutionDir::None)
								{
									firstResDir = resDir;
								}
								toAdd = std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> >{ &tile, {overlapRect, ResolutionDir::Right} };
								resVec.push_back(toAdd);
							}
						}
						else if (this->getVelocity().x > 0.f || storedVel.x > 0.f)
						{
							if (wasFacingLeft)
							{

								// collision happened on the right side
								std::cout << "Collision happened on the right" << std::endl;
								resDir = ResolutionDir::Right;
								if (firstResDir == ResolutionDir::None)
								{
									firstResDir = resDir;
								}
								toAdd = std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> >{ &tile, {overlapRect, ResolutionDir::Right} };
								resVec.push_back(toAdd);
							}
							else
							{
								// collision happened on the right side
								std::cout << "Collision happened on the right" << std::endl;
								resDir = ResolutionDir::Left;
								if (firstResDir == ResolutionDir::None)
								{
									firstResDir = resDir;
								}
								toAdd = std::pair<Tile*, std::pair<sf::FloatRect, ResolutionDir> >{ &tile, {overlapRect, ResolutionDir::Left} };
								resVec.push_back(toAdd);
							}
						}
					}
				}
			}
		}
	}
	// if some magic with resVec sees we are colliding with a walk and a floor or a ceiling ans a wall, then handle special
	int resUpCount=0;
	int resDownCount=0;
	int resLeftCount=0;
	int resRightCount=0;

	for (int i = 0; i < resVec.size(); i++)
	{
		switch (resVec[i].second.second)
		{
		case ResolutionDir::Up:
		{
			resUpCount++;
		}
			break;
		case ResolutionDir::Down:
		{
			resDownCount++;
		}
			break;
		case ResolutionDir::Left:
		{
			resLeftCount++;
		}
			break;
		case ResolutionDir::Right:
		{
			resRightCount++;
		}
			break;
		default:
			break;
		}
		// lets sort the elements by resolutiondir groups and count each
		
	}

	// display the counts of resolution directions for each tile collision to the player
	if (resUpCount > 0 || resDownCount > 0 || resLeftCount > 0 || resRightCount > 0)
	{
		if (mapMoved)
		{
			if (mapMovedRight)
			{
				if (resRightCount > 0)
				{
					gameView.move({ 250.f * gTime, 0.f });
					mapMovedRight = false;
				}
			}

			if (mapMovedLeft)
			{
				if (resLeftCount > 0)
				{
					gameView.move({ -250.f * gTime, 0.f });
					mapMovedLeft = false;
				}
			}
		}
		std::cout << "resUp:" << resUpCount << "\nresDown:" << resDownCount << "\nresLeft:" << resLeftCount << "\nresRight: " << resRightCount << std::endl;
	}


	if (firstTile != nullptr)
	{
	Tile& tile = *firstTile;

				// else do this junk
				if (firstResDir == ResolutionDir::Up)
				{
					dispatch(this->fsmHandler->getMachine(), evt_Landed{});

					if (fsmHandler->getMachine().wasJustChanged())
					{

						
						snd::Play("land");


						fsmHandler->getMachine().setJustChanged(false);
						this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
						this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
						currentAnim = fsmHandler->getMachine().getCurrentState();
						this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
						this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
						this->index = 0;
						elapsed = 0.f;
						pauseElapsed = 0.f;
						animPaused = true;
					}


					this->setPos({ this->getPos().x,  tile.getPos().y - this->getBBSize().y - 0.1f });
					this->setVelocity({ this->getVelocity().x, tile.getVelocity().y });
					this->canJump = true;
					this->setAffectedByGravity(false);
				}
				else if (firstResDir == ResolutionDir::Down)
				{
					this->setPos({ this->getPos().x,  tile.getPos().y + tile.getBBSize().y + 0.1f });
					this->setVelocity({ this->getVelocity().x, tile.getVelocity().y });

					if (this->fsmHandler->getMachine().getCurrentState() == "peakingJump" || this->jumping || this->fsmHandler->getMachine().getCurrentState() == "jumping")
					{
						falling = true;
						jumping = false;
						dispatch(fsmHandler->getMachine(), evt_ReachedJumpPeak{}, evt_Fell{});

						if (fsmHandler->getMachine().wasJustChanged())
						{
							fsmHandler->getMachine().setJustChanged(false);
							this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
							this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
							currentAnim = fsmHandler->getMachine().getCurrentState();
							this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
							this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
							this->index = 0;
							elapsed = 0.f;
							pauseElapsed = 0.f;
							animPaused = true;
						}
					}

				}
				else if (firstResDir == ResolutionDir::Left)
				{
					this->setPos({ tile.getPos().x - this->getBBSize().x - 0.1f , this->getPos().y });
					this->setVelocity({ tile.getVelocity().x, this->getVelocity().y });
				}
				else if (firstResDir == ResolutionDir::Right)
				{
					this->setPos({ tile.getPos().x + tile.getBBSize().x + 0.1f,  this->getPos().y });
					this->setVelocity({ tile.getVelocity().x, this->getVelocity().y });
				}
			}
}


bool Player::isTileBelow(std::vector<Tile>& tiles)
{
	rect<float> tmp{ bbRect() };
	tmp.pos.y += 10.f;

	bool collided = false;
	for (auto& tile : tiles)
	{
		if (Physics::RectVsRect(tmp, tile.bbRect()))
		{
			if (this->prevOverlapIsX(tile) && !this->prevOverlapIsY(tile))
			{
				
				dispatch(this->fsmHandler->getMachine(), evt_Landed{});

				if (fsmHandler->getMachine().wasJustChanged())
				{

					snd::Play("land");


					fsmHandler->getMachine().setJustChanged(false);
					this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
					this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
					currentAnim = fsmHandler->getMachine().getCurrentState();
					this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
					this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
					this->index = 0;
					elapsed = 0.f;
					pauseElapsed = 0.f;
					animPaused = true;
				}

				collided = true;
				break;


			}
		}
	}

	if (collided == false && !(onPlatform || riding))
	{
		dispatch(this->fsmHandler->getMachine(), evt_Fell{});

		if (fsmHandler->getMachine().wasJustChanged())
		{
			fsmHandler->getMachine().setJustChanged(false);
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			currentAnim = fsmHandler->getMachine().getCurrentState();
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
			this->index = 0;
			elapsed = 0.f;
			pauseElapsed = 0.f;
			animPaused = true;
		}
	}

	return collided;
}

void Player::setCanJump(bool cond_)
{
	canJump = cond_;
}

bool Player::AnimData::isOnLastFrame()
{
	return onLastFrame;
}

int Player::AnimData::getIndex()
{
	return index;
}

void Player::AnimData::animate()
{
	if (index + 1 >= numFrames && this->looping == false)
	{
		index = numFrames - 1;
		onLastFrame = true;
		
	}
	else if (index + 1 >= numFrames && this->looping == true)
	{
		onLastFrame = false;
		index = 0;
	}
	else if (index + 1 == numFrames - 1)
	{
		index++;
		onLastFrame = true;
	}
	else if (index + 1 < 0)
	{
		throw std::runtime_error("index negative!");
	}
	else
	{
		index++;
		onLastFrame = false;
	}
}

void Player::AnimData::resetData()
{
	this->index = 0;
	onLastFrame = false;
	playing = true;

}

void Player::AnimData::play()
{
	playing = true;
	this->index = 0;
}

void Player::AnimData::stop()
{
	playing = false;
	this->index = 0;
}

void Player::AnimData::pause()
{
	playing = false;
}

void Player::AnimData::resume()
{
	playing = true;
}
