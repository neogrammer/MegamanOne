#include <pch.h>
#include <ResourceManager.h>
#include <globals.h>

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
     music.load((int)Music::Stage1, "assets/music/stage1.mp3");
}

void Cfg::initSounds()
{
	sounds.load((int)Sounds::BusterShotNormal, "assets/sounds/busterShotNormal.ogg");
	sounds.load((int)Sounds::Jump, "assets/sounds/jump.ogg");
	sounds.load((int)Sounds::Land, "assets/sounds/land.ogg");
	auto smpCount = sounds.get((int)Sounds::BusterShotNormal).getSampleCount();
	std::cout << smpCount << std::endl;
	shootSound.setBuffer(sounds.get((int)Sounds::BusterShotNormal));
	shootSound.setAttenuation(0.f);
	shootSound.setRelativeToListener(false);
	shootSound.setVolume(80);
	jumpSound.setBuffer(sounds.get((int)Sounds::Jump));
	jumpSound.setAttenuation(0.f);
	jumpSound.setVolume(48.f);
	jumpSound.setRelativeToListener(false);
	landSound.setBuffer(sounds.get((int)Sounds::Land));
	landSound.setAttenuation(0.f);
	landSound.setRelativeToListener(false);

	landSound.setVolume(80);

}

void Cfg::initTextures()
{
	textures.load((int)Textures::PlayerAtlas, "assets/textures/actors/player/player_atlas1.png");
	textures.load((int)Textures::Tileset1, "assets/textures/tilesets/Tileset1_50x50.png");
	textures.load((int)Textures::China, "assets/textures/misc/face2.png");
	textures.load((int)Textures::FlyPad, "assets/textures/platforms/fly_pad67x40.png");
	textures.load((int)Textures::BGSpace, "assets/textures/backgrounds/space/bgSpace.png");
	textures.load((int)Textures::BusterBullet, "assets/textures/projectiles/busterBullet.png");
	textures.load((int)Textures::SnailEnemy, "assets/textures/actors/enemies/snailAtlas.png");


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
	fonts.load((int)Fonts::Font1, "assets/fonts/frisky_puppy.ttf");
}