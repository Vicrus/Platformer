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
	struct Rect_
	{
		RectangleShape rect;

	};

	Block block;
	

	
public:
	int count_blocks = 0;
	vector<Block> blocks;
	vector<Rect_> touch_r;

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

			x = x + 16;
			y = y + 16;

			this->blocks[i].sprite.setOrigin(16, 16);
			this->blocks[i].sprite.setPosition(x, y);

		}
		map_file.close();
		
		ifstream touch_file("touch.plat");
		touch_file >> count_blocks;

		for (int i = 0; i < count_blocks; i++) {
			Rect_ buff_rect;
			int x, y, w, h;
			touch_file >> x;
			touch_file >> y;
			touch_file >> w;
			touch_file >> h;

			x = x + w / 2;
			y = y + h / 2;

			buff_rect.rect.setFillColor(Color::Red);
			buff_rect.rect.setSize(Vector2f(w,h));
			buff_rect.rect.setOrigin(w / 2, h / 2);
			buff_rect.rect.setPosition(x,y);
			touch_r.push_back(buff_rect);

		}
		touch_file.close();
	}

	void draw() {
		for (int i = 0; i < this->blocks.size(); i++) {
			this->window->draw(this->blocks[i].sprite);
		}
		/*for (int i = 0; i < this->touch_r.size(); i++) {
			this->window->draw(touch_r[i].rect);
		}*/
	}
};


