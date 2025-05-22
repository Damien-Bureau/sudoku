# Sudoku

## Game generation algorithm

```
pour chaque case :
    tant qu'il y a des chiffres dispos (impossibleDigits.size() < 9):
        vérifier si on peut placer un chiffre (est-il dans impossibleDigits ?)
            si oui : placer le chiffre
            si non : ajouter à impossibleDigits
    si chiffre non placé (impossibleDigits.size() == 9):
        reset la case actuelle
        reset la case précédente
        se déplacer à la case précédente
```