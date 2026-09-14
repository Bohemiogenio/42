# 📋 CHEAT SHEET - FILOSOFOS (PARA USAR DURANTE PRESENTACIÓN)

## ESQUEMA RÁPIDO (15 MIN)

### ⏱️ TIMELINE PRESENTACIÓN

```
MINUTO 0-2:   Qué es el problema + por qué importa
MINUTO 2-4:   Requisitos + parámetros
MINUTO 4-7:   Arquitectura + flujo
MINUTO 7-10:  Sincronización (mutexes)
MINUTO 10-12: Deadlock + solución
MINUTO 12-14: Demostración + preguntas
MINUTO 14-15: Conclusión
```

---

## 🎯 PUNTOS CLAVE A RECORDAR

```
PROBLEMA:       5 filósofos, 5 tenedores (no hay suficientes)
DESAFÍO:        Evitar deadlock (espera infinita)
SOLUCIÓN:       Orden alternado (pares/impares)
VALIDACIÓN:     Boss thread detecta muertes
TERMINACIÓN:    Cuando todos comen lo necesario
```

---

## 📊 DIAGRAMA DE LA MESA

```
        FILOSOFO 1
         /      \
      FORK     FORK
       /          \
      5            2
      |            |
     PHI4----X----PHI2
      |            |
      3            4
       \          /
      FORK     FORK
         \      /
        FILOSOFO 3
        
Cada filósofo necesita AMBOS tenedores para comer
```

---

## 🔄 FLUJO PRINCIPAL (1 DIAPOSITIVA)

```
main()
  ↓
parse_args (verificar 4-5 parámetros)
  ↓
init_program (mutex + malloc)
  ↓
start_simulation
  ├─ Crear N threads (filósofos)
  ├─ Crear 1 thread BOSS (supervisor)
  └─ Esperar a todos
  ↓
destroy_program (liberar todo)
  ↓
EXIT
```

---

## 👤 RUTINA DE CADA FILÓSOFO

```
LOOP:
  1. Tomar fork izquierda/derecha (según ID par/impar)
  2. Tomar segundo tenedor
  3. COMER por time_eat ms
  4. Liberar ambos tenedores
  5. DORMIR por time_sleep ms
  6. PENSAR (loop)

SI: Pasa > time_die sin comer → MUERE
SI: Comió must_eat veces → TERMINA
```

---

## 🚔 RUTINA DEL BOSS

```
LOOP cada 1ms:
  1. Para cada filósofo:
     └─ ¿Pasaron > time_die sin comer?
        └─ SÍ → Printf "[timestamp] [id] died" + STOP

  2. ¿Todos comieron must_eat veces?
     └─ SÍ → STOP simulación
```

---

## 🔐 4 MUTEXES (MOSTRAR CON 1 DIAPOSITIVA)

| Mutex | Protege | Razón |
|-------|---------|-------|
| print_mtx | printf outputs | Evita prints entrelazados |
| meal_mtx | last_meal_ms + meals | Lectura/escritura segura |
| stop_mtx | stop flag | Parada sincronizada |
| forks[n] | tenedores | Acceso exclusivo a recursos |

---

## ⚠️ PREVENCIÓN DE DEADLOCK (1 DIAPOSITIVA)

```
❌ SIN PROTECCIÓN:
   Todos toman tenedor izq → esperan tenedor der → DEADLOCK

✅ SOLUCIÓN IMPLEMENTADA:
   if (id % 2 == 0)              if (id % 2 == 1)
       lock(right_fork);             lock(left_fork);
       lock(left_fork);              lock(right_fork);

   RESULTADO: Hay asimetría, imposible ciclo de espera
```

---

## 💻 COMANDOS DE DEMOSTRACIÓN

```bash
# 1. Compilar
make clean && make

# 2. Test normal (5 filósofos)
./philo 5 800 200 200

# 3. Test con comidas (cada uno come 10 veces)
./philo 4 410 200 200 10

# 4. Caso extremo (1 filósofo - muere)
./philo 1 800 200 200

# 5. Tiempos cortos (muerte rápida visible)
./philo 5 100 50 50

# CTRL+C para terminar
```

---

## 📈 OUTPUT ESPERADO

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 2 has taken a fork
...
800 3 died
```

**Formato:** `[timestamp_ms] [philo_id] [acción]`

---

## 🎨 CÓDIGO CLAVE (PARA MOSTRAR EN PANTALLA)

### Smart Sleep (Interrumpible)
```c
void smart_sleep(long long ms, t_program *p) {
    long long end = now_ms() + ms;
    while (!should_stop(p) && now_ms() < end)
        usleep(200);  // ← Check cada 200μs si debe parar
}
```

### Orden Alternado (Deadlock Prevention)
```c
if (philo->id % 2 == 0) {
    pthread_mutex_lock(philo->right_fork);   // Pares: derecha 1ero
    pthread_mutex_lock(philo->left_fork);
} else {
    pthread_mutex_lock(philo->left_fork);    // Impares: izq 1ero
    pthread_mutex_lock(philo->right_fork);
}
```

### Error Handling en Init
```c
p->forks = malloc(...);
if (!p->forks) return (1);          // Rollback 0

p->philos = malloc(...);
if (!p->philos) {
    free(p->forks);                 // Rollback 1
    return (1);
}
```

---

## ❓ PREGUNTAS FRECUENTES (PREPARARSE)

**P1: ¿Por qué no deadlock?**
R: "Orden alternado. Filósofos pares toman derecha primero, impares izquierda. Esto rompe el ciclo de espera."

**P2: ¿Cómo se detecta la muerte?**
R: "Boss thread. Cada 1ms suma (now - last_meal). Si > time_die, muere."

**P3: ¿Por qué smart_sleep y no sleep()?**
R: "sleep() no se interrumpe. smart_sleep() chequea stop flag cada 200μs para parada limpia."

**P4: ¿Qué pasa con 1 filósofo?**
R: "Caso especial. Solo 1 tenedor, nunca puede comer ambos. Muere por timeout."

**P5: ¿Memory leaks?**
R: "No. init() hace rollback en errores. destroy() libera todo en orden correcto."

**P6: ¿Por qué 4 mutexes?**
R: "print_mtx (evita prints rotos), meal_mtx (comidas), stop_mtx (parada), forks (tenedores)"

---

## 📌 ORDEN LÓGICO DE EXPLICACIÓN

```
1. MOSTRAR LA MESA (visual)
   └─ "5 filósofos, 5 tenedores, solo 2 pueden comer"

2. EXPLICAR PARÁMETROS
   └─ "Pasamos argumento por argumento"

3. MOSTRAR FLUJO PRINCIPAL
   └─ "Del archivo main.c hacia simulation"

4. EXPLICAR RUTINA FILÓSOFO
   └─ "Cada thread hace esto infinitamente"

5. HABLAR DEL PROBLEMA DEADLOCK
   └─ "Sin orden, todos quedan esperando"

6. MOSTRAR LA SOLUCIÓN
   └─ "Con orden alternado, imposible deadlock"

7. HABLAR DE SINCRONIZACIÓN
   └─ "4 mutexes = 4 problemas resueltos"

8. DEMOSTRAR EJECUCIÓN
   └─ "make && ./philo 5 800 200 200"

9. RESPONDER PREGUNTAS
   └─ "Info.c muestra el core logic"
```

---

## 🎓 SI TE PREGUNTAN SOBRE NORMA 42

```
✅ Compliant:
- Headers correctos (42 format)
- Funciones < 25 líneas
- Máx 5 parámetros por función
- Máx 5 variables locales
- Sin variables globales
- Sin for loops (solo while)
- Código limpio y modular

Respuesta lista:
"El proyecto pasa la Norma 42. Cada función tiene
su responsabilidad, y todo está debidamente documentado."
```

---

## ⏰ TIMING SUGERIDO

```
0:00 - 2:00    Introducción + Problema
2:00 - 3:00    Parámetros + Requisitos
3:00 - 6:00    Arquitectura + Flujo
6:00 - 8:00    Rutinas (Philo + Boss)
8:00 - 10:00   Sincronización (Mutexes)
10:00 - 12:00  Deadlock Prevention
12:00 - 13:30  Código + Demostración
13:30 - 15:00  Preguntas + Conclusión
```

---

## 🎤 CONCLUSIÓN IMPACTANTE

```
"El Problema de los Filósofos enseña conceptos
fundamentales de concurrencia:

1. No todos pueden acceder a todo simultaneamente
2. Necesitamos sincronización (mutexes)
3. Hay que cuidarse del deadlock (orden)
4. El supervisor detecta problemas (boss thread)

Conceptos que se usan en SO real:
- Servidores (múltiples clientes)
- Bases de datos (múltiples queries)
- Sistemas distribuidos
- Scheduling de CPU

Este proyecto demuestra cómo resolver estos
problemas de forma elegante."
```

---

## ✨ TIPS PARA LA PRESENTACIÓN

- **Mantén confianza**: Conoces el código
- **Sé específico**: "El método X hace Y porque Z"
- **Muestra código**: Abre los .c files relevant
- **Demuestra**: Ejecuta varios casos
- **Acepta preguntas**: No hay respuesta 'mala'
- **Cita números**: time_die=800ms, n_philo=5, etc
- **Usa visual**: Dibuja la mesa, los threads, los locks
