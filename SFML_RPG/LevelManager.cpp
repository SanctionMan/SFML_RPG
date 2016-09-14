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

	//setup floor vertices for rendering
	//int **p_mapArray[10][10];


	setupMapVertices(_floor, _floorVertices);

	//setup layer 1 vertices for rendering;
	
	setupMapVertices(_layer1, _layer1Vertices);

}

void LevelManager::update(sf::Time _deltaTime)
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*GetGameWindow()));
	sf::Vector2f newMousePosition = GetGameWindow()->mapPixelToCoords(sf::Vector2i(mousePos.x, mousePos.y), GetGameWindow()->getView());
	mousePos = sf::Vector2f(newMousePosition.x, newMousePosition.y);

	cout << "X: " << mousePos.x << " Y: " << mousePos.y << endl;
	//quad[0].position = topL + diamondOffSet + screenOffset;    //TL
	//quad[1].position = topR + diamondOffSet + screenOffset;    //TR
	//quad[2].position = bottomR + diamondOffSet + screenOffset; //BR
	//quad[3].position = bottomL + diamondOffSet + screenOffset; //BL
	sf::Vertex* quad = &_floorVertices[0];
	for (int x = 0; x < _mapSize.x; x++)
	{
		for (int y = 0; y < _mapSize.y; y++)
		{
			quad = &_floorVertices[(x + y * _mapSize.x) * 4];

			if(mousePos.x >= quad[0].position.x && mousePos.x <= quad[1].position.x &&
				mousePos.y >= quad[0].position.y && mousePos.y <= quad[2].position.y)
			{
				quad[0].color = sf::Color::Red;
				quad[1].color = sf::Color::Red;
				quad[2].color = sf::Color::Red;
				quad[3].color = sf::Color::Red;
			}
			else
			{
				if(quad[0].color != sf::Color::Transparent)
				{
					quad[0].color = sf::Color::White;
					quad[1].color = sf::Color::White;
					quad[2].color = sf::Color::White;
					quad[3].color = sf::Color::White;	
				}
			}
		}
	}


}

void LevelManager::renderFloor(sf::RenderWindow &_window)
{
	_window.draw(_floorVertices, _texture);
}

void LevelManager::renderLayer1(sf::RenderWindow& _window)
{
	_window.draw(_layer1Vertices, _texture);
}

void LevelManager::printMap()
{
	cout << "_floor" << endl;
	for (int i = 0; i < _mapSize.x; i++)
	{
		for (int j = 0; j < _mapSize.y; j++)
		{
			cout << _floor[i][j];
		}
		cout << endl;
	}
	cout << "_layer1" << endl;
	for (int i = 0; i < _mapSize.x; i++)
	{
		for (int j = 0; j < _mapSize.y; j++)
		{
			cout << _layer1[i][j];
		}
		cout << endl;
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
					_floor[_lineNumber][x] = num;
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
					_layer1[_lineNumber][x] = num;
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
			_layer1[_lineNumber][x] = num;
			x++;
		}
		return true;
	}

	return false;
}

template <size_t rows, size_t cols>
void LevelManager::setupMapVertices(int (&_mapArray)[rows][cols], sf::VertexArray &_vertexArray)
{
	//resize the vertex array to fit the level size
	_vertexArray.setPrimitiveType(sf::Quads);
	_vertexArray.resize(_mapSize.x * _mapSize.y * 4);

	// populate the vertex array, with one quad per tile
	for (int x = 0; x < _mapSize.x; x++)
	{
		for (int y = 0; y < _mapSize.y; y++)
		{
			// get the current tile number
			int tileNumber = _mapArray[x][y];
			if (tileNumber > 0)
			{
				tileNumber - 1;
			}

			// find its position in the tileset texture
			int tu = tileNumber % (_texture->getSize().x / _tileSize.x);
			int tv = tileNumber / (_texture->getSize().x / _tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &_vertexArray[(x + y * _mapSize.x) * 4];

			// Find screen offset
			float tileWidthHalf = _tileSize.x / 2;
			float tileHeightHalf = _tileSize.y / 2;
			sf::Vector2f screenOffset = sf::Vector2f(_mapSize.x * tileWidthHalf, 0);

			//Isometric adjustment for drawing in a diamond
			//float diamond_x = (x - y) * tileWidthHalf;
			//float diamond_y = (x + y) * tileHeightHalf;
			float diamond_x = (x * tileWidthHalf) + (y * tileWidthHalf);
			float diamond_y = (y * tileHeightHalf) - (x * tileHeightHalf);

			//sf::Vector2f diamondOffSet = sf::Vector2f(-diamond_x, -diamond_y);
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

			if (tileNumber > 0)
			{
				quad[0].texCoords = sf::Vector2f(tu *       _tileSize.x, tv *       _tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv *       _tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu *       _tileSize.x, (tv + 1) * _tileSize.y);
			}
			else
			{
				quad[0].texCoords = sf::Vector2f(1 * _tileSize.x, 1 * _tileSize.y);
				quad[1].texCoords = sf::Vector2f((1 + 1) * _tileSize.x, 1 * _tileSize.y);
				quad[2].texCoords = sf::Vector2f((1 + 1) * _tileSize.x, (1 + 1) * _tileSize.y);
				quad[3].texCoords = sf::Vector2f(1 * _tileSize.x, (1 + 1) * _tileSize.y);

				quad[0].color = sf::Color::Transparent;
				quad[1].color = sf::Color::Transparent;
				quad[2].color = sf::Color::Transparent;
				quad[3].color = sf::Color::Transparent;

			}

		}
	}
}
