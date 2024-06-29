// 5.9 seconds

#include <stdio.h>
#include <stdlib.h>

int is_prime(int n)
{
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int captacity = 1000;
    int *primes = malloc(sizeof(int) * captacity);
    int found = 0;

    for (int i = 2; i < 250001; i++)
    {
        if (is_prime(i))
        {
            primes[found] = i;
            found++;
            if (found == captacity - 1)
            {
                captacity *= 2;
                primes = realloc(primes, sizeof(int) * captacity);
            }
        }
    }

    printf("found: %d prime numbers\n", found);
}