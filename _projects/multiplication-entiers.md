---
layout: project
title: Multiplication d'entiers en temps quasi-linéaire
keywords: [FFT, multiplication, entiers, multi-précision]
plugins: mathjax
---

Le but de ce projet est de comparer différents algorithmes de
multiplication d'entiers asymptotiquement rapides.  On s'intéressera
principalement à la famille d'algorithmes de Toom-Cook, et à
l'algorithme en $$O(n\log n\log\log n)$$ de Schönage-Strassen.

# Résumé

# Objectifs

- Implanter les algorithmes de multiplication de Toom-Cook.

- Implanter l'algorithme de Schönage-Strassen.

- Comparer les implantation par des benchmarks, déterminer les points
  de seuil.

# Références

- R. Crandall, C. Pomerance.
  [*Prime numbers: a computational perspective*](http://viti2.bib.uvsq.fr/primo_library/libweb/action/display.do?tabs=detailsTab&ct=display&fn=search&doc=ALEPH_UVSQ000061677&indx=1&recIds=ALEPH_UVSQ000061677&recIdxs=0&elementId=&renderMode=poppedOut&displayMode=full&http://viti2.bib.uvsq.fr:80/primo_library/libweb/action/expand.do?dscnt=1&frbrVersion=&frbg=&scp.scps=scope%3A%28METALIB_UVSQ%29%2Cscope%3A%28ALEPH_UVSQ%29%2Cscope%3A%28SFX_UVSQ%29%2Cprimo_central_multiple_fe&tab=default_tab&dstmp=1448468848046&srt=rank&mode=Basic&gathStatTab=true&dum=true&tb=t&vl%28freeText0%29=crandall%20pomerance%20prime%20numbers&vid=DBIST&fromTabHeaderButtonPopout=true).

- P. Gaudry, A. Kruppa, P. Zimmermann.
  [*A GMP-based Implementation of Schönhage-Strassen’s Large Integer Multiplication Algorithm*](http://www.loria.fr/~gaudry/publis/issac07.pdf).
