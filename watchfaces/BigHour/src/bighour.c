#include <pebble.h>
#include "default.h"

//UI
static Window *s_main_window;
static Layer *s_dt_layer;

//color
static GColor s_bg_color;
static GColor s_digit_color;

//function
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed);
static void minute_update_proc(Layer *layer, GContext *ctx);

//window load function
//create and initialize layers
static void main_window_load(Window *window) {
	//get window layer
	Layer *window_layer = window_get_root_layer(window);

	//create date & time layer
	s_dt_layer = layer_create(GRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	layer_set_update_proc(s_dt_layer, minute_update_proc);

	layer_add_child(window_layer, s_dt_layer);
}

//
static void minute_update_proc(Layer *layer, GContext *ctx) {
	//draw background
	graphics_context_set_fill_color(ctx, s_bg_color);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);

	//get time
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	//draw digit
	graphics_context_set_fill_color(ctx, s_digit_color);//date
	graphics_context_set_stroke_color(ctx, s_digit_color);//digit
	drawBigHour(t, ctx);
}

//update time every minute
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
	//mark dirty to update date & time layer
	layer_mark_dirty(s_dt_layer);
}

static void main_window_unload(Window *window) {
	// Destroy Layer
	layer_destroy(s_dt_layer);
}

//
static void init(void) {
	#ifdef PBL_COLOR
		s_digit_color = GColorFromRGB(rand() % 255, rand() % 255, rand() % 255);
		s_bg_color = GColorFromRGB(rand() % 255, rand() % 255, rand() % 255);
	#elif defined(PBL_BW)
		s_digit_color = GColorBlack;
		s_bg_color = GColorWhite;
	#endif

	//Create main Window
	s_main_window = window_create();
	window_set_background_color(s_main_window, s_bg_color);
	window_set_window_handlers(s_main_window, (WindowHandlers )
			{ .load = main_window_load, .unload = main_window_unload });

	window_stack_push(s_main_window, true);

	//run once per minute
	tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);

	// Prevent starting blank
	layer_mark_dirty(s_dt_layer);
}

static void deinit(void) {
	//Destroy main Window
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
