//
//  PeepManager.hpp
//  Peeps
//
//  Created by Kyle Burns on 1/5/22.
//

#ifndef PeepManager_hpp
#define PeepManager_hpp
#include "Peep.hpp"

struct PeepManager {
    std::vector<Peep> peeps;
};

extern PeepManager peepManager;

#endif /* PeepManager_hpp */
