#!/bin/bash

# Funcion Salto de linea
function saltoLinea {
    echo ""
}

# Verificar si mi repositorio local esta actualizado con el remoto
git fetch origin

# Obtener el nombre de la rama actual
branch=$(git rev-parse --abbrev-ref HEAD)

# Obtener el nombre del repositorio remoto
remote=$(git config --get remote.origin.url)

# Obtener el nombre del repositorio local
local=$(git rev-parse --show-toplevel)

# Mostrar informacion del repositorio
echo "============================================================"
echo "Repositorio local: $local"
echo "============================================================"
echo "Repositorio remoto: $remote"
echo "============================================================"

# Salto de linea
saltoLinea

# Verificar si el repositorio local esta actualizado con el remoto
if git diff --quiet origin/$branch; then
    echo "============================================================"
    echo "El repositorio local esta actualizado con el remoto"
    echo "============================================================"
else
    echo "============================================================"
    echo "El repositorio local no esta actualizado con el remoto"
    echo "============================================================"
    
    # Salto de linea
    saltoLinea

    # Se muestra que tan desactualizado esta el repositorio local con el remoto
    git diff origin/$branch

    read -p "¿Desea actualizar el repositorio local con el remoto? (s/n): " option

    if [ $option == "s" ]; then
        git pull origin $branch

        echo "============================================================"
        echo "El repositorio local fue actualizado"
        echo "============================================================"
    else
        echo "============================================================"
        echo "El repositorio local no fue actualizado"
        echo "============================================================"
    fi
fi

# Salto de linea
saltoLinea

# Se pregunta si se desea verificar el estado del repositorio local
read -p "¿Desea verificar el estado del repositorio local? (s/n): " option

if [ $option == "s" ]; then
    git status

    # Salto de linea
    saltoLinea

    # Variable con el estado del repositorio local
    status=$(git status --porcelain)

    # Verificar si hay cambios en el repositorio local
    if [ "$(git status --porcelain)" ]; then
        echo "============================================================"
        echo "El repositorio local tiene los siguientes cambios:"
        echo "============================================================"

        # Mostramos los cambios en el repositorio local
        while read -r line; do
            echo "$line"
        done <<< "$status"

        # Salto de linea
        saltoLinea

        # Se pregunta si se desea agregar los cambios al repositorio local
        read -p "¿Desea agregar los cambios al repositorio local y hacer un commit? (s/n): " option

        if [ $option == "s" ]; then
            read -p "Ingrese el mensaje del commit: " message

            git add .

            git commit -m "$message"

            # Salto de linea
            saltoLinea

            echo "============================================================"
            echo "Los cambios fueron agregados al repositorio local"
            echo "============================================================"

            # Salto de linea
            saltoLinea

            # Se pregunta si se desea subir los cambios al repositorio remoto
            read -p "¿Desea subir los cambios al repositorio remoto? (s/n): " option

            if [ $option == "s" ]; then
                git push origin $branch

                # Salto de linea
                saltoLinea

                echo "============================================================"
                echo "Los cambios fueron subidos al repositorio remoto"
                echo "============================================================"
            else
                # Salto de linea
                saltoLinea

                echo "============================================================"
                echo "Los cambios no fueron subidos al repositorio remoto"
                echo "============================================================"
            fi
        else
            # Salto de linea
            saltoLinea

            echo "============================================================"
            echo "Los cambios no fueron agregados al repositorio local"
            echo "============================================================"
        fi       
    fi
else
    echo "============================================================"
    echo "El estado del repositorio local no fue verificado"
    echo "============================================================"
fi

# Terminar script
exit 0