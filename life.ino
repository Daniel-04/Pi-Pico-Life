#define ALIVE 0b10000000
#define DEAD 0b00000000
#define ALIVE_TWO_NEIGHBOUR 0b10000010
#define ALIVE_THREE_NEIGHBOUR 0b10000011
#define DEAD_THREE_NEIHGBOUR 0b00000011
#define THRESHOLD 10
#define DWIDTH 128
#define DHEIGHT 64
#define LWIDTH 128
#define LHEIGHT 64
byte life[LWIDTH + 2][LHEIGHT + 2];

struct iter_info {
  size_t alive_count;
  int min_x;
  int max_x;
  int min_y;
  int max_y;
};

struct iter_info next() {
  for (int i = 1; i < LWIDTH; i++) {
    for (int j = 1; j < LHEIGHT; j++) {
      if (life[i][j] & ALIVE) {
        life[i-1][j-1]++; life[i][j-1]++; life[i+1][j-1]++;
        life[i-1][j]++;                   life[i+1][j]++;
        life[i-1][j+1]++; life[i][j+1]++; life[i+1][j+1]++;
      }
    }
  }
  struct iter_info out = { 0, INTPTR_MAX, INTPTR_MIN, INTPTR_MAX, INTPTR_MIN };
  for (int i = 1; i < LWIDTH; i++) {
    for (int j = 1; j < LHEIGHT; j++) {
      switch (life[i][j]) {
        case ALIVE_TWO_NEIGHBOUR:
        case ALIVE_THREE_NEIGHBOUR:
        case DEAD_THREE_NEIHGBOUR:
          life[i][j] = ALIVE;
          out.alive_count++;
          out.max_x = MAX(out.max_x, i);
          out.max_y = MAX(out.max_y, j);
          out.min_x = MIN(out.min_x, i);
          out.min_y = MIN(out.min_y, j);
          break;
        default:
          life[i][j] = DEAD;
          break;
      }
    }
  }

  return out;
}

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64);

void draw_life(struct iter_info info) {
  display.clearDisplay();

  for (int i = info.min_x; i <= info.max_x; i++) {
    for (int j = info.min_y; j <= info.max_y; j++) {
      if (life[i][j]) {
        display.drawPixel(i, j, 1);
      }
    }
  }
  display.display();
}

void random_init() {
  // Clear life grid
  for (int i = 0; i < LWIDTH; i++) {
    for (int j = 0; j < LHEIGHT; j++) {
      life[i][j] = DEAD;
    }
  }

  // Fill block in the middle with random cells
  for (int i = DWIDTH * 0.4; i < DWIDTH * 0.6; i++) {
    for (int j = DHEIGHT * 0.4; j < DHEIGHT * 0.6; j++) {
      life[i][j] = random(2) ? ALIVE : DEAD;
    }
  }
}

void setup() {
  // Initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x32
  random_init();
}

void loop() {
  static size_t previous_count = 0;
  static int eq_count = 0;
  struct iter_info current = next();
  draw_life(current);

  // If alive count does not change significantly, reinit the grid
  /* 
  I could probably make this a bit better by checking wether
  min_{x,y} or max_{x,y} have changed too.
  */
  if (abs(previous_count - current.alive_count) < THRESHOLD / 2) {
    eq_count++;
  } else {
    eq_count = 0;
  }
  if (eq_count >= THRESHOLD) {
    random_init();
  }
  previous_count = current.alive_count;
}
