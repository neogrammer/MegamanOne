#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <Cfg.h>

#ifndef DRAW_SHAPE_H__
#define DRAW_SHAPE_H__

extern sf::RenderWindow gWnd;

namespace drw
{
	extern void CirS(const sf::Vector2f& pos_, float radius_, const sf::Color& stroke_ = sf::Color::White, float thickness_ = 1, bool origCenter_ = true);
	extern void CirF(const sf::Vector2f& pos_, float radius_, const sf::Color& fill_ = sf::Color::White, bool origCenter_ = true);
	extern void Cir(const sf::Vector2f& pos_, float radius_ , const sf::Color& fill_ =  sf::Color::White, const sf::Color& stroke_ = sf::Color::Black, float thickness_ = 1, bool origCenter_ = true);
	extern void RectS(const sf::Vector2f& pos_, const sf::Vector2f& dims_, const sf::Color& stroke_ = sf::Color::White, float thickness_ = 1, bool origCenter_ = false);
	extern void RectF(const sf::Vector2f& pos_, const sf::Vector2f& dims_, const sf::Color& fill_ = sf::Color::White, bool origCenter_ = false);
	extern void Rect(const sf::Vector2f& pos_, const sf::Vector2f& dims_, const sf::Color& fill_ = sf::Color::White, const sf::Color& stroke_ = sf::Color::Black, float thickness_ = 1, bool origCenter_ = false);

}

namespace mk
{
	extern std::unique_ptr<sf::Sprite> Spr(Cfg::Textures tex_, const sf::Vector2f& pos_, const sf::IntRect& texRect_, bool origCenter_ = false);
}


#endif