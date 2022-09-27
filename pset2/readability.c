#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string count_text);
int count_words();
int count_sentence(string s);
double math_index(int len, int words, int sentence);

int main(void)
{
    //get user imput
    string s = get_string("text: ");
    int str = count_letters(s);
    int words = count_words(s);
    int sentence = count_sentence(s);
    double index = math_index(str, words, sentence);

    //Conditional branch according to the calculated result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }

}

int count_words(string s)
{
    int count = 0;

    //Repeat for the number of characters entered
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        //char to ascii
        int asc = (int)s[i];
        //if it was space
        if (asc == 32)
        {
            count++;
        }
    }
    //The number of words is the number of spaces plus one
    count++;
    return (count);
}

int count_letters(string s)
{
    int count = 0;
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        //If it was alphabet
        if (isalpha(s[i]))
        {
            count++;
        }
    }
    return (count);
}

int count_sentence(string s)
{
    int count = 0;

    for (int i = 0, len = strlen(s); i < len; i++)
    {
        int asc = (int)s[i];
        //if (.) (!) (?)
        if (asc == 46 || asc == 33 || asc == 63)
        {
            count++;
        }
    }
    return (count);
}

double math_index(int len, int words, int sentence)
{
    //math with Coleman-Liau index
    double L = (double)len / (double)words * 100;
    double S = (double)sentence / (double)words * 100;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    double ans = round(index);
    return (ans);
}