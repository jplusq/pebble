#include <pebble.h>
#include <default.c>

#define DATE_BAR_HEIGHT 24

//UI
static Window *s_main_window;
static Layer *s_date_layer;
static Layer *s_time_layer;
static GRect s_window_bounds;

//function
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed);
static void date_update_proc(Layer *layer, GContext *ctx);
static void time_update_proc(Layer *layer, GContext *ctx);

//window load function
//create and initialize layers
static void main_window_load(Window *window) {
	//get window layer
	Layer *window_layer = window_get_root_layer(window);

	//get window size
	s_window_bounds = layer_get_bounds(window_layer);

	//create date layer
	s_date_layer = layer_create(GRect(0, 0, s_window_bounds.size.w, DATE_BAR_HEIGHT));
	layer_set_update_proc(s_date_layer, date_update_proc);

	//create time layer
	s_time_layer = layer_create(
			GRect(0, DATE_BAR_HEIGHT, s_window_bounds.size.w, s_window_bounds.size.h - DATE_BAR_HEIGHT));
	layer_set_update_proc(s_time_layer, time_update_proc);

	//add layers for display
	//the layer added early will be cover
	layer_add_child(window_layer, s_time_layer);
	layer_add_child(window_layer, s_date_layer);
}

//draw date bar
static void date_update_proc(Layer *layer, GContext *ctx) {
	//draw background
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);

	//get time
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	//draw week and date
	graphics_context_set_fill_color(ctx, GColorBlack);
	draw_date(t, ctx, s_window_bounds.size.w);

}

//
static void time_update_proc(Layer *layer, GContext *ctx) {
	//draw background
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);

	//get time
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	//draw digit
	graphics_context_set_stroke_color(ctx, GColorBlack);
	draw_time(t, ctx);
}

//update time every minute
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {

	//mark dirty to update date layer
	layer_mark_dirty(s_date_layer);

	//mark dirty to update time layer
	layer_mark_dirty(s_time_layer);
}

static void main_window_unload(Window *window) {
	// Destroy Layer
	layer_destroy(s_date_layer);
	//layer_destroy(s_white_layer);
	layer_destroy(s_time_layer);
}

//
static void init(void) {
	//Create main Window
	s_main_window = window_create();
	window_set_background_color(s_main_window, GColorWhite);
	window_set_window_handlers(s_main_window, (WindowHandlers )
			{ .load = main_window_load, .unload = main_window_unload });

	window_stack_push(s_main_window, true);

	//run once per minute
	tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);

	// Prevent starting blank
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	handle_minute_tick(t, MINUTE_UNIT);
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
