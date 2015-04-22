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
	sf::Font OSD_MONO;

	vector<Entity*> _allEntities;
	
	vector< vector <int> > tile_data;

	sf::Sprite icons[4];
	sf::Sprite bgs[3];

	sf::Sprite _dropable[2];

	sf::Sprite terrains[6];
	int TileData[64][64];
	int ResourceData[64][64];
	
public:

	TmxLoader(){};
	~TmxLoader(){};

	sf::Sprite* loadFile(const char* mapName)
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
			vector<int> temp;
			for (int j = 0; j < MapWidth; ++j)
			{
				temp.push_back(TileData[i][j]);
			}
			tile_data.push_back(temp);
		}
		/*
		LOAD ALL NECESARY ASSETS;
		*/
		//Font
		OSD_MONO.loadFromFile("Assets/osd_mono.ttf");

		//Icons_Bg
		sf::Texture* icon_energy = new sf::Texture();
		sf::Texture* icon_thirst = new sf::Texture();
		sf::Texture* icon_hunger = new sf::Texture();
		sf::Texture* icon_warmth = new sf::Texture();
		sf::Texture* bg_med = new sf::Texture();
		sf::Texture* bg_low = new sf::Texture();
		sf::Texture* bg_high = new sf::Texture();

		icon_energy->loadFromFile("Assets/icon_energy.png");
		icon_thirst->loadFromFile("Assets/icon_thirst.png");
		icon_hunger->loadFromFile("Assets/icon_hunger.png");
		icon_warmth->loadFromFile("Assets/icon_warmth.png");
		bg_med->loadFromFile("Assets/bg_med.png");
		bg_low->loadFromFile("Assets/bg_low.png");
		bg_high->loadFromFile("Assets/bg_high.png");

		bgs[0].setTexture(*bg_high);
		bgs[1].setTexture(*bg_med);
		bgs[2].setTexture(*bg_low);

		icons[0].setTexture(*icon_energy);
		icons[1].setTexture(*icon_thirst);
		icons[2].setTexture(*icon_hunger);
		icons[3].setTexture(*icon_warmth);

		//Terrain
		sf::Texture* stoneTerrain = new sf::Texture();
		sf::Texture* snowTerrain = new sf::Texture();
		sf::Texture* sandTerrain = new sf::Texture();
		sf::Texture* grassTerrain = new sf::Texture();
		sf::Texture* dirtTerrain = new sf::Texture();
		sf::Texture* pebbleTerrain = new sf::Texture();

		stoneTerrain->loadFromFile("Assets/terrain_stone.png");
		snowTerrain->loadFromFile("Assets/terrain_snow.png");
		sandTerrain->loadFromFile("Assets/terrain_sand.png");
		grassTerrain->loadFromFile("Assets/terrain_grass.png");
		dirtTerrain->loadFromFile("Assets/terrain_dirt.png");
		pebbleTerrain->loadFromFile("Assets/terrain_pebbles.png");

		terrains[0].setTexture(*stoneTerrain);
		terrains[1].setTexture(*snowTerrain);
		terrains[2].setTexture(*sandTerrain);
		terrains[3].setTexture(*grassTerrain);
		terrains[4].setTexture(*dirtTerrain);
		terrains[5].setTexture(*pebbleTerrain);

		//Resourcess
		sf::Texture* treeTexture = new sf::Texture();
		sf::Texture* rockTexture = new sf::Texture();
		sf::Texture* woodTexture = new sf::Texture();
		sf::Texture* fireTexture = new sf::Texture();
		sf::Texture* bedTexture = new sf::Texture();
		sf::Texture* appleTexture = new sf::Texture();

		sf::Texture* InvLogTexture = new sf::Texture();

		treeTexture->loadFromFile("Assets/Tree.png");
		rockTexture->loadFromFile("Assets/Stone.png");
		woodTexture->loadFromFile("Assets/Log.png");
		fireTexture->loadFromFile("Assets/Fire.png");
		bedTexture->loadFromFile("Assets/Bed.png");
		appleTexture->loadFromFile("Assets/Apple.png");

		InvLogTexture->loadFromFile("Assets/Inv_Log.png");

		sf::Sprite tree_;
		sf::Sprite rock_;
		sf::Sprite wood_;
		sf::Sprite apple_;

		sf::Sprite invlog_;

		tree_.setTexture(*treeTexture);
		rock_.setTexture(*rockTexture);
		wood_.setTexture(*woodTexture);
		_dropable[0].setTexture(*fireTexture);
		_dropable[1].setTexture(*bedTexture);
		apple_.setTexture(*appleTexture);

		invlog_.setTexture(*InvLogTexture);

		tree_.setScale(sf::Vector2f(0.64, 0.64));
		rock_.setScale(sf::Vector2f(0.64, 0.64));
		wood_.setScale(sf::Vector2f(0.64, 0.64));
		_dropable[0].setScale(sf::Vector2f(0.64, 0.64));
		_dropable[1].setScale(sf::Vector2f(0.64, 0.64));
		apple_.setScale(sf::Vector2f(0.64, 0.64));

		invlog_.setScale(sf::Vector2f(0.64, 0.64));

		for (int i = 0; i < MapHeight; ++i)
		{
			for (int j = 0; j < MapWidth; ++j)
			{
				if (ResourceData[i][j] == 1)
				{
					Entity* temp = new Static(ResourceData[i][j] + 100, j * 64, i * 64, tree_);
					_allEntities.push_back(temp);
				}
				if (ResourceData[i][j] == 2)
				{
					Entity* temp = new Static(ResourceData[i][j] + 100, j * 64, i * 64, rock_);
					_allEntities.push_back(temp);
				}	
				if (ResourceData[i][j] == 3)
				{
					Entity* temp = new Interactable(ResourceData[i][j] + 200, j * 64, i * 64, wood_, "wood");
					_allEntities.push_back(temp);
				}
				if (ResourceData[i][j] == 4)
				{
					Entity* temp = new Interactable(ResourceData[i][j] + 200, j * 64, i * 64, apple_, "apple");
					_allEntities.push_back(temp);
				}
					
			}
		}
		return terrains;
	}

	vector<Entity*>* getAllEntities()
	{
		return &_allEntities;
	}

	vector< vector <int> > getTiles()
	{
		return tile_data;
	}

	sf::Sprite* getIcons()
	{
		return icons;
	}
	sf::Sprite* getBgs()
	{
		return bgs;
	}

	sf::Font* getFont()
	{
		return &OSD_MONO;
	}

	sf::Sprite* getDroppable()
	{
		return _dropable;
	}
};

