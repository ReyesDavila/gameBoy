#!/bin/bash

# --- 1. LOCALIZACIÓN DE GBDK ---
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

# --- 2. NOMBRE DEL PROYECTO ---
PROJECT_NAME=$(basename "$PWD")
ROM_FILE="rom/$PROJECT_NAME.gb"

# --- 3. DETECCIÓN DE EMULADOR ---
EMULADOR=$(which mgba-qt || which mgba-sdl || which sameboy || which visualboyadvance-m || which bgb || which emulicious)

while true; do
    clear
    echo "=========================================================="
    echo " PANEL UNIVERSAL: $PROJECT_NAME"
    echo "=========================================================="
    
    mkdir -p build rom

    # Búsqueda de archivos
    SOURCES=$(find . -name "*.c" -not -path "./build/*")
    INC_DIRS=$(find . -name "*.h" -not -path "./build/*" -exec dirname {} + | sort -u | sed 's/^/-I/')
    
    # COMPILACIÓN
    $LCC -Wa-l -Wl-m -Wl-j $INC_DIRS -o "$ROM_FILE" $SOURCES 2> build/errores.log
    
    if [ $? -eq 0 ]; then
        mv *.map *.noi *.o *.lst *.rel *.sym *.asm build/ 2>/dev/null
        echo " [+] ÉXITO: ROM Generada"
        echo "----------------------------------------------------------"
        echo " [!] Cierra el emulador para volver a compilar"
        echo " [!] Cierra esta terminal para cerrar el emulador."
        echo "----------------------------------------------------------"
        
        if [ -n "$EMULADOR" ]; then
            # El script se detiene aquí hasta que el emulador se cierre
            $EMULADOR "$ROM_FILE" > /dev/null 2>&1
        else
            xdg-open "$ROM_FILE" > /dev/null 2>&1
        fi
    else
        echo "----------------------------------------------------------"
        echo " [ ERROR DE CÓDIGO ]"
        echo "----------------------------------------------------------"
        cat build/errores.log
        echo "----------------------------------------------------------"
        echo " [!] Corrige los errores y cierra el emulador (si sigue abierto)"
        echo " [!] o presiona Ctrl+C en esta terminal para abortar."
        echo "----------------------------------------------------------"
        
        # En caso de error, esperamos a que el usuario cierre el emulador 
        # o actúe sobre la terminal para que no entre en un bucle infinito de errores.
        sleep 3
    fi
done