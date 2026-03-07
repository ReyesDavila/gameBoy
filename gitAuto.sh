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


# --- [NUEVO] CONTROL DE VERSIONES LOCALES ---
echo -e "\n${AZUL}[PASO 2]: Creando Copia Local${NC}"

# 1. Obtener el nombre de la carpeta actual del proyecto
NOMBRE_PROYECTO=$(basename "$PWD")

# 2. Definir ruta FUERA del directorio actual (..)
DIR_LOCAL="../versiones_locales/$NOMBRE_PROYECTO"

# 3. Crear la carpeta si no existe
mkdir -p "$DIR_LOCAL"

# 4. Contar cuántas versiones (verXX) existen para generar la siguiente
NUM=$(ls -1 "$DIR_LOCAL" 2>/dev/null | grep -E '^ver[0-9]+$' | wc -l)
VER_NAME=$(printf "ver%02d" $((NUM + 1)))
DESTINO="$DIR_LOCAL/$VER_NAME"

# 5. Copia limpia (Al estar fuera, ya no hay riesgo de recursividad infinita)
mkdir -p "$DESTINO"
cp -r ./* "$DESTINO/" 2>/dev/null

echo -e "${VERDE} ✔ Backup guardado en $DESTINO${NC}"




# --- SEGURIDAD (Tu lógica original intacta) ---
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

verificar_acceso




# --- GESTIÓN DE SEGURIDAD Y PERFILES ---
gestionar_sistema() {
    echo -e "\n${AMARILLO}--- PANEL DE ADMINISTRACIÓN ---${NC}"
    echo "1) Seleccionar perfil existente"
    echo "2) Agregar nuevo perfil"
    echo "3) Cambiar contraseña de acceso"
    echo "4) ELIMINAR TODO (Perfiles y Clave)"
    echo "5) Salir"
    read -p "Selección: " ADMIN_OPT

    case $ADMIN_OPT in
        1) # Seleccionar existente
           if [ ! -f "$CONFIG_GLOBAL" ]; then echo "No hay perfiles."; gestionar_sistema; fi
           nl -s ") " "$CONFIG_GLOBAL" | cut -d',' -f1,2
           read -p "Número de perfil: " P_SEL
           LINEA=$(sed -n "${P_SEL}p" "$CONFIG_GLOBAL")
           ;;
        2) # Nuevo perfil
           read -p "Usuario GitHub: " GH_USER
           read -p "Repositorio: " GH_REPO
           echo -n "Token: "; stty -echo; read GH_TOKEN; stty echo; echo ""
           echo "$GH_USER,$GH_REPO,$GH_TOKEN" >> "$CONFIG_GLOBAL"
           LINEA="$GH_USER,$GH_REPO,$GH_TOKEN"
           ;;
        3) # Cambiar clave
           rm -f "$PASS_FILE"
           verificar_acceso
           gestionar_sistema
           ;;
        4) # Borrado total
           read -p "¿ESTÁS SEGURO? (s/n): " CONF
           if [ "$CONF" == "s" ]; then rm -f "$CONFIG_GLOBAL" "$PASS_FILE"; echo "Sistema reseteado."; exit 0; fi
           gestionar_sistema
           ;;
        *) exit 0 ;;
    esac
}

# Flujo de ejecución
verificar_acceso
gestionar_sistema

# Extraer datos para Git
GH_USER=$(echo $LINEA | cut -d',' -f1)
GH_REPO=$(echo $LINEA | cut -d',' -f2)
GH_TOKEN=$(echo $LINEA | cut -d',' -f3)



# --- PROCESO DE SUBIDA (Tu lógica original) ---
echo -e "\n${AZUL}[PASO 3]: Sincronizando GitHub${NC}"
read -p "¿Nota del cambio?: " MSJ
MSJ=${MSJ:-"Update $VER_NAME"}

git config --global user.name "$GH_USER"
git config --global user.email "$GH_USER@users.noreply.github.com"
[ ! -d ".git" ] && git init -q
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"
git branch -M main

git add .
git commit -m "$MSJ" -q
if git push -u origin main -f; then
    echo -e "\n${VERDE}¡PROCESO COMPLETADO!${NC}"
else
    echo -e "${ROJO}Error en el push.${NC}"
fi

read -p "Enter para salir..."