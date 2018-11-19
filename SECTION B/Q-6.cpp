
#include<iostream>
#include<math.h>

using namespace std; 

bool equivalenceTester(int a, int b)
{
	/*
	Description
	-----------
	This function tests whether two cards belong to same account.
	
	Input variables
	---------------
	- a : account number for card 1
	- b : account number for card 2
	Return value
	------------
	True, if both cards belong to same account.
	False, if both cards belong to different account.
	*/

	if(a==b) 
		return true;
	else
		return false;
}

int frequency(int card, int cards[], int n)
{
	/*
	Description
	-----------
	This function calculates the number of cards associated to same account as that of the card passed to this function.
	
	Input variables
	---------------
	- card : holds the account number of card to be tested.
	- cards : array of cards
	Return value
	------------
	returns the number of cards associated to same account as that of the card passed to this function.
	*/

	int count=0;
	for(int i=0; i<n; i++)
	{
		if(equivalenceTester(cards[i],card))
			count++;
	}
	return count;
}

int majority_card(int cards[], int n) 
{
	/*
	Description
	-----------
	This function returns the account which has more than n/2 cards asociated to it.
	
	Input variables
	---------------
	- cards : an array of account numbers of all cards.
	- n : total number of cards
	Return value
	------------
	account number of majority  card or -1 if there is no majority card	
	*/

	// if there is only one card, it is majority in itself
	if(n==1) 				
		return cards[0];
	int left_majority_freq;
	int right_majority_freq;
	int left_majority_card;
	int right_majority_card;
	int mid = floor(n/2);	
	int *left_subcards = new int[mid];
	int *right_subcards = new int[n - mid];

	for(int i = 0; i < mid; i++)
		left_subcards[i] = cards[i];
	int j = 0;
	for(int i = mid; i < n; i++)
		right_subcards[j++] = cards[i];
	
	//recursive calls
	left_majority_card = majority_card(left_subcards,mid);
	right_majority_card = majority_card(right_subcards,n-mid);
	
	if(equivalenceTester(left_majority_card, right_majority_card)) 
		return left_majority_card;
	
	left_majority_freq = frequency(left_majority_card, cards, n);
	right_majority_freq = frequency(right_majority_card, cards, n);

	if(left_majority_freq > mid) 
		return left_majority_card;
	if(right_majority_freq > mid) 
		return right_majority_card; 
	return -1;
}

int main() 
{
	int *bankcards, N;
	cout<<"\t\t\tBANKCARDS PROBLEM\n\n";
	while(true){	
		cout<<"\nEnter number of cards: ";
		cin>>N;
		if(N>=1)
			break;
		cout<<"\nNumber of card should be atleast 1!";
	}

	bankcards = new int[N];
	
	for(int i=0; i<N; i++)	
	{	
		cout<<"\n\nEnter account number for card "<<i+1<<" : ";
		cin>>bankcards[i];
	}

	//test whether there is a majority card in given bankcards
	if(majority_card(bankcards, N) != -1)
		cout<<"\n\nThere is a majority card. \n";
	else		
		cout<<"\n\nThere is not any majority card. \n";	
	return 0;
}

_______________________________________________________________________________________________________________________________________
................................................ PROGRAMMING APPROACH...............................................................
1. Divide and Conquer
2. Recursion

______________________________________________________________________________________________________________________________________
......................................................EXPLANATION.......................................................................

	---------------------------------
	Function 1: equivalentTester(a,b)
	---------------------------------

	**********
	Pseudocode
	**********

	equivalentTester(a,b):
	1.	if a == b
	2.		return true
	3. 	return false

	Description
	-----------
	equivalentTester(a,b) function tests whether two cards belong to same account.
	
	Input variables
	---------------
	- a : account number for card 1
	- b : account number for card 2

	Note: we are using account number just because we cannot replicate 
	      real cards. Anyhow, the main idea was that we can not perform > or <
	      operation on cards. Only == operator can be used, and that is being followed.
   
	Return value
	------------
	True, if both cards belong to same account.
	False, if both cards belong to different account.

======================================================================================================================

	-----------------------------------
	Function 2 : frequency(card, cards)
	-----------------------------------
	
	**********	
	Pseudocode
	**********

	frequency(card, cards):
	1.	count=0;
	2.	for i = 1 to N 
	3.		if equivalenceTester(cards[i],card) == true
	4.			count++
	5.	return count

	Description
	-----------
	frequency(card) function calculates the number of cards associated to same account as that of the card passed to this function.
	frequency of card in cards

	Input variables
	---------------
	- card : holds the account number of card to be tested.
	- cards : array of cards

	Return value
	------------
	returns the number of cards associated to same account as that of the card passed to this function.

======================================================================================================================

	------------------------------------
	Function 3 : majority_card(cards, n)
	------------------------------------

	**********
	Pseudocode
	**********

	majority_card(cards[1..n], n):
	1.	if n == 1
	2.		return cards[1]
	3.	mid = floor(n/2)
	4.	left_majority_card = majority_card(cards[1...mid], mid)
	5.	right_majority_card = majority_card(cards[mid+1...n], n-mid)
	6.	if equivalenceTester(left_majority_card, right_majority_card) == true:
	7.		return left_majority_card
	8.	left_majority_freq = frequency(left_majority_card, cards[1..n])
	9.	right_majority_freq = frequency(right_majority_card, cards[1..n])
	10.	if left_majority_freq > mid+1:
	11.		return left_majority_card
	12.	if right_majority_freq > mid+1:
	13.		return right_majority_card
	14.	return NO-MAJORITY-CARD

	Description
	-----------
	This function returns the account which has more than n/2 cards asociated to it.
	
	Input variables
	---------------
	- cards : an array of account numbers of all cards local to a recursive call.
	- n : total number of cards local to a recursive call

	Return value
	------------
	account number of majority  card or NO-MAJORITY-CARD if there is no majority card	

======================================================================================================================

--------
Approach
--------
We split the array A into 2 subarrays A1 and A2 of half the size. We choose the majority element of A1 and A2. 
After that we do a linear time equality operation to decide whether it is possible to find a majority element. 	

----------
Complexity
----------

Function 1: O(1)

line 1-3 	-> O(1)

--------------------------------------------------

Function 2: O(n)

line 1		-> O(1)
line 2-4	-> O(n) loop iterates n times and each iteration take constant time
line 5		-> O(1)

--------------------------------------------------

Function 3: O(nlogn)

line 3		-> Divide step 	 O(1) , divides the problem of size n into two subproblems of size floor(n/2) and n-floor(n/2)
line 4-5	-> Conquer	
		   Recurrence relation : T(n) = T(floor(n/2)) + T(n-floor(n/2)) + O(n)
					      = 2T(n/2) + O(n)
line 1-2	   Base case	       : T(1) = O(1)
line 4-12	-> Combine	O(n)	call to frequency() is made

--------------------------------------------------

	On applying masters theorem, case 2 is observed, therefore T(n) = O(nlogn)

	Time complexity = O(nlogn)

--------------------------------------------------
Member 1 = Harshul Kumar(14)
Member 2 = Akash (03)
