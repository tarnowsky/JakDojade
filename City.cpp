#include "City.h"

City::City(const char *_name, Point&& _coords, tVector<Neighbour>&& _neighbours) {
    m_name = _name;
    m_coords = _coords;
    m_neighbours = _neighbours;
}

City::City(tString &&_name, Point&& _coords, tVector<Neighbour> &&_neighbours) {
    m_name = std::move(_name);
    m_coords = _coords;
    m_neighbours = _neighbours;
}

City::City(tString &&_name, Point&& _coords) {
    m_name = _name;
    m_coords = _coords;
}

City::City(const char *_name, Point&& _coords) {
    m_name = _name;
    m_coords = _coords;
}

City::City(tVector<Neighbour>&& _neighbours, Point&& _coords) {
    m_name = tString();
    m_coords = _coords;
    m_neighbours = _neighbours;
}

tString& City::name() const{
    return m_name;
}

tVector<Neighbour>& City::neighbours() const{
    return m_neighbours;
}

std::ostream &operator<<(std::ostream &_out, const City &_city)  {
    _out << _city.m_name << "[";
    for (int i = 0; i < _city.neighbours().len(); i++) {
        if (i > 0) _out << ", ";
        _out << _city.neighbours()[i];
    }
    return _out << "]" << std::endl;
}

void City::addNeighbour(const Neighbour &_neighbour) {
    m_neighbours.push(_neighbour);
}

Point &City::pos() const {
    return m_coords;
}

City::City(const tString &_name, Point &&_coords) {
    m_name = _name;
    m_coords = _coords;
}

City &City::operator=(const City &_other) {
    if (this != &_other) {
        m_name = _other.m_name;
        m_coords = _other.m_coords;
        m_neighbours = _other.m_neighbours;
    }
    return *this;
}

City &City::operator=(City &&_other)  noexcept {
    if (this != &_other) {
        m_name = std::move(_other.m_name);
        m_coords = _other.m_coords;
        m_neighbours = std::move(_other.m_neighbours);
    }
    return *this;
}

City::City(const City &_other) {
    m_name = _other.m_name;
    m_coords = _other.m_coords;
    m_neighbours = _other.m_neighbours;
}

City::City(City &&_other) noexcept {
    m_name = std::move(_other.m_name);
    m_coords = _other.m_coords;
    m_neighbours = std::move(_other.m_neighbours);
}

City::City() {
    m_name = "";
    m_coords = {};
    m_neighbours = {};
}

