#pragma once

#include <vector>
#include <functional>
#include <cstddef>
#include <algorithm>

namespace core::container {

    /// A priority queue implemented using a std::vector.
    /// \tparam T The type of elements stored in the priority queue.
    /// \tparam Comp The comparison functor used to order the elements.
    template <typename T, typename Comp>
    class pqueue {
    public:
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;

        /// Constructs an empty priority queue.
        pqueue();
        ~pqueue() = default;

        /// Pushes a new element onto the priority queue.
        /// \param value The value of the element to push.
        void push(const T& value);

        /// Constructs and pushes a new element onto the priority queue.
        /// \tparam Args The types of the arguments to forward to the constructor of T.
        /// \param args The arguments to forward to the constructor of T.
        template <typename... Args>
        void emplace(Args&&... args);

        /// Removes the top element from the priority queue.
        void pop();

        /// Returns a reference to the top element in the priority queue.
        /// \return A reference to the top element.
        const T& top() const;

        /// Returns a reference to the top element in the priority queue.
        /// \return A reference to the top element.
        T& top();

        /// Checks if the priority queue is empty.
        /// \return True if the priority queue is empty, false otherwise.
        bool empty() const;

        /// Returns the number of elements in the priority queue.
        /// \return The number of elements.
        std::size_t size() const;

        /// Returns an iterator to the beginning of the priority queue.
        /// \return An iterator to the beginning.
        iterator begin();

        /// Returns an iterator to the end of the priority queue.
        /// \return An iterator to the end.
        iterator end();

        /// Returns a const iterator to the beginning of the priority queue.
        /// \return A const iterator to the beginning.
        const_iterator begin() const;

        /// Returns a const iterator to the end of the priority queue.
        /// \return A const iterator to the end.
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