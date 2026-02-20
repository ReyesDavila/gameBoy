#!/bin/bash

# Archivos de configuración globales en el hogar del usuario
CONFIG_GLOBAL="$HOME/.git_perfiles_acceso.txt"
PASS_FILE="$HOME/.git_clave_local.txt"

# --- ESTÉTICA Y COLORES ---
ROJO='\033[0;31m'
VERDE='\033[0;32m'
AZUL='\033[0;34m'
AMARILLO='\033[1;33m'
NC='\033[0m'

# --- FUNCIÓN DE SEGURIDAD LOCAL ---
verificar_acceso() {
    if [ ! -f "$PASS_FILE" ]; then
        echo -e "${AMARILLO}[!] CONFIGURACIÓN DE SEGURIDAD INICIAL${NC}"
        echo "Por seguridad, define una contraseña para proteger tus datos de GitHub en esta PC."
        read -s -p "Crea tu contraseña local: " P1; echo ""
        read -s -p "Confirma tu contraseña: " P2; echo ""
        if [ "$P1" == "$P2" ] && [ -n "$P1" ]; then
            echo "$P1" > "$PASS_FILE"
            echo -e "${VERDE}Contraseña establecida correctamente.${NC}"
        else
            echo -e "${ROJO}Las contraseñas no coinciden o están vacías.${NC}"
            exit 1
        fi
    else
        echo -n "Introduce tu contraseña de acceso: "
        stty -echo; read ACCESO; stty echo; echo ""
        if [ "$ACCESO" != "$(cat "$PASS_FILE")" ]; then
            echo -e "${ROJO}Acceso denegado.${NC}"
            exit 1
        fi
    fi
}

# --- FUNCIÓN DIDÁCTICA SOBRE EL TOKEN ---
explicar_token() {
    echo -e "\n${AZUL}--- ¿QUÉ ES EL TOKEN DE ACCESO PERSONAL (PAT)? ---${NC}"
    echo "Es una clave de seguridad que reemplaza a tu contraseña de GitHub."
    echo "1. En GitHub: Ve a tu Foto -> Settings -> Developer Settings."
    echo "2. Personal access tokens -> Tokens (classic)."
    echo "3. Pulsa 'Generate new token' y selecciona el permiso 'repo'."
    echo "4. Cópialo y pégalo aquí cuando se te pida."
    echo "----------------------------------------------------------"
}

# --- INICIO DEL ASISTENTE ---
clear
echo -e "${AZUL}=========================================================="
echo "          gitAuto.sh - ASISTENTE DE SINCRONIZACIÓN"
echo -e "==========================================================${NC}"

verificar_acceso

# --- ADMINISTRACIÓN DE PERFILES ---
if [ -f "$CONFIG_GLOBAL" ]; then
    echo -e "\n${VERDE}[Perfiles de GitHub guardados]:${NC}"
    nl -s ") " "$CONFIG_GLOBAL" | cut -d',' -f1,2
    echo "n) Registrar un nuevo perfil"
    echo "d) BORRAR registros y contraseña (Reset total)"
    read -p "Elige una opción (Enter para el último usado): " OPT
    
    if [ "$OPT" == "d" ]; then
        rm -f "$CONFIG_GLOBAL" "$PASS_FILE"
        echo -e "${VERDE}Datos eliminados correctamente.${NC}"
        exit 0
    elif [ "$OPT" == "n" ]; then
        NUEVO_PERFIL="si"
    elif [ -z "$OPT" ]; then
        LINEA=$(tail -n 1 "$CONFIG_GLOBAL")
    else
        LINEA=$(sed -n "${OPT}p" "$CONFIG_GLOBAL")
    fi
else
    NUEVO_PERFIL="si"
fi

# --- CAPTURA DE DATOS NUEVOS ---
if [ "$NUEVO_PERFIL" == "si" ]; then
    echo -e "\n${AMARILLO}[Nuevo Perfil de Usuario]${NC}"
    read -p "1. Usuario de GitHub: " GH_USER
    read -p "2. Nombre del Repositorio: " GH_REPO
    while true; do
        echo -n "3. Pega tu Token (invisible) o escribe 'ayuda': "
        stty -echo; read TOKEN_INPUT; stty echo; echo ""
        if [ "$TOKEN_INPUT" == "ayuda" ]; then
            explicar_token
        else
            GH_TOKEN=$TOKEN_INPUT
            break
        fi
    done
    echo "$GH_USER,$GH_REPO,$GH_TOKEN" >> "$CONFIG_GLOBAL"
else
    GH_USER=$(echo $LINEA | cut -d',' -f1)
    GH_REPO=$(echo $LINEA | cut -d',' -f2)
    GH_TOKEN=$(echo $LINEA | cut -d',' -f3)
fi

# --- LÓGICA DE SUBIDA RESPETUOSA ---
# Determinamos el nombre de la carpeta actual como sugerencia de versión
CARPETA_ACTUAL=$(basename "$PWD")

echo -e "\n${AMARILLO}--- CONFIGURACIÓN DE LA SUBIDA ---${NC}"
echo "El script enviará el contenido actual a GitHub sin alterar tus archivos locales."
read -p "Nombre del Proyecto en GitHub [$GH_REPO]: " PROYECTO_NAME
PROYECTO_NAME=${PROYECTO_NAME:-$GH_REPO}

read -p "Nombre de la Versión/Carpeta [$CARPETA_ACTUAL]: " VER_NAME
VER_NAME=${VER_NAME:-$CARPETA_ACTUAL}

# Configuración de identidad de Git para este envío
git config --global user.name "$GH_USER"
git config --global user.email "$GH_USER@users.noreply.github.com"

# --- INICIALIZACIÓN Y ENVÍO ---
[ ! -d ".git" ] && git init -q
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"
git branch -M main

# Añadir todos los archivos actuales
git add .
git commit -m "Sincronización: $PROYECTO_NAME - $VER_NAME ($(date +'%d/%m/%Y %H:%M'))" -q



echo -e "\n${AZUL}[*] Sincronizando con el servidor remoto...${NC}"
if git push -u origin main -f; then
    echo -e "\n${VERDE}=========================================================="
    echo "   ¡ÉXITO! Tu proyecto se ha sincronizado."
    echo "   Repositorio: $GH_REPO"
    echo "   Referencia: $PROYECTO_NAME / $VER_NAME"
    echo -e "==========================================================${NC}"
else
    echo -e "${ROJO}Hubo un problema. Revisa tu Token o el nombre del Repositorio.${NC}"
fi

read -p "Presiona [Enter] para finalizar..."