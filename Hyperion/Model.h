#pragma once
#include "Vertex.h"

#include <utility>

class Model
{
public:
    Model(std::vector<Vertex> vertices, std::vector<uint32_t> indices) :
        vertices(std::move(vertices)),
        indices(std::move(indices))
    {}
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};
