#include <SFML/Graphics/RenderWindow.hpp>
#include <string>


extern sf::RenderWindow gWnd;
extern sf::ContextSettings gWndSettings;
extern unsigned int gWW;
extern unsigned int gWH;
extern bool gWndFull;

extern float gTime;

namespace wndw
{
	extern void CreateWindow(std::string title_, unsigned int w_, unsigned int h_);
}