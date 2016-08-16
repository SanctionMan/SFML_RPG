#include "TileParser.h"

TileParser::TileParser()
{
}


TileParser::~TileParser()
{
}

bool TileParser::Init(string file)
{
	fstream stream(file, ios::binary | ios::in);
	if(stream.good())
	{
		fileContents = "";
		while(!stream.eof())
		{
			string line = "";
			std::getline(stream, line);
			if(line[0] != '#')
			{
				fileContents += line + "\n";
			}
		}
		cout << fileContents << endl;
		stream.close();
		return true;
	}else
	{
		cout << "Map file " << file << " does not exist! Please contact Matt you dumbass!" << endl;
		stream.close();
		return false;
	}
}

bool TileParser::Parse()
{
	stringstream stream;
	stream << fileContents;
	
	bool hitTextures = false;
	bool hitTypes = false;

	int currentMarker = 0;
	std::pair<int, Tile*> tilePair;
	string convert = "";
	int texID = 0;
	bool hitBracket = false;

	vector<string> allLines;

	while(!stream.eof())
	{
		string line = "";
		getline(stream, line);
		allLines.push_back(line);
	}

	//Read the lines
	for (int currentLine = 0; currentLine < allLines.size(); currentLine++)
	{
		string line = allLines.at(currentLine);

		currentMarker = 0;
		size_t found = line.find("textures:");
		if (found != std::string::npos)
		{
			hitTextures = true;
			hitTypes = false;
		}

		found = line.find("types:");
		if (found != std::string::npos)
		{
			hitTextures = false;
			hitTypes = true;
		}

		if (hitTextures)
		{
			for (int x = 0; x < line.length(); x++)
			{
				char c = line[x];
				switch (c)
				{
				case '[':
					hitBracket = true;
					break;
				case ']':
					hitBracket = false;
					break;
				default:
					if (hitBracket)
						convert += c;
						//texID = std::stoi(convert);
						int a = (currentLine == 0) ? 0 : 1;
						Tile* currentTile = new Tile(NULL, sf::Vector2f(50 * (currentMarker), 50 * (currentLine - a)));
						tilePair = std::pair<int, Tile*>(currentMarker, currentTile);
						currentTile->_tile.setTexture(textureManager->getTexture(texID));
						currentMarker += 1;
						//do last
						convert = "";
						texID = 0;
						tileID.insert(tilePair);
					}
					break;
				};
			}
		}
	return false;
}





Tile::Tile(sf::Texture* texture, sf::Vector2f position)
{
	_position = position;

	_tile.setTexture(texture);
	_tile.setPosition(sf::Vector2f(_position.x, _position.y));
	//_tile.setOrigin(sf::Vector2f(_tile.getGlobalBounds().height / 2, _tile.getGlobalBounds().width / 2));
	_tile.setSize(sf::Vector2f(50, 50));
}


Tile::~Tile()
{
}

void Tile::render(sf::RenderWindow & _window)
{
	_window.draw(_tile);
}

void Tile::processEvents(sf::Event & event)
{
	// Nothing at this point in time
}
