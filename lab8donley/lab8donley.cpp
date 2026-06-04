/* you may get a warning
* Libpng-1.6 is more stringent about checking ICC profiles than previous versions. You can ignore the warning. To get rid of it, remove the iCCP chunk from the PNG image.

Some applications treat warnings as errors; if you are using such an application you do have to remove the chunk. You can do that with any of a variety of PNG editors such as ImageMagick's convert in.png out.png.

To remove the invalid iCCP chunk from all of the PNG files in a folder (directory), you can use ImageMagick's mogrify *.png, provided that your ImageMagick was built with libpng16 (run convert -list format | grep PNG to be sure of that).
*/


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {

	const float FPS = 60;
	const int SCREEN_W = 900;
	const int SCREEN_H = 800;
	const int duck_SIZE = 32;
	int flag = 0;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	bool dontmove = false;
	float duck_x = SCREEN_W / 2.0 - duck_SIZE / 2.0;
	float duck_y = SCREEN_H / 2.0 - duck_SIZE / 2.0;
	float duck_dx = -4.0, duck_dy = 4.0;
	bool redraw = true;
	ALLEGRO_BITMAP* image = NULL;
	ALLEGRO_BITMAP* duck = NULL;

	if (!al_init()) {
		return -1;
	}
	al_install_keyboard();
	

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		al_destroy_timer(timer);
		return -1;
	}



	al_init_image_addon();
	image = al_load_bitmap("screenshot.png");
	int shotW = al_get_bitmap_width(image);
	int shotH = al_get_bitmap_height(image);

	
	//image.setScale(-1.0f, 1.0f)
	duck = al_load_bitmap("kirby0.png");
	//ALLEGRO_BITMAP* duck = al_create_sub_bitmap(ducks, 150, 0, 220, 210);
	al_convert_mask_to_alpha(duck, al_map_rgb(255, 0, 255));
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_destroy_bitmap(duck);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				//duck_x = duck_x;
				//duck_y = duck_y;
				dontmove = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
				//cout << "Pressed left key";
				flag = ALLEGRO_FLIP_HORIZONTAL;
				
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				//cout << "Pressed down key";
				flag = 3;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
				//cout << "Pressed up key";
				flag = 4;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				//cout << "Pressed right key";
				flag = 0;
			}
		}
		
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			int angle = 0;
			if (dontmove) {
				duck_x = duck_x;
				duck_y = duck_y;
			}
			else {
				if (duck_x < 0 || duck_x > SCREEN_W - duck_SIZE) {
					//if (duck_dx == 0 && angle<3)
					duck_dx = -duck_dx;
				}

				if (duck_y < 0 || duck_y > SCREEN_H - duck_SIZE) {
					duck_dy = -duck_dy;
				}

				duck_x += duck_dx;
				duck_y += duck_dy;
			}
			redraw = true;
		}
		
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_bitmap(image, 0, 0, 0);
			al_draw_scaled_bitmap(image, 0, 0, shotW, shotH, 0, 0, SCREEN_W, SCREEN_H, 0);
			if (flag == 4) {
				al_draw_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y, 3*ALLEGRO_PI/2, 0);
			}
			else if (flag == 3) {
				al_draw_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y, ALLEGRO_PI/2, 0);
			}
			else {
				al_draw_bitmap(duck, duck_x, duck_y, flag);
			}
			

			al_flip_display();
		}
	}

	al_destroy_bitmap(duck);
	al_destroy_bitmap(image);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	system("pause");
	return 0;
}