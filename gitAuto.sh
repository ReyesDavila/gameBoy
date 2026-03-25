#!/bin/bash

# --- CONFIGURACIÓN ---
CONFIG_GLOBAL="$HOME/.gitAuto_perfiles.txt"
PASS_FILE="$HOME/.gitAuto_clave.txt"

# --- COLORES ---
ROJO='\033[0;31m'
VERDE='\033[0;32m'
AZUL='\033[0;34m'
AMARILLO='\033[1;33m'
NC='\033[0m'

# --- ARTE ASCII ---
echo -e "${AZUL}  ___________________________________________"
echo " |    ______ _ _Auto   _____ _    _          |"
echo " |   |  ____(_) |     / ____| |  | |         |"
echo " |   | |__   _| |_   | |  __| |__| |         |"
echo " |   |  __| | | __|  | | |_ |  __  |         |"
echo " |   | |    | | |_   | |__| | |  | |         |"
echo " |   |_|    |_|\__|   \_____|_|  |_|         |"
echo " |___________________________________________|${NC}\n"

# --- SEGURIDAD ---
verificar_acceso() {
    if [ ! -f "$PASS_FILE" ]; then
        echo -e "${AMARILLO}[SISTEMA]: Creando contraseña inicial...${NC}"
        read -s -p "Crea tu clave: " P1; echo ""
        read -s -p "Confirma clave: " P2; echo ""
        [ "$P1" == "$P2" ] && echo "$P1" > "$PASS_FILE" || exit 1
    else
        echo -n "Introduce clave: "
        stty -echo; read ACCESO; stty echo; echo ""
        [ "$ACCESO" != "$(cat "$PASS_FILE")" ] && exit 1
    fi
}

gestionar_perfiles() {
    if [ ! -f "$CONFIG_GLOBAL" ]; then
        echo "Agregando primer perfil..."
        read -p "Usuario GitHub: " GH_USER
        read -p "Repositorio: " GH_REPO
        echo -n "Token: "; stty -echo; read GH_TOKEN; stty echo; echo ""
        echo "$GH_USER,$GH_REPO,$GH_TOKEN" > "$CONFIG_GLOBAL"
    fi
    LINEA=$(head -n 1 "$CONFIG_GLOBAL")
}

verificar_acceso
gestionar_perfiles

GH_USER=$(echo "$LINEA" | cut -d',' -f1)
GH_REPO=$(echo "$LINEA" | cut -d',' -f2)
GH_TOKEN=$(echo "$LINEA" | cut -d',' -f3)

# --- PASO 2: BACKUP LOCAL ---
NOMBRE_PROYECTO=$(basename "$PWD")
DIR_LOCAL_PATH="../versiones_locales/$NOMBRE_PROYECTO"
mkdir -p "$DIR_LOCAL_PATH"
NUM=$(ls -1 "$DIR_LOCAL_PATH" 2>/dev/null | grep -E '^ver[0-9]+$' | wc -l)
VER_NAME=$(printf "ver%02d" $((NUM + 1)))
cp -r . "$DIR_LOCAL_PATH/$VER_NAME" 2>/dev/null
echo -e "${VERDE} ✔ Backup local: $VER_NAME${NC}"

# --- PASO 3: SUBIDA FORZADA PERO CONTROLADA ---
echo -e "\n${AZUL}[PASO 3]: Enviando a GitHub...${NC}"
read -p "¿Nota del cambio?: " MSJ
MSJ=${MSJ:-"Update $VER_NAME"}

# Asegurar que Git existe aquí
[ ! -d ".git" ] && git init -q

git config user.name "$GH_USER"
git config user.email "$GH_USER@users.noreply.github.com"

# Limpiar y reconectar el remoto
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"

# Sincronizar (El truco para que NO bajen archivos y SÍ puedas subir)
git add .
git commit -m "$MSJ" -q

# Intentamos subir normal. Si falla por "non-fast-forward", forzamos SOLO esta vez.
if git push -u origin main; then
    echo -e "${VERDE}✔ Subido correctamente.${NC}"
else
    echo -e "${AMARILLO}Detectada diferencia de historial. Forzando actualización...${NC}"
    git push -u origin main --force
    echo -e "${VERDE}✔ GitHub actualizado con tu carpeta actual.${NC}"
fi

read -p "Listo. Enter para salir."
