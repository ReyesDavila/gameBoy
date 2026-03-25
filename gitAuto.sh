#!/bin/bash

# --- CONFIGURACIÓN ---
CONFIG_GLOBAL="$HOME/.gitAuto_perfiles.txt"
PASS_FILE="$HOME/.gitAuto_clave.txt"
DIR_LOCAL="versiones_locales" 

# --- COLORES ---
ROJO='\033[0;31m'
VERDE='\033[0;32m'
AZUL='\033[0;34m'
AMARILLO='\033[1;33m'
NC='\033[0m'

# --- ARTE ASCII ---
echo -e "${AZUL}"
echo "  ___________________________________________"
echo " |    ______ _ _Auto   _____ _    _          |"
echo " |   |  ____(_) |     / ____| |  | |         |"
echo " |   | |__   _| |_   | |  __| |__| |         |"
echo " |   |  __| | | __|  | | |_ |  __  |         |"
echo " |   | |    | | |_   | |__| | |  | |         |"
echo " |   |_|    |_|\__|   \_____|_|  |_|         |"
echo " |___________________________________________|"
echo -e "          [ MENTOR GBDK EDITION ]${NC}\n"

# --- [NUEVO] SENSOR DE DIRECTORIO ---
if [ ! -f "main.c" ]; then
    echo -e "${ROJO}[ERROR]: No se encuentra main.c en esta carpeta.${NC}"
    echo -e "${AMARILLO}Asegúrate de ejecutar este script desde la raíz de tu proyecto.${NC}"
    read -p "Presiona Enter para salir..."
    exit 1
fi

# --- [PASO 2]: CONTROL DE VERSIONES LOCALES ---
echo -e "\n${AZUL}[PASO 2]: Creando Copia Local (Seguridad)${NC}"

NOMBRE_PROYECTO=$(basename "$PWD")
DIR_LOCAL_PATH="../versiones_locales/$NOMBRE_PROYECTO"

mkdir -p "$DIR_LOCAL_PATH"
NUM=$(ls -1 "$DIR_LOCAL_PATH" 2>/dev/null | grep -E '^ver[0-9]+$' | wc -l)
VER_NAME=$(printf "ver%02d" $((NUM + 1)))
DESTINO="$DIR_LOCAL_PATH/$VER_NAME"

mkdir -p "$DESTINO"
cp -r ./* "$DESTINO/" 2>/dev/null
echo -e "${VERDE} ✔ Backup guardado en $DESTINO${NC}"

# --- SEGURIDAD ---
verificar_acceso() {
    if [ ! -f "$PASS_FILE" ]; then
        echo -e "${AMARILLO}[SISTEMA]: Configuración inicial...${NC}"
        read -s -p "Crea tu contraseña local: " P1; echo ""
        read -s -p "Confirma tu contraseña: " P2; echo ""
        if [ "$P1" == "$P2" ] && [ -n "$P1" ]; then
            echo "$P1" > "$PASS_FILE"
        else
            echo -e "${ROJO}Error: No coinciden.${NC}"; exit 1
        fi
    else
        echo -n "Introduce tu clave de acceso local: "
        stty -echo; read ACCESO; stty echo; echo ""
        if [ "$ACCESO" != "$(cat "$PASS_FILE")" ]; then
            echo -e "${ROJO}Acceso denegado.${NC}"; exit 1
        fi
    fi
}

gestionar_sistema() {
    echo -e "\n${AMARILLO}--- PANEL DE ADMINISTRACIÓN ---${NC}"
    echo "1) Seleccionar perfil existente"
    echo "2) Agregar nuevo perfil"
    echo "3) Cambiar contraseña de acceso"
    echo "4) ELIMINAR TODO"
    echo "5) Salir"
    read -p "Selección: " ADMIN_OPT

    case $ADMIN_OPT in
        1) 
           if [ ! -f "$CONFIG_GLOBAL" ]; then echo "No hay perfiles."; gestionar_sistema; fi
           nl -s ") " "$CONFIG_GLOBAL" | cut -d',' -f1,2
           read -p "Número de perfil: " P_SEL
           LINEA=$(sed -n "${P_SEL}p" "$CONFIG_GLOBAL")
           ;;
        2) 
           read -p "Usuario GitHub: " GH_USER
           read -p "Repositorio: " GH_REPO
           echo -n "Token: "; stty -echo; read GH_TOKEN; stty echo; echo ""
           echo "$GH_USER,$GH_REPO,$GH_TOKEN" >> "$CONFIG_GLOBAL"
           LINEA="$GH_USER,$GH_REPO,$GH_TOKEN"
           ;;
        3) rm -f "$PASS_FILE"; verificar_acceso; gestionar_sistema ;;
        4) read -p "¿SEGURO? (s/n): " CONF; [ "$CONF" == "s" ] && rm -f "$CONFIG_GLOBAL" "$PASS_FILE"; exit 0 ;;
        *) exit 0 ;;
    esac
}

verificar_acceso
gestionar_sistema

GH_USER=$(echo "$LINEA" | cut -d',' -f1)
GH_REPO=$(echo "$LINEA" | cut -d',' -f2)
GH_TOKEN=$(echo "$LINEA" | cut -d',' -f3)

# --- [PASO 3]: SINCRONIZACIÓN GITHUB (ESTRICTA) ---
echo -e "\n${AZUL}[PASO 3]: Enviando a GitHub${NC}"
read -p "¿Nota del cambio?: " MSJ
MSJ=${MSJ:-"Update $VER_NAME"}

# Configuración de Git
git config --global user.name "$GH_USER"
git config --global user.email "$GH_USER@users.noreply.github.com"

# Asegurar que Git está activo en esta carpeta
if [ ! -d ".git" ]; then
    git init -q
    git branch -M main
fi

# Refrescar conexión remota
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"

# Registrar cambios locales
git add .
git commit -m "$MSJ" -q

# UNIÓN DE HISTORIALES: El truco para no borrar el pasado
echo -e "${AMARILLO}Fusionando con el historial de la nube...${NC}"
git fetch origin main 2>/dev/null
# Intentamos unir las historias. Si hay choque, mandan TUS archivos (-X theirs)
git merge origin/main --allow-unrelated-histories -m "Merge branch 'main' of GitHub" -X theirs -q 2>/dev/null

# Subida final
if git push -u origin main; then
    echo -e "\n${VERDE}¡ÉXITO! Archivos subidos. Historial preservado.${NC}"
else
    echo -e "\n${ROJO}Fallo en el envío.${NC}"
    echo -e "${AMARILLO}Si el error persiste, asegúrate de haber hecho el 'Paso 1' (push -f manual).${NC}"
fi

read -p "Presiona Enter para finalizar..."
