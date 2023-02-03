#pragma once

#include <string>
#include <fstream>

std::string LoadTextFile(const std::string& filepath)
{
	std::ifstream file(filepath, std::ios::in);
	std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return text;
}
