#ifndef TAREA3_ENTITY_H
#define TAREA3_ENTITY_H
#include <string>

using namespace std;

class Entity
{
private:
    int x;
    int y;
    float vida;
    string nombre;
    int nivel;
    int recursos;

public:
    Entity(string nombre_);
    ~Entity() = default;
    void move(int dx, int dy);
    void heal(float amount);
    void damage(float amount);
    void reset();
    void rename(string name_);
    void ataque(int ataque_);
    string status() const;
};

#endif //TAREA3_ENTITY_H