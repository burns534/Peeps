//
//  Signals.hpp
//  Peeps
//
//  Created by Kyle Burns on 1/3/22.
//

#ifndef Signals_hpp
#define Signals_hpp

#include <stdio.h>
#include <stdlib.h>


struct Signals {
    Signals();
    void init(uint16_t width, uint16_t height, uint8_t count, uint8_t fade);
    void increment(uint16_t x, uint16_t y, uint8_t layer, uint8_t value);
    void update(); // perform fade
    void print_data(uint8_t layer);
private:
    uint8_t *data;
    uint16_t width, height;
    uint32_t area;
    uint16_t length;
    uint8_t fade;
};

#endif /* Signals_hpp */
