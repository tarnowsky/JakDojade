#include "City.h"

std::ostream& operator<<(std::ostream& _out, const Neighbour& _neighbour) {
    _out << "(";
    if (_neighbour.m_city) _out << _neighbour.m_city->name();
    _out << ", ";
    if (_neighbour.m_weight) _out << _neighbour.m_weight;
    _out << ")";

    return _out;
}

City& Neighbour::city() const {
    return *m_city;
}

int Neighbour::weight() const {
    return m_weight;
}

void Neighbour::addCity(City* _city) {
    m_city = _city;
}

void Neighbour::setWeight(const int &_weight) {
    m_weight = _weight;
}

bool Neighbour::isImaginary() {
    return m_city->name().isEmpty();
}

Neighbour::Neighbour(City *_city) {
    m_city = _city;
}

Neighbour::Neighbour(City *_city, int _weight) {
    m_city = _city;
    m_weight = _weight;
}

int Neighbour::checkID() const {
    return m_checked;
}

void Neighbour::check(int city_id) {
    m_checked = city_id;
}
