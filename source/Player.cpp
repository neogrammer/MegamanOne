#include <pch.h>
#include <Player.h>
#include <Physics.h>
#include <Platform.h>
#include <duck_fold.h>
#include <assert.h>

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
	
	this->animMap.emplace(std::pair{ "falling", false }, AnimData{});
	this->animMap[std::pair("falling", false)].frames = loadAnimation(1, 10, 9, 5, 0);
	this->animMap[std::pair("falling", false)].animDelay = 0.3f;
	this->animMap[std::pair("falling", false)].pauseDelay = 0.f;
	this->animMap[std::pair("falling", false)].looping = false;

	// left animations
	this->animMap.emplace(std::pair{ "falling", true }, AnimData{});
	this->animMap[std::pair("falling", true)].frames = loadAnimation(1, 10, 9, 18, 0);
	this->animMap[std::pair("falling", true)].animDelay = 0.3f;
	this->animMap[std::pair("falling", true)].pauseDelay = 0.f;
	this->animMap[std::pair("falling", true)].looping = false;

	this->animMap.emplace(std::pair{ "landing", false }, AnimData{});
	this->animMap[std::pair("landing", false)].frames = loadAnimation(3, 13, 10, 5, 0);
	this->animMap[std::pair("landing", false)].animDelay = 0.06f;
	this->animMap[std::pair("landing", false)].pauseDelay = 0.f;
	this->animMap[std::pair("landing", false)].looping = false;
	// left animations
	this->animMap.emplace(std::pair{ "landing", true }, AnimData{});
	this->animMap[std::pair("landing", true)].frames = loadAnimation(3, 13, 10, 18, 0);
	this->animMap[std::pair("landing", true)].animDelay = 0.06f;
	this->animMap[std::pair("landing", true)].pauseDelay = 0.f;
	this->animMap[std::pair("landing", true)].looping = false;



	this->loadBBoxes();

	this->currentAnim = "falling";

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

	fsmHandler = std::make_unique<MachineHandler>(MachineType::Player);
	dispatch(fsmHandler->getMachine(), evt_Fell {});
	
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
		facingLeft = true;
		if (this->getVelocity().x >= -MaxSpeed)
		{
			this->setVelocity({ -250.f, this->getVelocity().y });
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

	if (jump_down == false && getVelocity().y < -50.f && !onPlatform)
	{
		setVelocity({ getVelocity().x, -50.f });
	}

}

void Player::update()
{
	if (!fsmHandler->getMachine().wasJustChanged())
	{
		if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].isOnLastFrame())
		{
			dispatch(this->fsmHandler->getMachine(), evt_AnimationFinished{});
		}
	}

	currentAnim = fsmHandler->getMachine().getCurrentState();
	assert(animMap.find(std::pair(currentAnim, facingLeft)) != animMap.end());
	if (fsmHandler->getMachine().wasJustChanged())
	{
		this->animMap[std::pair(this->currentAnim, this->facingLeft)].index = 0;
		this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
		fsmHandler->getMachine().setJustChanged(false);
	}



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
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = 0;
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
			if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].isOnLastFrame() && !this->animMap[std::pair(this->currentAnim, this->facingLeft)].looping)
			{
				// do nothing
			}
			else
			{
				this->animMap[std::pair(this->currentAnim, this->facingLeft)].animate();
				this->index = this->animMap[std::pair(this->currentAnim, this->facingLeft)].index;
				this->animMap[std::pair(this->currentAnim, !this->facingLeft)].index = this->index;

				if (this->animMap[std::pair(this->currentAnim, this->facingLeft)].onLastFrame)
				{
					this->animPaused = true;
					this->pauseElapsed = 0.f;
				}
			}
		}
	}



	bbox = animMap[std::pair(currentAnim, facingLeft)].bboxes[index];
	texRect = animMap[std::pair(currentAnim, facingLeft)].frames[index];

	

}

void Player::handleMapCollisions(std::vector<Platform>& plats_)
{
	ResolutionDir resDir = ResolutionDir::None;
	std::vector<olc::vf2d> aVec;
	aVec.clear();
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


			aVec = intersects(plat.bbRect(), this->bbRect());

		

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
				
				this->setPos({ this->getPos().x, tmpPos.y });

				if (resDir == ResolutionDir::Up)
				{
						dispatch(this->fsmHandler->getMachine(), evt_Landed{});
				
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
					dispatch(this->fsmHandler->getMachine(), evt_Landed{});


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

				collided = true;
				break;


			}
		}
	}

	if (collided == false)
		dispatch(this->fsmHandler->getMachine(), evt_Fell{});


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
