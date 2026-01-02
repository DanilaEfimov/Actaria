#ifndef CONTEXTVARFABRIC_H
#define CONTEXTVARFABRIC_H

#include "utils.h"
#include "variables"
#include <memory>
#include <variant>

/**
 * @brief   The ContextVariableFabric struct
 *          Provides interface of emplace-like creating
 *          variables for Context.
 */
struct ContextVariableFabric {

    using value_types = std::variant<int, bool, QString>;

    static std::unique_ptr<ContextVar> make_default(VarType type, const QString& name = "");

    static std::unique_ptr<Counter> make_counter(const QString& name, const QString& value);

    static std::unique_ptr<Trigger> make_trigger(const QString& name, const QString& value);

    static std::unique_ptr<Counter> make_counter(const QString& name, const QByteArray& value);

    static std::unique_ptr<Trigger> make_trigger(const QString& name, const QByteArray& value);

    static std::unique_ptr<NameVar> make_namevar(const QString& name, const QByteArray& value);

    static std::unique_ptr<ContextVar> make_variable(VarType type, const QString& name, const QString& value);

    static std::unique_ptr<ContextVar> make_variable(VarType type, const QString& name, const QByteArray& value);

    static std::unique_ptr<Counter> make_counter(const QString& name, int value);

    static std::unique_ptr<NameVar> make_namevar(const QString& name, const QString& value);

    static std::unique_ptr<Trigger> make_trigger(const QString& name, bool value);

    static value_types getValue(VarType type, const QString& value);
};

#endif // CONTEXTVARFABRIC_H
