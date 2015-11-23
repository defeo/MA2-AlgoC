---
layout: project
title: Logarithme discret en petite charactéristique
keywords: [corps finis, logarithme discret]
plugins: mathjax
---

Le but de ce projet est d'implanter l'algorithme de calcul de
logarithme discret dans $$\mathbb{F}_{p^n}^\ast$$ en temps
quasi-polynomial de Barbulescu-Gaudry-Joux-Thomé.

# Résumé

La difficulté du problème du logarithme discret est à la base de
nombreux systèmes cryptographiques. Notamment, l'échange de clef de
Diffie-Hellman, le chiffrement d'El Gamal, et le standard de signature
DSA sont tous basé sur le problème du logarithme discret dans un corps
fini $$\mathbb{Z}/p\mathbb{Z}$$.

En plus des algorithmes génériques de complexité exponentielle (Baby
step–Giant step, Pollard), on connaît depuis les années '70 des
algorithmes sous-exponentiels de calcul du logarithme discret dans
$$\mathbb{F}_q$$. Jusqu'en 2012, les meilleurs algorithmes connus
étaient le *crible du corps de nombres* (NFS) pour les corps premiers,
et le *crible du corps de fonctions* (FFS) pour les corps de
caractéristique fixée, les deux avec une complexité heuristique en
$$L(1/3)$$.

En 2012, plusieurs travaux indépendants ont apporté des améliorations
pratiques importantes au problème du logarithme discret en petite
caractéristique. L'historique est résumé dans
[cette page Wikipedia](https://en.wikipedia.org/wiki/Discrete_logarithm_records).
Ces travaux ont permis d'aboutir au premier algorithme de logarithme
discret pour $\mathbb{F}_{p^n}$ en *temps quasi-polynomial* (c'est à
dire en $$n^{O(\log n)}$$).  Cette thématique de recherche continue
encore aujourd'hui à donner des résultats remarquables.

Le but de ce projet est d'implanter l'algorithme de
Barbulescu-Gaudry-Joux-Thomé, le premier algorithme quasi-polynomial
de calcul de logarithme discret dans un corps fini.

Pour réaliser l'algorithme il est nécessaire de disposer d'une
arithmétique sur les polynômes à coefficients dans $$\F_p$$.  Cela
peut être codé par l'étudiant, de façon naïve, ou bien récupéré dans
une bibliothèque de calcul algébrique comme [Flint](http://www.flintlib.org/).

# Prérequis

- Connaissances de base sur les corps finis.

# Objectifs

- Implanter l'algorithme BGJT.

- Comparer ses performances avec un algorithme naïf (BSGS ou Pollard).


# Références

- R. Barbulescu, P. Gaudry, A. Joux, E. Thomé.
  [*A quasi-polynomial algorithm for discrete logarithm in finite fields of small characteristic*](https://eprint.iacr.org/2013/400.pdf)
- W. Hart, F. Johansson, S. Pancratz.
  [*The FLINT manual*](http://www.flintlib.org/flint-2.5.pdf).
