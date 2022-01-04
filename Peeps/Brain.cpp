//
//  Brain.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/3/22.
//

#include "Brain.hpp"

Brain::Brain() {}

void Brain::init(Genome *g) {
    this->layers = g->shape;
//    uint8_t input_width[layers.size() -1];
    input_width = (uint8_t *) malloc(layers.size());
    input_buffer_length = 0;
    input_width[0] = 0;
    layer_max_width = 0;
    // allocate weights and biases
    for (uint8_t layer = 0; layer < layers.size() - 1; layer++) {
        matrices.push_back((float *)calloc((layers[layer] + input_buffer_length) * layers[layer + 1], sizeof(float)));
        printf("making matrix of size %d\n", (layers[layer] + input_buffer_length) * layers[layer + 1]);
        biases.push_back((float *)calloc(layers[layer + 1], sizeof(float)));
        input_buffer_length += layers[layer];
        input_width[layer + 1] = input_buffer_length;
        if (layers[layer] > layer_max_width) {
            layer_max_width = layers[layer];
        }
    }
    
    // populate weights and biases
    for (auto gene = g->genes.begin(); gene != g->genes.end(); gene++) {
        matrices[gene->o_layer - 1][ gene->o_neuron * input_width[gene->o_layer] + gene->s_neuron + input_width[gene->s_layer]] = gene->weight;
        biases[gene->o_layer - 1][gene->o_neuron] += gene->bias;
    }
}

void print_vector(float *v, size_t len) {
    for (int i = 0; i < len; i++) {
        printf("%f ", v[i]);
    }
    puts("");
}

void print_matrix(float *m, size_t cols, size_t rows) {
    for (int i = 0; i < cols * rows; i++) {
        printf("%f ", m[i]);
        if (i % cols == cols - 1) puts("");
    }
}

void Brain::feed_forward(const float *input, float *output) {
    // allocate buffer to transfer input to each layer
    // this buffer must have length of the sum of elements
    // of layers except the last layer.
    // basically it has to be able to accommodate connections
    // from all neurons before the last layer since
    // any neuron can be conected to any neuron on any
    // layer after its own layer
    // this means the input_buffer acts as a sort of accumulator of the outputs of each layer
    // and gets longer as the propagation flows
    printf("input buffer length: %hu\n", input_buffer_length);
    float input_buffer[input_buffer_length];
    
    // allocate temporary buffer with length of last layer
    // to hold biases and results
    float bias_temp[layer_max_width];
    // copy input into this buffer
    
    // it begins with the input provided from the signal layer
    memcpy(bias_temp, input, layers[0] * sizeof(float));
        
    for (uint8_t i = 0; i < layers.size() - 1; i++) {
        // append the result to the input buffer
        uint8_t in = layers[i];
        uint8_t out = layers[i + 1];
        
        memcpy(input_buffer + input_width[i], bias_temp, in * sizeof(float));
        print_vector(input_buffer, input_width[i + 1]);
        // each matrix has n+1 rows for number of output neurons
        // layers[i+1] is thus the rows
        // layers[i] is the cols
        // this operation calculates Y = aMX + bY
        // 1s are strides
        // 1.0f are a and b
        // copied biases[i] is Y
        // row major format and no matrix transpose
        // calculate weight * input vector + bias vector
        // store result in bias temporary
        
        // set biases
        cblas_scopy(out, biases[i], 1, bias_temp, 1);
        cblas_sgemv(CblasRowMajor, CblasNoTrans, out, input_width[i + 1], 1.0f, matrices[i], input_width[i + 1], input_buffer, 1, 1.0f, bias_temp, 1);
    }
    
    // return final activations
    cblas_scopy(layers.back(), bias_temp, 1, output, 1);
}
