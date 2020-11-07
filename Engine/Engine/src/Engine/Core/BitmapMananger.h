#pragma once
#include <string.h>
#include <unordered_map>
#include <windows.h>

namespace Engine {
	
	class BitmapMananger
	{
	public:
		static const HBITMAP& GetImage(const std::string& imageName);
	private:
		BitmapMananger() {};
		static std::unordered_map<std::string, HBITMAP> m_BitmapCache;
	};
}