# Power Grid – Producer Consumer Simulator (Smart Meter)

An Operating Systems project that demonstrates the **Producer → Bounded Buffer → Consumer** problem using a power grid.

| OS concept | Power grid |
|---|---|
| Producer | Power plants |
| Bounded buffer | Transmission grid (fixed capacity, default 100 MW) |
| Consumer | Households, factories, offices |
| `empty` / `full` semaphores | Free capacity / power available |
| Mutex | Protects the shared grid |

## Contents
- `index.html` – interactive web simulator (open in any browser, no install). Start, pause, resume, step, reset, speed control, scenarios (Normal, Shortage, Surplus, Overload), live charts, event log.
- `power_grid.c` – C version with real threads (pthreads, semaphores, mutex).
- `docs/flowchart.png` – flowchart of one simulation time unit.

## Run
**Web:** open `index.html`.

**C:**
```
gcc power_grid.c -o power_grid -pthread
./power_grid
```

## Formulas
- Supply = sum of producer output; Demand = sum of consumer demand
- Utilization = grid load / capacity x 100
- Supply < Demand: Unserved = Demand - Supply (load shedding)
- Supply > Demand: Excess = Supply - Demand (producers throttled)

Note: the web version runs producers and consumers as async tasks contending for a mutex and semaphores (JavaScript is single-threaded). The C version uses real OS threads.
