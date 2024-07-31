#include <pch.h>
#include <ResourceManager.h>


ResourceManager<sf::Texture, int> Cfg::textures = {};
ResourceManager<sf::Font, int> Cfg::fonts = {};
ResourceManager<sf::Music, int> Cfg::music = {};
ResourceManager<sf::SoundBuffer, int> Cfg::sounds = {};

ActionMap<int> Cfg::playerInputs = {};

void Cfg::Initialize()
{
    initTextures();
    initFonts();
    initMusic();
    initSounds();
	initPlayerInputs();
 
}

void Cfg::initMusic()
{
    /*  music.load(Music::Intro, "assets/sounds/music/tetrisc.wav"); */
}

void Cfg::initSounds()
{

}

void Cfg::initTextures()
{
	textures.load((int)Textures::PlayerAtlas, "assets/textures/actors/player/player_atlas1.png");
	textures.load((int)Textures::Tileset1, "assets/textures/tilesets/Tileset1_50x50.png");
	textures.load((int)Textures::China, "assets/textures/misc/face2.png");

}

void Cfg::initPlayerInputs()
{
	// realtime events
	// Keyboard pressed commands
	playerInputs.map(Cfg::PlayerInputs::X, Action(sf::Keyboard::Num9));
	playerInputs.map(Cfg::PlayerInputs::Y, Action(sf::Keyboard::X));
	playerInputs.map(Cfg::PlayerInputs::A, Action(sf::Keyboard::Num0));
	playerInputs.map(Cfg::PlayerInputs::B, Action(sf::Keyboard::Space));
	playerInputs.map(Cfg::PlayerInputs::L1, Action(sf::Keyboard::Num7));
	playerInputs.map(Cfg::PlayerInputs::R1, Action(sf::Keyboard::Add));
	// menu controls
	playerInputs.map(Cfg::PlayerInputs::Start, Action(sf::Keyboard::Enter));
	playerInputs.map(Cfg::PlayerInputs::Select, Action(sf::Keyboard::Backspace));
	// direction controls
	playerInputs.map(Cfg::PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map(Cfg::PlayerInputs::Down, Action(sf::Keyboard::Down));
	playerInputs.map(Cfg::PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map(Cfg::PlayerInputs::Right, Action(sf::Keyboard::Right));

	// Joystick Controls
	// Axis mappings
	playerInputs.map(Cfg::PlayerInputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
	// Button mappings
	playerInputs.map(Cfg::PlayerInputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));

}

void Cfg::initFonts()
{
}