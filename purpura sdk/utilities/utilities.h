#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <cmath>
#include <Psapi.h>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "vmatrix.h"

#define in_range(x,a,b)   (x >= a && x <= b)

#define get_bits( x )    (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (in_range(x,'0','9') ? x - '0' : 0))
#define get_byte( x )    (get_bits(x[0]) << 4 | get_bits(x[1]))

namespace global_utils {
	template <typename T>
	static T* get_interface(char* sz_module, char* sz_interface) {
		typedef void * (*o_interface_t)(char*, int);
		o_interface_t original = (o_interface_t)GetProcAddress(GetModuleHandleA(sz_module), "CreateInterface");
		return (T*)original(sz_interface, 0);
	}

	template <typename T>
	static T legacy_v_function(void* p_class, int i_index) {
		PDWORD p_vtable = *(PDWORD*)p_class;
		DWORD dw_address = p_vtable[i_index];
		return (T)(dw_address);
	}

	template <typename T>
	static T call_v_table(void* address, int index) {
		return (*reinterpret_cast<T**>(address))[index];
	}

	// this is pasted from somewhere and i dont have the time to rewrite to to fit snake_case sorry
	static uintptr_t get_signature(const char* szModule, const char* szSignature) {
		const char* pat = szSignature;
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(szModule);
		MODULEINFO miModInfo;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == get_byte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2;
			}
			else
			{
				pat = szSignature;
				firstMatch = 0;
			}
		}
		return NULL;
	}

	static DWORD find_pattern(const char* module_name, const BYTE* mask, const char* mask_string)
	{
		/// Get module address
		const unsigned int module_address = reinterpret_cast<unsigned int>(GetModuleHandleA(module_name));

		/// Get module information to the size
		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_address), &module_info, sizeof(MODULEINFO));

		auto IsCorrectMask = [](const unsigned char* data, const unsigned char* mask, const char* mask_string) -> bool
		{
			for (; *mask_string; ++mask_string, ++mask, ++data)
				if (*mask_string == 'x' && *mask != *data)
					return false;

			return (*mask_string) == 0;
		};

		/// Iterate until we find a matching mask
		for (unsigned int c = 0; c < module_info.SizeOfImage; c += 1)
		{
			/// does it match?
			if (IsCorrectMask(reinterpret_cast<unsigned char*>(module_address + c), mask, mask_string))
				return (module_address + c);
		}

		return 0;
	}

	static void console_log(const std::string& sz_output) {
		std::cout << "[log:] " << sz_output << "\n";
	}

	static void console_warn(const std::string& sz_output) {
		std::cout << "[warning:] " << sz_output << "\n";
	}

	static void console_error(const std::string& sz_output) {
		std::cout << "[ERROR:] " << sz_output << "\n";
	}

	static void set_clantag(const char* tag, const char* name) {
		static auto p_set_clantag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>((DWORD)(global_utils::get_signature("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));
		p_set_clantag(tag, name);
	}

	void* find_interface(const char* module, const char* interface_name);

	bool world_to_screen(const vec3_t & origin, vec3_t & screen);
}