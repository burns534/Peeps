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
    void print_gene();
};

struct Genome {
    std::vector<Gene> genes;
    std::vector<uint8_t> shape;
    void random_init(std::vector<uint8_t> shape, uint16_t gene_count);
    Genome * mate(Genome *p1, Genome *p2);
    void print_genome();
};

#endif /* Genome_hpp */
