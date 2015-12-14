---
layout: project
title: Modèles de courbes elliptiques
keywords: [courbes elliptiques]
plugins: mathjax
---

Le but de ce projet est d'implanter différents modèles de courbes
elliptiques et de comparer leurs performances.

# Résumé

Les courbes elliptiques sont traditionnellement présentées comme les
lieux d'annulation d'une *équation courte de Weierstrass projective*
$$Y^2Z = X^3 + aXZ^2 + bZ^3$$. Cette représentation a une importance
historique, et joue un rôle central dans la théorie des courbes
elliptiques sur $$ℂ$$, ce qui suffit à justifier son utilisation
presque universelle.

Cependant, lorsque on a pour objectif de faire une implantation
cryptographique la plus rapide possible, d'autres représentations des
courbes elliptiques se révèlent plus efficaces. C'est le cas des
modèles d'Edwards, de Jacobi, de Huff, ou encore du modèle Hessian.

En plus du choix du modèle, l'implantation de la multiplication
scalaire est sensible à d'autres paramètres, comme la représentation
du plan projectif, ou encore l'algorithme de *double-and-add* choisi.

Ce projet a pour but d'implanter différentes représentations de
courbes elliptiques sur des corps premiers, et de comparer leurs
performances. Il est conseillé d'utiliser la bibliothèque GMP pour la
représentation des grands entiers modulaires.

En bonus, on pourra s'intéresser à l'implantation de la courbe Ed25519
à partir des primitives pour les entiers en virgule flottante, sans
avoir recours à une bibliothèque de grands entiers.


# Objectifs

- Implanter le modèle de Weierstrass projectif, affine et Jacobian.

- Implanter le modèle d'Edwards projectif et inversé.

- Implanter le modèle des quartiques de Jacobi projectif.

- Implanter le modèle des intersections de Jacobi projectif.

- Implanter le modèle de Montgomery et la multiplication par échelle.

- Comparer les performances des implantations.

- Essayer d'approcher le mieux possible le record d'implantation de la
  courbe Ed25519 en utilisant de l'arithmétique flottante.


# Prérequis

- Notions de base sur les courbes elliptiques

# Références

- The [Explicit-Formulas Database](http://www.hyperelliptic.org/EFD/index.html).

- D. J. Bernstein, T. Lange.
  [*Analysis and optimization of elliptic-curve single-scalar multiplication*](http://www.hyperelliptic.org/EFD/precomp.pdf).

- D. J. Bernstein, P. Birkner, M. Joye, T. Lange, C. Peters.
  [*Twisted Edwards Curves*](http://cr.yp.to/newelliptic/twisted-20080313.pdf).

- P. L. Montgomery.
  [*Speeding the Pollard and Elliptic Curve Methods of Factorization*](http://www.ams.org/journals/mcom/1987-48-177/S0025-5718-1987-0866113-7/S0025-5718-1987-0866113-7.pdf).

- D. J. Bernstein.
  [*Curve25519: new Diffie-Hellman speed records*](http://cr.yp.to/ecdh/curve25519-20060209.pdf).

