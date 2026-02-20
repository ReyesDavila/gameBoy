#!/bin/bash

CONFIG_GLOBAL="$HOME/.git_profiles.txt"
PASS_FILE="$HOME/.git_access.txt"

# --- COLORES ---
ROJO='\033[0;31m'
VERDE='\033[0;32m'
AZUL='\033[0;34m'
AMARILLO='\033[1;33m'
NC='\033[0m'

# --- SEGURIDAD ---
verificar_acceso() {
    if [ ! -f "$PASS_FILE" ]; then
        echo -e "${AMARILLO}[!] SEGURIDAD: Crea una clave para esta PC:${NC}"
        read -s -p "Clave: " P1; echo ""; read -s -p "Confirma: " P2; echo ""
        [ "$P1" == "$P2" ] && echo "$P1" > "$PASS_FILE" || exit 1
    else
        echo -n "Introduce clave de acceso: "
        stty -echo; read ACC; stty echo; echo ""
        [ "$ACC" != "$(cat "$PASS_FILE")" ] && { echo "Error."; exit 1; }
    fi
}

clear
echo -e "${AZUL}=========================================================="
echo "          gitAuto.sh - GESTOR DE VERSIONES"
echo -e "==========================================================${NC}"

verificar_acceso

# --- PERFILES ---
if [ -f "$CONFIG_GLOBAL" ]; then
    echo -e "${VERDE}[Perfiles registrados]:${NC}"
    nl -s ") " "$CONFIG_GLOBAL" | cut -d',' -f1,2
    read -p "Opción (Enter para el último / d para borrar): " OPT
    if [ "$OPT" == "d" ]; then rm "$CONFIG_GLOBAL" "$PASS_FILE"; exit; fi
    if [ -z "$OPT" ]; then LINEA=$(tail -n 1 "$CONFIG_GLOBAL"); else LINEA=$(sed -n "${OPT}p" "$CONFIG_GLOBAL"); fi
    GH_USER=$(echo $LINEA | cut -d',' -f1); GH_REPO=$(echo $LINEA | cut -d',' -f2); GH_TOKEN=$(echo $LINEA | cut -d',' -f3)
else
    read -p "Usuario GitHub: " GH_USER
    read -p "Repositorio (ej: gameBoy): " GH_REPO
    echo -n "Token (invisible): "; stty -echo; read GH_TOKEN; stty echo; echo ""
    echo "$GH_USER,$GH_REPO,$GH_TOKEN" >> "$CONFIG_GLOBAL"
fi

# --- LÓGICA DE TRIPLE NIVEL ---
# Capturamos el nombre de la carpeta donde estás ahora (ej: mi_proyecto_gb)
CARPETA_LOCAL=$(basename "$PWD")

echo -e "\n${AMARILLO}--- CONFIGURACIÓN DE ESTRUCTURA ---${NC}"
echo -e "1. Nombre del JUEGO (Carpeta principal en GitHub)"
read -p "   Ejemplo: 'Pong' o 'Contra' [Sugerido: $CARPETA_LOCAL]: " JUEGO_NAME
JUEGO_NAME=${JUEGO_NAME:-$CARPETA_LOCAL}

echo -e "\n2. Nombre de la VERSIÓN (Sub-carpeta)"
read -p "   Ejemplo: 'ver01', 'v1.2', 'final' [Sugerido: v_actual]: " VER_NAME
VER_NAME=${VER_NAME:-"v_actual"}

# --- CREACIÓN DE LA ESTRUCTURA ---
# Creamos la ruta Juego/Version
RUTA_FINAL="$JUEGO_NAME/$VER_NAME"

echo -e "\n${AZUL}[*] Preparando: $GH_REPO / $RUTA_FINAL ...${NC}"

# Creamos las carpetas físicas temporalmente para organizar
mkdir -p "$RUTA_FINAL"

# Movemos TODO lo que hay en la carpeta actual hacia adentro de la carpeta de versión
# Evitamos mover la carpeta destino, la carpeta .git y el propio script
find . -maxdepth 1 ! -name "$JUEGO_NAME" ! -name ".git" ! -name "gitAuto.sh" ! -name "." -exec mv {} "$RUTA_FINAL/" \;

# --- SUBIDA A GITHUB ---
git config --global user.name "$GH_USER"
git config --global user.email "$GH_USER@users.noreply.github.com"

git init -q
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"
git branch -M main
git add .
git commit -m "Nuevo: $JUEGO_NAME - Versión: $VER_NAME" -q

echo -e "${AZUL}[*] Sincronizando repositorio remoto...${NC}"
if git push -u origin main -f; then
    echo -e "\n${VERDE}=========================================================="
    echo "   ¡ÉXITO! Estructura creada en GitHub:"
    echo "   $GH_REPO -> $JUEGO_NAME -> $VER_NAME"
    echo -e "==========================================================${NC}"
else
    echo -e "${ROJO}Error. Revisa tu Token o conexión.${NC}"
fi

read -p "Presiona Enter para cerrar..."