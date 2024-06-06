#include "Game/Base.h"

namespace CC {

Base::~Base() {
    for (Building* b : buildings)
        delete b;
    buildings.clear();
}

unsigned int Base::GetAvailableOre() {
    unsigned int ore = 0;

    for (Building* building : buildings) {
        if (building->HasID("Ore")) {
            ore += building->Get<unsigned int>("Ore");
        }
    }

    return ore;
}

void Base::RemoveOre(unsigned int amount) {
    if (amount > GetAvailableOre())
        return;

    for (Building* building : buildings) {
        if (building->HasID("Ore")) {
            unsigned int& ore = building->Get<unsigned int>("Ore");
            unsigned int oreRemoved = 0;

            if (ore <= amount)
                oreRemoved = ore;
            else
                oreRemoved = amount;

            amount -= oreRemoved;
            ore -= oreRemoved;

            if (amount == 0)
                break;
        }
    }
}

unsigned int Base::GetFreePowerGrid() {
    int PG = 0;

    for (Building* building : buildings) {
        if (building->HasID("PG")) {
            PG += building->Get<int>("PG");
        }
    }

    return PG;
}

}
