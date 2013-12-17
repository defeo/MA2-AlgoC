---
layout: index
title: Algorithmique et programmation C
styles: ["http://yandex.st/highlightjs/7.5/styles/default.min.css"]
scripts: ["http://yandex.st/highlightjs/7.5/highlight.min.js",
          "js/local.js"]
---

# Algorithmique et programmation C

Notes de cours pour le cours *Algorithmique et programmation C* du
*Master d'algèbre appliquée*, par [Luca De Feo](http://defeo.lu).

## Compilation séparée, bibliothèques logicielles

### Fichiers objets, *linkage*

Lorsqu'un projet grandit, il devient important de le découper en
sous-modules. Ceci pour plusieurs raisons:

* Meilleure lisibilité du code,
* Collaboration plus aisée,
* Modularité et réutilisabilité du code,
* Compilation plus rapide (seuls les fichiers modifiés doivent être
  recompilés).

Le premier niveau de découpage se réalise au niveau du projet : à
chaque fichier source C (extension `.c`) correspond un fichier *objet*
(extension `.o`), contenant le code compilé.

Pour produire les fichiers objets, on compile avec l'option `-c`

	gcc -c A.c
	gcc -c B.c
	gcc -c C.c
	...

ou, plus simplement,

	gcc -c *.c

Cela produit un fichier `.o` pour chaque fichier `.c`. Ces fichiers ne
sont pas exécutables.

Ensuite on *lie* tous les fichiers objets, et les bibliothèques
éventuelles, dans un *exécutable*.

	gcc -lm -o monprogramme.exe *.o

Cette étape s'appelle *linking* en anglais, et la partie du
compilateur qui l'effectue s'appelle *linker*.

Lorsque tout le code est contenu dans un seul fichier, les étapes de
compilation et d'exécution peuvent être exécutées d'un seul coup,
comme déjà vu en cours.

	gcc -lm -o hello hello.c

**Note :** Lorsqu'on *linke* un programme exécutable, un et un seul
des fichiers objets doit contenir une fonction nommée `main`. C'est
cette fonction qui s'exécute lorsque on lance le programme compilé.


### Fichiers d'entête (*headers*)

Dans un langage compilé, avant de pouvoir compiler une fonction il est
nécessaire de connaître les *prototypes* de toutes les autres
fonctions desquelles elle dépend ; ceci afin de pouvoir réaliser le
contrôle de typage (*type checking*).

Pour cette raison en C, même lorsque tout le code est contenu dans un
seul fichier, il est souvent nécessaire de commencer par déclarer les
prototypes de toutes les fonctions qui seront définies, comme dans
l'exemple suivant.

	int f(int);
	int g(int);

	int f(int x) {
		...
	    return f(f(x));
	}

	int g(int y) {
		...
		return g(y);
	}

	void main() {
		...
	}


La même chose vaut pour la compilation séparée. Une fonction `f()`
dans un fichier `f.c`, avant de pouvoir appeler une fonction `g()`
dans un fichier `g.c`, doit en connaître le prototype.

Ceci crée un problème pour la compilation séparée : comment compiler
`f.c` sans avoir d'abord compilé `g.c`, et inversement ? Le langage C
résout ce problème grâce aux *fichiers d'entêtes* (*headers* en
anglais). Ces fichiers, utilisant l'extension `.h`, ne contiennent
habituellement que des prototypes de fonction et, éventuellement, des
macros pour le préprocesseur.

Les fichiers d'entête sont traités avant la compilation par le
préprocesseur : tout code ayant besoin de connaître les prototypes
d'un certain groupe de fonctions inclut les entêtes correspondantes à
l'aide de la macro

	#include "entete.h"

Par exemple, l'exemple précédent pourrait être découpé comme suit.

* Un fichier d'entête `my_module.h`, contenant tous les prototypes
  
	  int f(int);
	  int g(int);

* Un fichier `f.c`, contenant la définition de `f()`
  
	  #include "my_module.h"
	  
	  int f(int x) {
		  ...
	      return f(f(x));
	  }

* Un fichier `g.c`, contenant la définition de `g()`
  
	  #include "my_module.h"
	  
	  int g(int y) {
		  ...
		  return g(y);
	  }

* Un fichier `module.c` contenant le code du programme exécutable
  
	  #include "my_module.h"
	  
	  void main() {
		  ...
	  }

Ces fichiers seraient alors compilés par la suite de commandes

	gcc -c *.c
	gcc -o my_module *.o

Remarquez que les commandes ne font pas mention des fichiers `.h`. En
effet pendant la phase de compilation ces fichiers sont inclus
directement par le préprocesseur, tandis que pendant le linkage les
informations sur les types sont tout simplement ignorés.

**Note :** Dans des projets complexes, il arrive souvent que des
entêtes incluent d'autres entêtes. Il peut même arriver que plusieurs
entêtes s'incluent mutuellement. Pour éviter les boucles d'inclusion
infinies une technique souvent employée consiste à utiliser des
*macros conditionnelles*. Considérez les deux fichiers suivants.

	#ifndef entete1_h
	#define entete1_h

	#include "entete2.h"
	...

	#endif

<!-- -->

	#ifndef entete2_h
	#define entete2_h

	#include "entete1.h"
	...
	
	#endif

Un fichier pourra inclure `entete1.h` et/ou `entete2.h`, sans que cela
engendre d'erreur. Le manuel de gcc décrit cette astuce standard :
<http://gcc.gnu.org/onlinedocs/cpp/Once-Only-Headers.html#Once-Only-Headers>

### Bibliothèques

L'avantage principal de la compilation séparée est la modularité du
code, ce qui en facilite la réutilisation au sein de plusieurs
projets. Cependant, copier des dizaines de fichiers `.o` dans plein de
dossiers différents peut amener rapidement à des erreurs.

Une *bibliothèque* est, dans sa forme la plus simple, une collection
de fichiers objets, un peu comme un fichier `.zip`. On distingue deux
types de bibliothèques :

* Les bibliothèques *statiques* sont destinées à être *linkées* au
  moment de la compilation de l'exécutable. Le *linker* produit alors
  un programme exécutable contenant aussi le code objet de la
  bibliothèque. Ces bibliothèques utilisent normalement l'extension
  `.a`.

* Les bibliothèques *dynamiques* sont destinées à être *linkées* au
  moment de l'exécution du programme. Le *linker* n'inclue pas le code
  objet de la bibliothèque dans l'exécutable, mais seulement des
  pointeurs vers les fonctions à exécuter. C'est le système
  d'exploitation qui se charge, au moment de l'exécution, d'aller
  chercher le code objet dans la bibliothèque. Ces bibliothèques
  utilisent l'extension `.dll` (*dynamic-link library*) sous Windows
  et `.so` (*shared object*) sous Unix ; leur format dépend du système
  d'exploitation, ainsi une `.dll` ne pourra pas être utilisée dans un
  système Linux et inversement.

Les bibliothèques dynamiques permettent de créer des exécutables moins
volumineux, et de réduire l'occupation de mémoire en permettant à
plusieurs exécutables d'accéder à la même bibliothèque au même
emplacement. Ces avantages ont un coût : leur création est plus
complexe, et la gestion des dépendances peut créer des soucis
(*dependency hell*). De nos jours, pratiquement toutes les
bibliothèques sont dynamiques, les bibliothèques statiques présentant
un intérêt exclusivement pour des petits projets personnels.

La commande Unix utilisée pour créer une bibliothèque statique
s'appelle `ar` et s'utilise ainsi

	gcc -c *.c
	ar rcs libmylib.a *.o

Pour créer un objet `.so` sous Unix, il faut tout d'abord compiler les
fichiers sources avec l'option `-fpic` (ou `-fPic`), et ensuite créer
la bibliothèque avec `-shared`.

	gcc -fpic -c *.c
	gcc -shared -o libmylib.so *.o

Dans un cas comme dans l'autre, un exécutable peut linker la
bibliothèque `libmylib.a` ou `libmylib.so` grâce à l'option `-l`
(attention, l'ordre des options est important !)

	gcc -o hello hello.o -lmylib

**Note :** Si la bibliothèque a été crée dans le dossier courant, il
faudra très probablement ajouter l'option `-L` pour indiquer au
compilateur où trouver le fichier :

	gcc -o hello hello.o -L. -lmylib

En plus, si la bibliothèque est dynamique, il faudra aussi instruire
le *linker* de système, à travers la variable `LD_LIBRARY_PATH`. Voir
la section suivante.

**Note :** La création de bibliothèques dynamiques compatibles avec
différents systèmes d'exploitation est une opération complexe, pour
laquelle il existe de nombreux outils qui visent à simplifier et
automatiser la tâche, le plus populaire étant *libtool*.

**Note :** On oublie souvent qu'une bibliothèque C est constituée de
*deux* composants : un code objet, contenu dans un fichier `.a` (ou
`.so`, ou `.dll`), et des entêtes, contenues dans des fichiers
`.h`. Les entêtes sont nécessaires uniquement au moment de la
compilation, alors que le code objet est nécessaire uniquement au
moment du *linkage* (qui peut advenir statiquement ou
dynamiquement).

Ceci est reflété dans les systèmes de gestion de paquets, tels les
gestionnaires de paquets des distributions Linux. Sous Debian (et
Ubuntu), chaque bibliothèque est divisée en un paquet contenant le
code objet, et un autre contenant les entêtes, ces derniers étant
toujours distingués par leur terminaison en `-dev`. Par exemple un
utilisateur qui voudrait simplement installer des logiciels dépendant
de la bibliothèque GMP n'aurait qu'à installer le paquet `libgmp10`,
alors qu'un développeur souhaitant développer un logiciel basé sur
cette bibliothèque devrait aussi installer `libgmp-dev`.

Contrairement aux formats `.a`, `.so`, `.dll`, il n'existe pas de
format permettant de regrouper plusieurs fichiers d'entête ; il n'est
cependant pas difficile de produire, si on le souhaite, un fichier
d'entête unique à l'aide du préprocesseur.


### Les chemins de recherche

Après avoir créé une bibliothèque, il est naturel de vouloir la mettre
à un endroit dans le système de fichiers où d'autres programmes
pourront la trouver.

À ce fin, les compilateurs configurent quelques chemins standard pour
placer les entêtes et les bibliothèques communes à tout le système.

Sous Unix, gcc cherche les entêtes dans ces dossiers (entre autres) :

* `/usr/include`,
* `/usr/local/include`.

En plus, les entêtes incluses avec

	#include "entete.h"

sont aussi recherchées dans le même dossier que le fichier source qui
demande l'inclusion. D'autres chemins peuvent être ajoutés avec
l'option `-I`. Pour plus de détails, voir la doc officielle
<http://gcc.gnu.org/onlinedocs/cpp/Search-Path.html>.

Toujours sous Unix, les bibliothèques sont recherchées dans ces
dossiers (entre autres) :

* `/lib/`,
* `/usr/lib/`,
* `/usr/local/lib/`.

L'option `-L` de gcc permet d'ajouter d'autres chemins, mais
attention : cette option n'a une utilité que avec les bibliothèques
statiques ; en effet les bibliothèques dynamiques sont *linkées* par
le système et pas par gcc. La variable d'environnement `LIBRARY_PATH`
a le même effet que `-L` pour gcc.

Enfin, la variable d'environnement `LD_LIBRARY_PATH` permet d'indiquer
au système d'autres chemins où trouver les bibliothèques dynamiques.


### Exercices

1. Considérez le code suivant
   
	   int e(unsigned int x) {
		   if (!x) return 1;
		   else return o(x-1);
	   }
	   
	   int o(unsigned int x) {
		   if (!x) return 0;
		   else return e(x-1);
	   }
	   
	   void main(int argc) {
		   printf("%d\n", e(argc));
	   }

	Complétez ce code et découpez-le d'au moins deux façons
    différentes en plusieurs fichiers `.c` et `.h`. Vérifiez qu'il
    compile et qu'il s'exécute sans erreurs.
	
2. Si ce n'est pas déjà fait, découpez le code du point précédent en
   trois fichiers source avec une fonction par fichier. Créez une
   bibliothèque statique contenant les deux fonctions `e()` et
   `o()`. Enfin, créez l'exécutable en *linkant* la bibliothèque.

3. Même question qu'auparavant, mais avec une bibliothèque dynamique.
    
4. Au cours des TDs précédents, vous avez codé un certain nombre de
   fonctionnalités pour les corps finis binaires. Faites-en une
   bibliothèque dynamique, et testez le résultat en produisant des
   exécutables.




## La bibliothèque de grands entiers GMP

GMP (Gnu Multiple Precision arithmetic library) <https://gmplib.org/>
est une bibliothèque C de grands entiers très populaire dans le milieu
du calcul exact. Elle est réputée pour sa robustesse et sa rapidité,
mais aussi pour ses faibles performances sous Windows.

Sa documentation est très compacte et facile à lire, elle se trouve à
l'adresse <https://gmplib.org/manual/>. En particulier, il est
impératif de lire l'intégralité du chapitre
<https://gmplib.org/manual/GMP-Basics.html#GMP-Basics>. Le chapitre
<https://gmplib.org/manual/Algorithms.html#Algorithms> est aussi très
intéressant.

Pour résumer, GMP fournit les types suivants :

* `mpz_t` : le type des entiers (exacts),
* `mpq_t` : le type des rationnels (exacts),
* `mpf_t` : le type des flottants (multi-précision).

De façon analogue, il y a plusieurs familles de fonctions :

* les fonctions commençant par `mpz_` agissent sur les entiers ;
* les fonctions commençant par `mpq_` agissent sur les rationnels ;
* les fonctions commençant par `mpf_` agissent sur les flottants ;
* les fonctions commençant par `mpn_` sont des fonctions de bas
  niveau, utiles pour optimiser au maximum ;
* quelques fonctions qui n'appartiennent à aucune des familles
  ci-dessus.

Les types `mpz_t`, ... ne sont que des pointeurs. Les vraies données
sont contenues dans des `struct` allouées dynamiquement. Pour cette
raison, toute variable doit être initialisée avec la fonction
appropriée avant d'être utilisée, et terminée lorsque elle n'est plus
nécessaire. Pour la même raison, les fonctions arithmétiques sont
généralement de type `void`, en effet la valeur de retour est passée
par référence dans le(s) premier(s) argument(s) : la fonction
`mpz_mul(a,b,c)` met dans `a` le résultat de `b*c`.

Par exemple, pour le type `mpz_t`, on fera

	mpz_t x;
	mpz_init(x);
	mpz_set_str(x, "12345", 10);  # met 12345 (lu en base 10) dans x
	mpz_mul(x, x, x);
	gmp_printf("%Zd\n", x);
	mpz_clear(x);

Les fonctions sur les entiers sont documentées ici :
<https://gmplib.org/manual/Integer-Functions.html#Integer-Functions>. Ce
sont essentiellement les seules fonctions dont on aura besoin dans ce
cours.


### Exercices

Nous allons commencer par installer GMP, *from scratch*.

1. Téléchargez la dernière version de GMP ici :
   <http://bourbaki.math.uvsq.fr/~defeo/gmp-5.1.3.tar.bz2> (ou ici
   <https://gmplib.org/#DOWNLOAD>), et décompressez-la avec la
   commande `tar xf`.

2. Lisez le fichier `INSTALL`. Il vous dit que GMP se compile et
   s'installe comme la majorité des bibliothèques GNU :
   
	   ./configure
	   make
	   make install

	Cependant, vous n'avez pas les droits de super-utilisateur sur
    bourbaki, du coup vous ne pourrez pas faire `make install`. Pour
    contourner ce problème, nous allons installer GMP dans notre
    espace d'utilisateur : passez l'option `--prefix=$HOME` à
    `./configure`, ensuite procédez comme décrit dans le fichier
    `INSTALL`. Faites pareil même si vous travaillez sur votre propre
    machine : on fera plus simple par la suite.

	Lorsque vous aurez réussi, vous aurez un dossier `lib`, un dossier
    `include` et un dossier `share` dans votre répertoire
    utilisateur. Ils contiennent respectivement le code objet,
    l'entête, et la documentation de GMP.

3. La suite de Fibonacci est définie par une récurrence linéaire, qui
   peut être représentée sous forme matricielle par

	$$\begin{pmatrix}f_{n}\\f_{n+1}\end{pmatrix} = \begin{pmatrix} 0 & 1\\ 1 & 1\end{pmatrix} \begin{pmatrix}f_{n-1}\\f_n\end{pmatrix}.$$

	Écrire un programme qui prend en entrée $$n$$ et qui affiche le
    $$n$$-ième nombre de Fibonacci. Le programme doit utiliser
    seulement $$O(\log n)$$ additions et multiplications.

    Vous trouverez ici une
	[soultion]({{site.github_base}}/sources/fibonacci.c). Elle
	pourrait être améliorée, mais ses performances ne sont pas tout à
	fait ridicules (par comparaison, la fonction `fibo` de Pari/gp est
	environ six fois plus rapide). On a choisi d'utiliser le format
	`long` pour le paramètre $$n$$, en effet les tests montrent qu'il
	est possible de calculer $$f_n$$ en quelques secondes pour
	$$n\sim2^{25}$$.

Pour taper des commandes plus courtes, dans la suite nous allons
utiliser la version de GMP installée par défaut par le système. Elle
est déjà présente sur bourbaki, il suffit d'ajouter `-lgmp` à la phase
de linkage. Pour installer GMP sur votre Ubuntu, utilisez la commande

	sudo apt-get install libgmp3-dev


## Factorisation d'entiers

Dans la suite $$N$$ est un entier composé et $$p$$ est l'un de ses
facteurs.

Les algorithmes présentés ci-dessous sont basés sur le théorème des
restes chinois qui donne une décomposition

$$ℤ/Nℤ ≃ \bigoplus_{\substack{q \vert N\\q \text{ premier}}} ℤ/qℤ.$$

### Rho de Pollard

L'algorithme rho de Pollard cherche des *collisions* modulo le plus
petit facteur $$p$$ de $$N$$. En effet, si l'on dispose de
$$a,b∈ℤ/Nℤ$$ tels que $$a ≠ b$$ et $$a≡b\bmod p$$, alors
$$p\vert\gcd(a-b, N)$$.

Par le paradoxe des anniversaires, après avoir examiner
$$O(\sqrt{p})$$ éléments, la probabilité d'avoir une collision modulo
$$p$$ est de $$\frac{1}{2}$$. L'idée fondamentale de l'algorithme
consiste à examiner $$O(\sqrt{p})$$ éléments, tout en gardant en
mémoire seulement deux d'entre eux à chaque itération.


### Méthode $$p-1$$

La méthode $$p-1$$ de Pollard se base sur le petit théorème de
Fermat. Elle est très efficace lorsque $$N$$ a un facteur $$p$$ tel
que $$p-1$$ n'a que des petits facteurs.

On suppose que tous les facteurs de $$p-1$$ sont plus petits d'une
borne $$B$$ et on calcule

$$x = \prod_{q \text{ prime } < B} q^{\lfloor\log_qp\rfloor}.$$

Alors $$(p-1) \vert x$$ et $$a^x ≡ 1 \bmod p$$. Comme auparavant,
$$p\vert\gcd(a^x - 1, N)$$, et si ce pgcd est différent de $$N$$ nous
avons une factorisation.

On peut interpréter la méthode $$p-1$$ comme une façon d'exploiter la
structure de groupe algébrique de $$(ℤ/Nℤ)^*$$. C'est cette
interprétation qui donne lieu à des généralisation intéressantes.

### Méthode $$p+1$$

La méthode $$p+1$$ est une généralisation de la méthode $$p-1$$. Elle
est très efficace lorsque $$N$$ a un facteur $$p$$ tel que $$p+1$$ n'a
que des petits facteurs.

Soit $$p≠2$$, la *conique de Pell* est la courbe affine définie sur
$$𝔽_p$$ par l'équation

$$\mathcal{C} : X^2 - ΔY^2 = 4.$$

Si $$\Delta$$ est un résidu quadratique de $$𝔽_p$$, alors
$$\mathcal{C}$$ a $$p-1$$ points rationnels et est isomorphe à
$$𝔽_p^*$$. Ce cas ne nous donne aucun nouvel algorithme de
factorisation.

Si par contre $$\Delta$$ est un non-résidu quadratique, alors
$$\mathcal{C}$$ a $$p+1$$ points rationnels, et on peut montrer
qu'elle est isomorphe au sous-groupe multiplicatif des éléments de
norme 1 de $$𝔽_{p^2}$$.

La loi de groupe sur $$\mathcal{C}$$ induite par l'isomorphisme a une
description géométrique simple. Son élément neutre a coordonnées
$$(2,0)$$, et l'addition est exprimée par des formules algébriques
simples :

$$P\oplus Q = \left(\frac{x_Px_Q + \Delta y_Py_Q}{2},\; \frac{x_Py_Q + x_Qy_P}{2}\right).$$

**Note :** Cette loi de groupe, sous le nom de
[méthode du *Chakravala*](http://en.wikipedia.org/wiki/Chakravala_method),
était déjà connue aux mathématiciens indiens du X siècle, qui
l'utilisaient pour la résolution d'équations quadratiques, dont
l'équation de Pell.

Par induction, on peut montrer que si $$α_1$$ est l'abscisse du point
$$P$$, alors l'abscisse $$α_n$$ de $$[n]P$$ est définie par la *suite
de Lucas*

$$α_{n+1} = α_1α_n - α_{n-1}.$$

Remarquez que cette formule ne dépend pas de $$Δ$$.  C'est maintenant
un exercice facile de déduire un algorithme de type *square and
multiply* pour calculer $$\alpha_m$$.

La méthode $$p+1$$ s'ensuit en considérant une conique de Pell à
coefficients dans $$ℤ/Nℤ$$. On suppose que tous les facteurs de
$$p+1$$ sont plus petits d'une borne $$B$$ et on calcule $$x$$ comme
auparavant :

$$x = \prod_{q \text{ prime } < B} q^{\lfloor\log_qp\rfloor}.$$

On choisit un point $$P$$ au hasard, en espérant qu'il s'agisse d'un
point sur une conique avec $$\bigl(\frac{Δ}{p}\bigr)=-1$$ (cela a une
environ chance sur deux d'arriver). On calcule l'abscisse de $$[x]P$$,
elle est nécessairement congrue à $$2$$ modulo $$p$$, par conséquent
$$p\vert\gcd(\alpha_x-2,N)$$.

Pour plus de détails voir le chapitre 10 des notes de cours de Franz
Lemmermeyer : <http://www.fen.bilkent.edu.tr/~franz/crypto/cryp06.pdf>

### Excercices

1. Implanter ces trois méthodes de factorisation et comparer leur
   performances, notamment sur les entiers

	* 2177241218019392284455749961185783753335013327591,
	* 199214358783833785496649131630759414803916321139456200129431155042143170897974614023327,
	* 6500836418678143176619908800773996927084289993776850414594757469264912497841920022968113.


## Logarithme discret

### Pohlig-Hellman

### Baby-step giant-step

### Pollard Rho

### Calcul d'index

### Exercices

1. Implanter la méthode de Pohlig-Hellman pour le groupe multiplicatif
   d'un corps premier $$𝔽_p$$. Tester pour $$p$$ égal à

	199214358783833785496649131630759414803916321139456200129431155042143170897974614023327.

## Courbes Elliptiques

### Loi de groupe

### La méthode de factorisation ECM


## Couplages

### Diviseurs

### Couplage de Weil

### Couplage de Tate

### Protocoles à base de couplages

