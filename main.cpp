#include <iostream>
#include <fstream>
#include "City.h"
#include "JakDojade.h"
using namespace std;

//for(auto& i : pathList)
//std::cout << i.to->name() << " <- " << i.from->name() << " cost: " << i.weight << "\n";

int main() {
    std::ifstream in("./Testing/12.in");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    JakDojade p;
    p.parseBoard();
    p.createCityList();
    p.addNeighbours();
    p.addPlanes();
//    p.printCityList();

    p.executeCommands();
    return EXIT_SUCCESS;
}
