#!/bin/bash
# Resumen recursivo de carpetas y archivos .c/.h
OUTPUT="resumen_proyecto.txt"

{
    echo "ESTRUCTURA DE CARPETAS Y ARCHIVOS (.c / .h)"
    echo "============================================"
    # Encuentra directorios que contienen archivos .c/.h o los archivos mismos
    find . -maxdepth 100 -not -path '*/.*' \( -type d -o -name "*.c" -o -name "*.h" \) | sort | sed -e 's/[^-][^\/]*\// | /g' -e 's/| \([^| ]\)/|-- \1/'
    
    echo -e "\n\nCONTENIDO DETALLADO DE ARCHIVOS"
    echo "================================"
    find . -maxdepth 100 -not -path '*/.*' \( -name "*.c" -o -name "*.h" \) -print | while read -r file; do
        echo -e "\n[RUTA: $file]"
        echo "--------------------------------------------"
        cat "$file"
        echo -e "\n--------------------------------------------"
    done
} > "$OUTPUT"

echo "Resumen generado en $OUTPUT."