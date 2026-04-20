#include "CommandCenter.h"
#include <iostream>
using namespace std;

CommandCenter::CommandCenter(Entity& e) : entity(e)
{
}
void CommandCenter::registerCommand(const string& name, Command cmd)
{
    comandos[name] = cmd;
}
void CommandCenter::execute(const string& name, const list<string>& args)
{
    map<string, Command>::iterator it = comandos.find(name);
    if (it == comandos.end())
    {
        cout << "Comando no encontrado.\n";
        return;
    }
    string antes = entity.status();
    it->second(args);
    string despues = entity.status();
    historial.push_back("Comando realizado: " + name + " " + antes + " -> " + despues);
}
void CommandCenter::removeCommand(const string& name)
{
    map<string, Command>::iterator it = comandos.find(name);
    if (it == comandos.end())
    {
        cout << "No existe el comando.\n";
        return;
    }
    comandos.erase(it);
    historial.push_back("Se elimino el comando " + name);
}
void CommandCenter::mostrar_historial()
{
    list<string>::iterator it = historial.begin();
    for (; it != historial.end(); ++it)
    {
        cout << *it << "\n";
    }
}
void CommandCenter::registerMacro(
    const string& name,
    const list<pair<string, list<string>>>& steps)
{
    macros[name] = steps;
}
void CommandCenter::executeMacro(const string& name)
{
    map<string, list<pair<string, list<string>>>>::iterator it = macros.find(name);
    if (it == macros.end())
    {
        cout << "Macro Comando no encontrado.\n";
        return;
    }
    list<pair<string, list<string>>>::iterator it2;
    for (it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
        string nombre = it2->first;
        list<string> args = it2->second;
        map<string, Command>::iterator itComando = comandos.find(nombre);
        if (itComando == comandos.end())
        {
            cout << "Error: el comando \"" << nombre << "\" no existe dentro del macro.\n";
            return;
        }
        execute(nombre, args);
    }
}