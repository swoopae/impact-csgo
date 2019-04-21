#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../sdk/recv.h"

class netvar_tree {
	struct node;
	using map_type = std::unordered_map<std::string, std::shared_ptr<node>>;

	struct node {
		node(int offset) : offset(offset) { }
		map_type nodes;
		int offset;
	};

	map_type nodes;

public:
	netvar_tree();

	template<typename ...args_t>
	int get_offset(const char *name, args_t ...args) {
		const auto &node = nodes[name];
		return this->get_offset_recursive(node->nodes, node->offset, args...);
	}

private:

	void populate_nodes(recv_table * recv_table, map_type * map_type);

	static int get_offset_recursive(map_type &map, int acc, const char *name) {
		return acc + map[name]->offset;
	}

	template<typename ...args_t>
	int get_offset_recursive(map_type &map, int acc, const char *name, args_t ...args) {
		const auto &node = map[name];
		return this->get_offset_recursive(node->nodes, acc + node->offset, args...);
	}
};

extern std::unique_ptr<netvar_tree> netvar_manager;