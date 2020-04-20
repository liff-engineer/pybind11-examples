#include "provider.hpp"

std::string formatPet(Pet const &pet)
{
    return std::string("Pet:") + pet.name;
}
