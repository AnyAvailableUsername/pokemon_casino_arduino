#include "Speaker.h"

// Constructor
Speaker::Speaker(int speakerPin) : pin(speakerPin) {}

// Initialize speaker
void Speaker::begin() {
    pinMode(pin, OUTPUT);
}

// Play a tone
void Speaker::playTone(int frequency, int duration) {
    tone(pin, frequency, duration); // Use Arduino's built-in tone function
}

void Speaker::play(Melody* const melody, unsigned long passedTimeMs) {
    if (melody->isPausing(passedTimeMs))
        return;

    Note note = melody->next();
    playTone(note.frequency, note.duration);
}

void Speaker::playMelody(const Note* melody, int size) {
    for (int t = 0; t < size; t++) {

        playTone(melody[t].frequency, melody[t].duration);

        int pauseBetweenNotes = melody[t].duration * 1.2;
        delay(pauseBetweenNotes);
    }
}

// Stop the tone
void Speaker::stopTone() {
    noTone(pin); // Stop the tone
}

// https://www.nayuki.io/page/transcription-of-pokemon-game-boy-music