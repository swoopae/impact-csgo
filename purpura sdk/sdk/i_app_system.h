#pragma once

typedef void* (*create_interface_fn)(const char *p_name, int *p_code);

class i_app_system
{
public:
	virtual bool                            connect(create_interface_fn factory) = 0;                                   // 0
	virtual void                            disconnect() = 0;                                                           // 1
	virtual void*                           query_interface(const char *p_interface_name) = 0;                          // 2
	virtual int /*InitReturnVal_t*/         init() = 0;                                                                 // 3
	virtual void                            shutdown() = 0;                                                             // 4
	virtual const void* /*AppSystemInfo_t*/ get_dependencies() = 0;                                                     // 5
	virtual int /*AppSystemTier_t*/         get_tier() = 0;                                                             // 6
	virtual void                            reconnect(create_interface_fn factory, const char *p_interface_name) = 0;   // 7
	virtual void                            unk_func() = 0;                                                             // 8
};