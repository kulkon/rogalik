#pragma once
#include "common.h"
#include <iostream>
#include <fstream>

class TextureInfo
{
public:
	TextureInfo(unsigned int textureID, std::string path, unsigned short w, unsigned short h, unsigned short c) {
		this->path = path;
		spriteWidth = w;
		spriteHeight = h;
		spriteCount = c;
		ID = textureID;
	}
	unsigned int ID;
	unsigned short spriteWidth, spriteHeight, spriteCount;
	std::string path;
	
};

class TexturesInfo {
public:
	std::vector<TextureInfo> textureInfos;
	void addInfo(unsigned int textureID, std::string path, unsigned short w, unsigned short h, unsigned short c) {
		textureInfos.push_back(TextureInfo(textureID, path, w, h, c));
	}

	void read() {
		std::ifstream f("../rogalik/textureInfo");
		std::string path;
		unsigned short w, h, c;
		unsigned int id;
		textureInfos.clear();
		while (f >> id >> path >> w >> h >> c) {
			textureInfos.push_back(TextureInfo(id, path, w, h, c));
		}
		f.close();
		for (int i = 0; i < textureInfos.size(); i++)
		{
			std::cout << textureInfos[i].path << " " << textureInfos[i].spriteWidth << " " << textureInfos[i].spriteHeight << " " << textureInfos[i].spriteCount;
			if (i < textureInfos.size() - 1) std::cout << std::endl;
		}
		
	}

	void write() {
		std::ofstream f("../rogalik/textureInfo");
		for (int i = 0; i < textureInfos.size(); i++)
		{
			f << textureInfos[i].ID << " " << textureInfos[i].path << " " << textureInfos[i].spriteWidth << " " << textureInfos[i].spriteHeight << " " << textureInfos[i].spriteCount;
			if (i < textureInfos.size() - 1) f << std::endl;
		}
		f.close();
	}
};