#include "Level.h"



Level::Level(sf::Texture * texture):
	_tileSize(sf::Vector2u(64,32))
{
	_texture = texture;
}


Level::~Level()
{
}

void Level::load(string path, sf::Vector2i size, const int* tiles)
{
	fstream file;
	file.open(path, ios::in);
	if (file.fail())
	{
		cout << "Failed to load: " << path << endl;
	}
	else 
	{
		int lineNumber = 0;
		int skipNumber = 0;
		while (!file.eof())
		{
			string line;
			getline(file, line);
			if (line[0] == '#')
				continue;

			for (int i = 0; i < line.length(); i++)
			{
				//cout << line[i];
				switch (line[i])
				{
				case '[':
					skipNumber++;
					break;
				case ']':
					skipNumber++;
					break;
				default:
					_map[lineNumber][i - skipNumber] = ((int)line[i] - 48);
					/*cout << ((int)line[i] - 48);*/
					break;
				}
			}
			skipNumber = 0;
			lineNumber++;
			/*cout << endl;*/
		}
	}
	file.close();

	_mapSize = size;
	//resize the vertex array to fit the level size
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(_mapSize.x * _mapSize.y * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int x = 0; x < _mapSize.x; x++)
	{
		for (unsigned int y = 0; y < _mapSize.y; y++)
		{
			// get the current tile number
			int tileNumber = tiles[x + y * _mapSize.x];

			// find its position in the tileset texture
			int tu = tileNumber % (_texture->getSize().x / _tileSize.x);
			int tv = tileNumber / (_texture->getSize().x / _tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &_vertices[(x + y * _mapSize.x) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(x *       _tileSize.x, y *       _tileSize.y);//TL   0,0   32,16
			quad[1].position = sf::Vector2f((x + 1) * _tileSize.x, y *       _tileSize.y);//TR  64,0   
			quad[2].position = sf::Vector2f((x + 1) * _tileSize.x, (y + 1) * _tileSize.y);//BR  64,32
			quad[3].position = sf::Vector2f(x *       _tileSize.x, (y + 1) * _tileSize.y);//BL   0,32

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu *       _tileSize.x, tv *       _tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv *       _tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu *       _tileSize.x, (tv + 1) * _tileSize.y);
		}
	}

}

void Level::render(sf::RenderWindow & _window)
{
	_window.draw(_vertices);
}

void Level::printMap()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << _map[i][j];
		}
		cout << endl;
	}
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
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
