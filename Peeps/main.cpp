//
//  main.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/3/22.
//

#include <iostream>
#include "Signals.hpp"
#include "Brain.hpp"

int main(int argc, const char * argv[]) {
    
//    Signals test;
//    test.init(128, 128, 1, 2);
//    // set 4,45 in layer 0 to 34
//    test.increment(4, 45, 0, 34);
//    for (int i = 0; i < 5000; i++) {
//        test.increment(rand() % 128, rand() % 128, 0, rand() % 10);
//    }
//    test.print_data(0);
//    test.update();
//    test.print_data(0);
    // layer 1
    Gene gene1 = Gene(0, 0, 1, 0, 0.5f, 0.1f);
    Gene gene2 = Gene(0, 1, 1, 0, 0.1f, 0.2f);
    // layer 2
    Gene gene3 = Gene(0, 1, 2, 0, 0.6f, 0.3f);
    Gene gene4 = Gene(1, 0, 2, 0, 0.3f, 0.4f);
    Gene gene5 = Gene(0, 1, 2, 1, -0.1f, 0.5f);
    Gene gene6 = Gene(1, 0, 2, 1, -0.9f, 0.6f);
    // layer 3
    Gene gene7 = Gene(1, 0, 3, 0, 0.4f, 0.7f);
    Gene gene8 = Gene(0, 0, 3, 1, 0.7f, 0.8f);
    Gene gene9 = Gene(2, 0, 3, 1, -0.7f, 0.9f);
    Gene gene10 = Gene(2, 1, 3, 1, -0.5f, 1.0f);
    
    Genome test_genome;
    test_genome.layers = { 2, 1, 2, 2 };
    test_genome.genes = {
        gene1, gene2, gene3, gene4,
        gene5, gene6, gene7, gene8,
        gene9, gene10
    };
    
    
    Brain test_brain;
    
    test_brain.init(&test_genome);
    
    printf("layers: %lu\n", test_brain.layers.size());
    
    print_vector(test_brain.biases[0], test_brain.layers[1]);
    print_vector(test_brain.biases[1], test_brain.layers[2]);
    print_vector(test_brain.biases[2], test_brain.layers[3]);
 
    for (int i = 0; i < test_brain.layers.size() - 1; i++) {
        printf("input width [%d]: %d\n", i, test_brain.input_width[i]);
        print_matrix(test_brain.matrices[i], test_brain.input_width[i + 1], test_brain.layers[i + 1]);
    }
//    print_matrix(test_brain.matrices[0], 2, 1);
    
    float test_input[2] = { 0.1f, -0.4f };
    float test_output[2];
    
    test_brain.feed_forward(test_input, test_output);
    
    print_vector(test_output, 2);
    
    
    
    return 0;
}
