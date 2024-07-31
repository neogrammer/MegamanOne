#include <pch.h>
#include <Player.h>
#include <Physics.h>
using namespace olc::utils::geom2d;

void Player::loadAnimations()
{

	this->currentAnim = "idle";
	this->facingLeft = false;
	// right animations
	this->animMap.emplace(std::pair{ "idle", false }, AnimData{});
	this->animMap[std::pair("idle", false)].frames = loadAnimation(3, 3, 0, 1, 0);
	this->animMap[std::pair("idle", false)].animDelay = 0.3f;
	this->animMap[std::pair("idle", false)].pauseDelay = 0.f;
	// left animations
	this->animMap.emplace(std::pair{ "idle", true }, AnimData{});
	this->animMap[std::pair("idle", true)].frames = loadAnimation(3, 3, 0, 14, 0);
	this->animMap[std::pair("idle", true)].animDelay = 0.3f;
	this->animMap[std::pair("idle", true)].pauseDelay = 0.f;
	this->loadBBoxes();
}

std::vector<sf::IntRect> Player::loadAnimation(int numFrames, int  pitch, int startCol, int startRow, int pitchColBegin)
{
	int colsFirst = pitch - startCol;
	float rowsAfter = ((float)numFrames - (float)colsFirst) / (float)pitch;
	int rowsBetween = static_cast<int>(rowsAfter);
	int colsLast = static_cast<int>(round((rowsAfter * (float)pitch) / this->texRect.getSize().x));

	std::vector<sf::IntRect> temp = {};
	temp.clear();
	temp.reserve(numFrames);

	// first row
	for (int x = startCol + pitchColBegin; x < pitch; x++)
	{
		temp.emplace_back(sf::IntRect{ {x * (int)texRect.getSize().x, startRow * (int)texRect.getSize().y},{(int)texRect.getSize().x,(int)texRect.getSize().y} });
	}
	//  middle full rows
	for (int y = 1; y < rowsBetween; y++)
	{
		for (int x = pitchColBegin; x < pitch; x++)
		{
			temp.emplace_back(sf::IntRect{ {x * (int)texRect.getSize().x, (startRow + y) * (int)texRect.getSize().y},{(int)texRect.getSize().x,(int)texRect.getSize().y} });
		}
	}
	// final partial row
	for (int x = pitchColBegin; x < colsLast; x++)
	{
		temp.emplace_back(sf::IntRect{ {x * (int)texRect.getSize().x, (startRow + rowsBetween + 1) * (int)texRect.getSize().y },{ (int)texRect.getSize().x,(int)texRect.getSize().y} });
	}
	//handled like a pimp
	this->numAnims++;

	return temp;
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

			this->animMap[std::pair(animname, left)].bboxes.clear();
			this->animMap[std::pair(animname, left)].bboxes.reserve(numberOfFrames);
			for (int i = 0; i < numberOfFrames; i++)
			{
				int l{}, t{}, w{}, h{};
				file >> l >> t >> w >> h;
				this->animMap[std::pair(animname, left)].bboxes.emplace_back(sf::IntRect{ {l,t},{w,h} });
				this->animMap[std::pair(animname, left)].numFrames++;
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

Player::Player(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
	: ASprite{ tex_, texRect_, bbox_, SpriteType::Player, pos_, animDir_, bAffectedByGravity_ }
{
	loadAnimations();
}

void Player::input()
{
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
		facingLeft = false;
		if (this->getVelocity().x <= MaxSpeed)
		{
			this->setVelocity({ 250.f, this->getVelocity().y });
			//nowFacingRight
		}
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
		facingLeft = true;
		if (this->getVelocity().x >= -MaxSpeed)
		{
			this->setVelocity({ -250.f, this->getVelocity().y });
			//nowFacingLeft
		}
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
			setVelocity({ getVelocity().x, JumpForce });
			this->setAffectedByGravity(true);

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
	}
}

void Player::update()
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

	if (this->isAffectedByGravity())
	{
		this->applyGravity(900.f);
	}

	// update actual positions now, once only
	this->tickMovement();
}

void Player::handleMapCollisions(std::vector<ASprite>& tiles)
{
	ResolutionDir resDir = ResolutionDir::None;
	std::vector<olc::vf2d> aVec;
	aVec.clear();




	for (auto& tile : tiles)
	{
		if (Physics::RectVsRect(tile.bbRect(), this->bbRect()))
		{
			aVec = intersects(tile.bbRect(), this->bbRect());
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
					else if (this->prevOverlapIsY(tile))
					{
						// this is the point we want to shoot a ray through
						// resolve on the x
						num = i;
						if (this->getVelocity().x < 0.f)
						{
							// collision happened on the left side
							std::cout << "Collision happened on the left" << std::endl;
							resDir = ResolutionDir::Right;
							break;
						}
						else if (this->getVelocity().x > 0.f)
						{
							// collision happened on the right side
							std::cout << "Collision happened on the right" << std::endl;
							resDir = ResolutionDir::Left;
							break;
						}
					}
				}
				if (resDir == ResolutionDir::Up)
				{
					this->setPos({ this->getPos().x,  tile.getPos().y - this->getBBSize().y - 0.1f });
					this->setVelocity({ this->getVelocity().x, tile.getVelocity().y });
					this->canJump = true;
					this->setAffectedByGravity(false);
				}
				else if (resDir == ResolutionDir::Down)
				{
					this->setPos({ this->getPos().x,  tile.getPos().y + tile.getBBSize().y + 0.1f });
					this->setVelocity({ this->getVelocity().x, tile.getVelocity().y });
				}
				else if (resDir == ResolutionDir::Left)
				{
					this->setPos({ tile.getPos().x - this->getBBSize().x - 0.1f , this->getPos().y });
					this->setVelocity({ tile.getVelocity().x, this->getVelocity().y });
				}
				else if (resDir == ResolutionDir::Right)
				{
					this->setPos({ tile.getPos().x + tile.getBBSize().x + 0.1f,  this->getPos().y });
					this->setVelocity({ tile.getVelocity().x, this->getVelocity().y });
				}
			}
		}
	}
}

bool Player::isTileBelow(std::vector<ASprite>& tiles)
{
	rect<float> tmp{ bbRect() };
	tmp.pos.y += 10.f;

	bool collided = false;
	for (auto& tile : tiles)
	{
		if (Physics::RectVsRect( tmp, tile.bbRect()))
		{
			if (this->prevOverlapIsX(tile) && !this->prevOverlapIsY(tile))
			{
				collided = true;
				break;

				
			}
		}
	}
	return collided;
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
