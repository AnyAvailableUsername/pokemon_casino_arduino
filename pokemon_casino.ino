
#include <Arduino.h>
#include "src/IO/Joystick/Joystick.h"
#include "src/IO/Display/Display.h"
#include "src/IO/Speaker/Speaker.h"
#include "src/Logic/Accelerator/Accelerator.h"
#include "src/Logic/Timer/Timer.h"

Display display;
Joystick joystick(A0, A1, 6);
Speaker speaker(4);
Timer timer = Timer();
Accelerator cursor = Accelerator();
int fps = 60;



// Note notes[] = {
// // https://www.nayuki.io/page/transcription-of-pokemon-game-boy-music
//  { 440, 497 }, { 415, 62 }, { 370, 62 }, { 330, 62 }, { 311, 62 }, { 277, 62 },
//  { 311, 62 }, { 277, 311 }, { 208, 311 }, { 330, 311 }, { 247, 311 }, { 440, 182
//  }, { 415, 652 }, { 415, 182 }, { 440, 182 }, { 494, 182 }, { 415, 497 }, { 330,
//  182 }, { 370, 182 }, { 330, 182 }, { 311, 182 }, { 330, 182 }, { 370, 652 }, {
//  311, 652 }, { 311, 311 }, { 247, 311 }, { 370, 311 }, { 311, 311 }, { 494, 182
//  }, { 440, 652 }, { 659, 182 }, { 622, 182 }, { 659, 182 }, { 622, 497 }, { 554,
//  182 }, { 311, 182 }, { 330, 182 }, { 370, 182 }, { 392, 182 }, { 415, 182 }, {
//  415, 89 }, { 392, 89 }, { 415, 89 }, { 392, 89 }, { 415, 182 }, { 370, 652 }, {
//  277, 311 }, { 208, 311 }, { 330, 311 }, { 247, 311 }, { 440, 182 }, { 415, 652
//  }, { 415, 182 }, { 440, 182 }, { 494, 182 }, { 415, 497 }, { 330, 182 }, { 370,
//  182 }, { 330, 182 }, { 311, 182 }, { 330, 182 }, { 370, 652 }, { 311, 311 }, {
//  277, 311 }, { 311, 311 }, { 247, 311 }, { 370, 311 }, { 311, 311 }, { 494, 182
//  }, { 440, 652 }, { 370, 182 }, { 415, 182 }, { 440, 182 }, { 494, 311 }, { 440,
//  311 }, { 494, 182 }, { 440, 182 }, { 415, 182 }, { 370, 182 }, { 330, 311 }, {
//  247, 311 }, { 330, 182 }, { 330, 311 }, { 330, 369 }, { 247, 182 }, { 277, 182
//  }, { 294, 182 }, { 311, 928 }, { 247, 182 }, { 277, 182 }, { 311, 182 }, { 330,
//  652 }, { 622, 311 }, { 494, 311 }, { 370, 311 }, { 311, 311 }, { 330, 276 }, {
//  311, 89 }, { 277, 182 }, { 311, 182 }, { 330, 311 }, { 247, 182 }, { 277, 182
//  }, { 294, 182 }, { 311, 928 }, { 247, 182 }, { 277, 182 }, { 311, 182 }, { 330,
//  652 }, { 622, 311 }, { 494, 311 }, { 370, 311 }, { 440, 311 }, { 415, 182 }, {
//  415, 89 }, { 392, 89 }, { 415, 89 }, { 392, 89 }, { 415, 89 }, { 392, 89 }, {
//  415, 652 }, { 277, 311 }, { 208, 311 }, { 330, 311 }, { 247, 311 }, { 440, 182
//  }, { 415, 652 }, { 415, 182 }, { 440, 182 }, { 494, 182 }, { 415, 497 }, { 330,
//  182 }, { 370, 182 }, { 330, 182 }, { 311, 182 }, { 330, 182 }, { 370, 652 }, {
//  311, 652 }, { 311, 311 }, { 247, 311 }, { 370, 311 }, { 311, 311 }, { 494, 182
//  }, { 440, 652 }, { 659, 182 }, { 622, 182 }, { 659, 182 }, { 622, 497 }, { 554,
//  182 }, { 311, 182 }, { 330, 182 }, { 370, 182 }, { 392, 182 }, { 415, 182 }, {
//  415, 89 }, { 392, 89 }, { 415, 89 }, { 392, 89 }, { 415, 182 }, { 370, 652 }, {
//  277, 311 }, { 208, 311 }, { 330, 311 }, { 247, 311 }, { 440, 182 }, { 415, 652
//  }, { 415, 182 }, { 440, 182 }, { 494, 182 }, { 415, 497 }, { 330, 182 }, { 370,
//  182 }, { 330, 182 }, { 311, 182 }, { 330, 182 }, { 370, 652 }
// };

// Melody *melody = new Melody(notes, sizeof(notes)/sizeof(notes[0]));

const int BITMAP_HEIGHT = 8;
const int BITMAP_WIDTH = 128;

unsigned char stars[BITMAP_WIDTH  * BITMAP_HEIGHT / 8] = { 0 };
static Symbol Stars = { stars, BITMAP_WIDTH, BITMAP_HEIGHT };

void put_star(int x, int y) {
    stars[y * BITMAP_HEIGHT + x] = 0;
    stars[(y + 1) * BITMAP_HEIGHT + x] = 1;
    stars[(y + 2) * BITMAP_HEIGHT + x] = 1;
    stars[(y - 1) * BITMAP_HEIGHT + x] = 1;
    stars[(y - 2) * BITMAP_HEIGHT + x] = 1;
    stars[y * BITMAP_HEIGHT + (x + 1)] = 1;
    stars[y * BITMAP_HEIGHT + (x + 2)] = 1;
    stars[y * BITMAP_HEIGHT + (x - 1)] = 1;
    stars[y * BITMAP_HEIGHT + (x - 2)] = 1;
}

void generate_stars() {
    for (int i=0; i < 10; i++) {
        int x = random(2, SCREEN_WIDTH - 2);
        int y = random(2, SCREEN_HEIGHT - 2);
        put_star(x, y);
    }
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    delay(10000);
    Serial.println("Initializing...");
    if (!display.begin()) {
        for (;;) {
            Serial.println("Display init failed");
        }
    }

    // display.say("Booting...", true);
    joystick.begin();
    Serial.println("Setup done");
    generate_stars();
}

void update(unsigned long passedTimeMs) {
    cursor.update(joystick.readX(), joystick.readY(), passedTimeMs);
    // speaker.play(melody, passedTimeMs);
}

void render() {
    joystick.print();
    display.firstPage();
    do {
        display.point(cursor.positionX(), cursor.positionY());
        display.draw(Stars, 0, 0);
    } while(display.nextPage());
}

void loop() {
    // Serial.println("Looping... ");
    int passedTime = timer.passedTime();
    if (passedTime >= 1000 / fps) {
        timer.update();

        update(passedTime);
        render();
    }
}


