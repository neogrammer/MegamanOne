#include <pch.h>
#include <draw_shape.h>

void drw::CirS(const sf::Vector2f& pos_, float radius_, const sf::Color& stroke_, float thickness_, bool origCenter_)
{
	sf::CircleShape shp{ radius_ };
	sf::Vector2f orig = sf::Vector2f((origCenter_) ? sf::Vector2f{radius_, radius_} : sf::Vector2f{0.f, 0.f});
	shp.setOrigin(orig);
	shp.setOutlineThickness(thickness_);
	shp.setOutlineColor(stroke_);
	shp.setFillColor(sf::Color::Transparent);
	shp.setPosition(pos_);

	gWnd.draw(shp);
}

void drw::CirF(const sf::Vector2f& pos_, float radius_,const sf::Color& fill_, bool origCenter_)
{

	sf::CircleShape shp{ radius_ };
	sf::Vector2f orig = sf::Vector2f((origCenter_) ? sf::Vector2f{ radius_, radius_ } : sf::Vector2f{ 0.f, 0.f });
	shp.setOrigin(orig);
	shp.setOutlineThickness(0);
	shp.setOutlineColor(sf::Color::Transparent);
	shp.setFillColor(fill_);
	shp.setPosition(pos_);

	gWnd.draw(shp);
}

void drw::Cir(const sf::Vector2f& pos_, float radius_,const sf::Color& fill_, const sf::Color& stroke_, float thickness_, bool origCenter_)
{

	sf::CircleShape shp{ radius_ };
	sf::Vector2f orig = sf::Vector2f((origCenter_) ? sf::Vector2f{ radius_, radius_ } : sf::Vector2f{ 0.f, 0.f });
	shp.setOrigin(orig);
	shp.setOutlineThickness(thickness_);
	shp.setOutlineColor(stroke_);
	shp.setFillColor(fill_);
	shp.setPosition(pos_);
	
	gWnd.draw(shp);

}

void drw::RectS(const sf::Vector2f& pos_, const sf::Vector2f& dims_, const sf::Color& stroke_, float thickness_, bool origCenter_)
{
	sf::RectangleShape shp{ dims_ };
	sf::Vector2f orig = sf::Vector2f((origCenter_) ? sf::Vector2f{ dims_.x / 2.f, dims_.y / 2.f } : sf::Vector2f{ 0.f, 0.f });
	shp.setOrigin(orig);
	shp.setOutlineThickness(thickness_);
	shp.setOutlineColor(stroke_);
	shp.setFillColor(sf::Color::Transparent);
	shp.setPosition(pos_);

	gWnd.draw(shp);

}

void drw::RectF(const sf::Vector2f& pos_, const sf::Vector2f& dims_, const sf::Color& fill_, bool origCenter_)
{
	sf::RectangleShape shp{ dims_ };
	sf::Vector2f orig = sf::Vector2f((origCenter_) ? sf::Vector2f{ dims_.x / 2.f, dims_.y / 2.f } : sf::Vector2f{ 0.f, 0.f });

	shp.setOrigin(orig);
	shp.setOutlineThickness(0);
	shp.setOutlineColor(sf::Color::Transparent);
	shp.setFillColor(fill_);
	shp.setPosition(pos_);

	gWnd.draw(shp);
}

void drw::Rect(const sf::Vector2f& pos_, const sf::Vector2f& dims_, const sf::Color& fill_, const sf::Color& stroke_, float thickness_, bool origCenter_)
{
	sf::RectangleShape shp{ dims_ };
	sf::Vector2f orig = sf::Vector2f((origCenter_) ? sf::Vector2f{ dims_.x / 2.f, dims_.y / 2.f } : sf::Vector2f{ 0.f, 0.f });

	shp.setOrigin(orig);
	shp.setOutlineThickness(thickness_);
	shp.setOutlineColor(stroke_);
	shp.setFillColor(fill_);
	shp.setPosition(pos_);

	gWnd.draw(shp);
}

std::unique_ptr<sf::Sprite> mk::Spr(Cfg::Textures tex_, const sf::Vector2f& pos_, const sf::IntRect& texRect_, bool origCenter_)
{
	std::unique_ptr<sf::Sprite> pass = std::make_unique<sf::Sprite>(Cfg::textures.get((int)tex_));
	pass->setTextureRect(texRect_);
	if (origCenter_)
	{
		pass->setOrigin(texRect_.width / 2.f, texRect_.height / 2.f);
	}
	pass->setPosition(pos_);

	return std::move(pass);
}
