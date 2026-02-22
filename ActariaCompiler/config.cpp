#include "config.h"

#include <QString>


struct CompilerOptions {
    QString output;
    int optimizationLevel;
    bool quote;
};


Config::Config() {}

Config& Config::instance()
{
    static Config config;
    return config;
}

const CompilerOptions& Config::getOptions() const
{
    return *this->options;
}
