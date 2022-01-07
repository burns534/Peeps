//
//  Grid.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/5/22.
//

#include "Grid.hpp"

Grid::Grid() {}

void Grid::initialize(uint16_t width, uint16_t height) {
    this->width = width;
    this->data = (uint8_t *) calloc(width * height, sizeof(uint8_t));
}

// should do bounds check ??
uint8_t Grid::get_tile(uint16_t x, uint16_t y) {
    
    return data[y * width + x];
}
