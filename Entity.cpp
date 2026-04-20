#include "Entity.h"
#include <sstream>
using namespace std;

Entity::Entity(string nombre_)
{
    x = 0;
    y = 0;
    vida = 100;
    nombre = nombre_;
    nivel = 1;
    recursos = 10;
}
void Entity::rename(string name_)
{
    nombre = name_;
}
void Entity::move(int dx, int dy)
{
    x += dx;
    y += dy;
}
void Entity::heal(float amount)
{
    vida += amount;
}
void Entity::damage(float amount)
{
    vida -= amount;
}
void Entity::reset()
{
    x = 0;
    y = 0;
    vida = 100;
    nivel = 1;
}
void Entity::ataque(int ataque_)
{
    recursos += ataque_;
}
string Entity::status() const
{
    ostringstream oss;
    oss << "\nEstatus\n"
        << "Nombre: " << nombre
        << " | Pos(" << x << ", " << y << ")"
        << " | Vida: " << vida
        << " | Nivel: " << nivel
        << " | Recursos: " << recursos;

    return oss.str();
}