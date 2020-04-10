#pragma once
#include "Model.h"

#include <unordered_map>

class ModelLoader
{
public:
    static ModelLoader& getInstance()
    {
        static ModelLoader instance;
        return instance;
    }
private:
    ModelLoader() {}
public:
	// Deleting the copy and move functions so you don't duplicate the singleton
    ModelLoader(ModelLoader const&) = delete;
    void operator=(ModelLoader const&) = delete;

    static Model loadModel(std::string path);
};
