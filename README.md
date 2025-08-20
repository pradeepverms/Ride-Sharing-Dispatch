# Ride-Sharing Dispatch Simulator (C++)

A C++ project demonstrating a simple ride-sharing system that assigns drivers to riders using queues and priority queues. Nearest drivers with higher ratings get matched first, and ride history is maintained for every completed trip.

## Features

- **Driver assignment based on proximity and rating**
- **Queues for rider requests and driver dispatches**
- **Priority queue for optimal driver selection**
- **Ride history tracking**
- Easy-to-understand sample code using standard library data structures (queue, priority_queue, list)

## How It Works

1. Riders request a ride and are placed in a queue.
2. Drivers become available with their current distance and rating.
3. The simulator matches the nearest, best-rated driver to each rider using a priority queue.
4. Ride history is saved and can be displayed.

## Getting Started

### Requirements

- C++11 or newer compiler (g++/clang++)
- macOS, Linux, or Windows

### How to Compile and Run

In your terminal, inside the project folder:

AUTHOR
PRADIP KUMAR VERMA