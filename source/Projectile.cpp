#include <pch.h>
#include <Projectile.h>
#include <Physics.h>
#include <fstream>
#include <ASprite.h>
#include <Tile.h>
#include <Player.h>
#include <ASprite.h>


Projectile::Projectile(const Projectile& o)
	: tex{ o.tex }
	, texRect{o.texRect}
	, bboxLocal{o.bboxLocal}
	, pos{ o.pos }
	, speed{ o.speed }
	, tDir{ o.tDir }
	, type{ o.type }
	, damage{ o.damage }
{
	frames_.clear();
	bboxes_.clear();
	frames_.resize(o.frames_.size());
	bboxes_.resize(o.bboxes_.size());
	for (int i = 0; i < o.frames_.size(); i++)
	{
		frames_[i] = o.frames_[i];
		bboxes_[i] = o.bboxes_[i];
	}
}

Projectile& Projectile::operator=(const Projectile& o)
{
	tex = o.tex;
	texRect = o.texRect;
	bboxLocal = o.bboxLocal;
	pos = o.pos;
	speed = o.speed;
	tDir = o.tDir;
	type = o.type;
	damage = o.damage;

	frames_.clear();
	bboxes_.clear();
	frames_.resize(o.frames_.size());
	bboxes_.resize(o.bboxes_.size());
	for (int i = 0; i < o.frames_.size(); i++)
	{
		frames_[i] = o.frames_[i];
		bboxes_[i] = o.bboxes_[i];
	}

	return *this;
}

Projectile::Projectile(Cfg::Textures tex_, const std::string& aabbFile, olc::v_2d<float> pos_, float speed_, TravelDir dir_, ProjectileType type_, int damage_)
	: tex{tex_}
	, texRect{}
	, bboxLocal{}
	, pos{pos_}
	, speed{speed_}
	, tDir{dir_}
	, type{type_}
	, damage{damage_}
{

	LoadAABB(aabbFile);

}

void Projectile::setup(Cfg::Textures tex_, const std::string& aabbFile, olc::v_2d<float> pos_, float speed_, TravelDir dir_, ProjectileType type_, int damage_)
{
	tex = tex_;
	texRect = {};
	bboxLocal = {};
	pos = pos_;
	speed = speed_;
	tDir = dir_;
	type = type_;
	damage = damage_;

	LoadAABB(aabbFile);
}

std::unique_ptr<sf::Sprite> Projectile::getSpr()
{
	if (tex != Cfg::Textures::Count && !markedForDeletion)
	{
		std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>();
		tmp->setTexture(Cfg::textures.get((int)tex));
		tmp->setTextureRect(texRect);
		tmp->setPosition({ pos.x - (bboxLocal.width / 2.f), pos.y - (bboxLocal.height / 2.f) });
		return std::move(tmp);
	}
	else
	{
		return nullptr;
	}
}

void Projectile::destoryAndDOT(ASprite& aSpr_)
{
}

void Projectile::destroyAndAOE(ASprite& aSpr_)
{
}

void Projectile::destroyAndHit(ASprite& aSpr_)
{
	aSpr_.takeDamage(damage);
	markedForDeletion = true;
}

bool Projectile::collide(ASprite& aSpr_)
{

	if (Physics::RectVsRect(aSpr_.bbRect(), this->aabb()))
	{
		return true;
	}

	// did the bullet collide with the ASprite in question?
	return false;
}

void Projectile::updateCheckHandle(Player& player_, std::vector<ASprite*>& sprites_, std::vector<Tile>& tiles_)
{
	if (markedForDeletion) return;

	animTimeElapsed += gTime;

	if (animTimeElapsed >= animDelay)
	{
		animTimeElapsed = 0.f;
		animate();
	}

	bool collided = false;
	if (!isFriendly)
	{
		if (collide(player_))
		{
			destroyAndHit(player_);
			collided = true;
		}
	}
	else
	{
		for (auto& s : sprites_)
		{
			if (!s) continue;
			
			if (collide(*s))
			{
				destroyAndHit(*s);
				collided = true;
				break;
			}
		}
	}

	if (!collided)
	{
		for (auto& t : tiles_)
		{
			if (collide(t))
			{
				destroy();
				collided = true;
				break;
			}
		}
	}

	if (!collided)
	{
		tickMovement();
	}
}

void Projectile::tickMovement()
{
	if (tDir == TravelDir::Horizontal)
	{
		pos.x += speed * gTime;
		distanceTravelled += abs(speed * gTime);
	}

	if (distanceTravelled > maxDistance)
	{
		markedForDeletion = true;
	}
}

void Projectile::render()
{
	if (!markedForDeletion)
	{
		std::unique_ptr<sf::Sprite> spr = std::move(getSpr());
		if (!spr) return;

		gWnd.draw(*spr);
	}
}

void Projectile::animate()
{
	index++;

	if (index >= numFrames)
	{
		index = 0;
	}

	texRect = frames_[index];
	bboxLocal = bboxes_[index];
}

void Projectile::LoadAABB(const std::string& aabbFile)
{
	std::ifstream file;
	file.open(aabbFile);

	if (file.is_open())
	{
		frames_.clear();
		bboxes_.clear();

		file >> numFrames;
		frames_.resize(numFrames);
		bboxes_.resize(numFrames);

		for (int i = 0; i < numFrames; i++)
		{
			file >> frames_[i].left >> frames_[i].top >> frames_[i].width >> frames_[i].height >> bboxes_[i].left >> bboxes_[i].top >> bboxes_[i].width >> bboxes_[i].height;
		}

		texRect = frames_[0];
		bboxLocal = bboxes_[0];
	}
}
