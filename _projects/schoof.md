---
layout: project
title: Algorithme de comptage de points de Schoof
keywords: [courbes elliptiques, comptage de points]
plugins: mathjax
---

Le but de ce projet est d'implanter l'algorithme de comptage de points
de courbes elliptiques de Schoof.


## Résumé

Déterminer le cardinal d'une courbe elliptique définie sur un corps
fini est un problème classique en théorie des nombres. Si $$E$$ est
une courbe définie sur un corps fini à $$q$$ éléments, Le théorème de
Hasse dit que $$\#E = q+1-t$$, avec $$|t|≤2\sqrt{q}$$, où $$t$$ est la
*trace de l'endomorphisme de Frobenius* de $$E$$.

Le méthodes générales de calcul d'ordre de groupes sont toutes de
complexité exponentielle, et ceci à longtemps été le cas aussi pour
les courbes elliptiques, pour lesquelles la meilleure méthode connue
était l'algorithme de Shanks-Mestre, de complexité $$O(q^{1/4})$$.
L'utilisation des courbes elliptiques en cryptographie a motivé la
recherche d'algorithmes plus efficaces pour ce problème.

Le premier algorithme de comptage de points de complexité polynomiale
est dû à Schoof. Il s'agit d'un algorithme *multi-modulaire*, qui
calcule la valeur de la trace $$t$$ modulo plein de petits nombres
premiers, et ensuite reconstruit la valeur de $$t$$ par restes
chinois. La complexité de l'algorithme de Schoof a été par la suite
améliorée par Atkin et Elkies, donnant un algorithme connu aujourd'hui
sous le nom SEA.

Le but de ce projet est d'implanter l'algorithme original de Schoof
pour des courbes définies sur des corps premiers. Les améliorations
d'Atkin et Elkies ne seront pas étudiées ici.  Il est conseillé
d'utiliser la bibliothèque C de calcul formel
[Flint](http://www.flintlib.org/) pour réaliser le projet.


## Prérequis

- Familiarité avec les courbes elliptiques.

## Objectifs

- Comprendre et être capable de présenter les principes de
  l'algorithme de Schoof.

- Implanter l'algorithme de Schoof par un programme C qui prend en
  entrée un premier $$p$$ et les coefficients $$a$$ et $$b$$
  définissant une équation de Weierstrass, et qui donne en sortie le
  nombre de points de la courbe $$y^2=x^3+ax+b$$ sur $$𝔽_p$$.

## Références

- R. Schoof.
  [*Elliptic curves over finite fields and the computation of square roots mod p*](http://www.ams.org/journals/mcom/1985-44-170/S0025-5718-1985-0777280-6/S0025-5718-1985-0777280-6.pdf).
  Mathematics of computation 44.170 (1985):483-494.

- R. Crandall, C. Pomerance. *Prime numbers: a computational
  perspective*. Vol. 182. Springer Science & Business
  Media, 2006. Côte 512.7 CRA. §7.5.2.

- I. F. Blake, G. Seroussi, N. Smart. *Elliptic curves in
  cryptography*. Vol. 265. Cambridge university press, 1999. Côte
  005.82 BLA. Chapitre VII.
