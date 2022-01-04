//
//  Brain.hpp
//  Peeps
//
//  Created by Kyle Burns on 1/3/22.
//

#ifndef Brain_hpp
#define Brain_hpp

#include "Genome.hpp"
#include <stdlib.h>
#include <vector>
#include <Accelerate/Accelerate.h>


void print_vector(float *v, size_t len);
void print_matrix(float *m, size_t cols, size_t rows);


struct Brain {
    Brain();
    void init(Genome *g);
    void feed_forward(const float *input, float *output);
//private:
    // number of neurons in each layer
    std::vector<uint8_t> layers;
    // fixed matrices for each layer
    std::vector<float *> matrices;
    // bias vector for each layer
    std::vector<float *> biases;
    uint16_t input_buffer_length;
    uint8_t *input_width;
    uint8_t layer_max_width;
};


#endif /* Brain_hpp */
