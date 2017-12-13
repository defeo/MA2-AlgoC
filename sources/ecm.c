/*
  Ce code implante trois variantes de la méthode de factorisation
  ECM. Chaque variante utilise un modèle de courbe différent :
  Weierstrass, Edwards et Montgomery. Dans les trois cas, les points
  sont représentés en coordonnées projectives.
*/

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

/* Des constantes pour désigner le modèle */
#define WEIERSTRASS 'W'
#define EDWARDS 'E'
#define MONTGOMERY 'M'

/* Un point représenté par ses coordonnées projectives */
typedef struct {
  mpz_t X;
  mpz_t Y;
  mpz_t Z;
} point_struct;

/*
  Une courbe, décrite par le "premier" p et un invariant i (le choix
  de l'invariant dépend du modèle.
*/
typedef struct {
  mpz_t p;
  mpz_t i;
} curve_struct;

/*
  Astuce à la gmp pour passer des pointeurs qui allouent la mémoire
  sur le stack.
*/
typedef point_struct point_t[1];
typedef curve_struct curve_t[1];

/*
  Quelques mpz_t temporaires, pour les routines d'addition, etc.

  Puisque les fonctions d'addition sont appelées souvent, il est plus
  efficace de faire un mpz_init une fois pour toutes dans le main,
  plutôt que de déclarer ces variables localement à chaque fonction
  et les initialiser à chaque appel.
*/
mpz_t tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;


/* 
   Comme mpz_init, initialise la mémoire.  En plus, il initialise les
   coordonnées au point neutre du modèle.
*/
void point_init(point_t P, char model) {
  mpz_init(P->X);
  mpz_init_set_ui(P->Y, 1);
  mpz_init_set_ui(P->Z, model == EDWARDS ? 1 : 0);
}
void point_copy(point_t P, const point_t Q) {
  mpz_set(P->X, Q->X);
  mpz_set(P->Y, Q->Y);
  mpz_set(P->Z, Q->Z);
}

/********************* Weierstrass  ************************

La courbe a equation

  y² = x³ + ax + b

Dans les algorithmes qui suivent, C->i est l'invariant a. La
connaissance de b n'est pas nécessaire pour les formules.

***********************************************************/

/* Formule de doublement de Weierstraß. */
void w_double(point_t res, const point_t P, const curve_t C) {
  mpz_mul_ui(tmp1, P->Y, 2);
  mpz_mul(tmp2, tmp1, P->Z);
  mpz_mod(tmp2, tmp2, C->p);

  // On vérifie que P n'est pas un point de 2-torsion
  if (mpz_sgn(tmp2) == 0) {
    mpz_set_ui(res->X, 0);
    mpz_set_ui(res->Y, 1);
    mpz_set_ui(res->Z, 0);
  } else {
    // tmp3 = X²
    // λ = (3X² + aZ²) / 2YZ = tmp1 / tmp2
    mpz_mul(tmp3, P->X, P->X);
    mpz_mul_ui(tmp1, tmp3, 3);
    mpz_mul(tmp3, C->i, P->Z);
    mpz_mod(tmp3, tmp3, C->p);
    mpz_mul(tmp3, tmp3, P->Z);
    mpz_add(tmp1, tmp1, tmp3);
    mpz_mod(tmp1, tmp1, C->p);

    // Soit λ = μ/ν
      
    // tmp4 = μ²
    mpz_mul(tmp4, tmp1, tmp1);
    mpz_mod(tmp4, tmp4, C->p);
    // tmp5 = ν²
    mpz_mul(tmp5, tmp2, tmp2);
    mpz_mod(tmp5, tmp5, C->p);
    
    // X₃ = μ²νZ - 2Xν³
    // tmp7 = Xν²
    mpz_mul(tmp6, tmp4, P->Z);
    mpz_mul(tmp7, P->X, tmp5);
    mpz_mul_2exp(tmp8, tmp7, 1);
    mpz_sub(tmp6, tmp6, tmp8);

    // tmp6 = X₃/ν
    mpz_mod(tmp6, tmp6, C->p);
    
    // Y₃ = μ(Xν² - X₃/ν) - ν³Y
    mpz_sub(tmp7, tmp7, tmp6);
    mpz_mod(tmp7, tmp7, C->p);
    mpz_mul(tmp7, tmp7, tmp1);
    mpz_mul(tmp8, tmp5, P->Y);
    mpz_mod(tmp8, tmp8, C->p);

    mpz_mul(tmp8, tmp8, tmp2);
    mpz_sub(tmp7, tmp7, tmp8);
    mpz_mod(res->Y, tmp7, C->p);

    // Z₃ = ν³Z
    mpz_mul(tmp7, tmp5, P->Z);
    mpz_mod(tmp7, tmp7, C->p);
    mpz_mul(tmp8, tmp7, tmp2);
    mpz_mod(res->Z, tmp8, C->p);

    // On ne pouvait pas faire ça avant, au cas ou res = P
    mpz_mul(tmp7, tmp6, tmp2);
    mpz_mod(res->X, tmp7, C->p);
  }
}

/* Formule d'addition de Weierstraß. */
void w_add(point_t res, const point_t P, const point_t Q, const curve_t C) {
  // On vérifie que P ≠ 0 et Q ≠ 0
  if (mpz_sgn(P->Z) == 0) {
    point_copy(res, Q);
    return;
  } else if (mpz_sgn(Q->Z) == 0) {
    point_copy(res, P);
    return;
  }

  // λ = (Y₂Z₁ - Y₁Z₂) / (X₂Z₁ - X₁Z₂) = tmp1 / tmp2
  mpz_mul(tmp1, Q->Y, P->Z);
  mpz_mul(tmp2, P->Y, Q->Z);
  mpz_sub(tmp1, tmp1, tmp2);
  mpz_mod(tmp1, tmp1, C->p);
  
  mpz_mul(tmp2, Q->X, P->Z);
  mpz_mul(tmp3, P->X, Q->Z);
  mpz_sub(tmp2, tmp2, tmp3);
  mpz_mod(tmp2, tmp2, C->p);
  
  if (mpz_sgn(tmp2) == 0) {
    // Si P = Q (dans ce cas λ = 0/0)
    if (mpz_sgn(tmp1) == 0) {
      w_double(res, P, C);
    } 
    // Si on additionne P et -P
    else {
      mpz_set_ui(res->X, 0);
      mpz_set_ui(res->Y, 1);
      mpz_set_ui(res->Z, 0);
    }
  } else {
    // Soit λ = μ/ν

    // tmp3 = μ²
    mpz_mul(tmp3, tmp1, tmp1);
    mpz_mod(tmp3, tmp3, C->p);
    // tmp4 = ν²
    mpz_mul(tmp4, tmp2, tmp2);
    mpz_mod(tmp4, tmp4, C->p);
    // tmp5 = Z₁Z₂
    mpz_mul(tmp5, P->Z, Q->Z);
    mpz_mod(tmp5, tmp5, C->p);
    
    // X₃ = μ²νZ₁Z₂ - (X₁Z₂ + X₂Z₁)ν³
    mpz_mul(tmp6, tmp3, tmp5);

    mpz_mul(tmp7, P->X, Q->Z);
    mpz_mul(tmp8, Q->X, P->Z);
    mpz_add(tmp7, tmp7, tmp8);
    mpz_mod(tmp7, tmp7, C->p);
    mpz_mul(tmp7, tmp7, tmp4);
    mpz_sub(tmp6, tmp6, tmp7);

    // tmp6 = X₃/ν
    mpz_mod(tmp6, tmp6, C->p);

    // Y₃ = ν²(μX₁ - νY₁)Z₂ - μX₃/ν 
    mpz_mul(tmp7, tmp1, P->X);
    mpz_mul(tmp8, tmp2, P->Y);
    mpz_sub(tmp7, tmp7, tmp8);
    mpz_mod(tmp7, tmp7, C->p);

    mpz_mul(tmp7, tmp7, tmp4);
    mpz_mod(tmp7, tmp7, C->p);
    mpz_mul(tmp7, tmp7, Q->Z);

    mpz_mul(tmp8, tmp1, tmp6);
    mpz_sub(tmp7, tmp7, tmp8);
    mpz_mod(res->Y, tmp7, C->p);

    // Z₃ = ν³Z₁Z₂
    mpz_mul(tmp7, tmp4, tmp5);
    mpz_mod(tmp7, tmp7, C->p);
    mpz_mul(tmp8, tmp2, tmp7);
    mpz_mod(res->Z, tmp8, C->p);

    // On ne pouvait pas faire ça avant, au cas ou res = P ou res = Q
    mpz_mul(tmp7, tmp6, tmp2);
    mpz_mod(res->X, tmp7, C->p);
  }
}


/************************* Edwards  ********************************

La courbe a equation

  x² + y² = 1 + dx²y²

Dans les algorithmes qui suivent, C->i est l'invariant d.  Pour
simplicité on utilise la formule unifiée pour les doublements et les
additions.

*******************************************************************/

/* Formule d'addition (et doublement) d'Edwards. */
void e_add(point_t res, const point_t P, const point_t Q, const curve_t C) {
  /* 
     Les formules projectives:

       X₃ = (X₁Y₂ + Y₁X₂) ((Ζ₁Ζ₂)² - dX₁X₂Y₁Y₂) Z₁Z₂
       Y₃ = (Y₁Y₂ - X₁X₂) ((Ζ₁Ζ₂)² + dX₁X₂Y₁Y₂) Z₁Z₂
       Z₃ = (Ζ₁Ζ₂)⁴ - (dX₁X₂Y₁Y₂)²
       
     Voir aussi

       <http://www.hyperelliptic.org/EFD/g1p/auto-edwards-projective.html#addition-add-2007-bl>
  */
  mpz_mul(tmp1, P->Z, Q->Z);
  mpz_mod(tmp1, tmp1, C->p); // Z₁Z₂
  mpz_mul(tmp2, tmp1, tmp1);
  mpz_mod(tmp2, tmp2, C->p); // (Z₁Z₂)²
  mpz_mul(tmp3, P->X, Q->X);
  mpz_mod(tmp3, tmp3, C->p); // X₁X₂
  mpz_mul(tmp4, P->Y, Q->Y);
  mpz_mod(tmp4, tmp4, C->p); // Y₁Y₂
  mpz_add(tmp5, P->X, P->Y);
  mpz_add(tmp6, Q->X, Q->Y);
  mpz_mul(tmp7, tmp5, tmp6);
  mpz_mod(tmp5, tmp7, C->p); // (X₁ + Y₁) (X₂ + Y₂)
  // À partir de maintenant, on ne touche plus à P et Q, 
  // on peut alors toucher à res.
  mpz_mul(tmp6, tmp3, tmp4);
  mpz_mod(tmp6, tmp6, C->p);
  mpz_mul(tmp6, tmp6, C->i);
  mpz_mod(tmp6, tmp6, C->p); // dX₁X₂Y₁Y₂
  mpz_sub(tmp7, tmp2, tmp6); // (Ζ₁Ζ₂)² - dX₁X₂Y₁Y₂
  mpz_add(tmp8, tmp2, tmp6); // (Ζ₁Ζ₂)² + dX₁X₂Y₁Y₂

  mpz_sub(res->X, tmp5, tmp3);
  mpz_sub(res->X, res->X, tmp4);
  mpz_mul(res->X, res->X, tmp7);
  mpz_mod(res->X, res->X, C->p);
  mpz_mul(res->X, res->X, tmp1);
  mpz_mod(res->X, res->X, C->p);

  mpz_sub(res->Y, tmp4, tmp3);
  mpz_mul(res->Y, res->Y, tmp8);
  mpz_mod(res->Y, res->Y, C->p);
  mpz_mul(res->Y, res->Y, tmp1);
  mpz_mod(res->Y, res->Y, C->p);

  mpz_mul(res->Z, tmp7, tmp8);
  mpz_mod(res->Z, res->Z, C->p);
}

/* Formule de doublement d'Edwards (fait appel à l'addition unifiée). */
void e_double(point_t res, const point_t P, const curve_t C) {
  e_add(res, P, P, C);
}

/*********************** Montgomery ********************************

La courbe a equation

  By² = x³ + Ax² + x

Dans les algorithmes qui suivent, C->i est l'invariant (A+2)/4.

*******************************************************************/

/*
  Formule d'addition différentielle de Montgomery. Calcule P+Q
  connaissant D = P-Q.
*/
void m_diffadd(point_t res, const point_t P, const point_t Q, 
	       const point_t D, const curve_t C) {
  // On vérifie que P ≠ 0 et Q ≠ 0
  if (mpz_sgn(P->Z) == 0) {
    point_copy(res, Q);
    return;
  } else if (mpz_sgn(Q->Z) == 0) {
    point_copy(res, P);
    return;
  }

  /*
    Formule projective

      X = Z₁ (X₂X₃ - Z₂Z₃)²
      Z = X₁ (X₂Z₃ - Z₂X₃)²

    Voir <http://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#diffadd-dadd-1987-m-3>.
  */
  mpz_add(tmp1, P->X, P->Z); // X₂ + Z₂
  mpz_sub(tmp2, P->X, P->Z); // X₂ - Z₂
  mpz_add(tmp3, Q->X, Q->Z); // X₃ + Z₃
  mpz_sub(tmp4, Q->X, Q->Z); // X₃ - Z₃
  mpz_mul(tmp5, tmp4, tmp1);
  mpz_mod(tmp5, tmp5, C->p); // X₂X₃ - Z₂Z₃ + X₃Z₂ - Z₃X₂
  mpz_mul(tmp6, tmp2, tmp3);
  mpz_mod(tmp6, tmp6, C->p); // X₂X₃ - Z₂Z₃ + X₂Z₃ - Z₂X₃

  mpz_sub(tmp3, tmp5, tmp6);
  // On vérifie que P ≠ -Q
  if (mpz_sgn(tmp3) == 0) {
    mpz_set_ui(res->X, 0);
    mpz_set_ui(res->Z, 0);
    return;
  }
  mpz_mul(tmp4, tmp3, tmp3);
  mpz_mod(tmp3, tmp4, C->p); // 4(X₃Z₂ - Z₃X₂)²
  mpz_mul(tmp4, D->X, tmp3); // 4X₁ (X₃Z₂ - Z₃X₂)²
  mpz_add(tmp1, tmp5, tmp6);
  mpz_mul(tmp2, tmp1, tmp1);
  mpz_mod(tmp1, tmp2, C->p); // 4(X₂X₃ - Z₂Z₃)²
  mpz_mul(tmp2, D->Z, tmp1); // 4Z₁ (X₂X₃ - Z₂Z₃)²
  mpz_mod(res->X, tmp2, C->p);
  mpz_mod(res->Z, tmp4, C->p);
}

/*
  Formule de doublement de Montgomery. 
*/
void m_double(point_t res, const point_t P, const curve_t C) {
  /*
    Formule projective

      X₂ = (X + Z)² (X - Z)²
      Z = 4XZ ((X - Z)² + 4XZ (A + 2)/4 )

    Voir <http://www.hyperelliptic.org/EFD/g1p/auto-montgom-xz.html#doubling-dbl-1987-m-3>
  */
  mpz_add(tmp1, P->X, P->Z);
  mpz_mul(tmp2, tmp1, tmp1);
  mpz_mod(tmp1, tmp2, C->p); // (X + Z)²
  mpz_sub(tmp2, P->X, P->Z);
  mpz_mul(tmp3, tmp2, tmp2);
  mpz_mod(tmp2, tmp3, C->p); // (X - Z)²
  mpz_sub(tmp3, tmp1, tmp2); // 4XZ
  mpz_mul(tmp4, tmp1, tmp2);
  mpz_mod(res->X, tmp4, C->p);
  mpz_mul(tmp5, tmp3, C->i);
  mpz_mod(tmp5, tmp5, C->p); // (A + 2) XZ
  mpz_add(tmp6, tmp2, tmp5);
  mpz_mul(tmp7, tmp3, tmp6);
  mpz_mod(res->Z, tmp7, C->p);
}

/******************** Double and add *******************************

Un double and add classique gauche-droite, et une échelle de
Montgomery.

*******************************************************************/

void double_and_add(point_t res, const point_t P, const mpz_t n, const curve_t C,
		    const char model) {
  long i;
  point_t tmp1, tmp2;
  point_init(tmp1, model);
  switch (model) {
  case WEIERSTRASS:
    for (i = mpz_sizeinbase(n, 2) - 1; i >= 0; i--) {
      w_double(tmp1, tmp1, C);
      if (mpz_tstbit(n, i)) w_add(tmp1, tmp1, P, C);
    }
    break;
  case EDWARDS:
    for (i = mpz_sizeinbase(n, 2) - 1; i >= 0; i--) {
      e_double(tmp1, tmp1, C);
      if (mpz_tstbit(n, i)) e_add(tmp1, tmp1, P, C);
    }
    break;
  case MONTGOMERY:
    point_init(tmp2, model);
    point_copy(tmp2, P);
    for (i = mpz_sizeinbase(n, 2) - 1; i >= 0; i--) {
      if (mpz_tstbit(n, i)) {
	m_diffadd(tmp1, tmp1, tmp2, P, C);
	m_double(tmp2, tmp2, C);
      } else {
	m_diffadd(tmp2, tmp1, tmp2, P, C);
	m_double(tmp1, tmp1, C);
      }
    }
    break;
  }
  point_copy(res, tmp1);
}

/****************************** ECM **********************************

L'algorithme ECM, qui prend en paramètre le modèle (void définitions
des macros).

Remarquez que dans la vraie vie les courbes sont choisies de façon à
avoir des propriétés spéciales (essentiellement, de façons à avoir
beaucoup de points de (petite) torsion sur ℚ, et par conséquent une
plus grande probabilité d'avoir un cardinal friable modulo des nombres
premiers).

Voir, par exemple <http://eecm.cr.yp.to/>.

Ici nous faisons un choix plus proche de l'algorithme original de
Lenstra, en choisissant d'abord les coordonnées du point, et ensuite
une courbe qui contient ce point.

*********************************************************************/
int ecm(mpz_t res, const mpz_t N, unsigned long B, gmp_randstate_t rand, char model) {
  mpz_t exp;
  curve_t C;
  point_t P;
  __mpz_struct* zero_coord;

  // On initialise l'exposant e à B!
  mpz_inits(exp, C->p, C->i, NULL);
  mpz_fac_ui(exp, B);

  switch (model) {
  case WEIERSTRASS:
    /*
      On initialise une courbe
        y² = x³ + ax + ?
      au hasard.
    */
    mpz_set(C->p, N);
    mpz_urandomm(C->i, rand, N);

    // On initilise un point P au hasard (le b de la courbe va dépendre de P)
    point_init(P, model);
    mpz_urandomm(P->X, rand, N);
    mpz_urandomm(P->Y, rand, N);
    mpz_set_ui(P->Z, 1);

    // On calcule exp*P
    double_and_add(P, P, exp, C, model);

    // Si la courbe a un cardinal friable, P = 0 et Z = 0
    zero_coord = P->Z;
    break;
  case EDWARDS:
    // On initilise un point P au hasard
    point_init(P, model);
    mpz_urandomm(P->X, rand, N);
    mpz_urandomm(P->Y, rand, N);
    mpz_set_ui(P->Z, 1);
    /*
      On détermine

        x² + y² = 1 + dx²y²

      avec 

        d = (x² + y² - 1) / x²y²
    */
    mpz_mul(tmp1, P->X, P->X);
    mpz_mod(tmp1, tmp1, N);
    mpz_mul(tmp2, P->Y, P->Y);
    mpz_mod(tmp2, tmp2, N);
    mpz_mul(tmp3, tmp1, tmp2);

    mpz_add(tmp1, tmp1, tmp2);
    mpz_sub_ui(tmp1, tmp1, 1);

    if (!mpz_invert(tmp4, tmp3, N)) {
      // Surprise ! On a trouvé un facteur de N par pure chanche
      zero_coord = tmp3;
      break;
    }
    
    mpz_mul(C->i, tmp1, tmp4);
    mpz_mod(C->i, C->i, N);
    mpz_set(C->p, N);

    // On calcule exp*P
    double_and_add(P, P, exp, C, model);

    // Si la courbe a un cardinal friable, P = 0 et X = 0
    zero_coord = P->X;
    break;
  case MONTGOMERY:
    /*
      On initialise une courbe
        ?y² = x³ + ax² + x
      au hasard.
    */
    mpz_set(C->p, N);
    mpz_urandomm(C->i, rand, N);

    // On initilise un point P au hasard (le b de la courbe va dépendre de P)
    point_init(P, model);
    mpz_urandomm(P->X, rand, N);
    mpz_set_ui(P->Z, 1);

    // On calcule exp*P
    double_and_add(P, P, exp, C, model);

    // Si la courbe a un cardinal friable, P = 0 et Z = 0
    zero_coord = P->Z;
    break;
  default:
    printf("Unknown model %c\n", model);
    return 2;
  }

  // On essaye d'inverser la coordonnée qui doit être égale à 0
  mpz_gcd(res, zero_coord, N);

  mpz_clears(exp, P->X, P->Y, P->Z, C->p, C->i, NULL);

  // On renvoie 0 si le test a trouvé un facteur non trivial
  return !mpz_cmp_ui(res, 1) || !mpz_cmp(res, N);
}

/* Fonction qui affiche l'aide */
void usage(char* prog) {
  fprintf(stderr, "Usage: %s [-m (weierstrass|edwards|montgomery)] [-B <smoothness bound>] [-s <seed>] [-r <number of tries>] N\n", prog);
}

int main(int argc, char** argv) {
  mpz_t N, x;
  long B = 10, r = 1;
  gmp_randstate_t rand;

  // Initialisation des variables auxiliaires
  gmp_randinit_default(rand);
  mpz_init(x);
  mpz_inits(tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, NULL);

  /* 
     Lecture des options en ligne de commande. L'ordre n'est pas important.

     Options possibles :
     -m : choix du modèle (Weierstraß, Edwards o Montgomery), seule la première lettre est considérée
     -s : choix d'une graine 
     -B : choix d'une borne de "friabilité" (pas exactement, voir implém)
     -r : combien de fois il faut répéter le test
  */
  int opt;
  char model = WEIERSTRASS;
  while ((opt = getopt(argc, argv, "hm:B:s:r:")) != -1) {
    switch (opt) {
    case 'm':
      model = optarg[0] < 0x5B ? optarg[0] : optarg[0] - 0x20;
      break;
    case 'B':
      B = atol(optarg);
      break;
    case 's':
      mpz_set_str(x, optarg, 10);
      gmp_randseed(rand, x);
      break;
    case 'r':
      r = atol(optarg);
      break;      
    default:
      usage(argv[0]);
      return 1;
    }
  }

  // Exécution de l'algorithme
  if (optind > 0 && optind < argc) {
    // On lit l'entier sur la ligne de commande
    mpz_init_set_str(N, argv[optind], 10);

    int status;
    for (r--; r >=0 && (status = ecm(x, N, B, rand, model)) == 1; r--);

    if (status == 0) {
      // On teste que le résultat divise vraiment N
      assert(mpz_divisible_p(N, x));
      // On calcule le cofacteur et on affiche
      mpz_divexact(N, N, x);
      gmp_printf("%Zd * %Zd\n", x, N);
    } else {
      gmp_printf("%Zd\n", x);
    }

    // On renvoie 0 si le test a trouvé un facteur non trivial
    return status;
  } else {
    usage(argv[0]);
    return 1;
  }
}
