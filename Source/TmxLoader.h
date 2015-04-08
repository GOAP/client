#pragma once

#include "tinyxml2.h"
#include <iostream>
#include "StaticEntity.h"
#include <vector>
#include "Entity.h"
#include "Static.h"

using namespace std;
using namespace tinyxml2;

class TmxLoader
{
private: 
	vector<Entity*> _allEntities;
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
		/*
		LOAD ALL NECESARY ASSETS;
		*/
		sf::Image treeImage;

		if (treeImage.loadFromFile("Assets/Tree.png"))
			std::cout << "hi" << std::endl;

		sf::Texture* treeTexture = new sf::Texture();
		sf::Texture* rockTexture = new sf::Texture();
		sf::Texture* woodTexture = new sf::Texture();

		treeTexture->loadFromFile("Assets/Tree.png");
		rockTexture->loadFromFile("Assets/Stone.png");
		woodTexture->loadFromFile("Assets/Wood.png");

		sf::Sprite tree_;
		sf::Sprite rock_;
		sf::Sprite wood_;

		tree_.setTexture(*treeTexture);
		rock_.setTexture(*rockTexture);
		wood_.setTexture(*woodTexture);

		
		for (int i = 0; i < MapHeight; ++i)
		{
			for (int j = 0; j < MapWidth; ++j)
			{
				if (ResourceData[i][j] == 1)
				{
					Entity* temp = new Static(ResourceData[i][j] + 100, j * 100, i * 100, tree_);
					_allEntities.push_back(temp);
				}
				if (ResourceData[i][j] == 2)
				{
					Entity* temp = new Static(ResourceData[i][j] + 100, j * 100, i * 100, rock_);
					_allEntities.push_back(temp);
				}	
				if (ResourceData[i][j] == 3)
				{
					Entity* temp = new Interactable(ResourceData[i][j] + 200, j * 100, i * 100, wood_, "wood");
					_allEntities.push_back(temp);
				}
					
			}
		}

	}

	vector<Entity*>* getAllEntities()
	{
		return &_allEntities;
	}

};

