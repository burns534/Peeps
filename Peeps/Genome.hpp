//
//  Genome.hpp
//  Peeps
//
//  Created by Kyle Burns on 1/4/22.
//

#ifndef Genome_hpp
#define Genome_hpp
#include <stdlib.h>
#include <vector>

struct Gene {
    uint8_t s_layer;
    uint8_t s_neuron;
    uint8_t o_layer;
    uint8_t o_neuron;
    float weight;
    float bias;
    Gene(uint8_t s_layer, uint8_t s_neuron, uint8_t o_layer, uint8_t o_neuron, float weight, float bias) : s_layer(s_layer), s_neuron(s_neuron), o_layer(o_layer), o_neuron(o_neuron), weight(weight), bias(bias) {}
};

struct Genome {
    std::vector<Gene> genes;
    std::vector<uint8_t> layers;
};

#endif /* Genome_hpp */
