#include <pch.h>
#include "AABB.h"

using namespace olc::utils::geom2d;
void AABB::applyGravity()
{
	vely += 980.f * gTime;
}

AABB::AABB()
{
olc::utils::geom2d::rect<float> current{};
olc::utils::geom2d::rect<float> previous{};
}

AABB::AABB(Cfg::Textures texType_, sf::IntRect texRect_, int imgOx_, int imgOy_, sf::FloatRect bboxRect_)
	: current{}
	, previous{}
{
	imgRect = texRect_;
	tex = texType_;
	currFrame = &imgRect;
	velx = 0.f;
	vely = 0.f;
	imgOffsetX = imgOx_;
	imgOffsetY = imgOy_;

	current.pos.x = previous.pos.x = bboxRect_.getPosition().x;
	current.pos.y = previous.pos.y = bboxRect_.getPosition().y;
	current.size.x = previous.size.x = bboxRect_.getSize().x;
	current.size.y = previous.size.y = bboxRect_.getSize().y;

}

float& AABB::posx()
{
	return current.pos.x;
}

float& AABB::posy()
{
	// TODO: insert return statement here
	return current.pos.y;

}

float& AABB::oldPosx()
{
	// TODO: insert return statement here
	return previous.pos.x;

}

float& AABB::oldPosy()
{
	// TODO: insert return statement here
	return previous.pos.y;

}

float AABB::width()
{
	return current.size.x;
}

float AABB::height()
{
	return current.size.y;

}

float AABB::hHeight()
{
	return current.size.y / 2.f;
}

float AABB::hWidth()
{
	return current.size.x / 2.f;

}

olc::utils::geom2d::ray<float> AABB::dir()
{
	olc::v_2d<float> d({ velx, vely });
	return ray<float>(olc::v_2d<float>({ current.pos.x + (current.size.x / 2.f ), current.pos.y+(current.size.y / 2.f )}), d.norm());
}

olc::utils::geom2d::line<float> AABB::fromTo(olc::v_2d<float> point_)
{
	return olc::utils::geom2d::line<float>(olc::v_2d<float>{ current.pos.x + (current.size.x / 2.f ), current.pos.y + (current.size.y / 2.f ) }, olc::v_2d<float>{ point_.x , point_.y});
}

olc::utils::geom2d::line<float> AABB::toFrom(olc::v_2d<float> point_)
{
	return olc::utils::geom2d::line<float>(olc::v_2d<float>{ point_.x, point_.y}, olc::v_2d<float>{ current.pos.x + (current.size.x / 2.f), current.pos.y + (current.size.y / 2.f) });
}

olc::utils::geom2d::rect<float> AABB::broadBox()
{
	olc::v_2d<float> plCenter{};
	plCenter.x = current.pos.x + (current.size.x / 2.f);
	plCenter.y = current.pos.y + (current.size.y / 2.f);
	rect<float> plNextRect = { { current.pos.x + velx * gTime, current.pos.y + vely * gTime }, { current.size.x,current.size.y } };
	rect<float> plBroadRect{};
	plBroadRect.pos.x = (current.pos.x < plNextRect.pos.x) ? current.pos.x : plNextRect.pos.x;
	plBroadRect.pos.y = (current.pos.y < plNextRect.pos.y) ? current.pos.y : plNextRect.pos.y;
	plBroadRect.size.x = current.size.x + abs(plNextRect.pos.x - current.pos.x);
	plBroadRect.size.y = current.size.y + abs(plNextRect.pos.y - current.pos.y);

	return plBroadRect;
}

void AABB::staticCollide(olc::utils::geom2d::rect<float> statObj_)
{

}

int AABB::imgXOffset()
{
	return imgOffsetX;
}

int AABB::imgYOffset()
{
	return imgOffsetY;

}

int AABB::imgX()
{
	return (int)(current.pos.x - imgOffsetX);
}

int AABB::imgY()
{
	return  (int)(current.pos.y - imgOffsetY);

}

int AABB::imgRectW()
{
	return imgRect.width;
}

int AABB::imgRectHW()
{
	return  (int)(imgRect.width / 2.f);
}

int AABB::imgRectH()
{
	return imgRect.height;

}

int AABB::imgRectHH()
{
	return (int)(imgRect.height / 2.f);
}

std::unique_ptr<sf::Sprite> AABB::mkSpr()
{
	std::unique_ptr<sf::Sprite> pass = std::make_unique<sf::Sprite>(Cfg::textures.get((int)this->tex));
	pass->setTextureRect(imgRect);
	pass->setOrigin({ 0.f,0.f});
	pass->setPosition({ current.pos.x + imgOffsetX,  current.pos.y + imgOffsetY});
	return std::move(pass);
}


void AABB::applyVelocity()
{
	current.pos.x += velx * gTime;
	current.pos.y += vely * gTime;

}

void AABB::setPos(sf::Vector2f pos_)
{
	current.pos.x = pos_.x;
	current.pos.y = pos_.y;


}

void AABB::move(sf::Vector2f pos_)
{
	current.pos.x += pos_.x;
	current.pos.y += pos_.y;

}

void AABB::setVelocity(sf::Vector2f vel_)
{
	velx = vel_.x;
	vely = vel_.y;
}

void AABB::accelerate(sf::Vector2f acc_)
{
	velx += acc_.x * gTime;
	vely += acc_.y * gTime;
}
