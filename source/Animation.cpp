#include "pch.h"
#include "Animation.h"

void Animation::addFrame(const sf::IntRect& iRect_)
{
}

void Animation::addFrameSheet(const std::string& filename_, const std::string& cfgFile_)
{
}


bool Animation::isOnLastFrame()
{
	return data.onLastFrame;
}

int Animation::getIndex()
{
	return data.index;
}

void Animation::animate()
{
	if (data.index + 1 >= data.numFrames && this->data.looping == false)
	{
		data.index = data.numFrames - 1;
		data.onLastFrame = true;

	}
	else if (data.index + 1 >= data.numFrames && this->data.looping == true)
	{
		data.onLastFrame = false;
		data.index = 0;
	}
	else if (data.index + 1 == data.numFrames - 1)
	{
		data.index++;
		data.onLastFrame = true;
	}
	else if (data.index + 1 < 0)
	{
		data.index = 0;
	}
	else
	{
		data.index++;
		data.onLastFrame = false;
	}
}

void Animation::resetData()
{
	data.index = 0;
	data.onLastFrame = false;
	data.playing = true;

}

void Animation::play()
{
	data.playing = true;
	data.index = 0;
}

void Animation::stop()
{
	data.playing = false;
	data.index = 0;
}

void Animation::pause()
{
	data.playing = false;
}

void Animation::resume()
{
	data.playing = true;
}

Animation::Animation()
{
	data = AnimData{};
}

AnimData::AnimData()
{
	name = "none" ;
		fallbackName = "none";
		numFrames = 0;
		index = 0;
		animDelay = 0.f;
		pauseDelay = 0.f;
		 playing =  true;
		 facingLeft =  true;
		 onLastFrame =  false;
		 looping = true;
		repeatTimes =  1;
		frames = std::vector<sf::IntRect>{};
		frames.clear();
		bboxes = std::vector<sf::FloatRect>{};
		bboxes.clear();
}
