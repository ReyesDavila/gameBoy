
/**
 * Función minimalista para escanear mapas de instancias.
 * @param map: El array del mapa (ej. scene01_instances)
 * @param w: Ancho del mapa
 * @param h: Alto del mapa
 */
 
#define scene_load_instances(map, w, h, relation_macro) { \
    uint16_t i = 0; \
    for (uint8_t py = 0; py < h; py++) { \
        for (uint8_t px = 0; px < w; px++) { \
            uint8_t t = map[i++]; \
            if (t != 0) { \
                /* Convertimos tile a coordenadas de píxel (x8) */ \
                relation_macro(t, px << 3, py << 3); \
            } \
        } \
    } \
}
