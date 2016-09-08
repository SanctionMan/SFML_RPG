#include "LevelManager.h"



LevelManager::LevelManager(sf::Texture * texture):
	_tileSize(sf::Vector2i(64,32))
{
	_texture = texture;
}


LevelManager::~LevelManager()
{
}

void LevelManager::load(string path)
{
	//get level file info
	this->_filepath = path;

	//load the map data from file
	loadMapData();

	//setup map vertices for rendering
	setupMapVertices("layer1");
	setupMapVertices("layer2");

}

void LevelManager::render(sf::RenderWindow & _window)
{
	_window.draw(_vertices);
}

void LevelManager::printMap()
{
	cout << "Layer1" << endl;
	for (int i = 0; i < _mapSize.x; i++)
	{
		for (int j = 0; j < _mapSize.y; j++)
		{
			cout << _map[i][j];
		}
		cout << endl;
	}
	cout << "Layer2" << endl;
	for (int i = 0; i < _mapSize.x; i++)
	{
		for (int j = 0; j < _mapSize.y; j++)
		{
			cout << _layer2[i][j];
		}
		cout << endl;
	}
}

void LevelManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = _texture;

		// draw the vertex array
		target.draw(_vertices, states);
	}
}

void LevelManager::loadMapData()
{
	fstream file;
	file.open(_filepath, ios::in);
	if (file.fail())
	{	//Error
		cout << "Failed to load: " << _filepath << endl;
	}
	else
	{	//Load Data
		cout << "Loading map data: " << _filepath << endl;
		while (!file.eof())
		{
			//Create line buffer and get each line
			string type = "";
			string line = "";
			getline(file, line);

			//If line starts with '#' ignore that line
			if (line[0] == '#')
				continue;
			//If line starts with ' ' ignore that line
			if (line[0] == ' ')
				continue;
			//If line starts with "size" get data
			type = "size";
			if (line[0] == type[0] && line[1] == type[1] && line[2] == type[2])
			{
				cout << "Loading: " << line << endl;
				stringstream stream(line);
				string temp1 = "";
				char temp2 = '0';
				int x = 0; 
				int y = 0;
				stream >> temp1 >>  x >> temp2 >> y;

				_mapSize.x = x;
				_mapSize.y = y;
				continue;
			}
			
			//Get map data
			type = "| 0 | 1 | 2 |";
			if (line[0] == type[0] && line[1] == type[1] && (_isFloorLoaded == false))
			{
				stringstream stream(line);
				char ctemp;
				int num = 0;
				int x = 0;
				for (int j = 0; j < _mapSize.y; j++)
				{
					stream >> ctemp;
					stream >> num;
					_map[_lineNumber][x] = num;
					x++;
				}
				if (_lineNumber >= _mapSize.x - 1)
				{
					_lineNumber = 0;
					_isFloorLoaded = true;
					continue;
				}
			}

			//Get map data
			type = "| 0 | 1 | 2 |";
			if (line[0] == type[0] && line[1] == type[1] && (_isFloorLoaded == true))
			{
				stringstream stream(line);
				char ctemp;
				int num = 0;
				int x = 0;
				for (int j = 0; j < _mapSize.y; j++)
				{
					stream >> ctemp;
					stream >> num;
					_layer2[_lineNumber][x] = num;
					x++;
				}
				if (_lineNumber >= _mapSize.x - 1)
				{
					_lineNumber = 0;
				}
			}


			_lineNumber++;
		}
	}
	file.close();

}

bool LevelManager::loadMapLayers(string &line, string &type)
{
	if (line[0] == type[0] && line[4] == type[4] && line[8] == type[8])
	{
		stringstream stream(line);
		char ctemp;
		int num = 0;
		int x = 0;
		for (int j = 0; j < _mapSize.y; j++)
		{
			stream >> ctemp;
			stream >> num;
			_layer2[_lineNumber][x] = num;
			x++;
		}
		return true;
	}

	return false;
}

void LevelManager::setupMapVertices(string layers)
{
	//resize the vertex array to fit the level size
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(_mapSize.x * _mapSize.y * 4);

	// populate the vertex array, with one quad per tile
	for (int x = 0; x < _mapSize.x; x++)
	{
		for (int y = 0; y < _mapSize.y; y++)
		{
			// get the current tile number
			/*int tileNumber = *_map[x + y * _mapSize.x]; This is for single array map[20]*/
			//
			int tileNumber = 0;
			if (layers == "layer1")
			{
				tileNumber = _map[y][x];
			}
			else 
			{
				tileNumber = _layer2[y][x];
			}

			// find its position in the tileset texture
			int tu = tileNumber % (_texture->getSize().x / _tileSize.x);
			int tv = tileNumber / (_texture->getSize().x / _tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &_vertices[(x + y * _mapSize.x) * 4];
			if (layers == "layer1")
			{
				quad = &_vertices[(x + y * _mapSize.x) * 4];

			}
			else
			{
				quad = &_vertices2[(x + y * _mapSize.x) * 4];
			}


			// Find screen offset
			float tileWidthHalf = _tileSize.x / 2;
			float tileHeightHalf = _tileSize.y / 2;
			sf::Vector2f screenOffset = sf::Vector2f(0, _mapSize.y * tileHeightHalf);

			//Isometric adjustment for drawing in a diamond
			float diamond_x = (x * tileWidthHalf) - (y * tileWidthHalf);
			float diamond_y = (x * tileHeightHalf) + (y * tileHeightHalf);

			sf::Vector2f diamondOffSet = sf::Vector2f(-diamond_x, -diamond_y);

			sf::Vector2f topL = sf::Vector2f(x * _tileSize.x, y * _tileSize.y);
			sf::Vector2f topR = sf::Vector2f((x + 1) * _tileSize.x, y * _tileSize.y);
			sf::Vector2f bottomR = sf::Vector2f((x + 1) * _tileSize.x, (y + 1) * _tileSize.y);
			sf::Vector2f bottomL = sf::Vector2f(x * _tileSize.x, (y + 1) * _tileSize.y);

			// define its 4 corners with adjustments
			quad[0].position = topL + diamondOffSet + screenOffset;    //TL
			quad[1].position = topR + diamondOffSet + screenOffset;    //TR
			quad[2].position = bottomR + diamondOffSet + screenOffset; //BR
			quad[3].position = bottomL + diamondOffSet + screenOffset; //BL

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu *       _tileSize.x, tv *       _tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv *       _tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu *       _tileSize.x, (tv + 1) * _tileSize.y);
		}
	}
}
