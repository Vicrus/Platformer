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
bool touch(Player* player, Map* map, int* num) {
	int count = 0;
	for (int i = 0; i < map->touch_r.size(); i++) {
		if (fabs(player->y - map->touch_r[i].rect.getPosition().y) <= (player->rect_height/2 + map->touch_r[i].rect.getSize().y/2) &&
			fabs(player->x - map->touch_r[i].rect.getPosition().x) <= (player->rect_width/2 + map->touch_r[i].rect.getSize().x/2)) {
			count++;
			*num = i;
			
		}	
	}
	if (count > 0) {
		return true;
		
	}
	else {
		return false;
	}
}

void do_not_touch(Player* player, Map* map, bool touch, int num) {


}
int main()
{
	RenderWindow window(VideoMode(1280, 800), "Platform-Game");
	Clock clock;
	float time;
	window.setVerticalSyncEnabled(true);
	int sige = 0;
	Player player(&window);
	Map map(&window);
	map.load_blocks();

	int num_block = 0;
	

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
		cout << istouch << endl;
		do_not_touch(&player, &map, istouch, num_block);
		

		map.draw();
		player.draw();

		window.display();
	}
	return 0;
}
