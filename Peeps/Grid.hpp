//
//  Grid.hpp
//  Peeps
//
//  Created by Kyle Burns on 1/5/22.
//

#ifndef Grid_hpp
#define Grid_hpp
#include <stdlib.h>

#define OCCUPIED 1


struct Grid {
    Grid();
    void initialize(uint16_t width, uint16_t height);
    uint8_t get_tile(uint16_t x, uint16_t y);
private:
    uint16_t width, height;
    uint8_t *data;
};

extern Grid grid;

#endif /* Grid_hpp */
