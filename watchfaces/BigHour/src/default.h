/*
 * default.h
 *
 *  Created on: 10/10/2015
 *      Author: qin
 */
#include <pebble.h>

#ifndef SRC_DEFAULT_H_
#define SRC_DEFAULT_H_

//SCREEN
#define SCREEN_WIDTH 			144
#define SCREEN_HEIGHT			168

//DATE
#define DATE_BAR_HEIGHT 		24
#define DATE_CHAR_SPACING		2
#define WEEK_DATE_SPACING		5
#define DATE_LEFT_MARGIN		5
#define DATE_TOP_MARGIN			5

//TIME
#define H_STROKE_SEG_NUM 		3
#define V_STROKE_SEG_NUM 		3
#define SEG_HEIGHT 				22
#define SEG_SPACING 			1
#define MINUTE_00_Y				DATE_BAR_HEIGHT + 3
#define MINUTE_59_Y				DATE_BAR_HEIGHT+MINUTE_00_Y+137
#define H_TOP_STROKE_Y			DATE_BAR_HEIGHT+3
#define H_MIDDLE_STROKE_Y		DATE_BAR_HEIGHT+60
#define H_BOTTOM_STROKE_Y		DATE_BAR_HEIGHT+118
#define H_MIDDLE_STROKE_SPLIT_Y	DATE_BAR_HEIGHT+71
#define V_UP_STROKE_Y			DATE_BAR_HEIGHT+3
#define V_DOWN_STROKE_Y			DATE_BAR_HEIGHT+72

//view1 1:xx
#define VIEW_1_SEG_WIDTH 		72
#define VIEW_1_FIRST_DIGIT_X 	36

//view2 0:xx~9:xx(exclude 1:xx)
#define VIEW_2_SEG_WIDTH 		32
#define VIEW_2_FIRST_DIGIT_X 	23

//view3 11:xx
#define VIEW_3_SEG_WIDTH 		40
#define VIEW_3_FIRST_DIGIT_X 	23
#define VIEW_3_SECOND_DIGIT_X 	81

//view4 1x:xx(exclude 11:xx)
#define VIEW_4_SEG_WIDTH 		30
#define VIEW_4_FIRST_DIGIT_X 	6
#define VIEW_4_SECOND_DIGIT_X 	46

//view5 21:xx
#define VIEW_5_SEG_WIDTH 		30
#define VIEW_5_FIRST_DIGIT_X 	6
#define VIEW_5_SECOND_DIGIT_X 	108

//view5 2x:xx(exclude 11:xx)
#define VIEW_6_SEG_WIDTH 		21
#define VIEW_6_FIRST_DIGIT_X 	4
#define VIEW_6_SECOND_DIGIT_X 	75

typedef enum StrokeName {
	StrokeA = 1, StrokeB = 2, StrokeC = 3, StrokeD = 4, StrokeE = 5, StrokeF = 6, StrokeG = 7
} Stroke;

typedef struct Character {
	int strokeNumber;
	int width;
	int strokes[][4];
} Character;

//alphabet
//A
static const Character CHAR_A = { 4, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 7, 0, 2, 14 }, { 0, 6, 9, 2 } } };
//B
static const Character CHAR_B = { 6, 9, { { 0, 0, 7, 2 }, { 0, 0, 2, 14 }, { 6, 0, 2, 6 }, { 0, 6, 9, 2 },
		{ 7, 6, 2, 8 }, { 0, 12, 9, 2 } } };
//C
static const Character CHAR_C = { 3, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 0, 12, 9, 2 } } };
//D
static const Character CHAR_D = { 4, 9, { { 0, 0, 7, 2 }, { 0, 0, 2, 14 }, { 7, 2, 2, 10 }, { 0, 12, 7, 2 } } };
//E
static const Character CHAR_E = { 4, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 0, 6, 9, 2 }, { 0, 12, 9, 2 } } };
//F
static const Character CHAR_F = { 3, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 0, 6, 9, 2 } } };
//G
static const Character CHAR_G = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 4, 6, 5, 2 }, { 0, 12, 9, 2 },
		{ 7, 6, 2, 8 } } };
//H
static const Character CHAR_H = { 3, 9, { { 0, 0, 2, 14 }, { 0, 6, 9, 2 }, { 7, 0, 2, 14 } } };
//I
static const Character CHAR_I = { 3, 6, { { 2, 0, 2, 14 }, { 0, 0, 6, 2 }, { 0, 12, 6, 2 } } };
//J
static const Character CHAR_J = { 3, 6, { { 4, 0, 2, 14 }, { 0, 12, 6, 2 }, { 0, 10, 2, 4 } } };
//K
static const Character CHAR_K = { 4, 9, { { 0, 0, 2, 14 }, { 6, 0, 2, 6 }, { 0, 6, 9, 2 }, { 7, 6, 2, 8 } } };
//L
static const Character CHAR_L = { 2, 6, { { 0, 0, 2, 14 }, { 0, 12, 6, 2 } } };
//M
static const Character CHAR_M = { 4, 12, { { 0, 0, 12, 2 }, { 0, 0, 2, 14 }, { 5, 0, 2, 14 }, { 10, 0, 2, 14 } } };
//N
static const Character CHAR_N = { 3, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 7, 0, 2, 14 } } };
//O
static const Character CHAR_O = { 4, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 7, 0, 2, 14 }, { 0, 12, 9, 2 } } };
//P
static const Character CHAR_P = { 4, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 7, 0, 2, 7 }, { 0, 6, 9, 2 } } };
//Q
static const Character CHAR_Q = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 7, 0, 2, 14 }, { 0, 12, 9, 2 }, { 4, 8, 5,
		2 } } };
//R
static const Character CHAR_R = { 5, 9, { { 0, 0, 7, 2 }, { 0, 0, 2, 14 }, { 6, 0, 2, 6 }, { 0, 6, 9, 2 },
		{ 7, 6, 2, 8 } } };
//S
static const Character CHAR_S = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 7 }, { 0, 6, 9, 2 }, { 7, 6, 2, 7 },
		{ 0, 12, 9, 2 } } };
//T
static const Character CHAR_T = { 2, 8, { { 0, 0, 8, 2 }, { 3, 0, 2, 14 } } };
//U
static const Character CHAR_U = { 3, 9, { { 0, 0, 2, 14 }, { 7, 0, 2, 14 }, { 0, 12, 9, 2 } } };
//V
static const Character CHAR_V = { 3, 9, { { 0, 0, 2, 12 }, { 7, 0, 2, 12 }, { 2, 12, 5, 2 } } };
//W
static const Character CHAR_W = { 4, 12, { { 0, 12, 12, 2 }, { 0, 0, 2, 14 }, { 5, 0, 2, 14 }, { 10, 0, 2, 14 } } };
//X
static const Character CHAR_X = { 5, 9,
		{ { 0, 0, 2, 6 }, { 7, 0, 2, 6 }, { 2, 6, 5, 2 }, { 0, 8, 2, 6 }, { 7, 8, 2, 6 } } };
//Y
static const Character CHAR_Y = { 4, 9, { { 0, 0, 2, 7 }, { 0, 6, 9, 2 }, { 7, 0, 2, 14 }, { 0, 12, 9, 2 } } };
//ZERO
static const Character CHAR_ZERO = { 4, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 },  { 7, 0, 2, 14 }, { 0, 12,
		9, 2 } } };
//ONE
static const Character CHAR_ONE = { 1, 2, { { 0, 0, 2, 14 } } };
//TWO
static const Character CHAR_TWO = { 5, 9, { { 0, 0, 9, 2 }, { 7, 0, 2, 8 }, { 0, 6, 9, 2 }, { 0, 6, 2, 7 }, { 0, 12, 9,
		2 } } };
//THREE
static const Character CHAR_THREE = { 4, 9, { { 0, 0, 9, 2 }, { 7, 0, 2, 14 }, { 0, 6, 9, 2 }, { 0, 12, 9, 2 } } };
//FOUR
static const Character CHAR_FOUR = { 3, 9, { { 0, 0, 2, 6 }, { 0, 6, 9, 2 }, { 7, 0, 2, 14 } } };
//FIVE
static const Character CHAR_FIVE = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 8 }, { 0, 6, 9, 2 }, { 7, 6, 2, 7 }, { 0, 12, 9,
		2 } } };
//SIX
static const Character CHAR_SIX = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 0, 6, 9, 2 }, { 7, 6, 2, 7 }, { 0, 12, 9,
		2 } } };
//SEVEN
static const Character CHAR_SEVEN = { 2, 9, { { 0, 0, 9, 2 }, { 7, 0, 2, 14 } } };
//EIGHT
static const Character CHAR_EIGHT = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 14 }, { 0, 6,9, 2 }, { 7, 0, 2, 14 }, { 0, 12,
		9, 2 } } };
//NINE
static const Character CHAR_NINE = { 5, 9, { { 0, 0, 9, 2 }, { 0, 0, 2, 6 }, { 0, 6, 9, 2 }, { 7, 0, 2, 14 }, { 0, 12,
		9, 2 } } };

static const Character *LETTER_TABLE[25] = { &CHAR_A, &CHAR_B, &CHAR_C, &CHAR_D, &CHAR_E, &CHAR_F, &CHAR_G, &CHAR_H,
		&CHAR_I, &CHAR_J, &CHAR_K, &CHAR_L, &CHAR_M, &CHAR_N, &CHAR_O, &CHAR_P, &CHAR_Q, &CHAR_R, &CHAR_S, &CHAR_T,
		&CHAR_U, &CHAR_V, &CHAR_W, &CHAR_X, &CHAR_Y};
static const Character *NUMBER_TABLE[10] = {&CHAR_ZERO, &CHAR_ONE, &CHAR_TWO, &CHAR_THREE, &CHAR_FOUR, &CHAR_FIVE,
		&CHAR_SIX, &CHAR_SEVEN, &CHAR_EIGHT, &CHAR_NINE};

void drawBigHour(struct tm* t, GContext* ctx);
#endif
/* SRC_DEFAULT_H_ */
