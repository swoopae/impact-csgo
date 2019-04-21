#include "netvar_manager.h"
#include "../interfaces/interfaces.h"

#include "../sdk/client_class.h"
#include "../sdk/i_client_entity.h"

// this is all 100% pasted but i dont care hahahahhAHAHAHAHHAhAHAHHA fuck

netvar_tree::netvar_tree()
{
	const c_client_class* client_class = interfaces::client->get_client_classes();

	while (client_class != nullptr)
	{
		const auto class_info = std::make_shared<node>(0);
		recv_table* recv_table = client_class->recvtable_ptr;

		this->populate_nodes(recv_table, &class_info->nodes);
		nodes.emplace(recv_table->table_name, class_info);

		client_class = client_class->next_ptr;
	}
}

void netvar_tree::populate_nodes(recv_table * recv_table, map_type * map_type)
{
	for (auto i = 0; i < recv_table->props_count; i++)
	{
		const recv_prop* prop = recv_table->get_prop(i);
		const auto propInfo = std::make_shared < node >(prop->offset);

		if (prop->prop_type == send_prop_type::_data_table)
			this->populate_nodes(prop->data_table, &propInfo->nodes);

		map_type->emplace(prop->prop_name, propInfo);
	}
}

std::unique_ptr<netvar_tree> netvar_manager;