#pragma once

#include "tinyxml2.h"
#include <iostream>
#include "StaticEntity.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

class TmxLoader
{
private: 
	vector<StaticEntity> _statics;
public:

	TmxLoader(){};
	~TmxLoader(){};

	void loadFile(const char* mapName)
	{
		XMLDocument xmlDoc;
		XMLError eResult = xmlDoc.LoadFile(mapName);

		XMLNode * Root = xmlDoc.FirstChild();

		XMLElement * Element = Root->FirstChild()->ToElement();

		int BiomeNr;
		eResult = Element->QueryIntAttribute("biomes", &BiomeNr);

		int MapHeight;
		eResult = Element->QueryIntAttribute("height", &MapHeight);

		int MapWidth;
		eResult = Element->QueryIntAttribute("width", &MapWidth);

		std::cout << BiomeNr << ' ' << MapHeight << ' ' << MapWidth << endl;

		int DataExtract1;
		int DataExtract2;

		//NOT USE TILEDATA FOR NOW!
		int TileData[64][64];
		int ResourceData[64][64];

		XMLElement * ListElement = Element->FirstChild()->ToElement();

		for (int i = 0; i < MapHeight; i++)
		{
			cout << endl;
			for (int j = 0; j < MapWidth; j++)
			{
				eResult = ListElement->QueryIntAttribute("Tile", &DataExtract1);
				TileData[i][j] = DataExtract1;

				eResult = ListElement->QueryIntAttribute("Resource", &DataExtract2);
				ResourceData[i][j] = DataExtract2;

				ListElement = ListElement->NextSiblingElement("Map");
				cout << DataExtract2;
			}
		}

		for (int i = 0; i < MapHeight; ++i)
		{
			for (int j = 0; j < MapWidth; ++j)
			{
				if (!ResourceData[i][j] == 0)
				_statics.push_back(StaticEntity(10, j * 15, i * 15));
			}
		}

	}

	vector<StaticEntity>* getStatics()
	{
		return &_statics;
	}

};

