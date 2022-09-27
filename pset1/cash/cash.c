#include<stdio.h>
#include<cs50.h>
#include<math.h>
int main(void)
{
    float input;
    int cash;
    do
    {
        //get user imput
        input = get_float("Change owed: ");
        cash = round(input * 100);
    }
    while (input < 0.00);
    //check money remaining
    int coin = 0;
    while (cash >= 25)
    {
        cash = cash - 25;
        //count number of coin
        coin++;
    }
    while (cash >= 10)
    {
        cash = cash - 10;
        coin++;
    }
    while (cash >= 5)
    {
        cash = cash - 5;
        coin++;
    }
    while (cash >= 1)
    {
        cash = cash - 1;
        coin++;
    }
    //output number of coins
    printf("%i\n", coin);


}