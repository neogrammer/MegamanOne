#include <pch.h>
#include <ASprite.h>
#include <Projectile.h>
#include <Tilemap.h>
using namespace olc::utils::geom2d;

void ASprite::shoot(ProjectileType type_, bool friendly_)
{
	switch (type_)
	{
	case ProjectileType::BusterBullet:
		projectiles.emplace_back(Projectile{ Cfg::Textures::BusterBullet, "assets/data/aabbs/busterBullet.aabb", (this->isFacingLeft()) ? olc::vf2d{bbPos.x - getBBOffset().x + 28, bbPos.y - getBBOffset().y + 67} : olc::vf2d{bbPos.x - getBBOffset().x + 99, bbPos.y - getBBOffset().y + 67} , (this->isFacingLeft()) ? -500.f : 500.f, TravelDir::Horizontal, type_, 1 });
		break;
	default:
		break;
	}
}

ASprite::ASprite(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
	: bbPos{pos_}
	, vel{ olc::v_2d<float>{0.f,0.f} }
	, accelY{0.0f}
	, tex{tex_}
	, eType{type_}
	, bAffectedByGravity{bAffectedByGravity_}
	, animDir{animDir_}
	, texRect{texRect_}
	, bbox{bbox_}
	, prevPos{ pos_ }
{
	projectiles.clear();
}

void ASprite::setup(Cfg::Textures tex_, sf::IntRect texRect_, sf::FloatRect bbox_, SpriteType type_, olc::v_2d<float> pos_, AnimDirType animDir_, bool bAffectedByGravity_)
{
	bbPos = pos_;
	vel = { olc::v_2d<float>{0.f, 0.f} };
	accelY = 0.0f;
	tex = tex_;
	bAffectedByGravity = bAffectedByGravity_;
	animDir = animDir_;
	texRect = texRect_;
	bbox = bbox_;
	prevPos = pos_;
	projectiles.clear();
}
olc::vi2d ASprite::getActualCollisionPt(olc::vf2d collPt_)
{
	olc::vi2d tmp{};
	tmp.x = (int)roundf((collPt_.x - this->getPos().x));   // - this->getPrevPos().x + (this->getPos().x - this->getPrevPos().x) + (this->getVelocity().x * gTime)));
	tmp.y = (int)roundf((collPt_.y - this->getPos().y));  // -this->getPrevPos().y + (this->getPos().y - this->getPrevPos().y) + (this->getVelocity().y * gTime)));
	return tmp;
}
bool ASprite::isAffectedByGravity()
{
	return bAffectedByGravity;
}
void ASprite::setAffectedByGravity(bool cond_)
{
	bAffectedByGravity = cond_;
}
AnimDirType ASprite::getAnimDirType()
{
	return animDir;
}
void ASprite::setAnimDirType(AnimDirType type_)
{
	animDir = type_;
}
sf::IntRect ASprite::getTexRect()
{
	return texRect;
}

sf::FloatRect ASprite::getBBox_local()
{
	return bbox;
}

rect<float> ASprite::bbRect()
{
	return rect<float>({ bbPos }, {bbox.getSize().x, bbox.getSize().y});
}

olc::utils::geom2d::rect<float> ASprite::bbPrevRect()
{
	return rect<float>({ prevPos }, { bbox.getSize().x, bbox.getSize().y });
}

bool ASprite::prevOverlapIsY(ASprite& other)
{
	if (this->getPrevPos().y  < other.getPos().y + other.getBBSize().y && this->getPrevPos().y + this->getBBSize().y > other.getPos().y)
	{
		return true;
	}
	return false;
}

bool ASprite::prevOverlapIsX(ASprite& other)
{
	if (this->getPrevPos().x  < other.getPos().x + other.getBBSize().x && this->getPrevPos().x + this->getBBSize().x > other.getPos().x)
	{
		return true;
	}
	return false;
}

bool ASprite::isFacingLeft()
{
	bool isFacingLeft(); { return true; }
}

olc::v_2d<float> ASprite::getPos()
{
    return bbPos;
}

olc::v_2d<float> ASprite::getBBCenter()
{
	return {bbPos + (getBBSize() / 2.f)};
}

olc::v_2d<float> ASprite::getPrevPos()
{
	return prevPos;
}

olc::v_2d<float> ASprite::getNextPos()
{
	return (bbPos + (vel * gTime));
}

rect<float> ASprite::getBroadRect()
{
	return {{((vel.x < 0) ? bbPos.x + (vel.x * gTime) : bbPos.x), ((vel.y < 0) ? bbPos.y + (vel.y * gTime) : bbPos.y)}, { getBBSize().x + fabs(vel.x * gTime), getBBSize().y + fabs(vel.y * gTime) }};
}

rect<float> ASprite::getNextRect()
{
	return { {getNextPos()}, {getBBSize()}};
}

void ASprite::setPrevPos(olc::v_2d<float> pos_)
{
	prevPos = pos_;
}

olc::v_2d<float> ASprite::getBBOffset()
{
	return {bbox.getPosition().x, bbox.getPosition().y};
}

olc::v_2d<float> ASprite::getBBSize()
{
    return  { bbox.getSize().x, bbox.getSize().y };
}

olc::vi2d ASprite::getFrameSize()
{
    return  { texRect.getSize().x, texRect.getSize().y };
}

olc::v_2d<float> ASprite::getVelocity()
{
    return vel;
}

void ASprite::setVelocity(olc::v_2d<float> vel_)
{
	vel = vel_;
}

void ASprite::adjustSpeed(olc::v_2d<float> vel_)
{
	vel += vel_;
}

void ASprite::setPos(olc::v_2d<float> pos_)
{
	bbPos = pos_;
}

void ASprite::displace(olc::v_2d<float> disp_)
{
	bbPos += disp_;
}

void ASprite::switchDirection()
{
	if (animDir == AnimDirType::Left)
	{
		animDir = AnimDirType::Right;
	}
	else if (animDir == AnimDirType::Right)
	{
		animDir = AnimDirType::Left;
	}
	return;
}


void ASprite::changeDirection(AnimDirType animDir_)
{
	if (animDir == AnimDirType::Uni)
	{
		std::cout << "sprite set to Uni, changing direction, I hope you know what you are doing, but I will allow it. (crosses fingers)" << std::endl;
	}
	animDir = animDir_;
}

void ASprite::applyGravity(float grav_)
{
	vel.y += grav_ * gTime;
}

void ASprite::render()
{
	if (this->getSpr() == nullptr) return;

	gWnd.draw(*(this->getSpr()));
	if (this->showBoundingBox == true)
	{
		sf::RectangleShape bounds;
		bounds.setSize({ this->getBBSize().x, this->getBBSize().y });
		bounds.setPosition({this->getPos().x, this->getPos().y});
		bounds.setFillColor(sf::Color(255, 0, 0, 130));
		gWnd.draw(bounds);
	}



}
void ASprite::applyExternalForces()
{
	if (isAffectedByGravity())
	{
		applyGravity(900.f);
	}
}
void ASprite::setControlledByScript(bool cond_)
{
	bControlledByScript = cond_;
}
bool ASprite::isControlledByScript()
{
	return bControlledByScript;
}
void ASprite::tickMovement()
{
	
	if (!bControlledByScript)
	{
		prevPos = bbPos;
		bbPos += vel * gTime;
	}
	else
	{
		bbPos += vel * gTime;
	}


}

ray<float> ASprite::castRay(OriginPtType oType_, RayDirType dirType, olc::v_2d<float> target)
{
	olc::v_2d<float> origin = {0.f,0.f};
	switch (oType_)
	{
	case OriginPtType::Center:
		origin = { bbPos.x + (bbox.getSize().x / 2.f), bbPos.y + (bbox.getSize().y / 2.f) };
		break;
	case OriginPtType::BL:
		origin = { bbPos.x, bbPos.y + bbox.getSize().y };
		break;
	case OriginPtType::BottomCenter:
		origin = { bbPos.x + (bbox.getSize().x / 2.f) , bbPos.y + bbox.getSize().y };
		break;
	case OriginPtType::BR:
		origin = { bbPos.x + (bbox.getSize().x) , bbPos.y + bbox.getSize().y };
		break;
	case OriginPtType::LeftCenter:
		origin = { bbPos.x  , bbPos.y + (bbox.getSize().y / 2.f) };
		break;
	case OriginPtType::RightCenter:
		origin = { bbPos.x + (bbox.getSize().x) , bbPos.y + (bbox.getSize().y / 2.f) };
		break;
	case OriginPtType::TL:
		origin = { bbPos.x  , bbPos.y };
		break;
	case OriginPtType::TopCenter:
		origin = { bbPos.x + (bbox.getSize().x / 2.f) , bbPos.y };
		break;
	case OriginPtType::TR:
		origin = { bbPos.x + (bbox.getSize().x) , bbPos.y };
		break;
	default:
		break;
	}


	olc::v_2d<float> dir = {0.f,0.f};
	switch (dirType)
	{
	case RayDirType::Velocity:
		dir = { vel.x - origin.x, vel.y - origin.y };
		break;
	case RayDirType::Target:
		dir = { target.x - origin.x, target.y - origin.y };
		break;
	case RayDirType::ReflectedVelocity:
		dir = {origin.x - vel.x, origin.y - vel.y };
		break;
	case RayDirType::ReflectedTarget:
		dir = { origin.x - target.x, origin.y - target.y};
		break;
	default:
		break;
	}
	return ray<float>{{origin}, { (dir.mag() == 0.f) ? olc::v_2d<float>{0.f,0.f} : dir.norm() }};
}

std::unique_ptr<sf::Sprite> ASprite::getSpr()
{
	if (tex != Cfg::Textures::Count)
	{
		std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>();
		tmp->setTexture(Cfg::textures.get((int)tex));
		tmp->setTextureRect(texRect);
		tmp->setPosition(sf::Vector2f{ getPos().x - getBBOffset().x, getPos().y - getBBOffset().y});
		return std::move(tmp);
	}
	else
	{
		return nullptr;
	}
}

void ASprite::takeDamage(int dmg)
{
	health -= dmg;


	if (health <= 0)
	{
		health = 0;
		// dead animation

		// if enemy, mark for deletion

		// if player lose game
	}
	else
	{
		// if enemy, change texture to all white for a split second, and keep the game going
		
		// if player
		// hit animation, flash, and inactivate controls for a small period, then resume controls and keep invincible for a lil bit while the player recouperates
	}
}
