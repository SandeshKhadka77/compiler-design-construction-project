#ifndef MINI_COMPILER_SYMBOL_TABLE_H
#define MINI_COMPILER_SYMBOL_TABLE_H

#include <map>
#include <string>

enum class ValueType {
    Int,
    Float,
    String,
    Bool,
    Unknown
};

std::string valueTypeToString(ValueType type);
ValueType valueTypeFromString(const std::string& name);

struct Symbol {
    std::string name;
    ValueType type;
};

class SymbolTable {
public:
    bool define(const std::string& name, ValueType type);
    const Symbol* lookup(const std::string& name) const;
    bool contains(const std::string& name) const;
    std::size_t size() const;

private:
    std::map<std::string, Symbol> symbols;
};

#endif
