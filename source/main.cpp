#include <pch.h>
#include <Game.h>
int main(int argc, char* argv[])
{
	Cfg::Initialize();
	Game demo{};
	demo.run();
}