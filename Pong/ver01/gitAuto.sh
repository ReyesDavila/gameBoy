#!/bin/bash

# Bases de datos globales
CONFIG_GLOBAL="$HOME/.git_perfiles.txt"
PASS_FILE="$HOME/.git_clave.txt"

# --- ESTÉTICA ---
ROJO='\033[0;31m'
VERDE='\033[0;32m'
AZUL='\033[0;34m'
AMARILLO='\033[1;33m'
NC='\033[0m'

# --- SEGURIDAD LOCAL ---
verificar_acceso() {
    if [ ! -f "$PASS_FILE" ]; then
        echo -e "${AMARILLO}[!] CONFIGURACIÓN DE SEGURIDAD${NC}"
        read -s -p "Crea una clave para proteger tus datos en esta PC: " P1; echo ""
        read -s -p "Confirma tu clave: " P2; echo ""
        [ "$P1" == "$P2" ] && [ -n "$P1" ] && echo "$P1" > "$PASS_FILE" || { echo "Error en claves."; exit 1; }
    else
        echo -n "Clave de acceso: "
        stty -echo; read ACC; stty echo; echo ""
        [ "$ACC" != "$(cat "$PASS_FILE")" ] && { echo -e "${ROJO}Acceso denegado.${NC}"; exit 1; }
    fi
}

clear
echo -e "${AZUL}=========================================================="
echo "          gitAuto.sh - SINCRONIZADOR DE PROYECTOS"
echo -e "==========================================================${NC}"

verificar_acceso

# --- GESTIÓN DE PERFILES Y PROYECTOS ---
if [ -f "$CONFIG_GLOBAL" ]; then
    echo -e "${VERDE}[Perfiles Guardados]:${NC}"
    # Formato del archivo: usuario,repositorio,token,ultimo_proyecto
    nl -s ") " "$CONFIG_GLOBAL" | cut -d',' -f1,2
    echo "n) Nuevo perfil / d) Borrar todo"
    read -p "Selecciona: " OPT
    
    if [ "$OPT" == "d" ]; then rm -f "$CONFIG_GLOBAL" "$PASS_FILE"; exit 0; fi
    if [ "$OPT" == "n" ]; then NUEVO="si"; 
    elif [ -z "$OPT" ]; then LINEA=$(tail -n 1 "$CONFIG_GLOBAL");
    else LINEA=$(sed -n "${OPT}p" "$CONFIG_GLOBAL"); fi
else
    NUEVO="si"
fi

if [ "$NUEVO" == "si" ]; then
    read -p "Usuario GitHub: " GH_USER
    read -p "Repositorio: " GH_REPO
    echo -n "Token (invisible): "; stty -echo; read GH_TOKEN; stty echo; echo ""
else
    GH_USER=$(echo $LINEA | cut -d',' -f1)
    GH_REPO=$(echo $LINEA | cut -d',' -f2)
    GH_TOKEN=$(echo $LINEA | cut -d',' -f3)
    LAST_PROJ=$(echo $LINEA | cut -d',' -f4)
fi

# --- DEFINICIÓN DE RUTA ---
echo -e "\n${AMARILLO}--- CONFIGURACIÓN DE RUTA ---${NC}"
[ -n "$LAST_PROJ" ] && echo "Último proyecto usado: $LAST_PROJ"
read -p "Nombre de la Carpeta Proyecto en GitHub: " PROJ_NAME
PROJ_NAME=${PROJ_NAME:-$LAST_PROJ}

# Nombre de la carpeta actual (CarpetaRaiz) - Inamovible
CARPETA_RAIZ=$(basename "$PWD")

# Actualizar base de datos con el último proyecto usado
if [ "$NUEVO" == "si" ]; then
    echo "$GH_USER,$GH_REPO,$GH_TOKEN,$PROJ_NAME" >> "$CONFIG_GLOBAL"
else
    # Actualiza la línea actual con el nuevo nombre de proyecto
    sed -i "s|$LINEA|$GH_USER,$GH_REPO,$GH_TOKEN,$PROJ_NAME|" "$CONFIG_GLOBAL"
fi

# --- PROCESO GIT (SIN MOVER ARCHIVOS LOCALES) ---
git config --global user.name "$GH_USER"
git config --global user.email "$GH_USER@users.noreply.github.com"

[ ! -d ".git" ] && git init -q
git remote remove origin 2>/dev/null
git remote add origin "https://$GH_USER:$GH_TOKEN@github.com/$GH_USER/$GH_REPO.git"
git branch -M main

# El truco: Para que en GitHub se vea Usuario/Repo/Proyecto/Raiz 
# sin mover archivos en tu PC, usamos el index de Git para crear el prefijo.
echo -e "\n${AZUL}[*] Preparando estructura remota...${NC}"
git add .
# Este comando es la clave: mueve todo al "staging" bajo la ruta deseada
git ls-files -s | sed "s|\t\"*|&${PROJ_NAME}/${CARPETA_RAIZ}/|" | git update-index --index-info
# Limpiamos los archivos que quedaron en la raíz del commit
git ls-files | grep -v "^${PROJ_NAME}/" | xargs git rm --cached -q 2>/dev/null

git commit -m "Sincronizado: ${PROJ_NAME}/${CARPETA_RAIZ}" -q



echo -e "${AZUL}[*] Subiendo a GitHub...${NC}"
if git push -u origin main -f; then
    echo -e "\n${VERDE}=========================================================="
    echo "   ¡ÉXITO! Sincronización completada."
    echo "   Destino: $GH_USER/$GH_REPO/$PROJ_NAME/$CARPETA_RAIZ"
    echo -e "==========================================================${NC}"
else
    echo -e "${ROJO}Error al subir. Revisa Token o Permisos.${NC}"
fi

read -p "Presiona Enter para cerrar..."