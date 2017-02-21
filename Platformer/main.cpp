#define RIGHT 1
#define LEFT  2
#define UP    3
#define DOWN  4

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Player.h"
#include "Map.h"

using namespace std;
using namespace sf;
bool check = true;

void do_not_touch(Player* player, Map* map, bool touch, int num) {
	if (touch) {
		int px = player->x;
		int py = player->y;
		int pH = player->rect_height;
		int pW = player->playerW;
		int dir_pl = player->direction;
		int mx = map->touch_r[num].rect.getPosition().x;
		int my = map->touch_r[num].rect.getPosition().y;
		int mH = map->touch_r[num].rect.getSize().y;
		int mW = map->touch_r[num].rect.getSize().x;

		int upline = my - mH / 2;
		int downline = my + mH / 2;
		int leftline = mx - mW / 2;
		int rightline = mx + mW / 2;


		if (dir_pl == RIGHT && px + pW/2 >= leftline && py + pH / 2 - 1 > upline && py - pH / 2 < downline) {
			//map->touch_r[num].rect.setFillColor(Color::Green);
			player->setPos(mx - mW / 2 - pW / 2 - 1, player->y);
		}
		else if (dir_pl == DOWN && py + pH/2 >= my - mH/2) {
			//map->touch_r[num].rect.setFillColor(Color::Blue);
			player->setPos(player->x, my - mH / 2 - pH / 2 );
		}
		else if (dir_pl == LEFT && px - pW / 2 <= rightline && py + pH / 2 - 1 > upline && py - pH / 2 < downline) {
			//map->touch_r[num].rect.setFillColor(Color::Cyan);
			player->setPos(mx + mW / 2 + pW / 2 + 1, player->y);
		}
		else if (dir_pl == UP && py - pH/2 <= my + mH/2) {
			//map->touch_r[num].rect.setFillColor(Color::Magenta);
			player->setPos(player->x, my + mH / 2 + pH / 2);
		}

		
	}

}
bool touch(Player* player, Map* map, int* num) {
	int count = 0;
	int s = 0;
	for (int i = 0; i < map->touch_r.size(); i++) {
		if (fabs(player->y - map->touch_r[i].rect.getPosition().y) <= (player->rect_height/2 + map->touch_r[i].rect.getSize().y/2) &&
			fabs(player->x - map->touch_r[i].rect.getPosition().x) <= (player->playerW/2 + map->touch_r[i].rect.getSize().x/2)) {
			count++;
			*num = i;
			s = i;
			
		}	
	}
	if (count > 0) {
		do_not_touch(player, map, true, s);
		return true;
		
	}
	else {
		return false;
	}
}



int main()
{
	RenderWindow window(VideoMode(1280, 800), "Platform-Game");
	Clock clock;
	float time;//время 
	window.setVerticalSyncEnabled(true);
	int sige = 0;
	Player player(&window);
	Map map(&window);
	map.load_blocks();

	int num_block = 0;
	cout << map.touch_r[0].rect.getSize().x << endl;

	//player.onGround = false;

	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}

		window.clear();
		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		player.update(time);
		bool istouch = touch(&player, &map, &num_block);
		

		//cout << istouch << endl;
		
		

		map.draw();
		player.draw();
		/*for (int i = 0; i < map.touch_r.size(); i++) {
			RectangleShape n_rect(Vector2f(5, 5));
			n_rect.setFillColor(Color::White);
			n_rect.setPosition(map.touch_r[i].rect.getPosition().x, map.touch_r[i].rect.getPosition().y);
			window.draw(n_rect);
		}
		RectangleShape pl_rect(Vector2f(5,5));
		pl_rect.setFillColor(Color::White);
		pl_rect.setPosition(player.x, player.y);
		window.draw(pl_rect);*/

		/*RectangleShape point_player(Vector2f(5,5));
		point_player.setFillColor(Color::Red);
		point_player.setPosition(map.touch_r[0].rect.getPosition().x - map.touch_r[0].rect.getSize().x/2 - 1, player.y);
		window.draw(point_player);*/

		window.display();
	}
	return 0;
}
