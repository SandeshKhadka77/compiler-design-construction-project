#include "symbol_table.h"

std::string valueTypeToString(ValueType type) {
    switch (type) {
        case ValueType::Int:
            return "int";
        case ValueType::Float:
            return "float";
        case ValueType::String:
            return "string";
        case ValueType::Bool:
            return "bool";
        case ValueType::Unknown:
            return "unknown";
    }
    return "unknown";
}

ValueType valueTypeFromString(const std::string& name) {
    if (name == "int") return ValueType::Int;
    if (name == "float") return ValueType::Float;
    if (name == "string") return ValueType::String;
    if (name == "bool") return ValueType::Bool;
    return ValueType::Unknown;
}

bool SymbolTable::define(const std::string& name, ValueType type) {
    return symbols.emplace(name, Symbol{name, type}).second;
}

const Symbol* SymbolTable::lookup(const std::string& name) const {
    const auto iterator = symbols.find(name);
    return iterator == symbols.end() ? nullptr : &iterator->second;
}

bool SymbolTable::contains(const std::string& name) const {
    return lookup(name) != nullptr;
}

std::size_t SymbolTable::size() const {
    return symbols.size();
}
