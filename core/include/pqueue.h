#pragma once

#include <vector>
#include <functional>
#include <cstddef>
#include <algorithm>

namespace core::container {

    template <typename T, typename Comp>
    class pqueue {
    public:
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;

        pqueue();
        ~pqueue() = default;

        void push(const T& value);
        template <typename... Args>
        void emplace(Args&&... args);
        void pop();
        const T& top() const;
        T& top();
        bool empty() const;
        std::size_t size() const;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

    private:
        std::vector<T> m_data;
        Comp m_comp;
    };

    template <typename T, typename Comp>
    pqueue<T, Comp>::pqueue() {
        m_data.reserve(16);
    }

    template <typename T, typename Comp>
    void pqueue<T, Comp>::push(const T& value) {
        m_data.push_back(value);
        std::push_heap(m_data.begin(), m_data.end(), m_comp);
    }

    template <typename T, typename Comp>
    template <typename... Args>
    void pqueue<T, Comp>::emplace(Args&&... args) {
        m_data.emplace_back(std::forward<Args>(args)...);
        std::push_heap(m_data.begin(), m_data.end(), m_comp);
    }

    template <typename T, typename Comp>
    void pqueue<T, Comp>::pop() {
        std::pop_heap(m_data.begin(), m_data.end(), m_comp);
        m_data.pop_back();
    }

    template <typename T, typename Comp>
    const T& pqueue<T, Comp>::top() const {
        return m_data.front();
    }

    template <typename T, typename Comp>
    T& pqueue<T, Comp>::top() {
        return m_data.front();
    }

    template <typename T, typename Comp>
    bool pqueue<T, Comp>::empty() const {
        return m_data.empty();
    }

    template <typename T, typename Comp>
    std::size_t pqueue<T, Comp>::size() const {
        return m_data.size();
    }

    template <typename T, typename Comp>
    typename pqueue<T, Comp>::iterator pqueue<T, Comp>::begin() {
        return m_data.begin();
    }

    template <typename T, typename Comp>
    typename pqueue<T, Comp>::iterator pqueue<T, Comp>::end() {
        return m_data.end();
    }

    template <typename T, typename Comp>
    typename pqueue<T, Comp>::const_iterator pqueue<T, Comp>::begin() const {
        return m_data.begin();
    }

    template <typename T, typename Comp>
    typename pqueue<T, Comp>::const_iterator pqueue<T, Comp>::end() const {
        return m_data.end();
    }

} // namespace core::container