#include "tString.h"


tString::tString(const char *_data) {
    for (int i = 0; _data[i] != '\0'; i++)
        m_data.push(_data[i]);
}

tString::tString(const tString &_str) {
    m_data = _str.m_data;
}

tString::tString(tString &&_str) noexcept {
    m_data = _str.m_data;
}

std::ostream &operator<<(std::ostream &_out, const tString &_string) {
    for (int i = 0; i < _string.m_data.len(); i++)
        _out << _string.m_data[i];
    return _out;
}

tString &tString::operator=(tString &&_other) noexcept {
    m_data = std::move(_other.m_data);
    return *this;
}

tString &tString::operator=(const tString &_other) = default;

void tString::clear() {
    m_data.clear();
}

bool tString::isEmpty() const {
    return m_data.len() > 0;
}

char tString::operator[](int indx) {
    return 0;
}

bool tString::operator<(const tString &_other) const {
    return m_data.len() < _other.len();
}

bool tString::operator<=(const tString &_other) const {
    return m_data.len() <= _other.len();
}

bool tString::operator>(const tString &_other) const {
    return m_data.len() > _other.len();
}

bool tString::operator>=(const tString &_other) const {
    return m_data.len() >= _other.len();
}

bool tString::operator==(const tString &_other) const {
    if (len() != _other.len()) return false;
    for (int i = 0; i < len(); i++)
        if (m_data[i] != _other.m_data[i])
            return false;
    return true;
}

bool tString::operator!=(const tString &_other) const {
    return !(*this == _other);
}

bool tString::operator==(const char *_other) const {
    int otherLen = 0;
    while(_other[otherLen++] != '\0');
    otherLen--;
    if (len() != otherLen) return false;
    for (int i = 0; i < len(); i++)
        if (m_data[i] != _other[i])
            return false;
    return true;
}



tString &tString::operator+=(const char &c) {
    m_data.push(c);
    return *this;
}

tString &tString::operator+=(const char *_data) {
    for (int i = 0; _data[i] != '\0'; i++)
        m_data.push(_data[i]);
    return *this;
}

int tString::len() const {
    return m_data.len();
}

tVector<char> &tString::getData() const {
    return m_data;
}

char *tString::begin() const{
    return m_data.begin();
}

char * tString::end() const {
    return m_data.end();
}

std::istream &operator>>(std::istream &_in, tString &_string) {
    int c;
    while((c = _in.get()) != ' ' && c != '\n' && c != EOF && c != '\t') _string += (char)c;
    return _in;
}



