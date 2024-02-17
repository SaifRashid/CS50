#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int starting_pop;

    do
    {
        starting_pop = get_int("What is the starting population? ");
    }
    while (starting_pop < 9);

    // TODO: Prompt for end size
    int ending_pop;

    do
    {
        ending_pop = get_int("What is the ending population? ");
    }
    while (ending_pop < starting_pop);

    // TODO: Calculate number of years until we reach threshold
    int i = 0;
    while (starting_pop < ending_pop)
    {
        starting_pop = starting_pop + (starting_pop / 3) - (starting_pop / 4);
        i++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", i);
}
