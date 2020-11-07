#include "stdafx.h"
#include "BitmapMananger.h"


namespace Engine {

	std::unordered_map<std::string, HBITMAP> BitmapMananger::m_BitmapCache;

	const HBITMAP& BitmapMananger::GetImage(const std::string& imageName)
	{
		HBITMAP bitmap;
		auto it = m_BitmapCache.find(imageName);
		if (m_BitmapCache.find(imageName) != m_BitmapCache.end())
		{
			return m_BitmapCache[imageName];
		}
		else
			bitmap = (HBITMAP)LoadImageA(GetModuleHandle(NULL),
			(imageName + ".bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (bitmap)
		{
			m_BitmapCache[imageName] = bitmap;
		}
		else
		{
			LOG("Cannot Load Bitmap");
		}

		return m_BitmapCache[imageName];
	}
}
