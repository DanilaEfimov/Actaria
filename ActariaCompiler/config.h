#ifndef CONFIG_H
#define CONFIG_H

#include <memory>


struct CompilerOptions;

class Config
{
    std::unique_ptr<CompilerOptions> options;

    Config();

public:

    static Config& instance();

    const CompilerOptions& getOptions() const;
};

#endif // CONFIG_H
