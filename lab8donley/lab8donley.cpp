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
	bool turningRight=false, turningLeft=true, goingUp=false, goingDown=false;
	int flag = 0;
	float curAngle =3.14;
	float destAngle = 0;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	bool dontmove = false;
	bool currentlyturning = false;
	float turned = 0.0;
	float duck_x = SCREEN_W / 2.0 - duck_SIZE / 2.0;
	float duck_y = SCREEN_H / 2.0 - duck_SIZE / 2.0;
	float duck_dx = 4.0, duck_dy = 4.0;
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
	duck = al_load_bitmap("turtle.png");
	al_convert_mask_to_alpha(duck, al_map_rgb(255, 255, 255));
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
				//flag = ALLEGRO_FLIP_HORIZONTAL;
				turningRight = false;
				turningLeft = true;
				goingUp = false;
				goingDown = false;
				
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				//cout << "Pressed right key";
				//flag = 0;
				turningRight = true;
				turningLeft = false;
				goingUp = false;
				goingDown = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				//cout << "Pressed down key";
				//flag = 3;
				turningRight = false;
				turningLeft = false;
				goingUp = false;
				goingDown = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
				//cout << "Pressed up key";
				//flag = 4;
				turningRight = false;
				turningLeft = false;
				goingUp = true;
				goingDown = false;

			}
			
		}
		
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			//int angle = 0;
			
			if (dontmove) {
				duck_x = duck_x;
				duck_y = duck_y;
			}
			
			if (duck_x <= 100 || duck_x >= SCREEN_W-100) {
				//destAngle = curAngle - ALLEGRO_PI;
				currentlyturning = true;
				dontmove = true;
				//duck_dx = -duck_dx;
				
			}

			if (duck_y < 100 || duck_y > SCREEN_H - duck_SIZE*3) {
				//angle = curAngle + ALLEGRO_PI;
				// destAngle = 0;
				currentlyturning = true;
				dontmove = true;
				//duck_dy = -duck_dy;
			}	
			if (currentlyturning) {
				if (turningLeft) {
					if (curAngle >= destAngle) {
						//if (turningLeft) {
						curAngle -= 0.05f;
						//}

						if (curAngle <= destAngle) {
							curAngle = destAngle;
							dontmove = false;
							currentlyturning = false;
							if (turningRight) {
								turningRight = false;
								turningLeft = true;
							}
							else if (turningLeft) {
								turningRight = true;
								turningLeft = false;
							}
							else if (goingUp) {
								goingUp = false;
								goingDown = true;
							}
							else if (goingDown) {
								goingDown = false;
								goingUp = true;
							}
						}
					}
				}
				else {
					if (curAngle <= 3.14) {
						//if (turningLeft) {
						curAngle += 0.05f;
						//}

						if (curAngle >= 3.14) {
							curAngle = 3.14;
							dontmove = false;
							currentlyturning = false;
							if (turningRight) {
								turningRight = false;
								turningLeft = true;
							}
							else if (turningLeft) {
								turningRight = true;
								turningLeft = false;
							}
							else if (goingUp) {
								goingUp = false;
								goingDown = true;
							}
							else if (goingDown) {
								goingDown = false;
								goingUp = true;
							}
						}
					}
				}

			}
			
			if (dontmove) {

			} else if (turningRight) {
				duck_x += duck_dx;
				duck_y = duck_y;
				//curAngle = 0;
				//goingUp = false;
				//goingDown = false;
				//turningRight = false;
				//turningLeft = true;
			}
			else if (turningLeft){
				duck_x -= duck_dx;
				duck_y = duck_y;
				//curAngle = 0;
				//goingUp = false;
				//goingDown = false;
				//turningRight = true;
				//turningLeft = false;
			}
			else if (goingUp) {
				duck_x = duck_x;
				duck_y -= duck_dy;
				//curAngle = 0;
				//goingUp = true;
				//goingDown = false;
				//turningRight = false;
				//turningLeft = false;
			}
			else if (goingDown) {
				duck_x = duck_x;
				duck_y += duck_dy;
				//curAngle = 0;
				//goingUp = false;
				//goingDown = true;
				//turningRight = false;
				//turningLeft = false;
					
			}
			//duck_x += duck_dx;
			//duck_y += duck_dy;		
			
			redraw = true;
		}
		
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (redraw) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_bitmap(image, 0, 0, 0);
			al_draw_scaled_bitmap(image, 0, 0, shotW, shotH, 0, 0, SCREEN_W, SCREEN_H, 0);
			if (curAngle != 0 && curAngle != destAngle) {
				al_draw_scaled_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y+50, 0.3, 0.3,  curAngle, 3);
			}
			else {
				if (goingUp) {
					al_draw_scaled_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y, 0.3, 0.3,ALLEGRO_PI/2, 0);
				}
				else if (goingDown) {
					al_draw_scaled_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y, 0.3, 0.3, ALLEGRO_PI*3/2, 0);
				}
				else if (turningLeft) {
					al_draw_scaled_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y, 0.3, 0.3, ALLEGRO_PI*2, 0);
				}
				else if (turningRight) {
					al_draw_scaled_rotated_bitmap(duck, al_get_bitmap_width(duck) / 2.0, al_get_bitmap_height(duck) / 2.0, duck_x, duck_y, 0.3, 0.3, ALLEGRO_PI, 0);
				}
				//al_draw_scaled_bitmap(duck, 0, 0, shotW, shotH, duck_x, duck_y, shotW / 3, shotH / 3, ALLEGRO_FLIP_HORIZONTAL);
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