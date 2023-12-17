#pragma once

#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>;

// Resource Type
enum class RES_TYPE
{
	TEXTURE,
	END,
};