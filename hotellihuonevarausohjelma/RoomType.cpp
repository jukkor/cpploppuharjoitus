#include "RoomType.h"

std::string roomTypeToString(RoomType roomType) {
	switch (roomType)
	{
	case RoomType::Single: return "Single";
	case RoomType::Double: return "Double";
	default: return "Unknown";
	}
}