#include <iostream>
#include <cstring>

#include "Pomme.h"
#include "PommeInit.h"
#include "PommeTime.h"
#include "PommeFiles.h"
#include "PommeGraphics.h"
#include "PommeSound.h"
#include "PommeInput.h"

#include "SDL.h"

#if _WIN32
	#include "Platform/Windows/PommeWindows.h"
#endif

//-----------------------------------------------------------------------------
// Our own utils

const char* Pomme::QuitRequest::what() const noexcept
{
	return "the user has requested to quit the application";
}

//-----------------------------------------------------------------------------
// Misc

void ExitToShell()
{
	throw Pomme::QuitRequest();
}

void SysBeep(short duration)
{
#ifdef _WIN32
	Pomme::Platform::Windows::SysBeep();
#else
	TODOMINOR();
#endif
}

void FlushEvents(short, short)
{
	TODOMINOR();
}

int NumToStringC(long theNum, Str255 theString)
{
	return snprintf(theString, 256, "%ld", theNum);
}

//-----------------------------------------------------------------------------
// Mouse cursor

void InitCursor()
{
	SDL_ShowCursor(1);
}

void HideCursor()
{
	SDL_ShowCursor(0);
}

//-----------------------------------------------------------------------------
// Our own init

void Pomme::Init(const InitParams& params)
{
	Pomme::Time::Init();
	Pomme::Files::Init();
	Pomme::Graphics::Init(params.windowName, params.windowWidth, params.windowHeight, params.msaaSamples);
	Pomme::Sound::Init();
	Pomme::Input::Init();
}

void Pomme::Shutdown()
{
	Pomme::Sound::Shutdown();
	Pomme::Graphics::Shutdown();
}
