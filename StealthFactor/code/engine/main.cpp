#include <iostream>
#include <cli.hpp>
#include <engine/Engine.hpp>

#if defined(PLATFORM_LINUX)
#include <unistd.h>

#elif defined(PLATFORM_WINDOWS)
#include <windows.h>

#else
#error Unsupported platform
#endif

int main(int argc, const char **argv)
{
	cli::Parser parser(argc, argv);

	parser.help()
		<< R"(Stealth Factor)";

	auto dataPath = parser.option("data")
		.description("Path to data directory")
		.defaultValue("data")
		.getValue();

#if defined(PLATFORM_LINUX)
	if (chdir(dataPath))
	{
		std::cerr << "Unable to set data directory." << std::endl;
		return EXIT_FAILURE;
	}

#elif defined(PLATFORM_WINDOWS)
	wchar_t wDataPath[4096];
	MultiByteToWideChar(CP_ACP, 0, dataPath, -1, wDataPath, 4096);
	if (!SetCurrentDirectory(wDataPath))
	{
		std::cerr << "Unable to set data directory." << std::endl;
		return EXIT_FAILURE;
	}
#endif

	engine::Engine::getInstance().loadConfiguration();
	engine::Engine::getInstance().run();

	return EXIT_SUCCESS;
}
