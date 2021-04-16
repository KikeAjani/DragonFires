#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "../swalib_example/Code/Game/Managers/world.h"
#include "../swalib_example/Code/Game/Managers/graphics_engine.h"

//-----------------------------------------------------------------------------
int Main(void)
{
	// Initialization.
	cGraphicsEngine::GetInstance().Init();
	cWorld::GetInstance().Init();

	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		cWorld::GetInstance().Slot();	// Logic slot.
		cGraphicsEngine::GetInstance().Slot();	// Render slot.
		SYS_Pump();	// Process Windows messages.
	}

	// Shutdown. In reverse order to initilization.
	cWorld::GetInstance().Terminate();
	cGraphicsEngine::GetInstance().Terminate();

	return 0;
}
