/* you may get a warning
* Libpng-1.6 is more stringent about checking ICC profiles than previous versions. You can ignore the warning. To get rid of it, remove the iCCP chunk from the PNG image.

Some applications treat warnings as errors; if you are using such an application you do have to remove the chunk. You can do that with any of a variety of PNG editors such as ImageMagick's convert in.png out.png.

To remove the invalid iCCP chunk from all of the PNG files in a folder (directory), you can use ImageMagick's mogrify *.png, provided that your ImageMagick was built with libpng16 (run convert -list format | grep PNG to be sure of that).
*/


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

int main(int argc, char** argv) {

	const float FPS = 60;
	const int SCREEN_W = 640;
	const int SCREEN_H = 480;
	const int duck_SIZE = 32;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	float duck_x = SCREEN_W / 2.0 - duck_SIZE / 2.0;
	float duck_y = SCREEN_H / 2.0 - duck_SIZE / 2.0;
	float duck_dx = -4.0, duck_dy = 4.0;
	bool redraw = true;
	ALLEGRO_BITMAP* image = NULL;
	ALLEGRO_BITMAP* duck = NULL;

	if (!al_init()) {
		return -1;
	}

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
	image = al_load_bitmap("cool.png");
	duck = al_load_bitmap("duck.png");
	al_convert_mask_to_alpha(duck, al_map_rgb(255, 0, 255));
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_destroy_bitmap(duck);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (duck_x < 0 || duck_x > SCREEN_W - duck_SIZE) {
				duck_dx = -duck_dx;
			}

			if (duck_y < 0 || duck_y > SCREEN_H - duck_SIZE) {
				duck_dy = -duck_dy;
			}

			duck_x += duck_dx;
			duck_y += duck_dy;

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(image, 0, 0, 0);
			al_draw_bitmap(duck, duck_x, duck_y, 0);

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