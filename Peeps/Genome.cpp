//
//  Genome.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/4/22.
//

#include "Genome.hpp"

void Gene::print_gene() {
    printf("%hhx%hhx%hhx%hhx", s_layer, s_neuron, o_layer, o_neuron);
    printf("%x%x", *(uint32_t *)&weight, *(uint32_t *)&bias);
}

void Genome::random_init(std::vector<uint8_t> shape, uint16_t gene_count) {
    this->shape = shape;
    for (uint16_t i = 0; i < gene_count; i++) {
        uint8_t source = rand() % (shape.size() - 1);
        uint8_t sink;
        if (source == shape.size() - 2)
            sink = source + 1;
        else
            sink = source + 1 + rand() % (shape.size() - source - 1);
        this->genes.push_back(Gene(source, rand() % shape[source], sink, rand() % shape[sink], -1.0f + 2 * rand() / (float) RAND_MAX, -1.0f + 2 * rand() / (float) RAND_MAX));
    }
}

void Genome::print_genome() {
    for (auto gene = genes.begin(); gene != genes.end(); gene++) {
        gene->print_gene();
        printf(" ");
    }
}
