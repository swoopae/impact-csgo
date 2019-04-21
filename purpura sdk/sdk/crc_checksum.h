//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Generic CRC functions
//
// $NoKeywords: $
//=============================================================================//
#ifndef CHECKSUM_CRC_H
#define CHECKSUM_CRC_H
#ifdef _WIN32
#pragma once
#endif

typedef unsigned int crc32_t;

void crc32_init(crc32_t *pulCRC);
void crc32_process_buffer(crc32_t *pulCRC, const void *p, int len);
void crc32_final(crc32_t *pulCRC);
crc32_t	crc32_get_table_entry(unsigned int slot);

inline crc32_t crc32_process_single_buffer(const void *p, int len)
{
	crc32_t crc;

	crc32_init(&crc);
	crc32_process_buffer(&crc, p, len);
	crc32_final(&crc);

	return crc;
}

#endif // CHECKSUM_CRC_H