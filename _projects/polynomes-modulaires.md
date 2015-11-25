---
layout: project
title: Division de polynômes et inversion dans les corps finis
keywords: [polynômes, division euclidéenne, inversion, corps finis]
plugins: mathjax
---

Le but de ce projet est d'implanter des méthodes asymptotiquement
rapides d'inversion de séries et de division de polynômes à
coefficients dans $$\mathbb{F}_p$$. Au dessus de ces routines, il sera
possible de construire une bibliothèque de calculs dans les corps
finis.


# Résumé

L'utilisation de la bibliothèque Flint pour la multiplication de
polynômes à coefficients dans $$\mathbb{F}_p$$ est conseillée.

# Objectifs

- Implanter l'itération de Newton pour l'inversion de séries.

- Implanter l'algorithme de Newton-Raphson pour la division de
  polynômes.

- Implanter le pgcd de polynômes.

- Implanter les fonctions de base pour calculer dans
  $$\mathbb{F}_{p^n}$$.  Comparer avec les performances d'une
  bibliothèque de calcul dans les corps finis, comme par exemple
  Flint.

# Prérequis

- Connaissances de base sur les corps finis.

# Références

- A. Bostan, F. Chyzak, M. Giusti, R. Lebreton, G. Lecerf, B. Salvy,
  É. Schost.
  [*Algorithmes Efficaces en Calcul Formel*](http://perso.ens-lyon.fr/bruno.salvy/mpri/poly.pdf),
  chapitre 4.

- <https://en.wikipedia.org/wiki/Division_algorithm#Newton.E2.80.93Raphson_division>
