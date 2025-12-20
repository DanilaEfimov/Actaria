#include "Entities/dialog.h"


namespace {
    constexpr const char* typeName = "Dialog";
};


Dialog::Dialog()
    : Entity(), root(-1) {}

quint32 Dialog::minimumSize() const
{
}

quint32 Dialog::minimumStrings() const
{
}

Entity::hash_type Dialog::hash() const
{
    return utils::fnv1a_64(typeName);
}

size_t Dialog::size() const
{
}

QByteArray Dialog::serialize() const
{
}

void Dialog::deserialize(const QByteArray &)
{
}

QString Dialog::represent() const
{
}

void Dialog::fromString(const QStringList &)
{
}

/**
 * @brief Dialog::switchBranch
 * @param variant
 * @throw invalid_argument if such variant doesn't exists for current root
 * @throw logic_error if switched branch doesn't contains in this dialog
 * switch dialog branch by variant for current root
 */
void Dialog::switchBranch(int variant)
{
    auto it = this->nodes.find(this->root);
    if (it == this->nodes.end()) {
        throw std::logic_error(
            "Dialog::switchBranch: root node not found: root=" +
            std::to_string(this->root)
            );
    }

    DialogNode& currentRoot = it.value();
    id_type switchedBranch = currentRoot.getChild(variant);

    if (switchedBranch == UNDEFINED_ID) {
        throw std::invalid_argument(
            "Dialog::switchBranch: invalid variant: "
            "(root=" + std::to_string(this->root) +
            "), (variant=" + std::to_string(variant) + ")"
            );
    }

    if (!this->nodes.contains(switchedBranch)) {
        throw std::logic_error(
            "Dialog::switchBranch: chosen branch not in dialog: "
            "(root=" + std::to_string(this->root) +
            "), (switchedBranch=" + std::to_string(switchedBranch) + ")"
            );
    }

    this->root = switchedBranch;
}

