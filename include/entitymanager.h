/**
 * @file entitymanager.h
 * This header defines id based container for game entities.
 * EntityManager doesn't control storage duration of
 * variables, only have straight access.
*/

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "common.h"
#include "Entities/entity.h"
#include <QHash>
#include <QBuffer>


template<utils::GameEntity T>
class EntityManager
{
public:
    using id_type = Entity::id_type;
    using container_t = QHash<id_type, T*>;

private:
    container_t objs;

public:
    /**
     * @brief EntityManager
     * @param container
     */
    EntityManager(container_t&& container = {})
        : objs(container)
    {};

    /**
     * @brief EntityManager
     * @param container
     */
    EntityManager(const container_t& container)
        : objs(container)
    {};

    ~EntityManager() = default;

    /**
     * @brief setObj
     * @param obj
     */
    void addObj(T* obj) {
        this->objs[obj->getId()] = obj;
    }

    /**
     * @brief getObj
     * @param id
     * @return entity by id
     */
    T* getObj(id_type id) const {
        if(this->contains(id)){
            return this->objs.value(id);
        }

        throw std::invalid_argument("EntityManager<T>::getObj: no such id: " + std::to_string(id));
    }

    /**
     * @brief removeObj
     * @param id
     */
    void removeObj(id_type id) {
        if(this->contains(id)){
            this->objs.remove(id);
        }
    }

    /**
     * @brief size
     * @return actual count of entities
     */
    int size() const noexcept {
        return this->objs.size();
    }

    /**
     * @brief contains
     * @param id
     * @return true if container contains such entity
     */
    bool contains(id_type id) const {
        return this->objs.contains(id);
    }

    /**
     * @brief empty
     * @return true if container is empty
     */
    bool empty() const noexcept {
        return this->objs.empty();
    }

    /**
     * @brief operator []
     * @param idx
     * @return
     */
    const T& operator[](int idx) const {
        if(this->size() <= idx)
            throw std::out_of_range("EntityManager::operator[]: index out of range");

        auto it = this->objs.begin();
        for(int i = 0; i < idx; i++) {
            it++;
        }

        return *(it.value());
    }
};

#endif // ENTITYMANAGER_H
