#!/bin/bash

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

    # Búsqueda de archivos de código (.c) y cabeceras (.h)
    SOURCES=$(find . -name "*.c" -not -path "./build/*")
    INC_DIRS=$(find . -name "*.h" -not -path "./build/*" -exec dirname {} + | sort -u | sed 's/^/-I/')
    
    # --- 4. COMPILACIÓN ---
    # lcc transforma tu código C en un archivo que la Game Boy entiende.
    $LCC -Wa-l -Wl-m -Wl-j $INC_DIRS -o "$ROM_FILE" $SOURCES 2> build/errores.log
    
    if [ $? -eq 0 ]; then
        # Si todo sale bien, movemos los archivos temporales a 'build' para limpiar la carpeta
        mv *.map *.noi *.o *.lst *.rel *.sym *.asm build/ 2>/dev/null
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
        echo " [!] El script reintentará la compilación automáticamente."
        echo "----------------------------------------------------------"
        
        sleep 3
    fi
done