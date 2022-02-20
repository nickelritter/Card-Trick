/* File: Cardtrick.cpp
*  Programmer: Steven Heid
*  Date: 17 November 2019
*  Course: COP 2931
*
*  Purpose:
*  Write a program that performs a card trick. The program will create a
*  random deck of cards, deal them out, pick them up, and determine the
*  secret card.
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes.
void BuildDeck(int deck[], const int size);
void PrintDeck(int deck[], const int size);
void PrintCard(int card);
void Deal(int deck[], int play[][3]);
void PickUp(int deck[], int play[][3], int column);
void SecretCard(int deck[]);

int main(void)
{
	/* Declare and initialize variables. */
	int column = 0, i = 0;
	int playAgain = 0;
	char name[20] = { 0 };  //name array.
	char seeDeck = 0;
	int size = 52;  // Card deck size.

	/* Declare a 52-element array of integers to be used as the deck of cards. */
	int deck[52] = { 0 };

	/* Declare a 7 by 3 array to receive the cards dealt to play the trick. */
	int play[7][3] = { 0 };

	/* Generate a random seed for the random number generator. */
	srand(time(0));

	/* Opening message. Ask the player for his/her name. */
	cout << "Hello, I am a really tricky computer program and " << endl
		<< "I can even perform a card trick.  Here's how." << endl
		<< "To begin the card trick type in your name: ";
	cin >> name;

	/* Capitalize the first letter of the person's name. */
	if (name[0] > 96 && name[0] < 123) // Check to see if lowercase using ASCII.
	{
		name[0] -= 32; // Capitalize first letter of name array using ASCII.
	}

	cout << endl << "Thank you " << name << endl;

	do  // Do loop for repeat plays.
	{
		/* Build the deck */
		BuildDeck(deck, 52);  // Function call to build deck.

		/* Ask if the player wants to see the entire deck. If so, print it out. */
		cout << "Ok " << name << ", first things first.  Do you want to see what" << endl
			<< "the deck of cards looks like (y/n)? ";
		cin >> seeDeck;

		if (seeDeck == 'y')  // Print out 52 card deck if prompted
		{
			PrintDeck(deck, 52);  // Function call to print deck of size 52.
			cout << endl;
		}
		system("Pause");

		cout << endl << name << " pick a card and remember it..." << endl;

		/* Begin the card trick loop */
		for (i = 0; i < 3; i++)
		{
			/* Begin the trick by calling the function to deal out the first 21 cards */
			Deal(deck, play);  // Function call to print deck array with play matrix.

			/* Include error checking for entering which column */
			do  // Do-While loop until valid input is registered (0-2)
			{
				/* Ask the player to pick a card and identify
				the column where the card is */
				cout << endl << "Which column is your card in (0, 1, or 2) ? : ";

				cin >> column;

			} while (column < 0 || column > 2);

			/* Pick up the cards, by column, with the selected column
			second */
			PickUp(deck, play, column);
		}

		SecretCard(deck);  // Function call to display secret card from deck array.

		/* if the player wants to play again */
		cout << name << ", would you like to play again (1 = yes, 0 = no)? ";
		cin >> playAgain;


	} while (playAgain == 1);

	/* Exiting message */
	cout << endl << endl << "Thank you for playing the card trick!" << endl;
}

// Build deck random from 0-52.
void BuildDeck(int deck[], const int size)
{
	int used[52] = { 0 };  // Used array to avoid duplicate cards
	int card = 0, i = 0;

	/* Generate cards until the deck is full of integers */
	while (i < size)
	{
		/* generate a random number between 0 and 51 */
		int card = rand() % size;

		/* Check the used array at the position of the card.
		   If 0, add the card and set the used location to 1.  If 1, generate another number */
		if (used[card] == 0)
		{
			deck[i] = card;  // Assigns unused card to deck array.
			used[card] = 1;  // Marked used in used card array.
			i++;  // Moves to next card
		}
		else  // Signifies used card, generates another random card.
		{
			card = rand() % 52;
		}
	}
	return;
}

/* Print out each card in the deck */
void PrintDeck(int deck[], const int size)
{
	for (int i = 0; i < size; i++)  // Loops 'size' number of times
	{
		PrintCard(deck[i]);  // Function call to display proper card symbol.
		cout << endl;
	}
}

/* Print out 7 row, 3 column play area matrix for first 21 cards in deck */
void Deal(int deck[], int play[][3])
{
	int row = 0, col = 0, card = 0;

	// Deal cards by passing addresses of card values from the deck array to the play matrix
	cout << endl;
	cout << "   Column 0           Column 1          Column 2 " << endl;
	cout << "=======================================================" << endl;

	//  Nested for loop to display matrix. 
	for (row = 0; row < 7; row++)  // Populates row.
	{
		for (col = 0; col < 3; col++)  // Populates column.
		{
			play[row][col] = deck[card];
			PrintCard(deck[card]);  // function call to display proper card symbol.
			card++;
		}
		cout << endl;
	}
}

/* Prints out card string from card integer */
void PrintCard(int card)
{
	int rank = 0;
	int suit = 0;

	rank = card % 13;  // Modules remainder to determine ranks regardless of suit.
	suit = card / 13;  // Divide by 13 to determine suit.

	switch (rank)  // Switch statement for face cards.
	{
	case 0:
		cout << " King";
		break;
	case 1:
		cout << "  Ace";
		break;
	case 11:
		cout << " Jack";
		break;
	case 12:
		cout << "Queen";
		break;

	default:  // Maintains numeric value as rank (2-10).
		cout << setw(5) << rank;
	}

	switch (suit)  // Switch statement for suit
	{
	case 0:
		cout << " of Clubs   ";
		break;
	case 1:
		cout << " of Hearts  ";
		break;
	case 2:
		cout << " of Diamonds";
		break;
	case 3:
		cout << " of Spades  ";
		break;
	}
}


/* Rearranges deck array using play matrix and column designator */
void PickUp(int deck[], int play[][3], int column)
{
	int card = 0, row = 0;
	int first = 0, last = 0;

	// Switch statement ensure 'column' as 2nd column in new deck array.
	switch (column)
	{
	case 0:
		first = 1;
		last = 2;
		break;
	case 1:
		first = 0;
		last = 2;
		break;
	case 2:
		first = 1;
		last = 0;
		break;
	}

	/* For loop to compile new deck array. Starting with column 'first',
	then column 'column', ending with column 'last'. */
	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][first];
		card++;
	}
	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][column];
		card++;

	}
	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][last];
		card++;
	}
	return;
}

/* Displays first 10 cards in deck array, then 11th card (secret card). */
void SecretCard(int deck[])
{
	int card = 0;

	cout << endl << "Finding secret card..." << endl;
	for (card = 0; card < 10; card++) // For loop to display 1st 10 cards in deck array.
	{
		PrintCard(deck[card]);
		cout << endl;
	}

	cout << endl << "Your secret card is: ";
	PrintCard(deck[card]); // Displays deck[10], or 11th card in deck array.
	cout << endl;
	return;
}
