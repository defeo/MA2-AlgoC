---
layout: project
title: Factorisation par la méthode du groupe des classes
keywords: [entiers, multi-précision, factorisation, formes quadratiques]
plugins: mathjax
---

Le but de ce projet est d'implanter la méthode du groupe des classes
de Lenstra-Schnorr pour la factorisation d'entiers.

# Résumé

La méthode de Lenstra-Schnorr est la première méthode de factorisation
en temps sous-exponentiel et en espace polynomial. Il s'agit d'une
généralisation de la méthode $$p-1$$ de Pollard, tout comme les
méthodes $$p+1$$ et ECM.

La méthode est basée sur l'observation que la détermination d'une
forme quadratique d'ordre $$2$$ dans le groupe des classes de
$$ℚ(\sqrt{-N})$$ donne une factorisation de $$N$$, non-triviale dans
la plus part des cas. La méthode essaye donc de déterminer le groupe
de classes de $$ℚ(\sqrt[-kN])$$ pour plusieurs entiers $$k$$, en
espérant de tomber sur un groupe de classes au cardinal friable.

Comme dans la méthode $$p-1$$, l'opération clef de la méthode consiste
à calculer une puissance d'un élément pris au hasard dans le groupe
des classes. Les algorithmes de composition de formes quadratiques
NUDUPL et NUCOMP sont ici les analogues des opérations de carré et de
multiplication dans $$ℤ/nℤ$$.

Comme dans les méthodes $$p-1$$ ou ECM, la méthode peut être optimisée
par une variante dite *des grands premiers*, qui ajoute une "phase 2",
permettant d'agrandir la borne de friabilité. La "phase 1" permet en
effet de capturer tout groupe de classes qui aurait un cardinal
composé de premiers en dessous d'une borne $$B_1$$, alors que la
"phase 2" permet d'y ajouter tout groupe de classes qui aurait en plus
un facteur plus grand, en dessous d'une borne $$B_2>B_1$$.

Il est conseillé d'utiliser la bibliothèque GMP pour la représentation
des entiers.

# Objectifs

- Implanter les algorithmes NUCOMP et NUDUPL de composition de formes
  quadratiques.

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
- H. Cohen.  [*A course in computation algebraic number theory*](http://link.springer.com/content/pdf/10.1007/978-3-662-02945-9.pdf),
  chapitres 5 et 10.
