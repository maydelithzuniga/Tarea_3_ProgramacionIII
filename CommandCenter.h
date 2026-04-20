#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <string>
#include <list>
#include <map>
#include <functional>
#include "Entity.h"

using Command = std::function<void(const std::list<std::string>&)>;

class CommandCenter
{
private:
    Entity& entity;
    std::map<std::string, Command> comandos;
    std::map<std::string, std::list<std::pair<std::string, std::list<std::string>>>> macros;
    std::list<std::string> historial;

public:
    CommandCenter(Entity& e);
    void registerCommand(const std::string& name, Command cmd);
    void execute(const std::string& name, const std::list<std::string>& args);
    void removeCommand(const std::string& name);
    void mostrar_historial();
    void registerMacro(const std::string& name,const std::list<std::pair<std::string, std::list<std::string>>>& steps);
    void executeMacro(const std::string& name);
};

#endif