#include <vector>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class Map
{

	RenderWindow* window;
	Image image;
	Texture textur;
	
	struct Block
	{
		int x;
		int type;
		Sprite sprite;
	};

	Block block;
	

	
public:
	int count_blocks = 0;
	vector<Block> blocks;

	Map(RenderWindow* window) {
		this->window = window;
		
	}

	void load_blocks() {
		this->image.loadFromFile("sprites\\map.png");
		this->textur.loadFromImage(this->image);

		ifstream map_file("map.plat");
		map_file >> count_blocks;

		int prev_x = 0;

		for (int i = 0; i < count_blocks; i++) {
			this->blocks.insert(this->blocks.end(), this->block);
			map_file >> this->blocks[i].type;

			this->blocks[i].sprite.setTexture(this->textur);
			this->blocks[i].sprite.setTextureRect(IntRect(32 * this->blocks[i].type,0,32,32));

			int x;
			int y;
			map_file >> x;
			map_file >> y;

			x = x - 16;
			y = y - 16;

			this->blocks[i].sprite.setOrigin(16, 16);
			this->blocks[i].sprite.setPosition(x, y);

		}
		map_file.close();

		ifstream map_file_try("map.plat");
		map_file_try >> count_blocks;

		blocks[0].x = blocks[0].sprite.getPosition().x;

		for (int i = 0; i < count_blocks / 2; i++) {

			int x1;
			int y1;
			int type1;
			map_file_try >> type1;
			map_file_try >> x1;
			map_file_try >> y1;

			int type2;
			int x2;
			int y2;

			map_file_try >> type2;
			map_file_try >> x2;
			map_file_try >> y2;

			if (y1 == y2 && type1 == type2 && x1+32 == x2) {
				blocks[i+1].x = x1-16;
			}
			else {
				blocks[i + 1].x = blocks[i + 1].sprite.getPosition().x;
			}


		}

	}

	void draw() {
		for (int i = 0; i < this->blocks.size(); i++) {
			this->window->draw(this->blocks[i].sprite);
		}
	}
};


