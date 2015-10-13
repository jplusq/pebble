#include "default.h"

static int get_hour(struct tm* t) {
	if (clock_is_24h_style() == true)
		return t->tm_hour;

	return t->tm_hour <= 12 ? t->tm_hour : t->tm_hour - 12;
}

static void put_pixel(void* ctx, int x, int y, int minuteY) {
	if (y < minuteY && (x + y) % 2 == 0) {
		graphics_draw_pixel(ctx, GPoint(x, y));
	} else if (y >= minuteY) {
		graphics_draw_pixel(ctx, GPoint(x, y));
	}
}

/*
 * set horizontal stroke in matrix
 */
static void put_horizontl_stroke(int x, int y, GContext* ctx, int segWidth, int mintueY, char isVMiddle) {
	int segX, hSegCount, hPixelCount, vPixelCount, vPixelNum;
	vPixelNum = isVMiddle ? SEG_HEIGHT + 1 : SEG_HEIGHT;
	//horizontal segment
	for (hSegCount = 0; hSegCount < H_STROKE_SEG_NUM; hSegCount++) {
		//segment left top x position
		segX = x + (segWidth + SEG_SPACING) * hSegCount;
		for (hPixelCount = 0; hPixelCount < segWidth; hPixelCount++) {
			for (vPixelCount = 0; vPixelCount < vPixelNum; vPixelCount++) {
				//current position
				if (isVMiddle && y + vPixelCount == H_MIDDLE_STROKE_SPLIT_Y) {
					vPixelCount++;
				}
				put_pixel(ctx, segX + hPixelCount, y + vPixelCount, mintueY);
			}
		}
	}
}

/*
 * set vertical stroke in matrix
 */
static void put_vertical_stroke(int x, int y, GContext* ctx, int segWidth, int mintueY) {
	int segY, vSegCount, hPixelCount, vPixelCount;
	//vertical segment
	for (vSegCount = 0; vSegCount < V_STROKE_SEG_NUM; vSegCount++) {
		//segment left top y position
		segY = y + (SEG_HEIGHT + SEG_SPACING) * vSegCount;
		for (hPixelCount = 0; hPixelCount < segWidth; hPixelCount++) {
			for (vPixelCount = 0; vPixelCount < SEG_HEIGHT; vPixelCount++) {
				//current position
				put_pixel(ctx, x + hPixelCount, segY + vPixelCount, mintueY);
			}
		}
	}
}
/*
 * pub stroke stroke in matrix
 */
static void put_stroke(Stroke stroke, int digitX, GContext* ctx, int segWidth, int mintueY) {
	int strokeX;
	if (stroke == StrokeA) {
		//A
		strokeX = digitX;
		put_horizontl_stroke(strokeX, H_TOP_STROKE_Y, ctx, segWidth, mintueY, 0);
	} else if (stroke == StrokeB) {
		//B
		strokeX = digitX + (segWidth + SEG_SPACING) * (V_STROKE_SEG_NUM - 1);
		put_vertical_stroke(strokeX, V_UP_STROKE_Y, ctx, segWidth, mintueY);
	} else if (stroke == StrokeC) {
		//C
		strokeX = digitX + (segWidth + SEG_SPACING) * (V_STROKE_SEG_NUM - 1);
		put_vertical_stroke(strokeX, V_DOWN_STROKE_Y, ctx, segWidth, mintueY);
	} else if (stroke == StrokeD) {
		//D
		strokeX = digitX;
		put_horizontl_stroke(strokeX, H_BOTTOM_STROKE_Y, ctx, segWidth, mintueY, 0);
	} else if (stroke == StrokeE) {
		//E
		strokeX = digitX;
		put_vertical_stroke(strokeX, V_DOWN_STROKE_Y, ctx, segWidth, mintueY);
	} else if (stroke == StrokeF) {
		strokeX = digitX;
		put_vertical_stroke(strokeX, V_UP_STROKE_Y, ctx, segWidth, mintueY);
	} else if (stroke == StrokeG) {
		strokeX = digitX;
		put_horizontl_stroke(strokeX, H_MIDDLE_STROKE_Y, ctx, segWidth, mintueY, 1);
	}
}
/*
 * pub digit stroke in matrix
 */
static void put_digit(int digit, GContext* ctx, int digitX, int segWidth, int mintueY) {
	//A
	if (digit != 1 && digit != 4)
		put_stroke(StrokeA, digitX, ctx, segWidth, mintueY);
	//B
	if (digit != 1 && digit != 5 && digit != 6)
		put_stroke(StrokeB, digitX, ctx, segWidth, mintueY);
	//C
	if (digit != 1 && digit != 2)
		put_stroke(StrokeC, digitX, ctx, segWidth, mintueY);
	//D
	if (digit != 1 && digit != 4 && digit != 7)
		put_stroke(StrokeD, digitX, ctx, segWidth, mintueY);
	//E
	if (digit != 3 && digit != 4 && digit != 5 && digit != 7 && digit != 9)
		put_stroke(StrokeE, digitX, ctx, segWidth, mintueY);
	//F
	if (digit != 2 && digit != 3 && digit != 7)
		put_stroke(StrokeF, digitX, ctx, segWidth, mintueY);
	//G
	if (digit != 1 && digit != 7 && digit != 0)
		put_stroke(StrokeG, digitX, ctx, segWidth, mintueY);
}

static void draw_time(struct tm* t, GContext* ctx) {
	int hour = get_hour(t);
	int mintueY = MINUTE_00_Y + t->tm_min * (MINUTE_59_Y - MINUTE_00_Y) / 60;
	if (hour == 1) {
		//view 1
		put_digit(hour, ctx, VIEW_1_FIRST_DIGIT_X, VIEW_1_SEG_WIDTH, mintueY);
	} else if (hour <= 9) {
		//view 2
		put_digit(hour, ctx, VIEW_2_FIRST_DIGIT_X, VIEW_2_SEG_WIDTH, mintueY);
	} else if (hour == 11) {
		//view 3
		put_digit(1, ctx, VIEW_3_FIRST_DIGIT_X, VIEW_3_SEG_WIDTH, mintueY);
		put_digit(1, ctx, VIEW_3_SECOND_DIGIT_X, VIEW_3_SEG_WIDTH, mintueY);
	} else if (hour <= 19) {
		//view 4
		put_digit(1, ctx, VIEW_4_FIRST_DIGIT_X, VIEW_4_SEG_WIDTH, mintueY);
		put_digit(hour % 10, ctx, VIEW_4_SECOND_DIGIT_X, VIEW_4_SEG_WIDTH, mintueY);
	} else if (hour == 21) {
		//view 5
		put_digit(2, ctx, VIEW_5_FIRST_DIGIT_X, VIEW_5_SEG_WIDTH, mintueY);
		put_digit(1, ctx, VIEW_5_SECOND_DIGIT_X, VIEW_5_SEG_WIDTH, mintueY);
	} else {
		//view 6
		put_digit(2, ctx, VIEW_6_FIRST_DIGIT_X, VIEW_6_SEG_WIDTH, mintueY);
		put_digit(hour % 10, ctx, VIEW_6_SECOND_DIGIT_X, VIEW_6_SEG_WIDTH, mintueY);
	}
}

static GRect getRect(int x, int y, int (*data)[4]) {
	return GRect((*data)[0] + x, (*data)[1] + y, (*data)[2], (*data)[3]);
}

static void put_letter(const Character *ch, GContext* ctx, int x, int y) {
	int i;
	for (i = 0; i < ch->strokeNumber; i++) {
		graphics_fill_rect(ctx, getRect(x, y, (int (*)[4]) ch->strokes[i]), 0, GCornerNone);
	}
}

static void draw_date(struct tm* t, GContext* ctx, int boundsWidth) {
	char txt[] = "XXX 00XXX";
	strftime(txt, sizeof(txt), "%a %e%b", t);

	int width = 0,x;
	const Character *ch;
	char* c = txt;
	while (*c != '\0') {
		if (*c >= 'A' && *c <= 'Z') {
			ch = LETTER_TABLE[*c - 65];
		} else if (*c >= 'a' && *c <= 'z') {
			ch = LETTER_TABLE[*c - 97];
		} else if (*c >= '0' && *c <= '9') {
			ch = NUMBER_TABLE[*c - 48];
		} else if (*c == ' '){
			width+=WEEK_DATE_SPACING;
			c++;
			continue;
		}else{
			continue;
		}
		width += ch->width + DATE_CHAR_SPACING;
		c++;
	}
	x = (boundsWidth - width + DATE_CHAR_SPACING)/2;

	c = txt;
	while (*c != '\0') {
		if (*c >= 'A' && *c <= 'Z') {
			ch = LETTER_TABLE[*c - 65];
		} else if (*c >= 'a' && *c <= 'z') {
			ch = LETTER_TABLE[*c - 97];
		} else if (*c >= '0' && *c <= '9') {
			ch = NUMBER_TABLE[*c - 48];
		} else if (*c == ' '){
			x+=WEEK_DATE_SPACING;
			c++;
			continue;
		}else{
			continue;
		}
		put_letter(ch, ctx, x, DATE_TOP_MARGIN);
		x += ch->width + DATE_CHAR_SPACING;
		c++;
	}

}
