#!/bin/bash

# Archivos de configuración ocultos en tu carpeta personal (HOME)
CONFIG_GLOBAL="$HOME/.gitAuto_perfiles.txt"
PASS_FILE="$HOME/.gitAuto_clave.txt"

# --- COLORES PARA LA TERMINAL ---
ROJO='\033[0;31m'
VERDE='\033[0;32m'
AZUL='\033[0;34m'
AMARILLO='\033[1;33m'
NC='\033[0m' # Sin color

# --- FUNCIÓN: SEGURIDAD ---
verificar_acceso() {
    if [ ! -f "$PASS_FILE" ]; then
        echo -e "${AMARILLO}[PEDAGOGÍA] Seguridad Inicial:${NC}"
        echo "Vamos a crear una contraseña LOCAL para proteger tu Token de GitHub."
        echo "---------------------------------------------------------------------"
        read -s -p "Crea tu contraseña local: " P1; echo ""
        read -s -p "Confirma tu contraseña: " P2; echo ""
        if [ "$P1" == "$P2" ] && [ -n "$P1" ]; then
            echo "$P1" > "$PASS_FILE"
            echo -e "${VERDE}¡Seguridad configurada!${NC}"
        else
            echo -e "${ROJO}Error: No coinciden. Reinicia el script.${NC}"
            exit 1
        fi
    else
        echo -n "Introduce tu clave de acceso local: "
        stty -echo; read ACCESO; stty echo; echo ""
        if [ "$ACCESO" != "$(cat "$PASS_FILE")" ]; then
            echo -e "${ROJO}Acceso denegado. Clave incorrecta.${NC}"
            exit 1
        fi
    fi
}

# --- INICIO ---
clear
echo -e "${AZUL}=========================================================="
echo "          gitAuto.sh - TU ASISTENTE DE GITHUB"
echo -e "==========================================================${NC}"

verificar_acceso

# --- GESTIÓN DE PERFILES ---
if [ -f "$CONFIG_GLOBAL" ]; then
    echo -e "\n${AZUL}[PASO 1]: Identidad de Usuario${NC}"
    nl -s ") " "$CONFIG_GLOBAL" | cut -d',' -f1,2
    echo "n) Registrar un nuevo perfil"
    echo "d) BORRAR REGISTROS (Limpiar todo)"
    read -p "Opción (Enter para usar el último): " OPT
    
    if [ "$OPT" == "d" ]; then
        rm -f "$CONFIG_GLOBAL" "$PASS_FILE"
        echo -e "${AMARILLO}Datos borrados. Reinicia para empezar de cero.${NC}"
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

# --- DATOS DE GITHUB ---
if [ "$NUEVO_PERFIL" == "si" ]; then
    echo -e "\n${AMARILLO}[NUEVO PERFIL]${NC}"
    read -p "1. Usuario de GitHub: " GH_USER
    read -p "2. Nombre del Repositorio: " GH_REPO
    echo -n "3. Pega tu Token (invisible): "; stty -echo; read GH_TOKEN; stty echo; echo ""
    echo "$GH_USER,$GH_REPO,$GH_TOKEN" >> "$CONFIG_GLOBAL"
else
    GH_USER=$(echo $LINEA | cut -d',' -f1)
    GH_REPO=$(echo $LINEA | cut -d',' -f2)
    GH_TOKEN=$(echo $LINEA | cut -d',' -f3)
fi

# --- PROCESO DE SUBIDA ---
echo -e "\n${AZUL}[PASO 2]: Preparando envío${NC}"
read -p "¿Nota para este cambio? [Update]: " MSJ
MSJ=${MSJ:-"Update automático desde gitAuto.sh"}

# Configurar identidad de Git
git config --global user.name "$GH_USER"
git config --global user.email "$GH_USER@users.noreply.github.com"

# Inicializar si no existe la carpeta .git
[ ! -d ".git" ] && git init -q

# Conectar al repositorio
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"
git branch -M main

# Ejecutar Git
echo -e "${AZUL}[*] Empaquetando y subiendo...${NC}"
git add .
git commit -m "$MSJ" -q

if git push -u origin main -f; then
    echo -e "\n${VERDE}=========================================================="
    echo "   ¡ÉXITO! Tu proyecto ya está en GitHub."
    echo "   URL: https://github.com/$GH_USER/$GH_REPO"
    echo -e "==========================================================${NC}"
else
    echo -e "${ROJO}[!] Falló la subida. Revisa tu Token o el nombre del Repo.${NC}"
fi

read -p "Presiona [Enter] para finalizar..."