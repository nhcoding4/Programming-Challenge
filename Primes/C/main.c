#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int capacity;
    int *data;
} List;

bool isPrime(int i)
{
    for (int x = 2; x < i; x++)
    {
        if (i % x == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    List foundPrimes = {
        capacity : 1,
        data : (int *)malloc(sizeof(int) * foundPrimes.capacity),
    };

    for (int i = 2; i < 250001; i++)
    {
        if (isPrime(i))
        {
            foundPrimes.data[foundPrimes.capacity - 1] = i;
            foundPrimes.capacity++;
            foundPrimes.data = realloc(foundPrimes.data, sizeof(int) * foundPrimes.capacity);
        }
    }

    printf("Found: %i\n", foundPrimes.capacity-1);
    free(foundPrimes.data);
}