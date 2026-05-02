from typing import Iterable
import pretty_midi
import math

def midi_to_frequency_duration(midi_path):
    midi = pretty_midi.PrettyMIDI(midi_path)
    out = []

    for instrument in midi.instruments:
        if instrument.is_drum:
            continue
        for note in instrument.notes:
            freq = round(440.0 * (2 ** ((note.pitch - 69) / 12.0)))
            duration_ms = round((note.end - note.start) * 1000)
            out.append((freq, duration_ms))

    return out

def compress_melody(tokens, min_len=2, max_len=16, min_occurrences=2):
    patterns = []
    pattern_map = {}
    used = [False] * len(tokens)

    candidates = []

    for length in range(max_len, min_len - 1, -1):
        counts = {}
        for i in range(len(tokens) - length + 1):
            chunk = tuple(tokens[i:i + length])
            counts.setdefault(chunk, []).append(i)

        for chunk, positions in counts.items():
            if len(positions) >= min_occurrences:
                score = len(chunk) * len(positions)
                candidates.append((score, chunk, positions))

    candidates.sort(reverse=True, key=lambda x: x[0])

    for _, chunk, positions in candidates:
        if chunk in pattern_map:
            continue

        length = len(chunk)
        valid_positions = []

        for pos in positions:
            if not any(used[pos:pos + length]):
                valid_positions.append(pos)

        if len(valid_positions) >= min_occurrences:
            pid = len(patterns)
            patterns.append(list(chunk))
            pattern_map[chunk] = pid
            for pos in valid_positions:
                for j in range(pos, pos + length):
                    used[j] = True

    sequence = []
    i = 0
    while i < len(tokens):
        matched = False
        for length in range(max_len, min_len - 1, -1):
            if i + length > len(tokens):
                continue
            chunk = tuple(tokens[i:i + length])
            if chunk in pattern_map:
                sequence.append(("P", pattern_map[chunk]))
                i += length
                matched = True
                break
        if not matched:
            sequence.append(("L", tokens[i]))
            i += 1

    return patterns, sequence



notes_org = midi_to_frequency_duration("./python_scripts/music/pokemon-rgby-game-corner-music.mid")

for i in range(1,len(notes_org), 100):
    notes = notes_org[:i]
    nl = len(notes)

    compressed = compress_melody(notes,min_len=3, max_len=16, min_occurrences=2)
    cl=sum(len(pattern) for pattern in compressed[0]) + len(compressed[1])
    print(len(notes))
    print(cl)
    print(cl/len(notes))
# print(", ".join([ f"{{ {note[0]}, {note[1]} }}" for note in notes]))