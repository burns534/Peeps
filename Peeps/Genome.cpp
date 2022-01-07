//
//  Genome.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/4/22.
//

#include "Genome.hpp"
#include "ParamManager.hpp"

void Gene::print_gene() {
    printf("%hhx%hhx%hhx%hhx", s_layer, s_neuron, o_layer, o_neuron);
    printf("%x%x", *(uint32_t *)&weight, *(uint32_t *)&bias);
}

void Genome::random_init() {
    // add random() value for input
    this->shape.push_back(p.min_input_neurons + random() % p.input_neuron_range);
    // calculate # of inner neurons
    uint8_t available_inner = p.min_inner_neurons + random() % p.inner_neuron_range;
    // distribute them to inner layers
    // this is pretty suboptimal. It won't use all of the "available" neurons so the
    // actual distribution will be a few less than expected on average
    while(available_inner > p.min_inner_per_layer) {
        uint8_t temp = p.min_inner_per_layer + random() % (available_inner + 1 - p.min_inner_per_layer);
        available_inner -= temp;
        this->shape.push_back(temp);
    }
    
    // add output neurons
    this->shape.push_back(p.min_output_neurons + random() % p.output_neuron_range);
    
    const uint8_t gene_count = p.min_genes + random() % p.gene_range;
    
    for (uint16_t i = 0; i < gene_count; i++) {
        uint8_t source = random() % (shape.size() - 1);
        uint8_t sink;
        if (source == shape.size() - 2)
            sink = source + 1;
        else
            sink = source + 1 + random() % (shape.size() - source - 1);
        this->genes.push_back(Gene(source, random() % shape[source], sink, random() % shape[sink], -1.0f + 2 * random() / (float) RAND_MAX, -1.0f + 2 * random() / (float) RAND_MAX));
    }
}

void Genome::print_genome() {
    for (auto gene = genes.begin(); gene != genes.end(); gene++) {
        gene->print_gene();
        printf(" ");
    }
}
