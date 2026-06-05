#pragma once

struct Symbol {
    const unsigned char* bitmap;
    int width;
    int height;
};

// int bitmap[] = {
//     0x1000000000000001,
//     0x1000000000000001,
//     0x1000000000000001,
//     0x1000000000000001,
//     0x1000000000000001,
//     0x1000000000000001,
// };

// Symbol s = { bitmap, 6 };