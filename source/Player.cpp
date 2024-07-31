#include <pch.h>
#include <Player.h>
#include <Physics.h>
using namespace olc::utils::geom2d;

Player::Player(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
	: ASprite{ tex_, texRect_, bbox_, pos_, animDir_, bAffectedByGravity_ }
{}

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
		if (this->getVelocity().x <= MaxSpeed)
		{
			this->setVelocity({ this->getVelocity().x + 450 * gTime, this->getVelocity().y });
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
		if (this->getVelocity().x >= -MaxSpeed)
		{
			this->setVelocity({ this->getVelocity().x - 450 * gTime, this->getVelocity().y });
			//nowFacingLeft
		}
	}
	else
	{
		left_down = false;
	}
}

void Player::update()
{
	if (this->isAffectedByGravity())
	{
		this->applyGravity(600.f);
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
