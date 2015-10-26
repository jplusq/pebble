#include <pebble.h>
#define NUM_SINGLE_LOG_LENGTH	60
#define MAX_NUM_ACCEL_SAMPLE  	15

Window *s_main_window;
TextLayer *s_text_layer;

char s_display_buffer[] = "RUNNING\r\nNUM: 99\r\nRATE: 999HZ";

char s_data_header[15] = "\0";	//#ACC#1234567890
char s_data_body[88] = "\0";	//999,-9999,-9999,-9999; 4 groups
uint64_t s_first_sample_tm = 0;

char s_running = 0;

int s_num_accel_sample = 8;
AccelSamplingRate s_sample_rate = ACCEL_SAMPLING_10HZ;

int s_sample_interval_ms = 100;
AppTimer *s_timer;

void showInfo() {
	snprintf(s_display_buffer, sizeof(s_display_buffer),
			"%s\r\nNUM: %d\r\nRATE: %dHZ", s_running ? "RUNNING" : "STOPPED",
			s_num_accel_sample, (int) 1000/s_sample_interval_ms);
	text_layer_set_text(s_text_layer, s_display_buffer);
}

void send_data(AccelData data) {
	//<CHAR 15>:<NUM 5><CHAR 87>
	char buff[30] = "\0";		//999,-9999,-9999,-9999,99999
	if (strlen(s_data_body) == 0) {
		//first sample
		s_first_sample_tm = data.timestamp;
		snprintf(s_data_header, sizeof(s_data_header), "#ACC#%u:",
				(int) (s_first_sample_tm % 10000000));
		snprintf(s_data_body, sizeof(s_data_body), "0,%d,%d,%d", data.x, data.y,
				data.z);
		return;
	}

	//build group
	snprintf(buff, sizeof(buff), "%d,%d,%d,%d",
			(int) (data.timestamp - s_first_sample_tm), data.x, data.y, data.z);

	//get current group length
	if (strlen(s_data_body) + strlen(buff) - 1 > NUM_SINGLE_LOG_LENGTH) {
		//output
		app_log(APP_LOG_LEVEL_INFO, s_data_header, 0, s_data_body);
		//new header
		s_first_sample_tm = data.timestamp;
		snprintf(s_data_header, sizeof(s_data_header), "#ACC#%u:",
				(int) (s_first_sample_tm % 10000000));
		//rebuild group
		snprintf(buff, sizeof(buff), "%d,%d,%d,%d",
				(int) (data.timestamp - s_first_sample_tm), data.x, data.y,
				data.z);
		//new first group
		strcpy(s_data_body, buff);
	} else {
		//add group
		strcat(s_data_body, ";");
		strcat(s_data_body, buff);
	}
}

void flush() {
	if (strlen(s_data_body) != 0) {
		app_log(APP_LOG_LEVEL_INFO, s_data_header, 0, s_data_body);
		//new header
		strcpy(s_data_body, "\0");
	}
}

//accelerometer data handler
static void accel_data_handler(AccelData *data, uint32_t num_samples) {
	int i;
	for (i = 0; i < (int) num_samples; i++) {
		//send_data(data[i], NULL);
	}
}

static void accel_timer_callback() {
	AccelData data = (AccelData ) { .x = 0, .y = 0, .z = 0 };
	accel_service_peek(&data);
	send_data(data);
	s_timer = app_timer_register(s_sample_interval_ms, accel_timer_callback,
			NULL);
}

void run() {
	//accel_data_service_subscribe(s_num_accel_sample, accel_data_handler);
	//accel_service_set_sampling_rate(s_sample_rate);
	accel_data_service_subscribe(0, NULL);
	s_timer = app_timer_register(s_sample_interval_ms, accel_timer_callback,
			NULL);
	s_running = 1;
}

void stop() {
	//accel_data_service_unsubscribe();
	//cancel timer
	app_timer_cancel(s_timer);
	flush();
	s_running = 0;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	if (s_running) {
		stop();
	} else {
		run();
	}
	showInfo();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	stop();
	if (s_num_accel_sample >= MAX_NUM_ACCEL_SAMPLE) {
		s_num_accel_sample = 1;
	} else {
		s_num_accel_sample++;
	}
	showInfo();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	stop();
	/*
	switch (s_sample_rate) {
	case ACCEL_SAMPLING_10HZ:
		s_sample_rate = ACCEL_SAMPLING_25HZ;
		break;
	case ACCEL_SAMPLING_25HZ:
		s_sample_rate = ACCEL_SAMPLING_50HZ;
		break;
	case ACCEL_SAMPLING_50HZ:
		s_sample_rate = ACCEL_SAMPLING_100HZ;
		break;
	case ACCEL_SAMPLING_100HZ:
		s_sample_rate = ACCEL_SAMPLING_10HZ;
		break;
	}*/
	if(s_sample_interval_ms == 100){
		s_sample_interval_ms = 10;
	}else{
		s_sample_interval_ms+=10;
	}

	showInfo();
}

static void click_config_provider(void *context) {
	// Register the ClickHandlers
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void init(void) {
	s_main_window = window_create();

	//info layer
	s_text_layer = text_layer_create(GRect(0, 0, 144, 154));
	text_layer_set_font(s_text_layer,
			fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	layer_add_child(window_get_root_layer(s_main_window),
			text_layer_get_layer(s_text_layer));
	showInfo();

	//register key event
	window_set_click_config_provider(s_main_window, click_config_provider);
	window_stack_push(s_main_window, true);
	app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);

	//send init
	app_log(APP_LOG_LEVEL_INFO, "INIT", 0, "INIT");
}

void handle_deinit(void) {
	app_comm_set_sniff_interval(SNIFF_INTERVAL_NORMAL);
	accel_data_service_unsubscribe();
	text_layer_destroy(s_text_layer);
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	handle_deinit();
}
