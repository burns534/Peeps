//
//  Peep.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/5/22.
//

#include "Peep.hpp"

// randomly initialize peep
Peep::Peep() {
    this->genome = new Genome();
    this->genome->random_init();
    this->brain = new Brain();
    this->brain->init(this->genome);
}

Peep::Peep(Genome *genome) {
    this->genome = genome;
    this->brain = new Brain();
    this->brain->init(this->genome);
}

