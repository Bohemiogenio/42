# 🎨 DIAGRAMAS VISUALES PARA PRESENTACIÓN

## 1. PROBLEMA DE LOS FILÓSOFOS - VISUALIZACIÓN

### La Mesa Circular (5 Filósofos)

```
                    FILÓSOFO 1
                    (thinking)
                    
         TENEDOR 5        TENEDOR 1
               ↓            ↓
               
FILÓSOFO 5                        FILÓSOFO 2
(eating)   ←→ MESA REDONDA ←→    (sleeping)

               ↑            ↑
         TENEDOR 4        TENEDOR 2
         
FILÓSOFO 4     ←← TENEDOR 3 →→    FILÓSOFO 3
(sleeping)                        (thinking)
```

### Requisito: Cada filósofo necesita AMBOS tenedores

```
┌─────────────────────────────────┐
│ Para comer:                     │
│                                 │
│ 1. Tomar tenedor IZQUIERDO      │
│ 2. Tomar tenedor DERECHO        │
│ 3. COMER por time_eat ms        │
│ 4. Liberar tenedor IZQUIERDO    │
│ 5. Liberar tenedor DERECHO      │
└─────────────────────────────────┘
```

---

## 2. FLUJO DE EJECUCIÓN COMPLETO

```
START
  │
  ├─→ main.c
  │   ├─→ parse_args()
  │   │   └─ Validar: 4-5 argumentos? ✓
  │   │   └─ Valores positivos? ✓
  │   │
  │   ├─→ init_program()
  │   │   ├─ Malloc forks[n_philo]
  │   │   ├─ Malloc philos[n_philo]
  │   │   ├─ Init mutexes (print, meal, stop)
  │   │   ├─ Init fork mutexes
  │   │   └─ Asignar tenedores a cada philo
  │   │
  │   ├─→ start_simulation()
  │   │   ├─ start_ms = now_ms()
  │   │   │
  │   │   ├─ CREAR THREADS:
  │   │   │  ├─ Thread 1: philo_routine(&philo[0])
  │   │   │  ├─ Thread 2: philo_routine(&philo[1])
  │   │   │  ├─ Thread 3: philo_routine(&philo[2])
  │   │   │  ├─ ...
  │   │   │  └─ BOSS Thread: boss_routine(&program)
  │   │   │
  │   │   ├─ pthread_join(boss) ← Espera a boss
  │   │   └─ pthread_join(philos[i]) ← Espera a todos
  │   │
  │   ├─→ destroy_program()
  │   │   ├─ Destroy fork mutexes
  │   │   ├─ Destroy control mutexes
  │   │   ├─ Free forks[]
  │   │   ├─ Free philos[]
  │   │   └─ Set pointers = NULL
  │   │
  │   └─→ return (0)
  │
  STOP
```

---

## 3. CONCURRENT THREADS TIMELINE

```
TIEMPO →

Thread Philo 1:
[delay]→[take_l_fork]→[take_r_fork]→[EATING 200ms]→[sleep 200ms]→[thinking]→...

Thread Philo 2:
[delay 1ms]→[waiting for forks...]→[take_l_fork]→[take_r_fork]→[EATING 200ms]→...

Thread Philo 3:
[delay]→[take_l_fork]→[take_r_fork]→[EATING 200ms]→[sleep 200ms]→...

Thread BOSS:
[check]→[check]→[check]→[check philo died?]→[check]→[check]→...
 (cada 1ms)
```

---

## 4. RUTINA DE CADA FILÓSOFO (Detallada)

```
philo_routine(void *arg) {
    │
    ├─ initial_delay()
    │  └─ if (id % 2 == 0) usleep(1000)
    │
    ├─ LOOP mientras !should_stop():
    │  │
    │  ├─ take_forks()
    │  │  │
    │  │  ├─ if (n_philo == 1)
    │  │  │  ├─ lock(left_fork)
    │  │  │  ├─ print "has taken a fork"
    │  │  │  └─ esperar mientras !should_stop()
    │  │  │
    │  │  └─ else (n_philo > 1)
    │  │     ├─ if (id % 2 == 0)
    │  │     │  ├─ lock(right_fork)
    │  │     │  ├─ print "has taken a fork"
    │  │     │  ├─ lock(left_fork)
    │  │     │  └─ print "has taken a fork"
    │  │     │
    │  │     └─ else
    │  │        ├─ lock(left_fork)
    │  │        ├─ print "has taken a fork"
    │  │        ├─ lock(right_fork)
    │  │        └─ print "has taken a fork"
    │  │
    │  ├─ philo_eat()
    │  │  ├─ lock(meal_mtx)
    │  │  ├─ last_meal_ms = now_ms()
    │  │  ├─ unlock(meal_mtx)
    │  │  ├─ print "is eating"
    │  │  ├─ smart_sleep(time_eat)
    │  │  ├─ lock(meal_mtx)
    │  │  ├─ meals_eaten++
    │  │  ├─ unlock(meal_mtx)
    │  │  ├─ unlock(left_fork)
    │  │  └─ unlock(right_fork)
    │  │
    │  ├─ print "is sleeping"
    │  ├─ smart_sleep(time_sleep)
    │  │
    │  └─ print "is thinking"
    │
    └─ return NULL
}
```

---

## 5. RUTINA DEL BOSS (Detallada)

```
boss_routine(void *arg) {
    │
    ├─ LOOP mientras !should_stop():
    │  │
    │  ├─ Para i=0 hasta n_philo-1:
    │  │  │
    │  │  ├─ check_philo_death(&philos[i])
    │  │  │  │
    │  │  │  ├─ now = now_ms()
    │  │  │  ├─ last = get_last_meal(philo)
    │  │  │  │
    │  │  │  └─ if (now - last > time_die):
    │  │  │     ├─ set_stop(p)
    │  │  │     ├─ lock(print_mtx)
    │  │  │     ├─ printf "%lld %d died\n"
    │  │  │     ├─ unlock(print_mtx)
    │  │  │     └─ return 1 ← SALIR
    │  │  │
    │  │  └─ return 0 si no murió
    │  │
    │  ├─ all_ate_enough(p)
    │  │  │
    │  │  ├─ if (must_eat <= 0) return 0
    │  │  │
    │  │  └─ Para cada philo:
    │  │     └─ if (get_meals(philo) < must_eat)
    │  │        └─ return 0
    │  │     └─ todos comieron suficiente
    │  │        ├─ set_stop(p)
    │  │        └─ return 1 ← SALIR
    │  │
    │  └─ usleep(1000) ← Check cada 1ms
    │
    └─ return NULL
}
```

---

## 6. PROBLEMA DE DEADLOCK (Paso a Paso)

### Escenario SIN Protección

```
TIEMPO → 

t=0ms:
  Philo 1: lock(left_fork=1)  ✓
  Philo 2: lock(left_fork=2)  ✓
  Philo 3: lock(left_fork=3)  ✓
  Philo 4: lock(left_fork=4)  ✓
  Philo 5: lock(left_fork=5)  ✓

t=1ms:
  Philo 1: lock(right_fork=2)  ← ESPERA a Philo 2
  Philo 2: lock(right_fork=3)  ← ESPERA a Philo 3
  Philo 3: lock(right_fork=4)  ← ESPERA a Philo 4
  Philo 4: lock(right_fork=5)  ← ESPERA a Philo 5
  Philo 5: lock(right_fork=1)  ← ESPERA a Philo 1

  ╔════════════════════════════════════════════╗
  ║  CICLO CIRCULAR: 1→2→3→4→5→1...           ║
  ║  ¡DEADLOCK! Todos esperan infinitamente   ║
  ╚════════════════════════════════════════════╝
```

### Solución CON Orden Alternado

```
TIEMPO →

Filósofos PARES (2,4):      Filósofos IMPARES (1,3,5):
┌─────────────────┐         ┌──────────────────┐
│ lock right_fork │         │ lock left_fork   │
│ lock left_fork  │         │ lock right_fork  │
└─────────────────┘         └──────────────────┘

Resultado:
  
  Philo 1 (IMPAR): toma LEFT (fork 1) ✓
  Philo 2 (PAR):   toma RIGHT (fork 2) ✓
  Philo 3 (IMPAR): toma LEFT (fork 3) ✓
  Philo 4 (PAR):   toma RIGHT (fork 4) ✓
  Philo 5 (IMPAR): toma LEFT (fork 5) ✓

  Philo 1: ahora quiere RIGHT (fork 2) ← PUEDE ESPERAR
  Philo 2: ahora quiere LEFT (fork 2) ← PUEDE ESPERAR
  ...
  
  ✓ Alguien SIEMPRE puede avanzar
  ✓ NO hay ciclo de espera circular
  ✓ DEADLOCK EVITADO
```

---

## 7. SINCRONIZACIÓN CON MUTEXES

### Race Condition SIN Mutex

```
Scenario 1 (Corrupted Data):

Thread 1 (Philo 1):            Thread 2 (Philo 2):
├─ Lee last_meal = 100         │
├─ Calcula...                  ├─ Lee last_meal = 100
├─ Escribe last_meal = 150     │
                               ├─ Escribe last_meal = 110

RESULTADO: last_meal = 110  ❌ (debería ser 150!)
```

### CORRECTO CON Mutex

```
Thread 1 (Philo 1):            Thread 2 (Philo 2):
├─ lock(meal_mtx)              │
├─ Lee last_meal = 100         ├─ ESPERA por meal_mtx
├─ Escribe last_meal = 150     │
├─ unlock(meal_mtx)            │
│                              ├─ lock(meal_mtx)   ✓
│                              ├─ Lee last_meal = 150
│                              ├─ (usa valor correcto)
│                              ├─ unlock(meal_mtx)

RESULTADO: last_meal = 150 ✓ (correcto!)
```

---

## 8. 4 MUTEXES EXPLICADOS

```
┌────────────────────────────────────────────────────────┐
│             PROGRAMA PHILOSOPHERS                      │
├─────────────────────┬──────────────────────────────────┤
│                     │                                  │
│  MUTEX 1: print_mtx │  Protege:                        │
│  │                  │  - printf() calls                │
│  │ Lock/Unlock      │  - Output format                 │
│  │                  │  Beneficio: Evita prints mixing  │
│  └──────────────────┘                                  │
│                                                        │
│  MUTEX 2: meal_mtx                                     │
│  │                  │  Protege:                        │
│  │ Lock/Unlock      │  - last_meal_ms (read/write)    │
│  │                  │  - meals_eaten (contador)        │
│  │                  │  Beneficio: Datos consistentes   │
│  └──────────────────┘                                  │
│                                                        │
│  MUTEX 3: stop_mtx                                     │
│  │                  │  Protege:                        │
│  │ Lock/Unlock      │  - stop flag (parada)            │
│  │                  │  Beneficio: Parada sincronizada  │
│  └──────────────────┘                                  │
│                                                        │
│  MUTEX 4: forks[n]                                     │
│  │                  │  Protege:                        │
│  │ Lock/Unlock      │  - Acceso a tenedores            │
│  │                  │  Beneficio: Evita deadlock       │
│  └──────────────────┘                                  │
└────────────────────────────────────────────────────────┘
```

---

## 9. SMART_SLEEP vs SLEEP

### Sin Smart Sleep (PROBLEMA)

```
Philo 1 comiendo por 1000ms (time_eat)
├─ t=0ms:   comienza
├─ t=500ms: MUERE (tiempo_die arrived)
│           Boss detecta muerte, set_stop = 1
├─ t=500ms: Pero philo sigue en usleep()
│           usleep(1000) NO se interrumpe ❌
├─ t=1000ms: Finalmente despierta
│            Ya debería haber terminado hace 500ms ❌

PROBLEMA: Reacción lenta a evento de muerte
```

### Con Smart Sleep (CORRECTO)

```
Philo 1 comiendo por 1000ms (time_eat)
├─ t=0ms:   comienza smart_sleep(1000)
├─ t=200ms: Chequea !should_stop? ✓ → continúa
├─ t=400ms: Chequea !should_stop? ✓ → continúa
├─ t=500ms: MUERE (tiempo_die arrived)
│           Boss detecta muerte, set_stop = 1
├─ t=500ms: Chequea !should_stop? ✗ → SALE de loop ✓
│           Termina inmediatamente ✓
│
│ Código:
│ while (!should_stop(p) && now_ms() < end)
│        └─ CHEQUEA STOP CADA 200μs
│           ↑
│           Permite interrupción rápida
└─ Reacción en < 1ms

BENEFICIO: Terminación limpia y rápida
```

---

## 10. ERROR HANDLING EN INIT

```
init_program(t_program *p)
│
├─ p->forks = malloc(sizeof(pthread_mutex_t) * n)
│  │
│  └─ if (!p->forks)
│     ├─ Liberar: nada (aún no malloc'd)
│     └─ return (1) ← ERROR
│
├─ p->philos = malloc(sizeof(t_philo) * n)
│  │
│  └─ if (!p->philos)
│     ├─ Liberar: p->forks (ya mallocd)
│     ├─ free(p->forks)
│     └─ return (1) ← ERROR
│
├─ init_mutexes(p)
│  │
│  └─ if (error)
│     ├─ Liberar: p->philos + p->forks
│     ├─ free(p->philos)
│     ├─ free(p->forks)
│     └─ return (1) ← ERROR
│
└─ init_philos(p)
   └─ return (0) ← SUCCESS

✓ Cada error rollback limpio
✓ No hay memory leaks
✓ Orden correcto de liberación
```

---

## 11. CASO ESPECIAL: 1 FILÓSOFO

```
Con 1 filósofo y 1 tenedor:

PROBLEMA:
├─ Necesita 2 tenedores para comer
├─ Solo hay 1 tenedor
└─ ¡NUNCA puede comer! ❌

SOLUCIÓN:
├─ lock(left_fork)
├─ print "has taken a fork"
├─ while (!should_stop()) usleep(200)  ← Espera muerte
├─ unlock(left_fork)
└─ return 1  ← Salir del loop
   
RESULTADO:
├─ se toma el único tenedor
├─ espera pasivamente
├─ muere cuando time_die expire
└─ Output esperado:
   0 1 has taken a fork
   800 1 died
```

---

## 12. TIMELINE REAL - EJEMPLO 3 FILÓSOFOS

```
PARÁMETROS: 3 filósofos, time_die=100, time_eat=30, time_sleep=30

t=0ms:
├─ Philo 1: START
├─ Philo 2: START (espera 1ms por initial_delay)
├─ Philo 3: START
└─ BOSS: START

t=1ms:
├─ Philo 1: lock(left=1), lock(right=2) → EATING
├─ Philo 2: despierta, intenta lock(right=2) → ESPERA
└─ Philo 3: lock(left=3), lock(right=1) → ESPERA a Philo 1

t=31ms:
├─ Philo 1: DONE eating, unlock ambos, SLEEPING
├─ Philo 2: ahora lock(right=2) ✓, lock(left=2) ✓ → EATING
└─ Philo 3: ahora lock(right=1) ✓ → EATING también

... (ciclos de eating/sleeping/thinking)

t=100ms:
├─ BOSS chequea: ¿pasaron 100ms?
├─ Si alguien no comió: MUERE
└─ Si todos comieron 0 veces (must_eat=-1): continúa

CONCLUSIÓN: Ciclo infinito o muerte si timeout
```

---

## 13. OUTPUT REAL VS ESPERADO

### Esperado (Normal)

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
32 1 is sleeping
62 1 is thinking
62 2 has taken a fork
62 2 has taken a fork
62 2 is eating
94 2 is sleeping
94 3 has taken a fork
...
```

### Con Muerte (Timeout)

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
400 1 is sleeping
600 1 is thinking
600 2 has taken a fork
...
800 2 died  ← Muerte por timeout
```

### Con must_eat Completado

```
0 1 has taken a fork
...
(múltiples ciclos)
...
1200 5 is eating
1248 5 is sleeping   ← Ultimo evento
(Simulación termina limpiamente sin "died")
```

---

## 14. COMPILACIÓN Y EJECUCIÓN

```
$ cd Philosophers

$ make clean && make
cc -Wall -Wextra -Werror -c main.c -o main.o
cc -Wall -Wextra -Werror -c parse.c -o parse.o
...
cc -Wall -Wextra -Werror main.o parse.o ... -o philo
philo Compiled successfully

$ ./philo 5 800 200 200
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
...

$ make clean
rm -f *.o
Clean completed

$ make fclean
rm -f *.o philo
Clean completed
```

---

## 15. RESUMEN ARQUITECTURA (1 DIAPOSITIVA)

```
┌─────────────────────────────────────────────┐
│      PHILOSOPHERS PROJECT ARCHITECTURE      │
├─────────────────────────────────────────────┤
│                                             │
│  INPUT: ./philo 5 800 200 200              │
│           ↓                                 │
│         PARSE (validar argumentos)          │
│           ↓                                 │
│         INIT (malloc + mutex init)          │
│           ↓                                 │
│    ┌──────SIMULATION──────┐                │
│    │                      │                │
│    ├─ 5 Threads FILÓSOFOS │                │
│    │  └─ Cada uno: take forks              │
│    │                eat, sleep, think       │
│    │                                       │
│    └─ 1 Thread BOSS                        │
│       └─ Detecta muertes                   │
│          Verifica must_eat                 │
│                      │                    │
│                      ↓                    │
│         DESTROY (free + mutex destroy)     │
│                      ↓                    │
│         OUTPUT: ✓ Success (exit 0)        │
│                                            │
└─────────────────────────────────────────────┘
```

---

## TIPS PARA LAS DIAPOSITIVAS

1. **Usa colores:**
   - 🔴 Locks en ROJO
   - 🟢 Eventos exitosos en VERDE
   - 🟡 Esperas en AMARILLO
   - 🔵 Threads en AZUL

2. **Animaciones sugeridas:**
   - Timeline: mostrar eventos uno a uno
   - Deadlock: mostrar orden de locks gradualmente
   - Threads: mostrar threads aparecer/desaparecer

3. **Código en GitHub/gist:**
   - Puedes mostrar código completo
   - Resalta las funciones clave con colores

4. **Demo live:**
   - Abre terminal: `./philo 5 800 200 200`
   - Muestra output vivo
   - Cierra con CTRL+C si quieres

5. **Preguntas esperadas:**
  - Ten listos los diagrams de deadlock y solución
   - Ten el código de smart_sleep visible
   - Ten el código de orden alternado visible
