#include <iostream>
#include <list>
#include <string>
#include <functional>
#include <cctype>
#include "Entity.h"
#include "CommandCenter.h"
using namespace std;

bool esNumero(string s)
{
    if (s.empty()) return false;

    int puntos = 0;
    int inicio = 0;
    bool tieneDigito = false;

    if (s[0] == '-' || s[0] == '+')
    {
        if (s.size() == 1) return false;
        inicio = 1;
    }

    for (int i = inicio; i < s.size(); i++)
    {
        if (s[i] == '.')
        {

            if (i == inicio || i == s.size() - 1)
                return false;


            if (!isdigit((unsigned char)s[i-1]) || !isdigit((unsigned char)s[i+1]))
                return false;

            puntos++;
            if (puntos > 1)
                return false;
        }
        else if (isdigit((unsigned char)s[i]))
        {
            tieneDigito = true;
        }
        else
        {
            return false;
        }
    }

    return tieneDigito;
}

bool esEntero(string s)
{
    if (s.empty())
    {
        return false;
    }
    int inicio = 0;
    if (s[0] == '-' or s[0] == '+')
    {
        if (s.size() == 1)
        {
            return false;
        }
        inicio = 1;
    }
    for (int i = inicio; i < s.size(); i++)
    {
        if (!isdigit((unsigned char)s[i]))
        {
            return false;
        }
    }
    return true;
}
void freeStatus(Entity& entity, const list<string>& args)
{
    if (args.size() != 0)
    {
        cout << "Error: status no recibe argumentos.\n";
        return;
    }
    cout << entity.status() << endl;
}
class DamageFunctor
{
private:
    Entity& entity;
    int contador;
public:
    DamageFunctor(Entity& e) : entity(e), contador(0)
    {
    }
    void operator()(const list<string>& args)
    {
        if (args.size() != 1)
        {
            cout << "Error: damage recibe 1 argumento.\n";
            return;
        }
        if (!esNumero(args.front()))
        {
            cout << "Error: argumento invalido en damage.\n";
            return;
        }
        float n = stof(args.front());
        entity.damage(n);
        contador++;
        cout << "Damage ejecutado. Veces usado: " << contador << endl;
    }
};

int main()
{
    Entity entity("Entidad_1");
    CommandCenter center(entity);
    center.registerCommand(
        "status",
        bind(freeStatus, ref(entity), placeholders::_1)
    );
    center.registerCommand("heal", [&entity](const list<string>& args)
    {
        if (args.size() != 1)
        {
            cout << "Error: heal recibe 1 argumento.\n";
            return;
        }
        if (!esNumero(args.front()))
        {
            cout << "Error: argumento invalido en heal.\n";
            return;
        }
        float n = stof(args.front());
        entity.heal(n);
    });
    center.registerCommand("move", [&entity](const list<string>& args)
    {
        if (args.size() != 2)
        {
            cout << "Error: move recibe 2 argumentos.\n";
            return;
        }
        list<string>::const_iterator it = args.begin();
        string a = *it;
        ++it;
        string b = *it;
        if (!esEntero(a) || !esEntero(b))
        {
            cout << "Error: argumentos invalidos en move.\n";
            return;
        }
        int dx = stoi(a);
        int dy = stoi(b);
        entity.move(dx, dy);
    });
    center.registerCommand("reset", [&entity](const list<string>& args)
    {
        if (args.size() != 0)
        {
            cout << "Error: reset no recibe argumentos.\n";
            return;
        }
        entity.reset();
    });

    center.registerCommand("Aumentar recursos", [&entity](const list<string>& args)
    {
        if (args.size() != 1)
        {
            cout << "Error: Aumentar recursos recibe 1 argumento.\n";
            return;
        }
        if (!esEntero(args.front()))
        {
            cout << "Error: argumento invalido en aumentar recursos.\n";
            return;
        }
        int n = stoi(args.front());
        entity.ataque(n);
    });

    DamageFunctor damageCmd(entity);
    center.registerCommand("damage", damageCmd);

    center.registerMacro("Macro_1", {{"move", {"1", "2"}}, {"heal", {"10"}}});
    center.registerMacro("Macro_2", {{"reset", {}}, {"status", {}}});
    center.registerMacro("Macro_3", {{"heal", {"20"}}, {"status", {}}});

    cout << "\nEjecucion de comandos validos\n";

    center.execute("status", {});
    center.execute("status", {});
    center.execute("status", {});

    center.execute("heal", {"50"});
    center.execute("heal", {"20"});
    center.execute("heal", {"5"});

    center.execute("Aumentar recursos", {"10"});
    center.execute("Aumentar recursos", {"30"});
    center.execute("Aumentar recursos", {"40"});

    center.execute("move", {"8", "5"});
    center.execute("move", {"-2", "3"});
    center.execute("move", {"0", "-4"});

    center.execute("reset", {});
    center.execute("reset", {});
    center.execute("reset", {});

    center.execute("damage", {"10"});
    center.execute("damage", {"5"});
    center.execute("damage", {"2"});

    center.executeMacro("Macro_1");
    center.executeMacro("Macro_2");
    center.executeMacro("Macro_3");

    cout << "\nEjecucion de comandos invalidos\n";

    center.execute("volar", {});
    center.execute("heal", {"abc"});
    center.execute("move", {"10"});
    center.execute("damage", {});
    center.execute("reset", {"1"});

    center.execute("status", {});

    cout << "\n---HISTORIAL---\n";
    center.mostrar_historial();

    return 0;
}