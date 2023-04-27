#include <iostream>
#include <fstream>
#include "City.h"
#include "JakDojade.h"
using namespace std;

//for(auto& i : pathList)
//std::cout << i.to->name() << " <- " << i.from->name() << " cost: " << i.weight << "\n";

int main() {
    JakDojade p;
    p.parseBoard();
    p.createCityList();
    p.addNeighbours();
    p.addPlanes();
//    p.printCityList();
    p.executeCommands();
    return EXIT_SUCCESS;
}
