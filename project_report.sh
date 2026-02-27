#!/bin/bash

OUTPUT="project_report.txt"

echo "Iniciando análisis del directorio actual..."
echo "------------------------------------------"

# Limpiar archivo previo
> "$OUTPUT"

# 1. Generar Árbol de Recursos
echo "[1/2] Escaneando estructura de carpetas y archivos..."
echo "=== ESTRUCTURA DEL PROYECTO ===" >> "$OUTPUT"

# Listar nombres sin rutas absolutas, ignorando archivos ocultos
find . -maxdepth 10 -not -path '*/.*' | sed -e "s/[^-][^\/]*\// |/g" -e "s/|\([^ ]\)/|-- \1/" >> "$OUTPUT"
echo " -> Estructura guardada."

# 2. Analizar archivos .c y .h
echo "[2/2] Analizando archivos .c y .h para extraer #includes..."
echo -e "\n=== ANÁLISIS DE ARCHIVOS C/H ===" >> "$OUTPUT"

# Buscar archivos .c y .h
find . -type f \( -name "*.c" -o -name "*.h" \) -not -path '*/.*' | while read -r FILE; do
    echo " -> Procesando: $FILE"
    
    echo "--------------------------------" >> "$OUTPUT"
    echo "Archivo: $(basename "$FILE")" >> "$OUTPUT"
    echo "Ruta: $FILE" >> "$OUTPUT"
    
    # Extraer líneas con #include sin espacios iniciales
    grep "#include" "$FILE" | sed 's/^[ \t]*//' >> "$OUTPUT"
done

echo "------------------------------------------"
echo "Análisis completado con éxito."
echo "Resultados guardados en: $OUTPUT"
echo ""
read -p "Presiona Enter para cerrar..."