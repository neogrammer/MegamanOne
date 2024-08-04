#include <pch.h>
#include <Platform.h>



#include <Physics.h>
using namespace olc::utils::geom2d;

void Platform::loadAnimations()
{
	
	this->currentAnim = "idle";
	this->facingLeft = true;
	// uni animations
	this->animMap.emplace(std::pair{ "idle", true }, AnimData{});
	this->animMap[std::pair("idle", true)].numFrames = loadAnimation(this->animMap[std::pair("idle", true)].frames, 3, 3, 0, 0, 0);
	this->animMap[std::pair("idle", true)].animDelay = 0.3f;
	this->animMap[std::pair("idle", true)].pauseDelay = 0.f;
	this->loadBBoxes();
}

int Platform::loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol, int startRow, int pitchColBegin)
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

void Platform::loadBBoxes()
{
	std::ifstream file;
	file.open("assets/data/bboxes/platforms/fly_pad.bbox");
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
bool Platform::hasBBoxesSet(const std::string& animname, bool facingleft)
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

Platform::Platform(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_)
	: ASprite{ tex_, texRect_, bbox_, SpriteType::Platform, pos_ }
{
	loadAnimations();
	setControlledByScript(true);
}

void Platform::input()
{
	
}

void Platform::update()
{
	// Handle animation frame switching and pause at the start of an animation if it has a pause delay of more than 0.f
	this->pauseElapsed += gTime;
	if (this->pauseElapsed >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].pauseDelay && this->animPaused == true)
	{
		this->elapsed = std::min(this->pauseElapsed - gTime, 0.f);
		this->animPaused = false;
	}
	if (this->animPaused)
	{
		if (pauseElapsed > this->animMap[std::pair(this->currentAnim, this->facingLeft)].animDelay)
		{
			if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].looping)
			{
				index = 0;
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
			}
		}
	}

	if (this->animPaused == false)
	{
		this->elapsed += gTime;
		if (this->index < 0 || this->index > this->animMap[std::pair(this->currentAnim, this->facingLeft)].numFrames)
		{
			throw std::runtime_error("Oh no! index for dynamic is out of range of the current animation selected to run");
		}

		if (this->elapsed >= this->animMap[std::pair(this->currentAnim, this->facingLeft)].animDelay)
		{
			this->elapsed = 0.f;
			this->animMap[std::pair(this->currentAnim, this->facingLeft)].animate();
			this->index = this->animMap[std::pair(this->currentAnim, this->facingLeft)].index;

			if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].onLastFrame)
			{
				this->animPaused = true;
				this->pauseElapsed = 0.f;
			}
		}
	}

	bbox = animMap[std::pair(currentAnim, facingLeft)].bboxes[index];
	texRect = animMap[std::pair(currentAnim, facingLeft)].frames[index];

	// update actual positions now, once only
	this->tickMovement();
}

float Platform::getMinY()
{
	return minY;
}

void Platform::setMinY(float val_)
{
	minY = val_;
}

bool Platform::isAtTopOfPath()
{
	return (this->getPos().y == this->getMinY());
}



bool Platform::AnimData::isOnLastFrame()
{
	return onLastFrame;
}

int Platform::AnimData::getIndex()
{
	return index;
}

void Platform::AnimData::animate()
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

void Platform::AnimData::resetData()
{
	this->index = 0;
	onLastFrame = false;
	playing = true;

}

void Platform::AnimData::play()
{
	playing = true;
	this->index = 0;
}

void Platform::AnimData::stop()
{
	playing = false;
	this->index = 0;
}

void Platform::AnimData::pause()
{
	playing = false;
}

void Platform::AnimData::resume()
{
	playing = true;
}
