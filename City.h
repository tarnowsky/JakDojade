#ifndef JAKDOJADE_CITY_H
#define JAKDOJADE_CITY_H
#include "tString.h"
#include "tVector.h"

class Neighbour;

struct Point {
    int x;
    int y;
    Point() : x(-1), y(-1) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(const Point& _other) const {
        return ((_other.x == x) && (_other.y == y));
    }
};

class City {
private:
    mutable tString m_name;
    mutable Point m_coords;
    mutable tVector<Neighbour> m_neighbours;
    friend std::ostream& operator<<(std::ostream& _out, const City& _city);
public:
    // Constructors
    City();

    City(const City& _other);
    City(City&& _other) noexcept;
    City(const char* _name, Point&& _coords, tVector<Neighbour>&& _neighbours);
    City(tString&& _name, Point&& _coords, tVector<Neighbour>&& _neighbours);
    City(const tString& _name, Point&& _coords);
    City(tString&& _name, Point&& _coords);
    City(const char* _name, Point&& _coords);
    City(tVector<Neighbour>&& _neighbours, Point&& _coords);

    City& operator=(const City& _other);
    City& operator=(City&& _other) noexcept ;
    // Getters
    tString& name() const;
    tVector<Neighbour>& neighbours() const;
    Point& pos() const;

    // Setters
    void addNeighbour(const Neighbour& _neighbour);

    // Destructors
    ~City() = default;
};

class Neighbour {
private:
    City* m_city{};
    int m_weight{};
    int m_checked = -1;
    friend std::ostream& operator<<(std::ostream& _out, const Neighbour& _edge);
public:
    Neighbour() = default;
    explicit Neighbour(City* _city);
    Neighbour(City* _city, int _weight);

    // Bool
    bool isImaginary();

    // Getters
    City& city() const;
    int weight() const;
    int checkID() const;

    // Setters
    void addCity(City* _city);
    void setWeight(const int& _weight);
    void check(int city_id);

    ~Neighbour() = default;
};

#endif //JAKDOJADE_CITY_H
