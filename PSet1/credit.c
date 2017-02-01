#include <stdio.h>
#include <cs50.h>

long long getCard()
{
	printf("Please provide your credit card number: ");
	return GetLongLong();
}

int firstDigit(long long cardNum)
{
	while (cardNum > 100)
		cardNum = cardNum / 10;

	return (int) cardNum;
}


bool checksum(long long cardNum)
{
		int sum1 = 0;
		int sum2 = 0;

		while (cardNum > 0)
    	{
    		//step 1
    		sum1 += cardNum % 10;
    		cardNum = cardNum / 10;

    		// step2
    		int toMultiply = (cardNum % 10) * 2;

    		if (toMultiply >= 10)
    		{
    			toMultiply = (toMultiply % 10) + (toMultiply / 10);
    		}
    		sum2 += toMultiply;
    		cardNum = cardNum/10;

    	};

    	int result = sum1 + sum2;
    	if (result % 10 == 0)
    		return true;
    	else
    		return false;
}

void printCardType(int firstDigit)
{
	if (firstDigit < 50 && firstDigit >= 40)
	{
		// Visa
		printf("VISA\n");
	}
	else if (firstDigit <= 55 && firstDigit >= 51 )
	{
		// Amex
		printf("MASTERCARD\n");
	}
	else if (firstDigit == 34 || firstDigit == 37)
	{
		// Mastercard
		printf("AMEX\n");
	}
	else
		printf("INVALID\n");
}

int main()
{
	long long cardNum = getCard();

	if (checksum(cardNum) == true)
		printCardType(firstDigit(cardNum));
	else printf("INVALID\n");
}