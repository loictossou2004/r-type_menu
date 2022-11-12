/*
** EPITECH PROJECT, 2022
** step1
** File description:
** sparse_array
*/

#ifndef sparse_array
#define sparse_array

    #include <algorithm>
    #include <cmath>
    #include <cstring>
    #include <functional>
    #include <fstream>
    #include <iostream>
    #include <list>
    #include <map>
    #include <any>
    #include <unordered_map>
    #include <memory>
    #include <sstream>
    #include <csignal>
    #include <string>
    #include <vector>
    #include <chrono>
    #include <thread>
    #include <typeindex>
    #include <optional>

/**
 * @brief Sparse Array of Component type class
 *
 * @tparam Component
 */
template <typename Component>
class Sparse_array {
    public :
        using value_type = std::optional<Component>;
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

    public:

        /**
         * @brief Construct a new Sparse_array object
         *
         */
        Sparse_array(){};

        /**
         * @brief Construct a new Sparse_array object
         *
         * @param t
         */
        Sparse_array(Sparse_array const &t)
        {
            //if (_data != t._data)
                _data = t._data;
        }

        /**
         * @brief Construct a new Sparse_array object
         *
         * @param source
         */
        Sparse_array(Sparse_array&& source) noexcept
        {
            _data = std::move(source._data);
        }

        /**
         * @brief Destroy the Sparse_array object
         *
         */
        ~Sparse_array(){};

        Sparse_array &operator=(Sparse_array const &t)
        {
            //if (_data != t._data)
                _data = t._data;
            return *this;
        }

        /**
         * @brief Overloading operator= of Sparse Array
         *
         * @param source
         * @return Sparse_array&
         */
        Sparse_array &operator=( Sparse_array &&source) noexcept
        {
            //if (_data != source._data)
                _data = std::move(source._data);
            return *this;
        }

        /**
         * @brief Overloading operator[] of Sparse Array
         *
         * @param idx
         * @return reference_type
         */
        reference_type operator [](size_t idx)
        {
            return _data[idx];
        }

        /**
         * @brief Overloading operator[] of Sparse Array
         *
         * @param idx
         * @return const_reference_type
         */
        const_reference_type operator [](size_t idx) const
        {
            return _data[idx];
        }

        /**
         * @brief Return an operator on the start of a Sparse Array
         *
         * @return iterator
         */
        iterator begin()
        {
            return _data.begin();
        }

        /**
         * @brief Return an const operator on the start of a Sparse Array
         *
         * @return const_iterator
         */
        const_iterator begin() const
        {
            return _data.begin();
        }

        /**
         * @brief Return an const operator on the start of a Sparse Array
         *
         * @return const_iterator
         */
        const_iterator cbegin() const
        {
            return _data.cbegin();
        }

        /**
         * @brief Return an iterator on the end of a Sparse Array
         *
         * @return iterator
         */
        iterator end()
        {
            return _data.end();
        }

        /**
         * @brief Return an const iterator on the end of a Sparse Array
         *
         * @return const_iterator
         */
        const_iterator end() const
        {
            return _data.end();
        }

        /**
         * @brief Return an const iterator on the end of a Sparse Array
         *
         * @return const_iterator
         */
        const_iterator cend() const
        {
            return _data.cend();
        }

        /**
         * @brief Return the size of the Sparse_array
         *
         * @return size_type
         */
        size_type size () const
        {
            return _data.size();
        }

        /**
         * @brief Insert Component at a position in the Sparse_array
         *
         * @param pos
         * @param my_cp
         * @return reference_type
         */
        reference_type insert_at(size_type pos, Component const &my_cp)
        {
            if (_data.size() <= pos) {
                unsigned int t = pos - _data.size();
                for (unsigned int i = 0; i <= t; i++)
                    _data.push_back(std::nullopt);
            }
            _data[pos] = std::nullopt;
            _data[pos] = my_cp;
            return _data[pos];
        }

        /**
         * @brief Insert Component at a position in the Sparse_array
         *
         * @param pos
         * @param my_cp
         * @return reference_type
         */
        reference_type insert_at(size_type pos, Component &&my_cp)
        {
            if (_data.size() <= pos) {
                unsigned int t = pos - _data.size();
                for (unsigned int i = 0; i <= t; i++)
                    _data.push_back(std::nullopt);
            }
            _data[pos] = std::nullopt;
            _data[pos] = my_cp;
            return _data[pos];
        }

        /**
         * @brief Build and emplace a Component at a Position in the Sparse_array
         *
         * @tparam Params
         * @param pos
         * @param param
         * @return reference_type
         */
        template <class ... Params>
        reference_type emplace_at(size_type pos , Params && ... param)
        {
            if (_data.size() <= pos) {
                unsigned int t = pos - _data.size();
                for (unsigned int i = 0; i <= t; i++)
                    _data.push_back(std::nullopt);
            }
            _data.get_allocator().destroy(&_data[pos]);
            _data.get_allocator().construct(&_data[pos], param ...);
            return (_data[pos]);
        }

        /**
         * @brief Erase some component
         *
         * @param pos
         */
        void erase(size_type pos)
        {
            if (_data.size() < pos)
                return;
            _data[pos] = std::nullopt;
        }

        /**
         * @brief Get the index of an object in the Sparse Array
         *
         * @param component
         * @return size_type
         */
        size_type get_index(value_type const &component) const
        {
            for(unsigned int i = 0; i < _data.size(); i++) {
                if (std::addressof(_data[i]) == std::addressof(component))
                    return i;
            }
        }

    private:
        container_t _data;
};
#endif /* !sparse_array */
