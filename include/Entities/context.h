#ifndef CONTEXT_H
#define CONTEXT_H

#include "Entities/entity.h"
#include "Entities/contextvar.h"
#include "Entities/contextvarfabric.h"
#include <QMap>
#include <QScopedPointer>


class Context : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;
    using value_type = QScopedPointer<ContextVar>;

private:
    QMap<QString, value_type> context;

public:
    Context();
    Context(const QMap<QString, value_type>& context);

    qsizetype size() const;

    void merge(Context&& other);

    template<typename T>
    void update(const QString& name, T&& value){
        if(!this->context.contains(name)){
            throw std::invalid_argument("no variable named " + name.toStdString() + " in context (id=" + std::to_string(this->getId()) + ")");
        }
        this->context[name] = ContextVarFabric::make<T>(name, std::forward<T>(value));
    }
    template<typename T>
    void set(const QString& name, T&& value){
        this->context[name] = ContextVarFabric::make<T>(name, std::forward<T>(value));
    }

    void remove(const QString& name);
    void clear();
};


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Context, V> {
    static constexpr bool is_fixed = false;
    static constexpr int minimum_bytes = minimumQStringSize;
    static constexpr int maximum_bytes = unlimited;

    static constexpr const char* name = "Context";
    static constexpr int minimum_words = 2;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized conetext var write interface
 */
template<abi::Version V>
struct Writer<Context, V> {
    static void write(QDataStream& out, const Context& c) {
        out << c.size();
        for(auto& variable : c.context){
            VarType type = vartype_traits<decltype(*variable.get())>::value;
            out << static_cast<int>(type);
            abi::Writer<decltype(*variable.get()), V>::write(out, *variable.get());
        }
    }

    static void write(StringListCursor& out, const Context& c) {
        out.append(entity_traits<Context, V>::name);
        out.append(QString::number(c.size()));
        for(auto& variable : c.context){
            VarType type = vartype_traits<decltype(*variable.get())>::value;
            out.append(QString::number(static_cast<int>(type)));
            abi::Writer<decltype(*variable.get()), V>::write(out, *variable.get());
        }
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<Context, V> {
    static void read(QDataStream& in, Context& c) {
        qsizetype size = 0;
        in >> size;
        for(qsizetype i = 0; i < size; i++){
            int vartype = static_cast<int>(VarType::Unknown);
            in >> vartype;
            //VarType type = vartype_traits<static_cast<VarType>(vartype)>::value;
        }
    }

    static void read(StringListCursor& in, Context& c) {
        if(in.remaining() < entity_traits<ContextVar>::minimum_words){
            qWarning() << "Reader<Context, V>: not enought words in list";
//TODO
            return;
        }

        in.skip();    // skipping this->name field
    }
};


#endif // CONTEXT_H
