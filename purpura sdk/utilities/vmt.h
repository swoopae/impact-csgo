#pragma once

#include <Windows.h>
#include <stdio.h>
#include <map>
#include <memory>

class vmt {
private:

	std::unique_ptr<std::uintptr_t[]> p_newvmt = nullptr;
	std::uintptr_t**                  p_baseclass = nullptr;
	std::uintptr_t*                   p_ogvmt = nullptr;
	std::size_t                       index_count = 0;

public:

	vmt(void* pp_class) {
		this->p_baseclass = static_cast <std::uintptr_t**> (pp_class);

		while (static_cast <std::uintptr_t*> (*this->p_baseclass)[this->index_count])
			++this->index_count;

		const std::size_t size_table = this->index_count * sizeof(std::uintptr_t);

		this->p_ogvmt = *this->p_baseclass;
		this->p_newvmt = std::make_unique < std::uintptr_t[] >(this->index_count);

		std::memcpy(this->p_newvmt.get(), this->p_ogvmt, size_table);

		*this->p_baseclass = this->p_newvmt.get();
	};
	~vmt() { *this->p_baseclass = this->p_ogvmt; };

	template<class T>
	T get_original(const std::size_t index) {
		return reinterpret_cast <T> (this->p_ogvmt[index]);
	};

	bool hook(const std::size_t index, void* fn_new) {
		if (index > this->index_count)
			return false;

		this->p_newvmt[index] = reinterpret_cast <std::uintptr_t> (fn_new);
		return true;
	};

	bool unhook(const std::size_t index) {
		if (index > this->index_count)
			return false;

		this->p_newvmt[index] = this->p_ogvmt[index];
		return true;
	};
};