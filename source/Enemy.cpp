#include <pch.h>
#include <Enemy.h>
#include <Projectile.h>
#include <MoveCommand.h>
using namespace olc::utils::geom2d;

Enemy::Enemy(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
	: ASprite{ tex_, texRect_, bbox_, type_, pos_, animDir_, bAffectedByGravity_ }
	, cmdList{}
{
	cmdList.clear();
}

void Enemy::setup(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
{
	ASprite::setup(tex_, texRect_, bbox_, type_, pos_, animDir_, bAffectedByGravity_);
	cmdList.clear();
}



int Enemy::loadAnimation(std::vector<sf::IntRect>& correctVec, int numFrames, int  pitch, int startCol, int startRow, int pitchColBegin)
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

void Enemy::loadBBoxes(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
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
bool Enemy::hasBBoxesSet(const std::string& animname, bool facingleft)
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

bool Enemy::isFacingLeft()
{
	return facingLeft;
}

void Enemy::pushCommand(CmdType cmd_, void* data_)
{
	switch (cmd_)
	{
	case CmdType::Move:
	{
		MoveData* data = reinterpret_cast<MoveData*>(data_);
		cmdList.emplace_back(std::make_unique<MoveCommand>(*this, data->target_, data->completeTime_));
	}
		break;

	default:
		break;
	}
	
}


bool Enemy::AnimData2::isOnLastFrame()
{
	return onLastFrame;
}

int Enemy::AnimData2::getIndex()
{
	return index;
}

void Enemy::AnimData2::animate()
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

void Enemy::AnimData2::resetData()
{
	this->index = 0;
	onLastFrame = false;
	playing = true;

}

void Enemy::AnimData2::play()
{
	playing = true;
	this->index = 0;
}

void Enemy::AnimData2::stop()
{
	playing = false;
	this->index = 0;
}

void Enemy::AnimData2::pause()
{
	playing = false;
}

void Enemy::AnimData2::resume()
{
	playing = true;
}
