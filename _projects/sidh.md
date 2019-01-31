---
layout: project
title: Échange de clefs dans les graphes d'isogénies supersingulières
keywords: [courbes elliptiques, isogénies, multi-précision]
plugins: mathjax
---

Le but de ce projet est d'implanter le protocôle d'échange de clefs
[SIDH (Supersingular Isogeny
Diffie-Hellman)](https://en.wikipedia.org/wiki/Supersingular_isogeny_key_exchange),
dans des graphes d'isogénies supersingulières de degré arbitraire.

# Résumé

Parmi les plus jeunes des protocoles post-quantiques, SIDH est un
échange de clef dont la sécurité repose sur la difficulté de trouver
des chemins dans de très grands graphes d'isogénies entre courbes
elliptiques supersingulières.  Initialement proposé en 2011, il fait
l'objet en 2017 d'une soumission à la compétition NIST pour la
standardisation de primitives post-quantiques.

Dans SIDH on fixe un nombre premier de la forme $$p=ℓ_1^aℓ_2^bf-1$$,
où $$ℓ_1$$ et $$ℓ_2$$ sont deux petits premiers distincts (typiquement
$$2$$ et $$3$$), et $$f$$ est un petit cofacteur (souvent égal à
$$1$$).  En supposant que $$4$$ divise $$p+1$$, on fixe la *courbe
initiale* $$E_0:y^2 = x^3 + x$$, le choix de $$p$$ garantit alors que
$$E_0$$ est supersingulière, d'ordre $$p+1$$ sur $$𝔽_p$$, et
$$(p+1)^2$$ sur $$𝔽_{p^2}$$.

La première phase de l'échange de clef consiste pour Alice à choisir
un point secret $$A$$ de $$E(𝔽_{p^2})$$ d'ordre $$ℓ_1^a$$, à calculer
l'isogénie de noyaux $$〈A〉$$, et à publier sa courbe image $$E_A$$.
Bob fait l'opération analogue avec les points de
$$ℓ_2^b$$-torsion. Dans la deuxième phase, Alice et Bob répètent leurs
calculs secret à partir des courbes publiques respectives, obtenant
ainsi la clef partagée.

La majorité des implantations de SIDH utilise $$2$$ et $$3$$ pour
$$ℓ_1$$ et $$ℓ_2$$. Il est néanmoins possible d'utiliser d'autres
nombres premiers et d'autres courbes de départ, avec potentiellement
des gains en efficacité. Le but de ce projet est d'implanter un
échange de clefs SIDH d'après l'état de l'art, ainsi que des
variations utilisant des degrés d'isogénies non conventionnels.

Le projet est à réaliser en C à l'aide d'une bibliothèque de grands
entiers, par exemple GMP.  Neanmoins du code externe dans d'autres
langages, par exemple Sage, peut être utilisé pour trouver des
paramètres $$p$$ et $$E_0$$ adaptés, ainsi que pour définir les
*stratégies de calcul*.

# Objectifs

- Lire et comprendre le fonctionnement de l'échange de clef.

- Implanter une version simple, utilisant $$2$$ et $$3$$, sans
  *stratégies optimales*, telle que décrite par Costello, Longa et
  Naehrig.
  
- Implanter les *stratégies optimales*, telles que décrites par De
  Feo, Jao et Plût.
  
- Implanter des degré d'isogénies arbitraires en utilisant les
  formules de Costello-Hisil, ou les formules de De Feo-Jao-Plût.

- Sélectionner différents paramètres à niveau de sécurité constant et
  comparer les performances.

# Prérequis

Connaissances en courbes elliptiques.

# Références

- D. Jao et al. [*Supersingular Isogeny Key
  Encapsulation*](https://sike.org/files/SIDH-spec.pdf). NIST PQ
  Candidate. <https://sike.org/>.
- L. De Feo, D. Jao, J. Plût. [*Towards Quantum-Resistant
  Cryptosystems From Supersingular Elliptic Curve
  Isogenies*](https://eprint.iacr.org/2011/506.pdf).
- C. Costello, P. Longa, M. Naehrig.  [*Efficient algorithms for
  supersingular isogeny
  Diffie-Hellman*](https://eprint.iacr.org/2016/413.pdf).
- C. Costello, H. Hisil.  [*A simple and compact algorithm for SIDH
  with arbitrary degree
  isogenies*](https://eprint.iacr.org/2017/504.pdf).
- L. De Feo. [*Mathematics of Isogeny Based
  Cryptography*](https://arxiv.org/abs/1711.04062).
- J. Silverman, *The arithmetic of elliptic curves*.
- Blake, Seroussi, Smart, *Elliptic curves in cryptography*.
- J.S. Milne,
  [*Elliptic curves*](http://www.jmilne.org/math/Books/ectext5.pdf).
