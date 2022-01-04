//
//  Signals.cpp
//  Peeps
//
//  Created by Kyle Burns on 1/3/22.
//

#include "Signals.hpp"

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <Metal/Metal.hpp>

//static MTL::Device *device;
static MTL::ComputePipelineState *signal_function_pso;
static MTL::CommandQueue *command_queue;
static MTL::Buffer *signal_buffer;


Signals::Signals() {}

void Signals::init(uint16_t width, uint16_t height, uint8_t count, uint8_t fade) {
    this->width = width;
    this->height = height;
    this->fade = fade;
    area = width * height;
    length = width * height * count;
    // create gpu reference
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    MTL::Library *default_library = device->newDefaultLibrary();
    
    if (default_library == nullptr) {
        puts("Failed to find the default library");
        exit(1);
    }
    
    MTL::Function *signal_function = default_library->newFunction(NS::String::string("add_arrays", NS::ASCIIStringEncoding));
    
    if (signal_function == nullptr) {
        puts("Failed to find the signal function");
        exit(1);
    }
    
    
    NS::Error *error;
    
    // create the pipeline state object
    signal_function_pso = device->newComputePipelineState(signal_function, &error);
    
    if (signal_function_pso == nullptr) {
        printf("Failed to create pipeline object: %s\n", error->localizedDescription()->cString(NS::ASCIIStringEncoding));
        exit(1);
    }
    
    
    command_queue = device->newCommandQueue();
    
    if (command_queue == nullptr) {
        puts("Failed to create command queue");
        exit(1);
    }
    
    // create the buffer
    // plus 1 for fade argument
    signal_buffer = device->newBuffer(length, MTL::ResourceStorageModeShared);
    
    data = (uint8_t *)signal_buffer->contents();
    // populate array with zeros
    for (unsigned i = 0; i < length; i++) {
        data[i] = 0;
    }
    
}

void Signals::increment(uint16_t x, uint16_t y, uint8_t layer, uint8_t value) {
    data[area * layer + y * width + x] += value;
}
// some of this may only need to be done once, not sure
void Signals::update() {
    MTL::CommandBuffer *command_buffer = command_queue->commandBuffer();
    assert(command_buffer != nullptr);
    
    MTL::ComputeCommandEncoder *compute_encoder = command_buffer->computeCommandEncoder();
    assert(compute_encoder != nullptr);
    
    // provide the state object
    compute_encoder->setComputePipelineState(signal_function_pso);
    // provide the buffer
    compute_encoder->setBuffer(signal_buffer, 0, 0);
    // set the fade argument
    compute_encoder->setBytes(&fade, 1, 1);
    // create gride size as 1 dimensional array
    MTL::Size grid_size = MTL::Size(length, 1, 1);
    
    unsigned long thread_group_max = signal_function_pso->maxTotalThreadsPerThreadgroup();
    
    if (thread_group_max > length) {
        thread_group_max = length;
    }
    
    MTL::Size thread_group_size = MTL::Size(thread_group_max, 1, 1);
    // encode the command to dispatch the threads
    compute_encoder->dispatchThreads(grid_size, thread_group_size);
    
    // end encoding
    compute_encoder->endEncoding();
    
    clock_t tic = clock();
    // execute command
    command_buffer->commit();
    
    command_buffer->waitUntilCompleted();
    
    printf("\nexecution time: %lf\n", (clock() - tic) / (double)CLOCKS_PER_SEC);
}

void Signals::print_data(uint8_t layer) {
    uint8_t *ptr = data + area * layer;
    for (int i = 0; i < area; i++) {
        if (i % width == 0) puts("");
        printf("%hhu", ptr[i]);
    }
}
