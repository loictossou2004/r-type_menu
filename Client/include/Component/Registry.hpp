/*
** EPITECH PROJECT, 2022
** registry
** File description:
** step2
*/

#ifndef registry
#define registry


#include "Sparse_array.hpp"
#include "../Entity/Entity.hpp"

/**
 * @brief Registry class
 *
 */
class Registry {
    public:
        /**
         * @brief Register Sparse Array of Component type in the registry
         *
         * @tparam Component
         * @return Sparse_array<Component>&
         */
        template <class Component>
        Sparse_array<Component> &register_component()
        {
            std::type_index key = std::type_index(typeid(Component));
            Sparse_array<Component> new_component_array;

            auto new_component = std::any(new_component_array);
            _components_arrays.emplace(key, new_component);
            auto eraseComp = [](Registry &my_registry, entity_t const &my_entity) {
                Sparse_array<Component> &searched = my_registry.get_components<Component>();
                searched[my_entity.e] = std::nullopt;
            };
            auto func = std::function<void(Registry &, entity_t const &)>(eraseComp);
            _erase_table[key] = func;
            return (std::any_cast<Sparse_array<Component>&>(_components_arrays[key]));
        }

        /**
         * @brief Get the components Sparse Array object
         *
         * @tparam Component
         * @return Sparse_array<Component>&
         */
        template <class Component>
        Sparse_array<Component> &get_components()
        {
            std::type_index key = std::type_index(typeid(Component));
            return (std::any_cast<Sparse_array<Component>&>(_components_arrays[key]));
        }

        /**
         * @brief Get the const components Sparse Array object
         *
         * @tparam Component
         * @return Sparse_array<Component> const&
         */
        template <class Component>
        Sparse_array<Component> const &get_components() const
        {
            return (std::any_cast<Sparse_array<Component> const &>(_components_arrays.find(std::type_index(typeid(Component)))));
        }

        /**
         * @brief Create new entity
         *
         * @return entity_t
         */
        entity_t spawn_entity()
        {
            unsigned int i = 0;
            if (_entity_track.size() == 0) {
                entity_t NewEntity(0);
                _entity_track.insert_at(0, std::make_optional(NewEntity));
                return NewEntity;
            } else {
                for (i = 0; i < _entity_track.size(); i++)
                    if (_entity_track[i] == std::nullopt) {
                        entity_t _NewEntity(i);
                        *_entity_track[i] = _NewEntity;
                        return _NewEntity;
                    }
                entity_t _NewEntity(i);
                _entity_track.insert_at(i, std::make_optional(_NewEntity));
                return _NewEntity;
            }
        }

        /**
         * @brief Get an entity with some index
         *
         * @param idx
         * @return entity_t
         */
        entity_t entity_from_index(std::size_t idx)
        {
            return(std::any_cast<entity_t>(_entity_track[idx]));
        }
        void kill_entity(entity_t const &e)
        {
            for (unsigned int i = 0; i < _entity_track.size(); i++)
                if (_entity_track[i] == e) {
                    _entity_track[i] = std::nullopt;
                    break;
                }
        }

        /**
         * @brief Add a component into the right Sparse Array
         *
         * @tparam Component
         * @param to
         * @param c
         * @return Sparse_array<Component>::reference_type
         */
        template <typename Component>
        typename Sparse_array<Component>::reference_type add_component(entity_t const &to, Component &&c)
        {
            Sparse_array<Component> &tmp = get_components<Component>();
            return (tmp.insert_at(to.e, c));
        }

        /**
         * @brief Add a component into the right Sparse Array
         *
         * @tparam Component
         * @param to
         * @param c
         * @return Sparse_array<Component>::reference_type
         */
        template <typename Component>
        typename Sparse_array<Component>::reference_type add_component(entity_t const &to, Component &c)
        {
            Sparse_array<Component> &tmp = get_components<Component>();
            return (tmp.insert_at(to.e, c));
        }

        /**
         * @brief Build and emplace a new Component object into right Sparse Array
         *
         * @tparam Component
         * @tparam Params
         * @param to
         * @param p
         * @return Sparse_array<Component>::reference_type
         */
        template <typename Component, typename ... Params>
        typename Sparse_array<Component>::reference_type emplace_component(entity_t const &to, Params &&... p)
        {
            Sparse_array<Component> &tmp = get_components<Component>();
            return (std::forward<Component>(tmp.emplace_at(to.e, p ...)));
        }

        /**
         * @brief Remove a component from the right sparse array
         *
         * @tparam Component
         * @param from
         */
        template <typename Component>
        void remove_component(entity_t const &from)
        {
            Sparse_array<Component> &tmp = get_components<Component>();
            tmp.erase(from.e);
        }
        //méthode pour ajouter une Position
    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::unordered_map<std::type_index, std::function<void(Registry &, entity_t const &)>> _erase_table;
        Sparse_array<std::optional<entity_t>> _entity_track;
};


#endif /* !registry */
