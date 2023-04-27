#ifndef JAKDOJADE_JAKDOJADE_H
#define JAKDOJADE_JAKDOJADE_H
#include <iostream>
#include "City.h"
#include "tPriorityQueue.h"


enum Directions {
    UP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    DOWN,
    BOTTOM_LEFT,
    LEFT,
    TOP_LEFT
};

struct ResultPath {
    tVector<tString*> visitedCities;
    int cost;
};

struct Node {
    char m_id{};
    Point m_posistion;
    int m_visitor = 0;
    int m_distance = 0;
};

class JakDojade {
private:
    Node** m_board;
    int m_rows, m_cols;
    mutable tVector<City> m_cityList;

    friend std::ostream& operator<<(std::ostream& _out,const JakDojade& _jdojade);


    // Miasta
    tString getCityName(int x, int y);
    void prepareAvailableDirections(bool *availableDirections, int x, int y) const;
    int getFirstLetterIndx(int x, int y) const;
    tString getCityNameFromIndx(int x, int y) const;
    static bool canBePartOfCityName(const char& c);

    // Sasiedzi
    void preparePossibleNeighbours(bool *possibleMoves, int x, int y) const;
    static bool canBeNeighbour(const char& c);

    // Djikstra

public:
    JakDojade();

    void parseBoard();
    void createCityList();
    void addNeighbours();
    void addPlanes();
    void executeCommands();
    static tVector<Path> findPath(City* from);

    tVector<City>& cityList() const;
    void printCityList() const;

    ~JakDojade();
};


#endif //JAKDOJADE_JAKDOJADE_H
