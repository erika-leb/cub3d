#!/bin/bash

# Dossier où se trouvent les fichiers
DIR="maps/good"

# Parcourt tous les fichiers .cub dans le dossier
for file in "$DIR"/*.cub; do
    echo "Traitement de $file"
    # Utilise sed pour supprimer les \r en place
    sed -i 's/\r$//' "$file"
done

echo "Tous les fichiers ont été corrigés !"
