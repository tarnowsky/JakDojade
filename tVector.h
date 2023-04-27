#ifndef JAKDOJADE_TVECTOR_H
#define JAKDOJADE_TVECTOR_H
#include <iostream>
#include <initializer_list>

constexpr int BUFFOR_SIZE = 20;

template <class T>
class tVector {
private:
    T* m_data;
    int m_size;
    int m_len;
    template<class U>
    friend std::ostream& operator<<(std::ostream& _out, const tVector<U>& _vector);
public:
    tVector();
    tVector(std::initializer_list<T> _initList);

    tVector(const tVector<T>& _vec);
    tVector(tVector<T>&& _vec) noexcept;

    void push(const T& _element);
    void push(T &&_element);
    void print() const;
    T pop();
    T first();
    void remove(const int& _indx);
    void insert(const T &_element, const int &_indx = -1);
    tVector<T> _reversed_();
    tVector<T>& reverse();

    tVector<T>& operator=(const tVector<T>& _other);
    tVector<T>& operator=(tVector<T>&& _other);

    T* getData() const;
    int len() const;
    int size() const;

    void clear();
    void resize(int _size);
    T* begin();
    T* end();

    T& operator[](const int& _indx) const;
    ~tVector();
};


#include "tVector.cpp"
#endif //JAKDOJADE_TVECTOR_H
