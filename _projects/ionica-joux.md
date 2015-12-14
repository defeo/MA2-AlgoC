---
layout: project
title: Pairing the volcano
keywords: [courbes elliptiques, couplages, isogénies]
plugins: mathjax
---

Le but de ce projet est l'implantation des algorithmes présentés dans
le papier *Pairing the volcano*, de S. Ionica et
A. Joux.

## Résumé

Les *isogénies* sont les morphismes non constants de courbes
elliptiques. Ce sont des morphismes de groupe, ainsi que des
morphismes de variétés algébriques.

Les isogénies d'une courbe $$E$$ vers elle même sont appelées des
*endomorphismes*. L'exemple le plus simple d'endomorphisme est la
multiplication par un scalaire $$n∈ℤ$$. L'endomorphisme de Frobenius
d'une courbe définie sur un corps fini est un autre exemple. Le
théorème de l'isogénie duale dit que pour toute isogénie $$φ:E→E'$$ de
degré $$n$$ il existe une isogénie $$\hat{φ}:E'→E$$, dite la duale de
$$φ$$, telle que $$φ∘\hat{φ}$$ est la multiplication par $$n$$ de
$$E$$.

Lorsqu'on étudie les courbes sur les corps finis, il est classique de
s'intéresser aux *graphes d'isogénies*, c'est à dire les graphes dont
les sommets sont les courbes elliptiques à isomorphisme près, et les
arêtes sont les isogénies. Pour des courbes *ordinaires* et un degré
$$ℓ$$ premier fixé, ces graphes sont appelés *volcans d'isogénies*. Ce
sont des graphes non orientés, où tous les sommets ont degré $$ℓ+1$$
ou $$1$$. Leur structure *par niveaux* est fortement reliée à la
structure des anneaux d'endomorphismes des courbes. Au sein d'un
volcan on classifie les isogénies en *horizontales*, *descendentes* ou
*ascendantes*.

Un problème classique dans l'étude des volcans est le suivant: étant
donnée une courbe elliptique $$E$$ est un degré $$ℓ$$, déterminer le
niveau de $$E$$ dans le volcan, et classifier les isogénies en
descendantes, ascendantes et montantes.

Le papier étudié dans ce projet utilise les propriétés des
*auto-couplages* afin de déterminer les types des isogénies pour une
courbe donnée.

Le projet est à développer en langage C, à l'aide de la bibliothèque
[Pari](http://pari.math.u-bordeaux.fr/).

## Prérequis

- Familiarité avec les courbes elliptiques.

- Une connaissance préalable d'au moins un concept parmi couplage et
  isogénie est recommandée.

## Objectifs

- Comprendre et être capable d'exposer les notions d'isogénie, anneau
  d'endomorphismes, couplage, graphe d'isogénie, ordre dans un corps
  quadratique imaginaire.

- Familiarisation avec la bibliothèque de théorie des nombres Pari.

- Implanter les algorithmes 1 et 2 du papier *Pairing the Volcano*.

## Références

- S. Ionica, A. Joux, [*Pairing the Volcano*](http://arxiv.org/pdf/1110.3602.pdf).
- S. Ionica,
  [*Algorithmique des couplages et cryptographie*](http://www.lix.polytechnique.fr/~ionica/thesis.pdf).
- V. Vitse,
[*Couplages sur courbes elliptiques définies sur des corps finis*](http://www-fourier.ujf-grenoble.fr/~viva/research/articles/thesis.pdf).
- M. Fouquet.
  [Anneau d'endomorphismes et cardinalité de courbes elliptiques : aspects algorithmiques](http://www.lix.polytechnique.fr/Labo/Mireille.Fouquet/Manuscrit.ps.gz)
- J. Silverman, *The arithmetic of elliptic curves*.
- Blake, Seroussi, Smart, *Elliptic curves in cryptography*.
- J.S. Milne,
  [*Elliptic curves*](http://www.jmilne.org/math/Books/ectext5.pdf).
