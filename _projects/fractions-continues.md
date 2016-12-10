---
layout: project
title: Arithmétique des fractions continues
keywords: [Gosper, fractions continues, rationnels, approximation, multi-précision]
plugins: mathjax
---

Le but de ce projet est d'implanter des algorithmes pour les calculs
avec les *fractions continues*.

# Résumé

La représentation des nombres réels par fractions continues, à
laquelle Euler avait déjà consacré un ouvrage entier, est un sujet
classique en mathématiques, à l'origine de nombreux théorèmes
remarquables. L'utilisation des fractions continues en informatique a
été suggérée à plusieurs reprises. Au delà de l'intérêt mathématique,
les avantages perçus d'une telle représentation sont une meilleure
analyse de l'erreur, et une représentation unique des nombres.

Gosper a été l'un des plus fervents avocats de l'utilisation des
fractions continues en informatique. Il est l'inventeur de plusieurs
algorithmes, non publiés, de calcul arithmétique et algébrique sur la
représentation en fractions continues.

Le but de ce projet est d'implanter les conversions entre nombres
flottants multi-précision et fractions continues, ainsi que les
algorithmes de Gosper pour les opérations arithmétiques. Il est
conseillé d'utiliser la bibliothèque GMP pour la représentation des
entiers et des flottants multi-précision.

# Objectifs

- Lire et comprendre les différentes définitions de fractions
  continues, donner une exposition formelle des algorithmes de Gosper
  pour les transformations homographiques et bi-homographiques.

- Implanter les conversions entre nombres flottants et fractions
continues.

- Implanter l'algorithme de Gosper pour les transformations
homographiques.

- Implanter l'algorithme de Gosper pour les transformations
bi-homographiques.

# Références

- <http://www.plover.com/~mjd/cftalk/>
- <http://perl.plover.com/yak/cftalk/INFO/gosper.txt>.
- <http://www.inwap.com/pdp10/hbaker/hakmem/cf.html>.
- <https://hal.inria.fr/file/index/docid/75792/filename/RR-0760.pdf>.
- D. E. Knuth, *The Art of Computer Programming, vol. 2. Seminumerical
  Algorithms*. Addison Wesley, 1981. Côtes BU 005.1 KNU, 004.1 KNU.
