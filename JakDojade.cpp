#include "JakDojade.h"

JakDojade::JakDojade() : m_rows(0), m_cols(0){
    std::cin >> m_cols >> m_rows;

    m_board = new Node*[m_rows];
    for (int i = 0; i < m_rows; i++)
        m_board[i] = new Node[m_cols];

}

std::ostream &operator<<(std::ostream &_out, const JakDojade& _jdojade) {
    for (int i = 0; i < _jdojade.m_rows; i++) {
        for (int j = 0; j < _jdojade.m_cols; j++)
            _out << _jdojade.m_board[i][j].m_id;
        _out << std::endl;
    }
    return _out;
}

void JakDojade::parseBoard() {
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++) {
            std::cin >> m_board[i][j].m_id;
            m_board[i][j].m_posistion = {j, i};
        }
}

JakDojade::~JakDojade() {
    for (int i = 0; i < m_rows; i++)
        delete[] m_board[i];
    delete[] m_board;
}

void JakDojade::createCityList() {
    char c;
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            c = m_board[i][j].m_id;
            if (c == '*') {
                tString city_name = getCityName(j, i);
                m_cityList.push(City(getCityName(j, i), {j, i}));
            }
        }
    }
}

tString JakDojade::getCityName(int x, int y) {
    bool availableDirections[8];
    for (bool & direction : availableDirections) direction = true;
    prepareAvailableDirections(availableDirections, x, y);
    for (int i = 0; i < 8; i++) {
        if (availableDirections[i]) {
            switch (i) {
                case UP:
                    if (canBePartOfCityName(m_board[y - 1][x].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x, y - 1), y - 1);
                    break;
                case TOP_RIGHT:
                    if (canBePartOfCityName(m_board[y - 1][x + 1].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x + 1, y - 1), y - 1);
                    break;
                case RIGHT:
                    if (canBePartOfCityName(m_board[y][x + 1].m_id))
                        return getCityNameFromIndx(x + 1, y);
                    break;
                case BOTTOM_RIGHT:
                    if (canBePartOfCityName(m_board[y + 1][x + 1].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x + 1, y + 1), y + 1);
                    break;
                case DOWN:
                    if (canBePartOfCityName(m_board[y + 1][x].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x, y + 1), y + 1);
                    break;
                case BOTTOM_LEFT:
                    if (canBePartOfCityName(m_board[y + 1][x - 1].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x - 1, y + 1), y + 1);
                    break;
                case LEFT:
                    if (canBePartOfCityName(m_board[y][x - 1].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x - 1, y), y);
                    break;
                case TOP_LEFT:
                    if (canBePartOfCityName(m_board[y - 1][x - 1].m_id))
                        return getCityNameFromIndx(getFirstLetterIndx(x - 1, y - 1), y - 1);
                    break;
                default: break;
            }
        }
    }
    return {};
}

void JakDojade::prepareAvailableDirections(bool *availableDirections, int x, int y) const {
    if (y == 0) {
        availableDirections[UP] = false;
        availableDirections[TOP_LEFT] = false;
        availableDirections[TOP_RIGHT] = false;
    }
    if (y == m_rows - 1) {
        availableDirections[DOWN] = false;
        availableDirections[BOTTOM_LEFT] = false;
        availableDirections[BOTTOM_RIGHT] = false;
    }
    if (x == 0) {
        availableDirections[TOP_LEFT] = false;
        availableDirections[LEFT] = false;
        availableDirections[BOTTOM_LEFT] = false;
    }
    if (x == m_cols - 1) {
        availableDirections[RIGHT] = false;
        availableDirections[BOTTOM_RIGHT] = false;
        availableDirections[TOP_RIGHT] = false;
    }
}

int JakDojade::getFirstLetterIndx(int x, int y) const{
    while (x >= 0 && canBePartOfCityName(m_board[y][x].m_id)) x--;
    return ++x;
}

tString JakDojade::getCityNameFromIndx(int x, int y) const {
    tString name;
    while (x < m_cols && canBePartOfCityName(m_board[y][x].m_id)) name += m_board[y][x++].m_id;
    return name;
}

tVector<City> &JakDojade::cityList() const {
    return m_cityList;
}

bool JakDojade::canBePartOfCityName(const char &c) {
    return ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

void JakDojade::addNeighbours() {
    bool cityFounded;
    int city_id = 0;
    for (auto &curr_city : m_cityList) {

        city_id++;
        tVector<Node> queue;

        m_board[curr_city.pos().y][curr_city.pos().x].m_visitor = city_id;
        m_board[curr_city.pos().y][curr_city.pos().x].m_distance = 0;

        queue.insert(m_board[curr_city.pos().y][curr_city.pos().x], 0);

        while (queue.len() > 0) {
            Node _this = queue.pop();

            bool possibleMoves[4] = {true, true, true, true};
            preparePossibleNeighbours(possibleMoves, _this.m_posistion.x, _this.m_posistion.y);

            for (int i = 0; i < 4; i++) {
                if (possibleMoves[i]) {
                    switch(i) {
                        case UP/2:
                            if (m_board[_this.m_posistion.y - 1][_this.m_posistion.x].m_visitor == city_id) break;
                            if (!canBeNeighbour(m_board[_this.m_posistion.y - 1][_this.m_posistion.x].m_id)) break;

                            cityFounded = false;
                            m_board[_this.m_posistion.y - 1][_this.m_posistion.x].m_visitor = city_id;
                            m_board[_this.m_posistion.y - 1][_this.m_posistion.x].m_distance = _this.m_distance + 1;

                            if (m_board[_this.m_posistion.y - 1][_this.m_posistion.x].m_id == '*') {
                                for (auto &_city : m_cityList) {
                                    if (_city.pos() == Point(_this.m_posistion.x, _this.m_posistion.y - 1 )) {
                                        curr_city.addNeighbour(Neighbour(&_city, _this.m_distance + 1));
                                        cityFounded = true;
                                        break;
                                    }
                                }
                            }
                            if (cityFounded) break;

                            queue.insert(m_board[_this.m_posistion.y - 1][_this.m_posistion.x], 0);
                            break;
                        case RIGHT/2:
                            if (m_board[_this.m_posistion.y][_this.m_posistion.x + 1].m_visitor == city_id) break;
                            if (!canBeNeighbour(m_board[_this.m_posistion.y][_this.m_posistion.x + 1].m_id)) break;

                            cityFounded = false;
                            m_board[_this.m_posistion.y][_this.m_posistion.x + 1].m_visitor = city_id;
                            m_board[_this.m_posistion.y][_this.m_posistion.x + 1].m_distance = _this.m_distance + 1;

                            if (m_board[_this.m_posistion.y][_this.m_posistion.x + 1].m_id == '*') {
                                for (auto &_city : m_cityList) {
                                    if (_city.pos() == Point(_this.m_posistion.x + 1, _this.m_posistion.y)) {
                                        curr_city.addNeighbour(Neighbour(&_city, _this.m_distance + 1));
                                        cityFounded = true;
                                        break;
                                    }
                                }
                            }
                            if (cityFounded) break;

                            queue.insert(m_board[_this.m_posistion.y][_this.m_posistion.x + 1], 0);
                            break;
                        case DOWN/2:
                            if (m_board[_this.m_posistion.y + 1][_this.m_posistion.x].m_visitor == city_id) break;
                            if (!canBeNeighbour(m_board[_this.m_posistion.y + 1][_this.m_posistion.x].m_id)) break;

                            cityFounded = false;
                            m_board[_this.m_posistion.y + 1][_this.m_posistion.x].m_visitor = city_id;
                            m_board[_this.m_posistion.y + 1][_this.m_posistion.x].m_distance = _this.m_distance + 1;

                            if (m_board[_this.m_posistion.y + 1][_this.m_posistion.x].m_id == '*') {
                                for (auto &_city : m_cityList) {
                                    if (_city.pos() == Point(_this.m_posistion.x, _this.m_posistion.y + 1)) {
                                        curr_city.addNeighbour(Neighbour(&_city, _this.m_distance + 1));
                                        cityFounded = true;
                                        break;
                                    }
                                }
                            }
                            if (cityFounded) break;

                            queue.insert(m_board[_this.m_posistion.y + 1][_this.m_posistion.x], 0);
                            break;
                        case LEFT/2:
                            if (m_board[_this.m_posistion.y][_this.m_posistion.x - 1].m_visitor == city_id) break;
                            if (!canBeNeighbour(m_board[_this.m_posistion.y][_this.m_posistion.x - 1].m_id)) break;

                            cityFounded = false;
                            m_board[_this.m_posistion.y][_this.m_posistion.x - 1].m_visitor = city_id;
                            m_board[_this.m_posistion.y][_this.m_posistion.x - 1].m_distance = _this.m_distance + 1;

                            if (m_board[_this.m_posistion.y][_this.m_posistion.x - 1].m_id == '*') {
                                for (auto &_city : m_cityList) {
                                    if (_city.pos() == Point(_this.m_posistion.x - 1, _this.m_posistion.y)) {
                                        curr_city.addNeighbour(Neighbour(&_city, _this.m_distance + 1));
                                        cityFounded = true;
                                        break;
                                    }
                                }
                            }
                            if (cityFounded) break;

                            queue.insert(m_board[_this.m_posistion.y][_this.m_posistion.x - 1], 0);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void JakDojade::preparePossibleNeighbours(bool *possibleMoves, int x, int y) const {
    if (y == 0) possibleMoves[UP / 2] = false;
    if (y == m_rows - 1) possibleMoves[DOWN / 2] = false;
    if (x == 0) possibleMoves[LEFT / 2] = false;
    if (x == m_cols - 1) possibleMoves[RIGHT / 2] = false;
}

bool JakDojade::canBeNeighbour(const char &c) {
    return (c == '#' || c == '*');
}

void JakDojade::printCityList() const {
    for (auto &_city : m_cityList)
        std::cout << _city;
}

void JakDojade::addPlanes() {
    int numOfPlanes, distance;
    tString city1, city2;
    City* neighbourCity;
    bool planeSet;
    std::cin >> numOfPlanes;
    while(numOfPlanes--) {
        planeSet = false;
        std::cin.get();
        std::cin >> city1 >> city2 >> distance;
        for (auto& _city : m_cityList)
            if (_city.name() == city2)
                neighbourCity = &_city;
        for (auto& _city : m_cityList) {
            if (_city.name() == city1) {
                for (auto& _neighbour : _city.neighbours()) {
                    if (_neighbour.city().name() == city2) {
                        if (_neighbour.weight() > distance) {
                            _neighbour.setWeight(distance);
                            planeSet = true;
                            break;
                        }
                    }
                }
                if (planeSet) break;
                else _city.addNeighbour(Neighbour(neighbourCity, distance));
                break;
            }
        }
        city1.clear();
        city2.clear();
    }
}

tVector<Path> JakDojade::findPath(City *from) {
    ResultPath result = {{}, -1};
    static int city_id = 0;
    tPriorityQueue queue;
    tVector<Path> pathList;
    int actualCost;

    for (auto& neighB : from->neighbours()) {
        neighB.check(city_id);
        queue.push({from, &(neighB.city()), neighB.weight()});
    }

    while(queue.len() > 0) {
        bool ignore = false;
        Path poped_path = queue.pop();
        for (auto& path : pathList) {
            if (poped_path.to->name() == path.to->name() || poped_path.to->name() == from->name()) {
                ignore = true;
                break;
            }
        }
        if (ignore) continue;

        pathList.push(poped_path);
        actualCost = poped_path.weight;

        for (auto& neighB : poped_path.to->neighbours()) {
            if (neighB.checkID() != city_id) {
                neighB.check(city_id);
                queue.push({poped_path.to, &(neighB.city()), neighB.weight() + actualCost});
            }
        }
    }
    city_id++;
    return pathList;
}

void JakDojade::executeCommands() {
    ResultPath res{};
    tVector<Path> pathList;
    int command_num, mode;
    tString city1, city2;
    std::cin >> command_num;
    std::cin.get();
    while(command_num--) {
        std::cin >> city1 >> city2 >> mode;
        std::cin.get();

        if (city1 != city2) {
            for (auto &_city: m_cityList)
                if (_city.name() == city1) {
                    pathList = findPath(&_city);
                    break;
                }
            for(auto &path : pathList) {
                if (path.to->name() == city2) {
                    std::cout << path.weight;
                    if (mode) {
                        bool city_founded = false;
                        if (path.from->name() == city1) break;
                        tString city_name = path.from->name();
                        while(city_name != city1){
                            res.visitedCities.push(city_name);
                            for (int i = 0; i < pathList.len(); i++) {
                                if (pathList[i].to->name() == city_name) {
                                    city_name = pathList[i].from->name();
                                    city_founded = true;
                                    break;
                                }
                            }
                        }
                        for (auto &city : res.visitedCities.reverse())
                            std::cout << " " << city;
                        if (city_founded) break;
                    }
                }
            }
        }
        else  {
            res.cost = 0;
            std::cout << res.cost;
        }
        std::cout << std::endl;

        city1.clear();
        city2.clear();
        res.visitedCities.clear();
    }
}
