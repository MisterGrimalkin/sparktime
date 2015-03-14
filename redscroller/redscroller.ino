/*
 * 18 * 5x7 modules = 90x7 screen
 * A0 data
 * A1 latch?
 * A2 enable? data2?
 * A3 clock1
 * A4 clock2
 */

#define LED_DATA	A0
#define LED_LATCH	A1
#define LED_ENABLE	A2
#define LED_CLOCK1	A3
#define LED_CLOCK2	A4

#define WIDTH 90
#define HEIGHT 7

static uint8_t fb[HEIGHT][WIDTH];

void setup()
{
	pinMode(D0, INPUT);
	pinMode(D1, INPUT);
	pinMode(D3, INPUT);
	pinMode(D4, INPUT);
	pinMode(D5, INPUT);
	pinMode(D6, INPUT);
	pinMode(D7, INPUT);

	digitalWrite(D0, 0);
	digitalWrite(D1, 0);
	digitalWrite(D3, 0);
	digitalWrite(D4, 0);
	digitalWrite(D5, 0);
	digitalWrite(D6, 0);
	digitalWrite(D7, 0);

	pinMode(LED_DATA, OUTPUT);
	pinMode(LED_LATCH, OUTPUT);
	pinMode(LED_ENABLE, OUTPUT);
	pinMode(LED_CLOCK1, OUTPUT);
	pinMode(LED_CLOCK2, OUTPUT);

	for (int y = 0 ; y < HEIGHT ; y++)
	{
		for (int x = 0 ; x < WIDTH ; x++)
		{
			//fb[y][x] = (x % 8) > y ? 0 : 1;
			fb[y][x] = y & 1;
		}
	}
}


static inline void
row(
	const int row_pin,
	const uint8_t * const data
)
{
	digitalWrite(LED_ENABLE, 0);

	digitalWrite(row_pin, 0);
	pinMode(row_pin, OUTPUT);

	for (unsigned i = 0 ; i < WIDTH/2 ; i++)
	{
		digitalWrite(LED_CLOCK1, 1);
		digitalWrite(LED_DATA, data[i] ?  1 : 0);
		digitalWrite(LED_CLOCK1, 0);
	}

	for (unsigned i = WIDTH/2 ; i < WIDTH ; i++)
	{
		digitalWrite(LED_CLOCK2, 1);
		digitalWrite(LED_DATA, data[i] ?  1 : 0);
		digitalWrite(LED_CLOCK2, 0);
	}

	digitalWrite(LED_LATCH, 1);
	delayMicroseconds(10);
	digitalWrite(LED_LATCH, 0);

	pinMode(row_pin, INPUT);
	digitalWrite(LED_ENABLE, 1);
}


void loop()
{
	row(D0, fb[0]);
	row(D1, fb[1]);
	row(D3, fb[2]);
	row(D4, fb[3]);
	row(D5, fb[4]);
	row(D6, fb[5]);
	row(D7, fb[6]);
}