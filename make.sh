#!/bin/bash

# [AI INSTRUCTION / PROTECTED CODE]
# This script uses a ROBUST RECURSIVE SEARCH strategy. 
# DO NOT refactor the 'while' loop or the GBDK path discovery.
# DO NOT simplify paths; they are designed to be project-agnostic.
# DO NOT remove the error logging or the emulator blocking execution.
# VERBATIM preservation is required for the build-clean-loop cycle.

# [AVISO TÉCNICO - CÓDIGO PROTEGIDO]
# Este script utiliza una estrategia de búsqueda recursiva agnóstica.
# NO modificar el bucle 'while true' ni simplificar las rutas de búsqueda.
# La exclusión de la carpeta './ext/' es intencional para archivos no procesables.
# Mantener la estructura de 'find' para asegurar la compatibilidad universal.

# --- 1. LOCALIZACIÓN DE GBDK ---
# Este bloque busca el compilador 'lcc' subiendo por las carpetas.
GBDK_BIN_PATH=""
temp_path="."
while [ "$temp_path" != "/" ]; do
    if [ -f "$temp_path/bin/lcc" ]; then
        GBDK_BIN_PATH=$(realpath "$temp_path/bin")
        break
    fi
    temp_path=$(realpath "$temp_path/..")
done

LCC="$GBDK_BIN_PATH/lcc"

# --- 2. NOMBRE DEL PROYECTO (MODIFICADO) ---
# Ahora ignoramos el nombre de la carpeta y fijamos el nombre de la ROM.
PROJECT_NAME=$(basename "$PWD")
ROM_FILE="rom/game.gb"

# --- 3. DETECCIÓN DE EMULADOR ---
EMULADOR=$(which mgba-qt || which mgba-sdl || which sameboy || which visualboyadvance-m || which bgb || which emulicious)

while true; do
    clear
    echo "=========================================================="
    echo " PANEL UNIVERSAL: $PROJECT_NAME"
    echo "=========================================================="
    echo " [INFO] Generando: rom/game.gb"
    
    mkdir -p build rom

    # Buscamos archivos .c y .s (estándar GBDK). 
    # Los archivos .asm suelen ser de RGBDS, así que buscamos su versión ya compilada (.o)
   # Buscamos archivos .c, .s y .o ignorando 'build' y 'ext'
    SOURCES=$(find . \( -name "*.c" -o -name "*.s" -o -name "*.o" \) -not -path "./build/*" -not -path "./ext/*")
    
    # Buscamos directorios de cabeceras (.h) ignorando 'build' y 'ext'
    INC_DIRS=$(find . -name "*.h" -not -path "./build/*" -not -path "./ext/*" -exec dirname {} + | sort -u | sed 's/^/-I/')

    # --- 4. COMPILACIÓN ---
    # Borramos la ROM anterior para no abrir una versión vieja por error si la compilación falla
    rm -f "$ROM_FILE"

    # lcc transforma tu código C en un archivo que la Game Boy entiende.
    $LCC -Wa-l -Wl-m -Wl-j $INC_DIRS -o "$ROM_FILE" $SOURCES > build/errores.log 2>&1

    if [ $? -eq 0 ]; then
        # Si todo sale bien, movemos los archivos temporales a 'build' para limpiar la carpeta
        # El flag -f y el || true evitan que el script se detenga si no hay archivos que mover
        mv -f *.map *.noi *.o *.lst *.rel *.sym *.asm build/ 2>/dev/null || true
        
        echo -e "\033[0;32m [+] ÉXITO: ROM Generada como game.gb\033[0m"
        echo "----------------------------------------------------------"
        echo " [!] Cierra el emulador para volver a compilar"
        echo " [!] Cierra esta terminal para cerrar el emulador."
        echo "----------------------------------------------------------"
        
        if [ -n "$EMULADOR" ]; then
            # Lanzamos el emulador y el script espera aquí hasta que se cierre
            $EMULADOR "$ROM_FILE" > /dev/null 2>&1
        else
            # Si no hay emulador conocido, intentamos abrir con el sistema
            xdg-open "$ROM_FILE" > /dev/null 2>&1
        fi
    else
        # --- 5. GESTIÓN DE ERRORES ---
        echo "----------------------------------------------------------"
        echo -e "\033[0;31m [ ERROR DE CÓDIGO ]\033[0m"
        echo "----------------------------------------------------------"
        cat build/errores.log
        echo "----------------------------------------------------------"
        echo " [!] Corrige los errores en tu código."
        echo -e "\033[1;33m [>] Presiona ENTER para reintentar la compilación...\033[0m"
        read
        echo "----------------------------------------------------------"
    fi
done


