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
bool touch(Player* player, Map* map, int* num, int height, int width) {
	int count = 0;
	for (int i = 0; i < map->blocks.size(); i++) {
		if (fabs(player->y - map->blocks[i].sprite.getPosition().y) <= (player->rect_height/2 + height) &&
			fabs(player->x - map->blocks[i].sprite.getPosition().x) <= (player->rect_width / 2 + width)) {
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
	if (touch && player->x < map->blocks[num].sprite.getPosition().x ) {
		if (player->y <= map->blocks[num].sprite.getPosition().y) {
			player->y = map->blocks[num].sprite.getPosition().y - player->rect_height / 2 - 16;
			cout << map->blocks[num].x << endl;
		}
		else if (player->y >= map->blocks[num].sprite.getPosition().y) {
			player->y = map->blocks[num].sprite.getPosition().y + player->rect_height / 2 + 16;
		}
	}
	if(touch && player->x + player->rect_width/2 +16 <= map->blocks[num].sprite.getPosition().x){
		if (touch && player->x < map->blocks[num].sprite.getPosition().x) {
			player->x = map->blocks[num].sprite.getPosition().x - player->rect_width / 2 - 16-1;
		}
		else if (touch) {

		}
	}

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
		bool istouch = touch(&player, &map, &num_block, 16, 16);
		//cout << istouch << endl;
		do_not_touch(&player, &map, istouch, num_block);
		

		map.draw();
		player.draw();

		window.display();
	}
	return 0;
}
