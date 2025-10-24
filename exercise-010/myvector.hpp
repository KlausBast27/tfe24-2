// simple myvector implementation for the exercise
#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace mystd {

template <typename T>
class myvector {
public:
    // constructors
    myvector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}

    explicit myvector(std::size_t count) : m_data(nullptr), m_size(0), m_capacity(0) {
        reserve(count);
        m_size = count;
        // default-initialize elements
        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = T{};
        }
    }

    // copy constructor (Rule of Three)
    myvector(const myvector &other) : m_data(nullptr), m_size(0), m_capacity(0) {
        if (other.m_size > 0) {
            reserve(other.m_size);
            for (std::size_t i = 0; i < other.m_size; ++i) {
                m_data[i] = other.m_data[i];
            }
            m_size = other.m_size;
        }
    }

    // copy assignment
    myvector &operator=(const myvector &other) {
        if (this == &other) return *this;
        // make a copy and swap (strong exception safety)
        myvector tmp(other);
        swap(tmp);
        return *this;
    }

    ~myvector() noexcept {
        delete[] m_data;
    }

    // basic modifiers
    void push_back(const T &value) {
        if (m_size >= m_capacity) {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        m_data[m_size++] = value;
    }

    void clear() noexcept {
        // destroy elements if needed (we assume trivially destructible or rely on T's destructor)
        m_size = 0;
    }

    void resize(std::size_t new_size) {
        if (new_size > m_capacity) reserve(new_size);
        if (new_size > m_size) {
            for (std::size_t i = m_size; i < new_size; ++i) m_data[i] = T{};
        }
        m_size = new_size;
    }

    // capacity
    std::size_t size() const noexcept { return m_size; }
    std::size_t capacity() const noexcept { return m_capacity; }

    void reserve(std::size_t new_cap) {
        if (new_cap <= m_capacity) return;
        T *new_data = new T[new_cap];
        for (std::size_t i = 0; i < m_size; ++i) new_data[i] = m_data[i];
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_cap;
    }

    // element access
    T &at(std::size_t index) {
        if (index >= m_size) throw std::out_of_range("myvector::at: index out of range");
        return m_data[index];
    }

    const T &at(std::size_t index) const {
        if (index >= m_size) throw std::out_of_range("myvector::at: index out of range");
        return m_data[index];
    }

    T &operator[](std::size_t index) noexcept { return m_data[index]; }
    const T &operator[](std::size_t index) const noexcept { return m_data[index]; }

private:
    T *m_data;
    std::size_t m_size;
    std::size_t m_capacity;

    void swap(myvector &other) noexcept {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }
};

} // namespace mystd
