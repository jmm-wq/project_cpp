#include "Graphic/Texture.h"

#include <iostream>

namespace CC {

bool TextureCollection::Load() {
    bool result = true;

    std::unordered_map<TextureCollection::Id, std::string> paths {
        {Andromeda,     "./Assets/Andromeda.png"},
        {Galaxy1,       "./Assets/Galaxy1.png"},
        {Galaxy2,       "./Assets/Galaxy2.png"},
        {GalaxyCluster, "./Assets/GalaxyCluster.png"},
        {MilkyWay1,     "./Assets/MilkyWay1.png"},
        {MilkyWay2,     "./Assets/MilkyWay2.png"},
        {Nebula,        "./Assets/Nebula.png"},
        {PurpleSun,     "./Assets/PurpleSun.png"},
        {SpriteSheet,   "./Assets/SpriteSheet.png"},
        {StarCluster1,  "./Assets/StarCluster1.png"},
        {StarCluster2,  "./Assets/StarCluster2.png"},
        {YellowSun,     "./Assets/YellowSun.png"},
        {Enemy,         "./Assets/Enemy.png"}
    };

    for (auto it : paths) {
        if (!instance.textures[it.first].loadFromFile(it.second)) {
            std::cerr << "Unable to open texture file : " + it.second
                      << std::endl;
            result = false;
        }
    }

    return result;
}

TextureCollection TextureCollection::instance;

}
