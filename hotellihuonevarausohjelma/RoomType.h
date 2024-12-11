#pragma once
#include <string>
enum class RoomType
{
	Single,
	Double
};

std::string roomTypeToString(RoomType roomType);
