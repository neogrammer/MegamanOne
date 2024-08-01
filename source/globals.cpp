#include <pch.h>

sf::RenderWindow gWnd = {};
sf::ContextSettings gWndSettings = { sf::ContextSettings{} };
unsigned int gWW = {};
unsigned int gWH = {};
sf::Vector2f mpos = {};
bool gWndFull = false;

float gTime = 0.f;

void wndw::CreateWindow(std::string title_, unsigned int w_, unsigned int h_)
{
	gWW = w_;
	gWH = h_;
	gWndSettings.antialiasingLevel = 8;
	if (gWndFull == true)
		gWnd.create({ gWW,gWH,32U }, title_, sf::Style::Fullscreen, gWndSettings);
	else if (gWndFull == false)
		gWnd.create({ gWW,gWH,32U }, title_, sf::Style::Close, gWndSettings);

}


bool scr::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}