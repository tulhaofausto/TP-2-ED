#include "depot.hpp"

Depot::Depot(int id, const std::string& name) : id(id), name(name) {};

bool Depot::operator==(const Depot& other) const {
    return this->id == other.id;
}