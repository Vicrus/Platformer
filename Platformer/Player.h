#include <SFML/Graphics.hpp>


#define RIGHT 1
#define LEFT  2
#define UP    3
#define DOWN  4

#define DOWN_LEFT  5
#define DOWN_RIGHT 6
#define UP_LEFT    7
#define UP_RIGHT   8

using namespace sf;
using namespace std;

class Player
{
	RenderWindow* window;
	Image player_img;
	Texture player_tex;
	Sprite player;

	const int step_player = 30;
	int step_check = 0;

	
	int tex_x = 0;
	int tex_y = 165;

	int prev_y = 0;

	int count = 0;
	
public:
	int x = 100;
	int y = 100;
	int rect_height = 62;
	int rect_width = 52;
	int playerH = rect_height;
	int playerW = rect_width - rect_width / 2;
	int direction = 0;

	int gravity_time = 0;
	bool gravity_on = false;

	sf::RectangleShape rectangle;

	Player(RenderWindow* window) {
		this->window = window;
		load_img();
		this->player.setOrigin(rect_width/2, rect_height/2);
		setPos(this->x, this->y);
	}
	
	void load_img() {
		this->player_img.loadFromFile("sprites\\player.png");
		this->player_tex.loadFromImage(player_img);
		this->player.setTexture(player_tex);
		this->player.setTextureRect(IntRect(tex_x,tex_y,rect_width, rect_height));
		
	}

	void jump(float time) {
			direction = UP;
			this->y -= time* 0.6;
			setPos(this->x, this->y);
			gravity_time++;
	}

	void update(float time) {

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			direction = DOWN;
			this->tex_y = 12;
			this->y += time*0.3;
			step(time);	
		}

		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (gravity_on) {
				direction = DOWN_RIGHT;
			}
			else {
				direction = RIGHT;
			}
			this->tex_y = 165;
			this->x += time*0.3;
			step(time);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (gravity_on) {
				direction = DOWN_LEFT;
			}
			else {
				direction = LEFT;
			}
			this->tex_y = 90;
			this->x -= time*0.3;
			step(time);
		}
		else {
			//direction = RIGHT;
			count = 4;
		}
		
		setPos(this->x, this->y);
		
	}


	void setPos(int x, int y) {
		
		playerRect(false, x,y);
		this->x = x;
		this->y = y;
		this->player.setPosition(this->x, this->y);
		if (this->count>3) {
			count = 0;
			this->tex_x = 0;
		}
		this->player.setTextureRect(IntRect(tex_x, tex_y, rect_width, rect_height));
	}

	void draw() {
		this->window->draw(rectangle);
		this->window->draw(player);

		
	}

	void step(int time) {
		if (step_check >= step_player) {
			this->step_check = 0;
			this->count++;
			this->tex_x += rect_width;
		}
		else{
			
			this->step_check += time*0.3;
		}
		
	}

	void playerRect(bool ison, int x, int y) {
		if (ison) {
			rectangle.setSize(sf::Vector2f(playerW, playerH));
			rectangle.setFillColor(Color::Transparent);
			rectangle.setOutlineColor(sf::Color::Red);
			rectangle.setOutlineThickness(1);
			rectangle.setOrigin(playerW / 2, playerH / 2);
			rectangle.setPosition(x, y);
		}
	}
};


