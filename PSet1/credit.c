#include <stdio.h>
#include <cs50.h>

long long getCard()
{
	printf("Please provide your credit card number: ");
	return GetLongLong();
}

int main()
{
	long long cardNum = getCard();


}