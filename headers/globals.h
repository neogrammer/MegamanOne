#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>


extern sf::RenderWindow gWnd;
extern sf::ContextSettings gWndSettings;
extern sf::Vector2f mpos;
extern unsigned int gWW;
extern unsigned int gWH;
extern bool gWndFull;

extern float gTime;

namespace wndw
{
	extern void CreateWindow(std::string title_, unsigned int w_, unsigned int h_);
	
}

namespace scr
{
	extern bool CheckLua(lua_State* L, int r);
}