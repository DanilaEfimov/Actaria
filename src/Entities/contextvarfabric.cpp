#include "Entities/contextvarfabric.h"

#ifdef ACTARIA_TEST
#include <random>
#include <type_traits>

/**
 * @brief random_value
 * @return
 */
template<typename T>
T random_value(){
    static_assert(std::is_trivially_copyable_v<T>,
                  "random_value<T>: T must be trivially copyable");

    union u {
        T value;
        std::byte bytes[sizeof(T)];
    } data;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for (auto& b : data.bytes)
        b = static_cast<std::byte>(dist(gen));

    return data.value;
}

/**
 * @brief random_variable
 * @return
 */
std::unique_ptr<ContextVar> random_variable() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 2);

    int type = dist(gen);

    QString randomName = QString("var_%1").arg(random_value<uint32_t>());

    switch (type) {
    case 0: // Counter
        return std::make_unique<Counter>(
            random_value<Counter::value_type>(),
            randomName
            );

    case 1: // Trigger
        return std::make_unique<Trigger>(
            static_cast<Trigger::value_type>(random_value<uint8_t>() & 1),
            randomName
            );

    case 2: // NameVar
        return std::make_unique<NameVar>(
            QString::number(random_value<uint32_t>()),
            randomName
            );

    default:
        return nullptr;
    }
}
#endif
