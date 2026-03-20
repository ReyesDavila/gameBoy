#!/bin/bash

# --- CONFIGURACIÓN DE RUTAS ---
IMG_DIR="imagenes"
OUT_DIR="codigos"
SPRITES_H="$OUT_DIR/_sprites.h"
SPRITES_C="$OUT_DIR/_sprites.c"

# --- FUNCIÓN: FINALIZAR CON PAUSA ---
finalizar() {
    echo -e "\n------------------------------------------------"
    read -p "Presiona [Enter] para cerrar..."
    exit $1
}

# --- FUNCIÓN: BUSCAR PNG2ASSET ---
find_png2asset() {
    local curr_dir="$PWD"
    while [ "$curr_dir" != "" ]; do
        if [ -x "$curr_dir/bin/png2asset" ]; then
            echo "$curr_dir/bin/png2asset"
            return 0
        fi
        [ "$curr_dir" = "/" ] && break
        curr_dir=$(dirname "$curr_dir")
    done
    return 1
}

echo "🏗️  Iniciando Generador de Activos Encapsulado"
echo "================================================"

# ETAPA I: Saneamiento Profundo
echo "Etapa I: Limpiando entorno..."
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"
PNG2ASSET_PATH=$(find_png2asset)

if [ -z "$PNG2ASSET_PATH" ]; then
    echo "❌ ERROR: No se encontró png2asset."
    finalizar 1
fi

# ETAPA II: Escaneo y Normalización
echo "Etapa II: Normalizando imágenes..."
shopt -s nullglob
for extra in "$IMG_DIR"/*.{bmp,jpg,jpeg,ico,png,gif,webp,tiff,BMP,GIF,PNG}; do
    # Si ya es png, solo lo copia, si no, lo convierte
    nombre_ext="${extra##*/}"
    nombre_base="${nombre_ext%.*}"
    convert "$extra" "$IMG_DIR/${nombre_base}.png" 2>/dev/null
done

# ETAPA III: Análisis de Metadatos y Cerebro de Nombres
echo "Etapa III: Analizando nombres y dimensiones..."
SPRITE_NAMES=()
SPRITE_W=()
SPRITE_H=()

# Leemos PNGs ordenados alfabéticamente
for img_path in $(ls "$IMG_DIR"/*.png | sort); do
    img_file="${img_path##*/}"
    
    # Regla de Cirugía de Nombres: Extraer dimensiones y Limpiar nombre
    if [[ "$img_file" =~ ^(.*)_([0-9]+)x([0-9]+)\.png$ ]]; then
        CLEAN_NAME="${BASH_REMATCH[1]}"
        W="${BASH_REMATCH[2]}"
        H="${BASH_REMATCH[3]}"
    else
        CLEAN_NAME="${img_file%.*}"
        H=$(identify -format "%h" "$img_path" 2>/dev/null)
        W=$H # Asumimos cuadrado si no hay info
    fi
    
    SPRITE_NAMES+=("$CLEAN_NAME")
    SPRITE_W+=("$W")
    SPRITE_H+=("$H")
    echo "  > Detectado: $CLEAN_NAME [${W}x${H}]"
done

# ETAPA IV: Conversión Masiva (png2asset)
echo "Etapa IV: Ejecutando conversión a C..."
for i in "${!SPRITE_NAMES[@]}"; do
    NAME="${SPRITE_NAMES[$i]}"
    W="${SPRITE_W[$i]}"
    H="${SPRITE_H[$i]}"
    
    # Ejecutamos png2asset enviando el resultado a la carpeta 'codigos'
    # Usamos -c para especificar el nombre del archivo de salida limpio
    #"$PNG2ASSET_PATH" "$IMG_DIR/${NAME}"*".png" -sw "$W" -sh "$H" -c "$OUT_DIR/${NAME}.c"

    # Cambiamos la línea de ejecución de png2asset para incluir la bandera obligatoria -spr8x8
    "$PNG2ASSET_PATH" "$IMG_DIR/${NAME}"*".png" -sw "$W" -sh "$H" -spr8x8 -c "$OUT_DIR/${NAME}.c"
done

# ETAPA V: Generación de _sprites.h (El Contrato)
echo "Etapa V: Creando _sprites.h..."
{
    echo "#ifndef _SPRITES_H"
    echo "#define _SPRITES_H"
    echo ""
    echo "#include <gbdk/metasprites.h>"
    echo "#include <stdint.h>"
    echo ""
    echo "// --- INCLUDES DE ACTIVOS ---"
    for NAME in "${SPRITE_NAMES[@]}"; do
        echo "#include \"${NAME}.h\""
    done
    echo ""
    echo "// --- DEFINICIONES DE ID (ALFABÉTICO) ---"
    for i in "${!SPRITE_NAMES[@]}"; do
        echo "#define ${SPRITE_NAMES[$i]} $i"
    done
    echo ""
    echo "extern const metasprite_t** const lista_metasprites[];"
    echo "extern const uint8_t* const lista_tile_data[];"
    echo "extern const uint8_t lista_tile_count[];"
    echo ""
    echo "#endif"
} > "$SPRITES_H"

# ETAPA VI: Generación de _sprites.c (El Almacén)
echo "Etapa VI: Creando _sprites.c..."
{
    echo "#include \"_sprites.h\""
    echo ""
    echo "// 1. Punteros a Metasprites"
    echo "const metasprite_t** const lista_metasprites[] = {"
    for NAME in "${SPRITE_NAMES[@]}"; do
        echo "    ${NAME}_metasprites,"
    done
    echo "};"
    echo ""
    echo "// 2. Punteros a Datos de Tiles"
    echo "const uint8_t* const lista_tile_data[] = {"
    for NAME in "${SPRITE_NAMES[@]}"; do
        echo "    ${NAME}_tiles,"
    done
    echo "};"
    echo ""
    echo "// 3. Conteo de Tiles"
    echo "const uint8_t lista_tile_count[] = {"
    for NAME in "${SPRITE_NAMES[@]}"; do
        echo "    ${NAME}_TILE_COUNT,"
    done
    echo "};"
} > "$SPRITES_C"

echo "------------------------------------------------"
echo "✅ PROCESO COMPLETADO CON ÉXITO"
finalizar 0