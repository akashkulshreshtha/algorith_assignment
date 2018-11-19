#include<iostream>

using namespace std;

bool **adj_matrix;
bool *isPotential;

int countknown(int n, int person_x)
{
	/*
	Description
	-----------
	This function calculates number of people that a person_x knows.
	
	Input variables
	---------------
	- n : size of array isPotenital
	- person_x : person for which number of his/her acquaintance has to be calculated
	
	Global variable
	---------------
	- isPotenital : a boolean array, where value of isPotenital[i] states whether a person i can considered for invititation. True, if yes. False, if no.
	
	Return value
	------------
	number of people that person_x knows
	*/
	
	int count=0;
	for(int i=1; i<=n; i++){
		// test whether person i is a potenital invitee and also if person i and person_x know each other 
		if(isPotential[i] && adj_matrix[i][person_x])
			count++;
	}
	return count;
}	

void plan_party(int n){
	
	/*
	Description
	-----------
	This function computes all persons who can be invitated for a party out of n people based on following conditions:
		1. Every person invited should know at least five other people that are invited.
		2. Every person invited should not know at least five other people that are invited.
		3. Number of invitees is maximized
	
	Input variable
	--------------
	- n : Number of people to choose from
	
	Global variables
	----------------
	- adj_matrix : a boolean 2D matrix, where value at adj_matrix[x][y] states whether person x knows person y. True, if yes. False, if no.
	- isPotenital : a boolean array, where value at isPotenital[i] states whether a person i can considered for invititation. True, if yes. False, if no.
	Return value
	------------
	None
	
	Side effects
	------------
	If either condition 1 or condition 2 is not true for a person x then, update isPotenital[x] to false
	
	*/
	
	int potential_count = n;
	for(int j=1; j<=n; j++)
	{
			//stores the number of people j knows
			int known = countknown(n,j);
			//stores the number of people j does not know
			int unknown = potential_count - known - 1;
			
			//if a potenital invitee disqualifies any of condition 1 or 2, make him invalid and start checking from person 1 again
			if( isPotential[j] && (known < 5 || unknown < 5) )
			{
				isPotential[j]=false;
				potential_count--;
				j = 0;
				//if number of potenital invitee become less than 11, there is no way we can find a person who know 5 person and does not know 5 person
				if(potential_count < 11){
					for(int i=1;i<=n;i++)
						isPotential[i] = false;
					break;
				}
			}	
	}//the loop ends when every potential invitee satisfy both condition 1 and 2 or everyone become impotential
	
}

void print_invitees(int n){
	
	/*Description
	  -----------
	  This function print the final invitees and the count of invitees.
	*/ 
	int count = 0;
	cout<<"\n\nAlice can invite following people\n\n";
	for(int i=1; i<=n; i++){
		if(isPotential[i]){
			cout<<i<<"\t";
			count++;
		}
	}
	if(count == 0)
		cout<<"\n\nNo one can be invited.";
	else
		cout<<"\n\nMaximum number of people who can be invited is : "<<count;			
	
}
int main()
{
	int n;
	while(true){
		cout<<"\nEnter value of n(greater than or equal to 11): ";
		cin>>n;
		if(n>=11)
			break;
	}
	
	//dyanamic allocation
	adj_matrix = new bool*[n+1];
	for(int i=0;i<=n;i++)
		adj_matrix[i] = new bool[n+1];

	isPotential = new bool[n+1];
	
	//initialize adj_matrix such that nobody knows anyone
	for(int i=1; i<=n; i++)
	{
		isPotential[i] = true;
		for(int j=1; j<=n; j++)
		{
			adj_matrix[i][j] = false;
		}
	}
	
	char choice;
	
	//input pairs
	while(true) 
	{
		int x, y;
		cout<<"\nEnter pair (x,y) who know each other(person number starts from 1 and goes till n) \n";
		cout<<"\n Person x : ";
		cin>>x;
		if(x<1 || x>n){
			cout<<"\nInvald pair!Enter again!\n";
			continue;
		}
		cout<<"\n Person y : ";
		cin>>y;
		if(y<1 || y>n || y == x){
			cout<<"\nInvald pair!Enter again!\n";
			continue;
		}
		//update adjacency matrix
		adj_matrix[x][y] = true;
		adj_matrix[y][x] = true;
		cout<<"\nAre there any more pairs who know each other?(y/n): ";
		cin>>choice;
		if(choice=='n')
			break;
		x++; 
		y++;
	}
	plan_party(n);
	print_invitees(n);
	return 0;
}

____________________________________________________________________________________________________________________________________
.......................................................PROGRAMMING APPROACH.......................................................

1. Greedy
2. Iterative

__________________________________________________________________________________________________________________________________
...........................................................EXPLANATION..........................................................

Global variables
	----------------
	
	- adj_matrix : a boolean 2D matrix, where value at adj_matrix[x][y] states whether person x knows person y. True, if yes. False, if no.
	- isPotenital : a boolean array, where value at isPotenital[i] states whether a person i can considered for invititation. True, if yes. 
			False, if no.
	
======================================================================================================================
	
	--------------------------------------
	Function 1: countknown(n, person_x)
	--------------------------------------
 
	**********
	Pseudocode
	**********

	countknown(n, person_x)
    	1.	count = 0;
    	2.	for i = 1 to n
    	3.		if isPotential[i] == true and adj_matrix[i][person_x]
    	4.			count = count + 1
      	5.	return count

	Description
	-----------
	The function countknown(n, person_x) calculates number of people that a person_x knows.
	
	Input variables
	---------------
	
	- n : size of array isPotenital
	- person_x : person for which number of his/her acquaintance has to be calculated
	
	Return value
	------------
	number of people that person_x knows

======================================================================================================================

	-------------------------
	Function 2: plan_party(n)
	-------------------------

	**********
	Pseudocode
	**********

	plan_party(n):
	1.	potential_count = n;
	2.	for j = 1 to n
	3.		known = countknown(n,j);
	4.		unknown = potential_count - known - 1;
	5.		if isPotential[j] and (known < 5 or unknown < 5) 
	6.			isPotential[j] = false
	7.			potential_count = potential_count - 1
	8.			j = 0
	9.			if potential_count < 11
	10.				for i = 1 to n
	11.					isPotential[i] = false
	12.				break	

	Description
	-----------
	This function computes all persons who can be invitated for a party out of n people based on following conditions:
		1. Every person invited should know at least five other people that are invited.
		2. Every person invited should not know at least five other people that are invited.
		3. Number of invitees is maximized
	
	Input variable
	--------------
	- n : Number of people to choose from
	
	Return value
	------------
	None
	
	Side effects
	------------
	If either condition 1 or condition 2 is not true for a person x then, update isPotenital[x] to false

======================================================================================================================

	-----------------------------
	Function 3: print_invitees(n)
	-----------------------------
	
	**********
	Pseudocode
	**********

	print_invitees(n):
	1.	count = 0
	2.	for i = 1 to n
	3.		if isPotential[i] == true
	4.			print i
	5.			count = count + 1
	6.	print count

	Description
	-----------
	print_invitee(n) function prints the final invitees and the count of invitees.		

======================================================================================================================	

	Approach
	--------
	Initially, zero people are removed. Check for condition 1 and 2 for every person.
	Whenever a failure occur remove that person and start all over again with remaining persons.
	Stop when no one will fail the conditions or everyone fails it.
 
----------
Complexity
----------

Function 1:

line 1 		-> O(1)
loop 2-4	-> O(n)	linear time
line 5		-> O(1)

--------------------------------------------------

Function 2:

line 1		-> O(1)
line 2		-> j iterates from 1 to n, 
line 3		-> O(n) it makes a call to countknown in every iteration
line 4		-> O(1)
line 5		-> if the condition in this line is satisfied, the value of j is again set to 1.
		   which implies there will be more than n iterations in line 2. In worst case value of j is set to 1 by every value of j,
		   therefore the main loop runs atmost n^2 times.
line 6-8	-> O(1)
line 9		-> if this condition is true, we will come out of the main loop. and line 10-11 will iterate n times but only once, hence it 			   will not effect the degree of time complexity

--------------------------------------------------

Since, countknown is called atmost n^2 time. 

	Time complexity  = O(n^3)
	Space complexity = O(n^2)


--------------------------------------------------
Member 1 = Harshul Kumar(14)
Member 2 = Akash (03)
