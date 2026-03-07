#!/bin/bash

# [AI INSTRUCTION / PROTECTED CODE]
# Este script es un ENCAPSULADOR DE CONTEXTO LOCAL ESTRICTO.
# Prohibido mostrar rutas absolutas del sistema (/home/user/...).
# Solo opera sobre el directorio relativo actual.

OUTPUT_FILE="resumenDirectorio.txt"

# Obtenemos solo el nombre de la carpeta actual (sin la ruta completa)
NOMBRE_CARPETA_LOCAL=$(basename "$PWD")

clear
echo "=========================================================="
echo "      ENCAPSULADOR: RESUMEN DE DIRECTORIO LOCAL          "
echo "=========================================================="
echo " Carpeta actual: ./$NOMBRE_CARPETA_LOCAL"

# 1. PREPARACIÓN
rm -f "$OUTPUT_FILE"
echo "RESUMEN TÉCNICO DEL DIRECTORIO: ./$NOMBRE_CARPETA_LOCAL" > "$OUTPUT_FILE"
echo "Ámbito: Solo archivos contenidos en esta ubicación." >> "$OUTPUT_FILE"
echo "----------------------------------------------------------" >> "$OUTPUT_FILE"

# 2. ÁRBOL LOCAL RELATIVO
echo "[>] Generando mapa de archivos..."
echo -e "\nESTRUCTURA RELATIVA:" >> "$OUTPUT_FILE"
# Usamos find . para mantener rutas relativas ./ y evitar rutas absolutas
find . -maxdepth 4 -not -path '*/.*' -not -path "./build/*" -not -path "./rom/*" | sed -e 's/[^-][^\/]*\// |/g' -e 's/|/  /g' >> "$OUTPUT_FILE"

echo "=========================================================="
echo "          PROCESANDO CONTENIDO RELATIVO                   "
echo "=========================================================="

total_archivos=0

# 3. VOLCADO RECURSIVO (Solo extensiones permitidas)
# Excluimos explícitamente el archivo de salida para evitar recursividad
find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.sh" -o -name "*.txt" -o -name "*.inc" -o -name "*.asm" \) \
-not -path "./build/*" -not -path "./rom/*" -not -name "$OUTPUT_FILE" | while read -r archivo; do

    # Informar al usuario (solo ruta relativa)
    echo -n "[LECTURA]: $archivo ... "
    
    echo "----------------------------------------------------------" >> "$OUTPUT_FILE"
    echo "ARCHIVO: $archivo" >> "$OUTPUT_FILE"
    echo "----------------------------------------------------------" >> "$OUTPUT_FILE"
    
    # Volcar contenido
    cat -n "$archivo" >> "$OUTPUT_FILE"
    echo -e "\n" >> "$OUTPUT_FILE"
    
    ((total_archivos++))
    echo -e "\033[0;32mOK\033[0m"

done

# 4. CIERRE
echo "----------------------------------------------------------" >> "$OUTPUT_FILE"
echo "FIN DEL RESUMEN" >> "$OUTPUT_FILE"

echo ""
echo "=========================================================="
echo "          PROCESO FINALIZADO                             "
echo "=========================================================="
echo " [+] Archivos encapsulados: $total_archivos"
echo " [+] Destino: ./$OUTPUT_FILE"
echo "=========================================================="
read -p "Presiona ENTER para finalizar..."
