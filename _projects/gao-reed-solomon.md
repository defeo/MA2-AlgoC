---
layout: project
title: Décodage de codes de Reed-Solomon par l'algorithme de Gao
keywords: [codes, Reed-Solomon, corps finis, polynômes, FFT]
plugins: mathjax
---

Le but de ce projet est d'implanter l'algorithme de Gao pour le
décodage des codes de Reed-Solomon.

# Résumé

# Prérequis

- Connaissances de base sur les corps finis et les codes.

# Objectifs

- Implanter l'arithmétique des polynômes à coefficients dans $$\mathbb{F}_p$$
  (addition, multiplication, division euclidéenne, xgcd, interpolation)

- Implanter l'algorithme de Gao pour des Reed-Solomon sur un corps
  premier

- Revenir sur l'arithmétique de $$\mathbb{F}_p[X]$$ en implantant la
  FFT pour certains premiers p spéciaux, comme décrit dans le papier.

- Faire des tests de performances.


# Références

- S. Gao.
  [*A new algorithm for decoding Reed-Solomon codes*](http://www.math.clemson.edu/~sgao/papers/RS.pdf)
- A. Rudra. [*Error Correcting Codes: Combinatorics, Algorithms and Applications*](http://www.cse.buffalo.edu/~atri/courses/coding-theory/fall07.html).
- J.-G. Dumas. *Théorie des codes : compression, cryptage, correction*. Côte BU: 005.82 THE.
- B. Martin. *Codage, cryptologie et applications*. Côte BU: 005.82 MAR.
- R. Lidl. *Finite fields*. (chapitres 9 et 10 sur les codes).
- R. Lidl, H. Niederreiter. *Introduction to Finite fields and their
  applications* (chapitre 8).
- J. von zur Gathen, J. Gerhard. [*Modern computer Algebra*](http://www.cambridge.org/us/academic/subjects/computer-science/algorithmics-complexity-computer-algebra-and-computational-g/modern-computer-algebra-3rd-edition).
- A. Bostan, F. Chyzak, M. Giusti, R. Lebreton, G. Lecerf, B. Salvy,
  É. Schost.
  [*Algorithmes Efficaces en Calcul Formel*](http://perso.ens-lyon.fr/bruno.salvy/mpri/poly.pdf).
- S. Fedorenko.
  [*A simple algorithm for decoding Reed-Solomon codes and its relation to the Welch-Berlekamp algorithm*](http://pdf.aminer.org/001/105/526/a_simple_algorithm_for_decoding_reed_solomon_codes_and_its.pdf).
