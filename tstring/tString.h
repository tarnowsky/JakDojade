#ifndef JAKDOJADE_TSTRING_H
#define JAKDOJADE_TSTRING_H
#include <iostream>
#include "tVector.h"

class tString {
private:
    mutable tVector<char> m_data;

    friend std::ostream &operator<<(std::ostream &_out, const tString &_string);
    friend std::istream &operator>>(std::istream &_in, tString &_string);

public:
    tString() = default;

    tString(const char *_data);
    tString(const tString& _str);
    tString(tString &&_str) noexcept;
    tString &operator=(tString &&_other) noexcept;
    tString &operator=(const tString &_other);

    void clear();
    bool isEmpty() const;

    char operator[](int indx);
    bool operator<(const tString &_other) const;
    bool operator<=(const tString &_other) const;
    bool operator>(const tString &_other) const;
    bool operator>=(const tString &_other) const;
    bool operator==(const tString &_other) const;
    bool operator!=(const tString &_other) const;
    bool operator==(const char* _other) const;
    tString &operator+=(const char &c);
    tString &operator+=(const char *_data);

    int len() const;
    tVector<char>& getData() const;

    char* begin() const;
    char * end() const;

    ~tString() = default;
};

#endif //JAKDOJADE_TSTRING_H
