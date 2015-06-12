/* Based on http://mbostock.github.com/protovis/ex/bzr.js */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "libs/mathemb.h"

#include "libs/text_5x3.h"



#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static uint8_t *bzr_a, *bzr_b, *bzr_c;
static uint8_t *t_bzr_a, *t_bzr_b, *t_bzr_c;


static void init(void) {
	bzr_a = malloc(LED_WIDTH * LED_HEIGHT * sizeof(*bzr_a));
	bzr_b = malloc(LED_WIDTH * LED_HEIGHT * sizeof(*bzr_b));
	bzr_c = malloc(LED_WIDTH * LED_HEIGHT * sizeof(*bzr_c));
	t_bzr_a = malloc(LED_WIDTH * LED_HEIGHT * sizeof(*t_bzr_a));
	t_bzr_b = malloc(LED_WIDTH * LED_HEIGHT * sizeof(*t_bzr_b));
	t_bzr_c = malloc(LED_WIDTH * LED_HEIGHT * sizeof(*t_bzr_c));

	for(int y = 0, p = 0; y < LED_HEIGHT; y++) {
		for (int x = 0; x < LED_WIDTH; x++, p++) {
			bzr_a[p] = rand() & 0xFF;
			bzr_b[p] = rand() & 0xFF;
			bzr_c[p] = rand() & 0xFF;
		}
	}
}

static void deinit(void) {
	free(bzr_a);
	free(bzr_b);
	free(bzr_c);
	free(t_bzr_a);
	free(t_bzr_b);
	free(t_bzr_c);
}


static uint8_t tick(void) {
	static int time = 0;
	time++;


	for(int y = 0, p = 0; y < LED_HEIGHT; y++) {
		for (int x = 0; x < LED_WIDTH; x++, p++) {
			/* Compute neighbor averages, with wrap-around. */
			int16_t sa = 0, sb = 0, sc = 0;
			for(int j = y - 1 ; j < y + 2; j++) {
				for(int i = x - 1; i < x + 2; i++) {
					int q =
					(j < 0 ? j + LED_HEIGHT : j >= LED_HEIGHT ? j - LED_HEIGHT : j) * LED_WIDTH +
					(i < 0 ? i + LED_WIDTH : i >= LED_WIDTH ? i - LED_WIDTH : i);
					sa += bzr_a[q];
					sb += bzr_b[q];
					sc += bzr_c[q];
				}
			}


			sa /= 9;
			sb /= 9;
			sc /= 9;

			int16_t ta = (sa * (259 + sb - sc)) >> 8;
			int16_t tb = (sb * (259 + sc - sa)) >> 8;
			int16_t tc = (sc * (259 + sa - sb)) >> 8;
			t_bzr_a[p] = MIN(ta,255);
			t_bzr_b[p] = MIN(tb,255);
			t_bzr_c[p] = MIN(tc,255);
			//setLedXY(x, y, bzr_a[p], bzr_b[p], bzr_c[p]);
			setLedXY(x, y, 
					sini(time*50+50*t_bzr_a[p])>>8  ,
					sini(0x1555+time*70+30*t_bzr_b[p])>>8  ,
					sini(0x2aaa+time*30+20*t_bzr_c[p])>>8

					);
		}
	}  

	for(int y = 0, p = 0; y < LED_HEIGHT; y++) {
		for (int x = 0; x < LED_WIDTH; x++, p++) {
			bzr_a[p] = t_bzr_a[p];
			bzr_b[p] = t_bzr_b[p];
			bzr_c[p] = (t_bzr_a[p]>>4)+(t_bzr_c[p]);

		}
	}

	print_5x3_at (1,5,"PRESS",255,255,255);
	print_5x3_at (1,15,"BUTTON",255,255,255);

	if(joy_button_click())
		return 1;

	return 0;
}

static void constructor(void) CONSTRUCTOR_ATTRIBUTES
void constructor(void) {
	registerAnimation(init,tick,deinit, 40, 2000);
}
