//
//  signal.metal
//  Peeps
//
//  Created by Kyle Burns on 1/3/22.
//

#include <metal_stdlib>
using namespace metal;

kernel void fade_signals(device unsigned char *arr [[buffer(0)]],
                       constant const unsigned char& fade[[buffer(1)]],
                       uint index [[thread_position_in_grid]]) {
    if (arr[index] - fade > 0) {
        arr[index] -= fade;
    } else {
        arr[index] = 0;
    }
}


