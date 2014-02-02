/*
  Ce code implante trois méthodes de factorisation : Pollard rho, p-1
  et p+1.
 */

#include <gmp.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

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


/* Équivalent de mpz_init pour les points */
void point_init(point_t P) {
  mpz_init(P->X);
  mpz_init_set_ui(P->Y, 1);
  mpz_init(P->Z);
}
void point_copy(point_t P, const point_t Q) {
  mpz_set(P->X, Q->X);
  mpz_set(P->Y, Q->Y);
  mpz_set(P->Z, Q->Z);
}


/* Formule d'addition de Weierstraß. */
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

/* L'algorithme double and add gauche-droite classique */
void double_and_add(point_t res, const point_t P, const mpz_t n, const curve_t C) {
  long i;
  point_t tmp;
  point_init(tmp);
  for (i = mpz_sizeinbase(n, 2) - 1; i >= 0; i--) {
    w_double(tmp, tmp, C);
    if (mpz_tstbit(n, i)) {
      /* Si le bit vaut 1 */
      w_add(tmp, tmp, P, C);
    }
  }
  point_copy(res, tmp);
}

/* L'algorithme de factorisation ECM */
int ecm(mpz_t res, const mpz_t N, unsigned long B, gmp_randstate_t rand) {
  mpz_t exp;
  curve_t C;
  point_t P;
  // On initialise l'exposant e à B!
  mpz_inits(exp, C->p, C->i, NULL);
  mpz_fac_ui(exp, B);
  // On initialise une courbe C au hasard
  mpz_set(C->p, N);
  mpz_urandomm(C->i, rand, N);
  // On initilise un point P au hasard (on ne vérifie même pas qu'il
  // appartient à C)
  point_init(P);
  mpz_urandomm(P->X, rand, N);
  mpz_urandomm(P->Y, rand, N);
  mpz_set_ui(P->Z, 1);
  // On calcule exp*P
  double_and_add(P, P, exp, C);
  mpz_invert(tmp1, P->Z, C->p);
  mpz_mul(tmp2, P->X, tmp1);
  mpz_mod(tmp2, tmp2, C->p);
  mpz_mul(tmp3, P->Y, tmp1);
  mpz_mod(tmp3, tmp3, C->p);
  // On essaye d'inverser la coordonnée Z
  mpz_gcd(res, P->Z, N);

  mpz_clears(exp, P->X, P->Y, P->Z, C->p, C->i, NULL);

  // On renvoie 0 si le test a trouvé un facteur non trivial
  return !mpz_cmp_ui(res, 1) || !mpz_cmp(res, N);
}

/* Fonction qui affiche l'aide */
void usage(char* prog) {
  fprintf(stderr, "Usage: %s [-m (weierstrass|edwards|montgomery)] [-B smoothness bound] [-s seed] N\n", prog);
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
  char model = 'w';
  while ((opt = getopt(argc, argv, "hm:B:s:r:")) != -1) {
    switch (opt) {
    case 'm':
      model = optarg[0];
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

  // Execution de l'algorithme
  if (optind > 0 && optind < argc) {
    // On lit l'entier sur la ligne de commande
    mpz_init_set_str(N, argv[optind], 10);

    // On choisit l'algo à exécuter
    int status;
    switch (model) {
    case 'w':
    case 'W':
      for (r--; r >=0 && (status = ecm(x, N, B, rand)); r--);
      break;
    case 'e':
    case 'E':
      printf("Not implented yet.\n");
      break;
    case 'm':
    case 'M':
      printf("Not implented yet.\n");
      break;
    default:
      usage(argv[0]);
      printf("Unknown model %c\n", model);
      return 1;
    }

    // On teste que le résultat divise vraiment N
    assert(mpz_divisible_p(N, x));
    // On calcule le cofacteur et on affiche
    mpz_divexact(N, N, x);
    gmp_printf("%Zd * %Zd\n", x, N);

    
    // On renvoie 0 si le test a trouvé un facteur non trivial
    return status;
  } else {
    usage(argv[0]);
    return 1;
  }
}
