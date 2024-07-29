#include <pch.h>
#include <Dynamic.h>

void  Dynamic::applyVelocity()
{
	aabb.pos.x += vel.x   * gTime;
	aabb.pos.y += vel.y  *  gTime;
}

std::unique_ptr<sf::Sprite> Dynamic::spr()
{
	std::unique_ptr<sf::Sprite> pass = std::make_unique<sf::Sprite>(Cfg::textures.get((int)this->texType));
	pass->setTextureRect(texRect);
	pass->setOrigin(this->imgOrigin);
	pass->setPosition({ aabb.pos.x - bbox.left, aabb.pos.y - bbox.top });
	return std::move(pass);
}

void  Dynamic::setPos(sf::Vector2f pos_)
{
	aabb.pos.x = pos_.x;
	aabb.pos.y = pos_.y;
}

void  Dynamic::move(sf::Vector2f pos_)
{
	aabb.pos.x += pos_.x;
	aabb.pos.y += pos_.y;
}

void  Dynamic::setVelocity(sf::Vector2f vel_)
{
	vel.x = vel_.x;
	vel.y = vel_.y;
}

void  Dynamic::accelerate(sf::Vector2f acc_)
{
	vel.x += acc_.x * gTime;
	vel.y += acc_.y * gTime;
}

void Dynamic::applyGravity()
{
	vel.y += 986.6667f * gTime;
}

sf::Vector2f Dynamic::getImgSize()
{
	return { (float)texRect.width,(float)texRect.height };
}

sf::Vector2f Dynamic::getImgHSize()
{
	return { (float)texRect.width / 2.f,(float)texRect.height / 2.f };
}

sf::Vector2f Dynamic::getBBoxSize()
{
	return { (float)bbox.width,(float)bbox.height };
}

sf::Vector2f Dynamic::getBBoxHSize()
{
	return { (float)bbox.width / 2.f,(float)bbox.height / 2.f };

}

sf::FloatRect Dynamic::getAABB()
{
	sf::FloatRect tmp{};
	tmp.left = pos.x;
	tmp.top = pos.y;
	tmp.left += (float)bbox.left;
	tmp.top += (float)bbox.top;
	tmp.width = (float)bbox.width;
	tmp.height = (float)bbox.height;
	tmp.left = aabb.pos.x;
	tmp.top = aabb.pos.y;
	tmp.width =  aabb.size.x;
	tmp.height =aabb.size.y;

	return tmp;
}

sf::Vector2f Dynamic::getAABBCenter()
{


	return { aabb.middle().x, aabb.middle().y };
}

void Dynamic::setup(Cfg::Textures texType_, sf::Vector2f pos_, sf::Vector2f orig_, sf::IntRect texRect_, sf::IntRect bboxRect_, sf::Vector2f vel_)
{


	texType = texType_;
	pos = pos_;
	imgOrigin = orig_;
	texRect = texRect_;
	bbox = bboxRect_;
	vel = vel_;

	aabb.pos.x = pos_.x + bboxRect_.left;
	aabb.pos.y = pos_.y + bboxRect_.top;
	aabb.size.x = (float)bboxRect_.width;
	aabb.size.y = (float)bboxRect_.height;
	


}
