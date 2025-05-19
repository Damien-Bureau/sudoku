# Sudoku

## Game generation algorithm

```
pour chaque square dans la board:
    pour chaque chiffre de 1 à 9:
        vérifier les emplacements interdits du chiffre
            → emplacements interdits par les lignes et colonnes
                → vérifier si frame.forbiddenDigits contient le chiffre actuel
            → emplacements interdits car il y a déjà un autre chiffre
                → vérifier si frame.digit n'est pas nul
        récupérer la liste/quantité d'emplacements possibles
        générer un nombre aléatoire entre 0 et cette quantité
        placer le chiffre selon le nombre généré aléatoirement
        appliquer une interdiction du chiffre sur la ligne et la colonne où le chiffre a été placé
```