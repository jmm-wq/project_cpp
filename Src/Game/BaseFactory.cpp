#include "Game/BaseFactory.h"

#include <fstream>

#include "Game/Buildings/Buildings"
#include "Tool/Tool.h"

namespace CC {

void BaseFactory::Load() {
    std::ifstream ifs("Base.dat", std::ifstream::in);

    if (ifs.is_open()) {
        while (ifs.good()) {
            std::string line;
            std::getline(ifs, line);

            if (line == "")
                continue;

            std::vector<std::string> split = Split(line, ':');

            if (split.size() != 2) {
                std::cerr << "Error while loading building : <" << line << " >"
                          << "':' split size != 2";
                continue;
            }

            std::vector<std::string> coordSplit = Split(split[0], ',');

            if (split.size() != 2) {
                std::cerr << "Error while loading building : <" << line << " >"
                          << "',' split size != 2 when loading coord";
                continue;
            }

            unsigned int x = std::stoul(coordSplit[0]);
            unsigned int y = std::stoul(coordSplit[1]);
            sf::Vector2u position(x, y);

            std::vector<std::string> buildingSplit = Split(split[1], ' ');

            Building* building = LoadBuilding(buildingSplit, position);

            if (building != nullptr)
                base.GetBuildings().push_back(building);
        }

        ifs.close();
    } else {
        base.GetBuildings().push_back(new Core(sf::Vector2u(10, 7)));
        base.GetBuildings().push_back(new OreSilo(sf::Vector2u(12, 7)));
    }
}

void BaseFactory::Save() {
    std::ofstream ofs("Base.dat", std::ofstream::out | std::ofstream::trunc);

    if (ofs.is_open()) {
        for (Building* b : base.GetBuildings()) {
            sf::Vector2u pos = b->Get<sf::Vector2u>("Position");

            ofs << pos.x << "," << pos.y << ":" << b->Save() << std::endl;
        }

        ofs.close();
    } else {
        std::cerr << "Unable to open Base.dat for writing base" << std::endl;
    }
}

Building* BaseFactory::LoadBuilding(const std::vector<std::string>& buildingSplit,
                                    const sf::Vector2u& position) {
    Building* result = nullptr;

    std::string name = buildingSplit[0];

    if (name == "Core")
        result = new Core(position);
    else if (name == "OreSilo")
        result = new OreSilo(position);
    else
        std::cerr << "Unknown building : " << buildingSplit[0] << std::endl;

    if (result != nullptr)
        result->Load(buildingSplit);

    return result;
}

}
