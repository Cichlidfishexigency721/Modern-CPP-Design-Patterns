#!/bin/bash

# Buscar todos los archivos 00.Readme.txt y procesarlos uno por uno
find . -name "00.Readme.txt" | while read -r file; do
   echo "Processing $file..."

   # Aplicamos una serie de comandos sed:
   # 1. Eliminamos las líneas que son puramente marcas de '=' (barras superiores/inferiores)
   # 2. Eliminamos los espacios en blanco al principio de cada línea (trim)
   # 3. La primera línea que contenga el título (ej: FACTORY METHOD) le ponemos un '#' delante
   # 4. Las palabras seguidas de ':' (ej: Intent:, Problem:) las ponemos como sub-encabezados '##'
   # 5. Las líneas de guiones '---' internas las convertimos en reglas horizontales de Markdown
   
   sed -i -r '
      /^[=]{5,}/d;                  # Elimina líneas con 5 o más "="
      s/^[[:space:]]+//;            # Elimina espacios al inicio de las líneas
      
      # Si la línea está en MAYÚSCULAS (el título), la convierte en H1
      # Esto detecta patrones como "FACTORY METHOD PATTERN (CREATIONAL)"
      /^[A-Z ]+(\(.*\))?$/ s/^/# /; 

      # Convierte secciones como "Intent:", "The Problem:", etc. en H2
      s/^([A-Z][a-zA-Z ]+):/## \1/;

      # Reemplaza líneas de guiones internos por una regla horizontal limpia
      /^-{5,}/ s/.*/---/;
   ' "$file"

   # Opcional: Aseguramos que el archivo termine con una regla horizontal
   echo -e "\n---" >> "$file"
done

echo "All Readmes have been optimized for GitHub."
