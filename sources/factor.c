/*
  Ce code implante trois méthodes de factorisation : Pollard rho, p-1
  et p+1.
 */

#include <gmp.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

/* Méthode rho de Pollard */
int pollard_rho(mpz_t res, const mpz_t N, gmp_randstate_t rand) {
  mpz_t a, b;
  // On initialise a et b à un entier aléatoire mod N
  mpz_inits(a, b, NULL);
  mpz_urandomm(a, rand, N);
  mpz_set(b, a);

  // res va contenir le pgcd de a-b et N
  mpz_set_ui(res, 1);
  
  while (!mpz_cmp_ui(res, 1)) {
    /*
      On utilise la fonction  f(x) = x^2 + x pour deux raisons :
      - c'est non linéaire
      - ça tient en une seule instruction GMP (addmul)
    */
    // Une itération sur a
    mpz_addmul(a, a, a);
    mpz_mod(a, a, N);
    // Deux itérations sur b
    mpz_addmul(b, b, b);
    mpz_mod(b, b, N);
    mpz_addmul(b, b, b);
    mpz_mod(b, b, N);
    // On calcule pgcd(a-b, N)
    mpz_sub(res, a, b);
    mpz_gcd(res, res, N);
  }

  mpz_clears(a, b, NULL);

  // On renvoie 0 si le test a trouvé un facteur non trivial
  return !mpz_cmp(N, res);
}

/* Méthode p-1 de Pollard */
int p_minus_one(mpz_t res, const mpz_t N, unsigned long B, gmp_randstate_t rand) {
  mpz_t exp, a;
  /*
    On initialise l'exposant e à B!

    Ce choix n'est pas le même que dans le cours, mais il est aussi
    raisonnable : il faut espérer que (p-1) | B!
   */
  mpz_inits(exp, a, NULL);
  mpz_fac_ui(exp, B);
  // On initialise a au hasard
  mpz_urandomm(a, rand, N);
  // On calcule a^e mod N
  mpz_powm(res, a, exp, N);
  // On calcule pgcd(a-1, N)
  mpz_sub_ui(res, res, 1);
  mpz_gcd(res, res, N);
  mpz_clears(exp, a, NULL);

  // On renvoie 0 si le test a trouvé un facteur non trivial
  return !mpz_cmp(N, res);
}

/* Fonction qui affiche l'aide */
void usage(char* prog) {
  fprintf(stderr, "Usage: %s [-a (rho|minusone|plusone)] [-B smoothness bound] [-s seed] N\n", prog);
}

int main(int argc, char** argv) {
  mpz_t N, x;
  long B = 10;
  gmp_randstate_t rand;

  // Initialisation des variables auxiliaires
  gmp_randinit_default(rand);
  mpz_init(x);

  /* 
     Lecture des options en ligne de commande. L'ordre n'est pas important.

     Options possibles :
     -a : choix de l'algo (Rho, Minusone, ou Plusone), seule la première lettre est considérée
     -s : choix d'une graine 
     -B : choix d'une borne de "friabilité" (pas exactement, voir implém)
  */
  int opt;
  char alg = 'r';
  while ((opt = getopt(argc, argv, "ha:B:s:")) != -1) {
    switch (opt) {
    case 'a':
      alg = optarg[0];
      break;
    case 'B':
      B = atol(optarg);
      break;
    case 's':
      mpz_set_str(x, optarg, 10);
      gmp_randseed(rand, x);
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
    switch (alg) {
    case 'r':
    case 'R':
      status = pollard_rho(x, N, rand);
      break;
    case 'p':
    case 'P':
      break;
    case 'm':
    case 'M':
      status = p_minus_one(x, N, B, rand);
      break;
    default:
      usage(argv[0]);
      printf("Unknown algorithm %c\n", alg);
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
