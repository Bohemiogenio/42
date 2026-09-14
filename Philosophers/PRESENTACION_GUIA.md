# 🍽️ PRESENTACIÓN PROYECTO PHILOSOPHERS - GUÍA COMPLETA

## ESTRUCTURA DE PRESENTACIÓN (15-20 MIN)

---

## 📌 PARTE 1: INTRODUCCIÓN (2 MIN)

### ¿Qué es el Problema de los Filósofos Comensales?

**Concepto Clásico:**
```
5 filósofos sentados alrededor de una mesa redonda
• Cada filósofo tiene un plato
• Entre cada par de filósofos hay 1 tenedor
• Total: 5 tenedores

CICLO:
1. Piensa
2. Come (necesita 2 tenedores)
3. Duerme
4. Repite

DESAFÍO: Evitar DEADLOCK (todos esperando recursos)
```

**Por qué es importante?**
- Problema clásico de concurrencia
- Enseña sincronización de threads
- Demuestra race conditions
- Real en sistemas distribuidos

---

## 🎯 PARTE 2: REQUISITOS DEL PROYECTO (2 MIN)

### Parámetros de Entrada
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [nb_of_times_each_philosopher_must_eat]
```

**Explicación de cada parámetro:**

| Parámetro | Símbolo | Significado |
|-----------|---------|------------|
| number_of_philosophers | n_philo | Cantidad de filósofos (1-200) |
| time_to_die | time_die | ms sin comer antes de morir |
| time_to_eat | time_eat | ms que tarda en comer |
| time_to_sleep | time_sleep | ms que duerme |
| nb_of_times_each_philosopher_must_eat | must_eat | Opcional: comidas necesarias |

**Ejemplo de ejecución:**
```bash
./philo 5 800 200 200      # 5 filósofos, mueren si no comen en 800ms
./philo 4 410 200 200 7    # 4 filósofos, cada uno debe comer 7 veces
```

### Output Esperado
```
[timestamp_ms] [philo_id] [status]

STATUS POSIBLES:
- "is eating"           → Filósofo comiendo
- "is sleeping"         → Filósofo durmiendo
- "is thinking"         → Filósofo pensando
- "has taken a fork"    → Tomó un tenedor
- "died"                → Filósofo murió
```

**Ejemplo de salida:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 2 has taken a fork
...
```

---

## 🏗️ PARTE 3: ARQUITECTURA DEL PROYECTO (3 MIN)

### Estructura de Datos Principal

```c
typedef struct s_philo {
    int id;                      // IDs 1 a n_philo
    pthread_t thread;            // Thread del filósofo
    pthread_mutex_t *left_fork;  // Tenedor izquierdo
    pthread_mutex_t *right_fork; // Tenedor derecho
    long long last_meal_ms;      // Timestamp última comida
    int meals_eaten;             // Contador de comidas
    t_program *prog;             // Referencia al programa
}
```

```c
typedef struct s_program {
    int n_philo;                 // Cantidad de filósofos
    int time_die;                // ms para morir
    int time_eat;                // ms para comer
    int time_sleep;              // ms para dormir
    int must_eat;                // Comidas requeridas (-1 si no especificado)
    long long start_ms;          // Timestamp inicio simulación
    int stop;                    // Bandera de parada
    pthread_mutex_t *forks;      // Array de mutex (tenedores)
    pthread_mutex_t print_mtx;   // Mutex para print
    pthread_mutex_t meal_mtx;    // Mutex para comidas
    pthread_mutex_t stop_mtx;    // Mutex para stop flag
    t_philo *philos;             // Array de filósofos
}
```

### Organización de Archivos

```
philo/
├── philo.h           → Headers y estructuras
├── main.c            → Punto de entrada
├── parse.c           → Parseo de argumentos
├── init.c            → Inicialización de programa
├── destroy.c         → Liberación de recursos
├── simulation.c      → Control de simulación
├── routine.c         → Rutina de filósofo
├── boss.c            → Thread supervisor (detección de muerte)
├── forks.c           → Lógica de tomar tenedores
├── eat.c             → Lógica de comer
├── print.c           → Funciones de impresión
├── stop.c            → Control de parada
├── time.c            → Funciones de tiempo
├── utils.c           → Funciones auxiliares
└── Makefile          → Compilación
```

---

## ⚙️ PARTE 4: FLUJO DE EJECUCIÓN (4 MIN)

### Flujo Principal

```
START
  ↓
parse_args              → Validar argumentos (4-5 parámetros)
  ↓
init_program            → Inicializar estructuras datos
  ├─ Crear array de forks (mutexes)
  ├─ Crear array de filósofos
  ├─ Inicializar todos los mutexes
  └─ Asignar tenedores a cada filósofo
  ↓
start_simulation        → Iniciar simulación
  ├─ Registrar timestamp inicio (start_ms)
  ├─ Crear n_philo threads (filósofos)
  ├─ Crear 1 thread boss (supervisor)
  ├─ Esperar a terminar boss
  └─ Esperar a terminar todos los filósofos
  ↓
destroy_program         → Liberar memoria
  ├─ Destruir todos los mutexes
  ├─ Liberar arrays
  └─ Liberar estructuras
  ↓
END
```

### Ciclo de cada Filósofo

```
philo_routine (ejecutado en paralelo por cada filósofo)
  ↓
initial_delay           → Desalternizar (filósofos pares esperan 1ms)
  ↓
LOOP (mientras !should_stop):
  ├─ take_forks()       → Obtener 2 tenedores
  │  ├─ Lock fork izquierda
  │  ├─ Print "has taken a fork"
  │  ├─ Lock fork derecha
  │  └─ Print "has taken a fork"
  │
  ├─ philo_eat()        → Comer
  │  ├─ Actualizar last_meal_ms
  │  ├─ Print "is eating"
  │  ├─ smart_sleep(time_eat)
  │  ├─ Incrementar meals_eaten
  │  └─ Liberar ambos tenedores (unlock)
  │
  ├─ Print "is sleeping"
  ├─ smart_sleep(time_sleep)
  │
  └─ Print "is thinking"
  ↓
RETURN
```

### Ciclo del Boss (Supervisor)

```
boss_routine (thread supervisor)
  ↓
LOOP (mientras !should_stop):
  ├─ Para cada filósofo:
  │  └─ check_philo_death()
  │     ├─ Si now_ms() - last_meal > time_die:
  │     │  ├─ Set stop = 1
  │     │  ├─ Print "[timestamp] [id] died"
  │     │  └─ TERMINAR
  │     └─ Si no: continuar
  │
  ├─ all_ate_enough()
  │  └─ Si todos comieron must_eat veces:
  │     ├─ Set stop = 1
  │     └─ TERMINAR
  │
  └─ usleep(1000)  → Revisar cada 1ms
  ↓
RETURN
```

---

## 🔐 PARTE 5: SINCRONIZACIÓN Y MUTEXES (3 MIN)

### ¿Por qué Mutexes?

**Problema sin sincronización:**
```
Thread 1 (Philo 1) y Thread 2 (Philo 2) acceden a last_meal_ms simultáneamente

Sin mutex:
Time 1: Philo 1 lee   last_meal_ms = 100
Time 2: Philo 2 lee   last_meal_ms = 100
Time 3: Philo 1 escribe last_meal_ms = 150
Time 4: Philo 2 escribe last_meal_ms = 110    ❌ CORRUPCIÓN DE DATOS!
```

### Tres Mutexes Utilizados

#### 1. **print_mtx** - Sincroniza Salida
```c
void print_status(t_philo *philo, const char *msg) {
    pthread_mutex_lock(&philo->prog->print_mtx);
    // Sección crítica: nadie más puede imprimir
    if (!should_stop(philo->prog)) {
        ts = now_ms() - philo->prog->start_ms;
        printf("%lld %d %s\n", ts, philo->id, msg);
    }
    pthread_mutex_unlock(&philo->prog->print_mtx);
}
```
**Beneficio:** Evita que prints de diferentes threads se mezclen

#### 2. **meal_mtx** - Sincroniza Comidas
```c
// Lectura segura
static long long get_last_meal(t_philo *philo) {
    pthread_mutex_lock(&philo->prog->meal_mtx);
    long long last = philo->last_meal_ms;
    pthread_mutex_unlock(&philo->prog->meal_mtx);
    return last;
}

// Escritura segura
static void set_last_meal(t_philo *philo) {
    pthread_mutex_lock(&philo->prog->meal_mtx);
    philo->last_meal_ms = now_ms();
    pthread_mutex_unlock(&philo->prog->meal_mtx);
}
```
**Beneficio:** Lectura/escritura de last_meal_ms es atómica

#### 3. **stop_mtx** - Sincroniza Bandera de Parada
```c
int should_stop(t_program *p) {
    pthread_mutex_lock(&p->stop_mtx);
    int val = p->stop;
    pthread_mutex_unlock(&p->stop_mtx);
    return val;
}

void set_stop(t_program *p) {
    pthread_mutex_lock(&p->stop_mtx);
    p->stop = 1;
    pthread_mutex_unlock(&p->stop_mtx);
}
```
**Beneficio:** Parada limpia y sincronizada de todos los threads

#### 4. **Tenedores (forks)** - Sincroniza Acceso a Recursos
```c
static void lock_forks(t_philo *philo) {
    // Orden decide el ID del filósofo:
    // Pares: tenedor derecho primero
    // Impares: tenedor izquierdo primero
    
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
    } else {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
    }
    print_status(philo, "has taken a fork");
}
```
**Beneficio:** Evita deadlock desalternizando el orden de toma de tenedores

---

## 🚫 PARTE 6: PREVENCIÓN DE DEADLOCK (2 MIN)

### Problema de Deadlock

```
Escenario de 5 filósofos SIN protección:

Philo 1: Toma tenedor izquierdo (1)
Philo 2: Toma tenedor izquierdo (2)
Philo 3: Toma tenedor izquierdo (3)
Philo 4: Toma tenedor izquierdo (4)
Philo 5: Toma tenedor izquierdo (5)

AHORA TODOS ESPERAN POR EL TENEDOR DERECHO...
¡DEADLOCK! 💀 (el orden cíclico causa espera infinita)
```

### Solución Implementada: Orden Alternado

```c
// ANTES (puede causar deadlock):
// pthread_mutex_lock(left_fork);
// pthread_mutex_lock(right_fork);

// DESPUÉS (previene deadlock):
if (philo->id % 2 == 0) {  // Filósofos PARES
    lock(right_fork);
    lock(left_fork);
} else {                     // Filósofos IMPARES
    lock(left_fork);
    lock(right_fork);
}
```

**¿Por qué funciona?**
- Los filósofos no crean un ciclo de espera
- Hay asimetría: unos toman derecha primero, otros izquierda
- Garantiza que siempre puede avanzar alguien

**Visualización:**
```
Mesa circular 5 filósofos (orden modificado):

      1 (IMPAR - izq primero)
     / \
    5   2 (PAR - der primero)
   / \ / \
  4   X   3 (IMPAR - izq primero)
   \ / \ /
    +   +
    
Con este orden alternado, es imposible que todos 
queden bloqueados esperando al mismo tiempo.
```

---

## ⏱️ PARTE 7: FUNCIONES CLAVE (3 MIN)

### 1. **now_ms()** - Obtener Timestamp Actual

```c
long long now_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}
```
**Uso:** Todos los timestamps se manejan en milisegundos desde el epoch

---

### 2. **smart_sleep()** - Dormir con Interrupción Limpia

```c
void smart_sleep(long long ms, t_program *p) {
    long long end;
    
    end = now_ms() + ms;
    while (!should_stop(p) && now_ms() < end)
        usleep(200);  // Check cada 200μs
}
```

**¿Por qué no `sleep()` o `usleep()` directo?**
- `usleep()` no se puede interrumpir
- Con `smart_sleep()` se detiene limpiamente si un filósofo muere
- Permite reacción inmediata a eventos (stop signal)

**Ejemplo:**
```
Philo comiendo por 1000ms, pero muere en ms 500:
- Sin smart_sleep: Sigue durmiendo hasta ms 1000 (error)
- Con smart_sleep: Se detiene en ms 500 (correcto)
```

---

### 3. **take_forks()** - Obtener Tenedores

```c
int take_forks(t_philo *philo) {
    if (philo->prog->n_philo == 1)
        return (single_philo_case(philo));  // Caso especial!
    
    lock_forks(philo);
    return (0);
}
```

**Caso especial (1 filósofo):**
```c
static int single_philo_case(t_philo *philo) {
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork");
    while (!should_stop(philo->prog))
        usleep(200);
    pthread_mutex_unlock(philo->left_fork);
    return (1);  // Return 1 = salir del loop
}
```

**¿Por qué esto es necesario?**
- Con 1 filósofo: sólo hay 1 tenedor
- Nunca puede comer (necesita 2)
- Debe morir por timeout
- Se maneja como caso especial para evitar bloqueo infinito

---

### 4. **init_program()** - Inicialización Completa

```c
int init_program(t_program *p) {
    // 1. Asignar memoria para forks
    p->forks = malloc(sizeof(pthread_mutex_t) * p->n_philo);
    if (!p->forks) return (1);  // Error handling
    
    // 2. Asignar memoria para philos
    p->philos = malloc(sizeof(t_philo) * p->n_philo);
    if (!p->philos) {
        free(p->forks);
        return (1);  // Error handling
    }
    
    // 3. Inicializar todos los mutexes (con rollback si falla)
    if (init_mutexes(p)) {
        free(p->philos);
        free(p->forks);
        return (1);
    }
    
    // 4. Configurar cada filósofo
    init_philos(p);
    
    return (0);
}
```

**Error Handling Crítico:**
- Si malloc falla → liberar lo anterior
- Si mutex_init falla → liberar memory + forks creados
- Garantiza NO hay memory leaks en caso de error

---

### 5. **destroy_program()** - Limpieza Total

```c
void destroy_program(t_program *p) {
    if (!p) return;
    
    // Destruir forks
    destroy_forks(p);
    
    // Destruir mutexes de control
    pthread_mutex_destroy(&p->print_mtx);
    pthread_mutex_destroy(&p->meal_mtx);
    pthread_mutex_destroy(&p->stop_mtx);
    
    // Liberar arrays
    free(p->philos);
    p->philos = NULL;
}
```

**Orden importante:**
1. Primero: destroy mutexes de forks
2. Luego: destroy mutexes de control
3. Finalmente: free memory

**Sin set NULL:**
- Pointers quedan apuntando a memoria liberada (dangling pointers)
- Con NULL: más fácil detectar bugs

---

## 🧪 PARTE 8: TESTING Y CASOS ESPECIALES (1 MIN)

### Pruebas Básicas

```bash
# Test 1: Simulación normal
./philo 5 800 200 200

# Test 2: Con número de comidas
./philo 4 410 200 200 10

# Test 3: Caso extremo (1 filósofo)
./philo 1 800 200 200

# Test 4: Tiempos muy cortos (muerte rápida)
./philo 5 100 50 50

# Test 5: Muchos filósofos
./philo 100 800 200 200
```

### Comportamiento Esperado

| Caso | Esperado |
|------|----------|
| `5 800 200 200` | Filósofos comen/duermen infinitamente |
| `4 410 200 200 10` | Todos comen 10 veces, entonces termina |
| `1 800 200 200` | Philo 1 toma tenedor y muere en 800ms |
| Argumentos inválidos | Error message y salida con código 1 |

---

## 🎓 PARTE 9: CONCEPTOS CLAVE PARA DIAPOSITIVAS (2 MIN)

### Terminología

- **Thread (Hilo):** Proceso ligero que corre en paralelo
- **Mutex (Mutual Exclusion):** Lock que garantiza acceso exclusivo
- **Deadlock:** Situación donde threads esperan infinitamente
- **Race Condition:** Resultado depende del timing entre threads
- **Atomic Operation:** Operación que no puede ser interrumpida
- **Critical Section:** Código accedido por múltiples threads

### Conceptos Avanzados

```
┌─────────────────────────────────────┐
│  PROBLEMA DE CONCURRENCIA           │
├─────────────────────────────────────┤
│ N threads compiten por K recursos    │
│ (N > K en este caso: 5 philos, 5 forks)
│                                      │
│ SOLUCIONES:                          │
│ 1. Mutex: Exclusión mutua            │
│ 2. Semáforos: Contador de recursos  │
│ 3. Monitores: Abstracciones de alto  │
│ 4. Orden alternado: Evitar ciclos   │
│ 5. Timeout: Detectar deadlock        │
└─────────────────────────────────────┘
```

---

## 📊 PARTE 10: FLUJO VISUAL COMPLETO

### Timeline de Ejemplo (3 Filósofos, tiempos: die=100, eat=30, sleep=30)

```
TIMELINE:
t=0ms
├─ Philo 1: (start)
├─ Philo 2: (start)
└─ Philo 3: (start)

t=5ms (initial_delay para pares)
├─ Philo 1: toma fork, toma fork, COME (hasta t=35)
├─ Philo 2: delay 1ms...
└─ Philo 3: toma fork, toma fork, COME (hasta t=35)

t=35ms
├─ Philo 1: libera forks, DUERME (hasta t=65)
├─ Philo 2: ahora puede tomar forks, COME (hasta t=65)
└─ Philo 3: libera forks, DUERME (hasta t=65)

t=65ms
├─ Philo 1: despierta, PIENSA
├─ Philo 2: despierta, DUERME (hasta t=95)
└─ Philo 3: despierta, PIENSA, toma fork...

... (ciclo continúa)

Si miss un fork por 100ms → MUERE
```

---

## 🎤 GUIÓN DE PRESENTACIÓN (ORDEN SUGERIDO)

### 1️⃣ **Introducción (2 min)**
- "¿Qué es el Problema de los Filósofos?"
- "¿Por qué es importante?"
- Mostrar diagrama de la mesa

### 2️⃣ **Requisitos (1 min)**
- Mostrar parámetros
- Ejemplo de ejecución
- Output esperado

### 3️⃣ **Arquitectura (2 min)**
- Mostrar estructuras de datos
- Mostrar organización de archivos
- Dibujar el flujo principal

### 4️⃣ **Flujo de Ejecución (2 min)**
- Main → Parse → Init → Simulate → Destroy
- Philo routine loop
- Boss routine loop

### 5️⃣ **Sincronización (2 min)**
- ¿Por qué necesitamos mutexes?
- 4 mutexes explicados
- Ejemplo de race condition

### 6️⃣ **Prevención de Deadlock (2 min)**
- Mostrar problema
- Mostrar solución (orden alternado)
- Demostración con valores impares/pares

### 7️⃣ **Código Importante (2 min)**
- smart_sleep (interrumpible)
- take_forks (desalternizado)
- init y destroy (error handling)

### 8️⃣ **Pruebas (1 min)**
- Demostrar ejecución
- Mostrar output
- Casos especiales

### 9️⃣ **Conclusiones (1 min)**
- Aprendizajes principales
- Aplicaciones reales

---

## ✨ PUNTOS DE ÉNFASIS

### Lo más importante en la evaluación:

✅ **Entiender QUÉ es el problema visualizado**
✅ **CÓMO se evita el deadlock** (orden alternado)
✅ **POR QUÉ se usan mutexes** (race conditions)
✅ **CÓMO se detecta la muerte** (timestamp + boss)
✅ **CÓMO se termina limpiamente** (stop flag + smart_sleep)

### Si te preguntan sobre...

| Pregunta | Respuesta Clave |
|----------|-----------------|
| "¿Por qué no deadlock?" | "Orden alternado: pares derecha primero, impares izquierda primero" |
| "¿Cómo se sincroniza?" | "4 mutexes: print, meal, stop, y forks (tenedores)" |
| "¿Por qué smart_sleep?" | "usleep normal no se puede interrumpir; smart_sleep chequea stop flag" |
| "¿Qué pasa con 1 filósofo?" | "Caso especial: solo 1 tenedor, nunca come, muere por timeout" |
| "¿Memory leaks?" | "No: init hace rollback en errores, destroy libera todo" |

---

## 🚀 ENVÍO FINAL

Cuando presentes:

1. **Abre la carpeta** y muestra los archivos
2. **Compila** (make clean && make)
3. **Ejecuta** con ejemplo visual
4. **Muestra el output** explicando cada línea
5. **Responde preguntas** con confianza (tienes la arquitectura clara)

---

**¡Buena suerte en la presentación! 🎓**
