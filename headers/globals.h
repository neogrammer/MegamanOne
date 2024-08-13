#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

#include <rec.h>
class DFlyPad;
class DynoPlayer;
extern sf::RenderWindow gWnd;
extern sf::ContextSettings gWndSettings;
extern sf::Vector2f mpos;
extern unsigned int gWW;
extern unsigned int gWH;
extern bool gWndFull;

extern sf::Sound shootSound;
extern sf::Sound jumpSound;
extern sf::Sound landSound;


extern float gTime;
extern float gPrevTime;

extern sf::View gameView;

namespace wndw
{
	extern void CreateWindow(std::string title_, unsigned int w_, unsigned int h_);
	
}

namespace scr
{
	extern bool CheckLua(lua_State* L, int r);
}

namespace snd
{
	extern void Play(std::string soundName_);
}




namespace phys
{

	

	extern std::unique_ptr<sf::Sprite> spr(rec& r);
	extern std::unique_ptr<sf::Sprite> sprAnim(rec& r, sf::IntRect iRect_, DynoPlayer& p_);
	extern std::unique_ptr<sf::Sprite> sprAnim(rec& r, sf::IntRect iRect_, DFlyPad& p_);

	extern bool PointVsRect(const olc::vf2d& p, const rec& r);


	extern bool RectVsRect(const rec& r1, const rec& r2);


	extern bool RayVsRect(const olc::vf2d& ray_origin, const olc::vf2d& ray_dir, const rec& target, olc::vf2d& contact_point, olc::vi2d& contact_normal, float& t_hit_near);


	extern bool DynamicRectVsRect(const rec& in, const rec& target, olc::vf2d& contact_point, olc::vi2d& contact_normal, float& contact_time, float fElapsedTime);


}
