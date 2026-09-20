# INFORME DE CAMBIOS — Buscaminas Qt

Fecha: 2026-09-20

## Resumen de esta sesión

Revisión general del proyecto: arreglo de pantallas estiradas, bugs en la pantalla de récords, pruebas de lógica en todo el proyecto (60 pruebas nuevas) y mejoras de calidad de vida. **175/175 pruebas pasan.**

---

## 1. Bugs encontrados y corregidos

### 1.1 Bucle infinito en Tablero (minas >= celdas)
- **Síntoma**: `Tablero(filas, columnas, minas)` con `minas >= filas*columnas` hacía que `sembrarMinas()` entrara en bucle infinito (nunca podía colocar todas las minas porque la celda segura queda libre).
- **Fix** (`tablero.cpp`): el constructor limita las minas a `filas*columnas - 1` (mínimo 0).
- **Prueba**: `tablero: minas limitadas a celdas-1 (3x3 -> 8)` y `tablero: sembrado termina con 8 minas (sin bucle infinito)`.

### 1.2 Pantalla de récords: tarjetas desbordaban la ventana
- **Síntoma**: con muchos puntajes, las tarjetas se salían de la ventana y el botón VOLVER quedaba fuera de alcance (no se podía volver al menú).
- **Fix** (`ventanarecords.cpp`): la lista de tarjetas ahora vive dentro de un `QScrollArea`; el botón VOLVER siempre queda visible.
- **Prueba**: el flujo completo de entrar a récords y volver al menú pasa.

### 1.3 Login roto por el hashing de contraseñas (detectado por las pruebas)
- **Síntoma**: el compañero agregó SHA-256 a las contraseñas, pero los `usuarios.txt` existentes con contraseñas en texto plano dejaron de funcionar (el login comparaba hash contra texto plano).
- **Acción**: el harness ahora escribe contraseñas hasheadas y verifica el hash al registrarse.
- **IMPORTANTE para el usuario**: cualquier `usuarios.txt` viejo con contraseñas en texto plano ya no permite entrar. Hay que re-registrar los usuarios o migrar el archivo a hashes.

### 1.4 Pantallas estiradas
- **Síntoma**: al redimensionar la ventana, todas las pantallas se estiraban (botones y tarjetas a lo ancho).
- **Fix**:
  - `buscaminasmain.cpp`: la ventana ahora tiene **tamaño fijo** (720x580) — no se puede estirar.
  - Tarjetas de login, registro, opciones y ayuda con ancho máximo (460-560 px) y centradas.
  - Botones de victoria/derrota con ancho máximo (380 px) y centrados.

---

## 2. Mejoras implementadas

### 2.1 Título de ventana dinámico
Cada pantalla muestra su título: "Buscaminas - Menú Principal", "Buscaminas - Partida", "Buscaminas - Récords", etc. (`buscaminasmain.cpp`, en `currentChanged`).

### 2.2 Filtro de récords por dificultad
`ventanarecords.cpp/h`: combo con TODOS / FÁCIL / MEDIO / DIFÍCIL / PERSONALIZADO.
- FÁCIL = 8x8, MEDIO = 16x16, DIFÍCIL = 16x30, PERSONALIZADO = cualquier otro tamaño.
- Por defecto muestra TODOS (comportamiento anterior intacto).

### 2.3 Botón MUTE en la partida
`ventanajuego.cpp`: botón en el encabezado que silencia música y efectos al instante (guarda los volúmenes y los restaura al desmutear).

### 2.4 Pantalla de Ayuda conectada
El compañero había creado `ventanaayuda.cpp` ("¿CÓMO JUGAR?") pero el botón no tenía estilo. Se le dio estilo (azul) y quedó accesible desde el menú.

### 2.5 Ya implementado por el compañero (verificado)
- Contraseñas con SHA-256 (login y registro).
- Validación de usuario duplicado (case-insensitive).
- Tooltips en dificultades bloqueadas.
- Medalla PNG en pantalla de victoria.

---

## 3. Pruebas de lógica nuevas (harness)

Se agregaron 60 pruebas al harness (115 -> **175**):

| Área | Qué se prueba |
|---|---|
| Tablero | minas exactas, primer clic seguro, flood fill, victoria 1x1, banderas, límites fuera de rango, bug de minas>=celdas, conteo de vecinas con patrón conocido |
| Celda | estado inicial, mina, revelar, bandera en celda revelada/cerrada, conteo de vecinas |
| Cronómetro | arranca en 0, cuenta segundos, detener congela |
| GestorMedallas | prerequisitos (Bronce->Plata->Oro->Diamante), rechazo sin prerequisito, sin duplicados, Valiente sin prerequisito |
| GestorAudio | setVolumenMusica/Efectos se reflejan en getters |
| UI | ventana de tamaño fijo, pantalla de Ayuda navegable, filtro de récords (FÁCIL=2, MEDIO=1, DIFÍCIL=1, PERSONALIZADO=2, TODOS=6) |

---

## 4. Archivos modificados

- `tablero.cpp` — límite de minas (fix bucle infinito)
- `buscaminasmain.cpp` — tamaño fijo, título dinámico, estilo botón AYUDA
- `ventanarecords.h/.cpp` — scroll + filtro por dificultad
- `ventanajuego.cpp` — botón MUTE
- `VentanaLogin.cpp`, `RegistroUsuario.cpp` — tarjeta con ancho máximo
- `ventanaopciones.cpp`, `ventanaayuda.cpp` — tarjeta con ancho máximo
- `ventanavictoria.cpp`, `ventanaderrota.cpp` — botones con ancho máximo

## 5. Despliegue

- `dist/` y `EjecutableFinal/` actualizados con el Release nuevo (544 KB) + `recursos/medallas/`.
- Smoke tests OK en ambos.
- Build Debug de Qt Creator actualizado.