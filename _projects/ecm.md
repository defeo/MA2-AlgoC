---
layout: project
title: Modèles rationnels pour ECM et EECM
keywords: [courbes elliptiques, factorisation]
---

Le but de ce projet est d'analyser des variantes de l'algorithme de
factorisation ECM.


## Résumé

L'algorithme de factorisation ECM a été initialement proposé par
H. Lenstra en 1985. Des nombreuses variantes et optimisations ont par
la suite été proposées, notamment par Suyama (1985), Brent (1986) et
Montgomery (1987, 1992).

Les ajouts les plus importants à l'algorithme original consistent en
la "phase 2", et en l'utilisation de courbes avec une grande torsion
rationnelle, et en l'optimisation de l'arithmétique des courbes.

La "phase 2" permet d'agrandir la borne de friabilité utilisée par
l'algorithme. La "phase 1" permet en effet de capturer toute courbe
qui aurait un cardinal composé de premiers en dessous d'une borne
$$B_1$$, alors que la "phase 2" permet d'y ajouter toute courbe qui
aurait en plus un facteur plus grand, en dessous d'une borne
$$B_2>B_1$$.

L'utilisation de courbes spéciales sur $$ℚ$$ permet de forcer les
courbes à avoir une certaine structure de torsion modulo le facteurs à
trouver. Cette structure de torsion augmente à son tour la probabilité
que le cardinal de la courbe soit friable.

Outre le choix de courbes spécifiques, le choix de leur modèle est
aussi crucial. Traditionnellement, on utilise des courbes sous forme
de Montgomery, mais le modèle d'Edwards, introduit récemment par
Bernstein, Birkner, Lange et Peters, offre une alternative performante,
surtout pour la "phase 2".

Le but de ce projet est d'implanter quelques variantes de ECM, en
comparant différents choix pour les courbes et en analysant leur
efficacité et probabilité de succès.

Il est conseillé d'utiliser la bibliothèque
[Pari](http://pari.math.u-bordeaux.fr/) pour les sous-routines (par
ex.: test de primalité) et pour tester le code (par ex.: vérifier les
formules d'addition).

## Prérequis

- Familiarité avec les courbes elliptiques.

## Objectifs

- Implanter une version complète de ECM, comprenant une "phase 1" et
  une "phase 2".

- Implanter le plus d'améliorations possibles pour chaque étape. Le
  choix est vaste, l'étudiant sélectionnera les optimisations qui lui
  conviennent mieux.

- Utiliser plusieurs modèles de courbes : Montgomery, Suyama,
  Edwards. Comparer les statistiques de friabilité et l'efficacité
  globale du modèle.

## Références

- P. Zimmerman.
  [*20 years of ECM*](http://www.loria.fr/~zimmerma/papers/ecm-submitted.pdf).
- D. Bernstein, P. Birkner, T. Lange, C. Peters.
  [*ECM using Edwards curves*](http://eprint.iacr.org/2008/016.pdf).
- P. Montgomery.
  [*Speeding the Pollard and elliptic curve methods of factorization*](http://www.ams.org/journals/mcom/1987-48-177/S0025-5718-1987-0866113-7/S0025-5718-1987-0866113-7.pdf).
- A. Kruppa.
  [*Speeding up Integer Multiplication and Factorization*](https://tel.archives-ouvertes.fr/tel-00477005v2/document).
- R. Barbulescu, J. Bos, C. Bouvier, T. Kleinjung, P. Montgomery.
  [*Finding ECM-friendly curves through a study of Galois properties*](https://hal.inria.fr/hal-00671948/file/article.pdf)
- R. Barbulescu.
  [*Familles de courbes adaptées à la factorisation des entiers*](https://hal.inria.fr/inria-00419218/file/Familles_version2.pdf).
