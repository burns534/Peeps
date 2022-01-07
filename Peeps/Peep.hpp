//
//  Peep.hpp
//  Peeps
//
//  Created by Kyle Burns on 1/5/22.
//

#ifndef Peep_hpp
#define Peep_hpp

#include "Genome.hpp"
#include "Brain.hpp"

struct Peep {
    Peep();
    Peep(Genome *genome);
    Genome *genome;
    Brain *brain;
    uint16_t x, y;
    uint16_t age;
    uint8_t r, g, b;
    bool alive;
};

#endif /* Peep_hpp */
