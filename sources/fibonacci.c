#include <gmp.h>
#include <stdlib.h>

void fibonacci(mpz_t res, long n) {
  /*
    On intialize le résultat à M⁰, i.e
      |0 1|⁰
      |1 1|  
    (i.e., l'identité)
  */
  mpz_t a00, a01, a10, a11;
  mpz_init_set_ui(a00, 1); mpz_init_set_ui(a01, 0);
  mpz_init_set_ui(a10, 0); mpz_init_set_ui(a11, 1);
  // des variables auxiliaires
  mpz_t tmp1, tmp2;
  mpz_init(tmp1); mpz_init(tmp2);

  // On calcule M^n par un square and multiply de gauche à droite
  long i;
  for (i = 1 ; i < n ; i <<= 1);
  for ( ; i >= 1 ; i >>= 1) {
    /*
      Square (générique) :
      |a₀₀ a₀₁|² = |a₀₀²+a₀₁a₁₀  a₀₁(a₀₀+a₁₁)|
      |a₁₀ a₁₁|    |a₁₀(a₀₀+a₁₁)  a₀₁a₁₀+a₁₁²|
    */
    mpz_add(tmp1, a00, a11);
    mpz_mul(tmp2, a01, a10);
    mpz_mul(a01, a01, tmp1);
    mpz_mul(a10, a10, tmp1);
    mpz_mul(tmp1, a00, a00);
    mpz_add(a00, tmp1, tmp2);
    mpz_mul(tmp1, a11, a11);
    mpz_add(a11, tmp1, tmp2);
    if (n & i) {
      /*
	Multiply (spécifique à M) :
	|a₀₀ a₀₁| |0 1| = |a₀₁  a₀₀+a₀₁|
	|a₁₀ a₁₁| |1 1|   |a₁₁  a₁₀+a₁₁|
      */
      mpz_add(a01, a00, a01);
      mpz_add(a11, a10, a11);
      mpz_sub(a00, a01, a00);
      mpz_sub(a10, a11, a10);
    }
  }
  // f(n) apparaît sur la diagonale de M
  mpz_set(res, a01);
}

void main(int argc, char** argv) {
  if (argc > 1) {
    long n = atol(argv[1]);
    mpz_t f;
    mpz_init(f);
    fibonacci(f, n);
    gmp_printf("%Zd\n", f);
    mpz_clear(f);
  }
}
