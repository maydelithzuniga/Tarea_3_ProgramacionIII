
Sistema de comandos en C++ que simula el control de una entidad (personaje/unidad) mediante un centro de comandos con soporte para comandos individuales y macros (secuencias de comandos).

## Autores

- Maydelith Zuñiga
- Joaquin Llallire

## Descripción

El proyecto implementa dos clases principales:

- **`Entity`**: representa una entidad con posición (x, y), vida, nivel y recursos. Expone operaciones como moverse, curarse, recibir daño, reiniciar su estado y aumentar recursos.
- **`CommandCenter`**: administra el registro y ejecución de comandos sobre una `Entity`. Cada comando es un objeto `std::function` (puede ser una función libre, una lambda o un funtor), lo que permite validar argumentos y ejecutar lógica de forma flexible. También permite agrupar comandos en **macros** y mantiene un **historial** con el estado de la entidad antes y después de cada comando ejecutado.

## Estructura del repositorio

| Archivo | Descripción |
|---|---|
| `Entity.h` / `Entity.cpp` | Definición e implementación de la clase `Entity`. |
| `CommandCenter.h` / `CommandCenter.cpp` | Definición e implementación de la clase `CommandCenter`. |
| `main.cpp` | Programa principal: registra comandos y macros, y ejecuta pruebas con casos válidos e inválidos. |

## Comandos disponibles

| Comando | Argumentos | Descripción |
|---|---|---|
| `status` | ninguno | Muestra el estado actual de la entidad. |
| `heal` | 1 (número) | Aumenta la vida de la entidad. |
| `damage` | 1 (número) | Reduce la vida de la entidad y cuenta cuántas veces se ha usado. |
| `move` | 2 (enteros) | Mueve la entidad según `dx` y `dy`. |
| `reset` | ninguno | Reinicia posición, vida y nivel a sus valores por defecto. |
| `Aumentar recursos` | 1 (entero) | Incrementa los recursos de la entidad. |

Cada comando valida el número y tipo de argumentos recibidos, mostrando un mensaje de error descriptivo si no son correctos.

## Macros

Las macros permiten ejecutar una secuencia de comandos en orden. En `main.cpp` se registran tres ejemplos:

- **`Macro_1`**: `move(1, 2)` → `heal(10)`
- **`Macro_2`**: `reset()` → `status()`
- **`Macro_3`**: `heal(20)` → `status()`

## Historial

`CommandCenter` guarda un historial de texto con el estado de la entidad antes y después de cada comando ejecutado, accesible mediante `mostrar_historial()`.

## Compilación y ejecución

Requiere un compilador compatible con C++11 o superior (por el uso de `std::function`, lambdas y listas de inicialización).

```bash
g++ -std=c++11 main.cpp Entity.cpp CommandCenter.cpp -o tarea3
./tarea3
```

## Ejemplo de salida

El programa `main.cpp` ejecuta primero una serie de comandos válidos (status, heal, aumentar recursos, move, reset, damage y las tres macros), y luego una serie de comandos inválidos (comando inexistente, argumentos faltantes o con tipo incorrecto) para demostrar el manejo de errores. Al final imprime el historial completo de comandos ejecutados.
