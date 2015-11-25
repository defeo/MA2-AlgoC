---
layout: project
title: Factorisation par la méthode du groupe des classes
keywords: [entiers, multi-précision, factorisation, formes quadratiques]
plugins: mathjax
---

Le but de ce projet est d'implanter la méthode du groupe des classes
de Lenstra-Schnorr pour la factorisation d'entiers.

# Résumé

Il est conseillé d'utiliser la bibliothèque GMP.

# Objectifs

- Implanter l'algorithme NUCOMP de composition de formes quadratiques.

- Implanter la méthode de Lenstra-Schnorr, comprenant une "phase 1" et
  une "phase 2".

- Évaluer les performances et déterminer les bornes optimales.

# Prérequis

- Notions de théorie des nombres: corps de nombres, idéaux
  fractionnaires, formes quadratiques, groupe des classes.

# Références

- A. J. van der Poorten.
  [*A note on NUCOMP*](http://www.ams.org/journals/mcom/2003-72-244/S0025-5718-03-01518-7/S0025-5718-03-01518-7.pdf).
- C. P. Schnorr, H. W. Lenstra.
  [*A Monte Carlo factoring algorithm with linear storage*](http://www.ams.org/journals/mcom/1984-43-167/S0025-5718-1984-0744939-5/S0025-5718-1984-0744939-5.pdf).
- H. Cohen.  *A course in computation algebraic number theory*,
  chapitres 5 et 10.
