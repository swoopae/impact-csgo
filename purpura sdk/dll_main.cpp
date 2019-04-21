#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>

#include "utilities/utilities.h"
#include "interfaces/interfaces.h"
#include "utilities/render_manager.h"
#include "hooks/hooks.h"
#include "utilities/netvar_manager.h"

VOID WINAPI setup_debug_console() {
	AllocConsole();

	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	SetConsoleTitleA("[purpura sdk] console: ");
}

void write_chams() {
	// chams
	std::ofstream("csgo\\materials\\chams.vmt") << R"#("VertexLitGeneric"
		{
			"$basetexture" "vgui/white_additive"
			"$ignorez"      "0"
			"$envmap" ""
			"$nofog"        "1"
			"$model"        "1"
			"$nocull"       "0"
			"$selfillum"    "1"
			"$halflambert"  "1"
			"$znearer"      "0"
			"$flat"         "1"
			"$wireframe"    "0"
		}
		)#";

	// cooler chams that i never got around to use oof
	std::ofstream("csgo\\materials\\metallic_chams.vmt") << R"#("VertexLitGeneric"
		{
		  "$basetexture"	   "vgui/white_additive"
		  "$ignorez"		   "0"
		  "$envmap"			   "env_cubemap"
		  "$nofog"			   "1"
		  "$model"			   "1"
		  "$nocull"			   "0"
		  "$selfillum"		   "1"
		  "$halflambert"       "1"
		  "$znearer"           "0"
		  "$flat"              "1"
		  "$rimlight"          "1"
		  "$rimlightexponent"  "2"
		  "$rimlightboost"     ".2"
		  "$reflectivity"	   "[1 1 1]"
		}
		)#";

	return;
}

DWORD WINAPI dll_setup(HINSTANCE module_handle) {
	setup_debug_console();

	global_utils::console_log("impact debug console loaded.");

	write_chams();

	interfaces::init();
	netvar_manager = std::make_unique < netvar_tree >();
	render_manager::init();
	hooks::init();

	while (true) {
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(1s);

		if (GetAsyncKeyState(VK_DELETE)) {
			fclose((FILE*)stdin);
			fclose((FILE*)stdout);

			HWND hw_ConsoleHwnd = GetConsoleWindow();

			FreeConsole();
			PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);

			hooks::restore();

			FreeLibraryAndExitThread(module_handle, 1);
		}
	}
}

BOOL APIENTRY DllMain(HMODULE module, DWORD  reason_for_call, LPVOID reserved) {
	switch (reason_for_call) {
	case DLL_PROCESS_ATTACH:

		DisableThreadLibraryCalls(module);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)dll_setup, NULL, NULL, NULL);
		break;
	}

	return TRUE;
}