#include<iostream>
#include<math.h>
using namespace std;

struct license{
	//structure to store license no. along with rate of growth of its price
	int license_no;
	float rate_of_growth;
};

int find_max(license l_arr[], int n){
	
	/*
	Description
	-----------
	This function returns the license_no of software having maximum rate_of_growth value in l_arr.
	
	Input variables
	---------------
	- l_arr : array of objects of license type
	- n : number of objects in array l_arr
	
	Return value
	------------
	license number with maximum rate_of_growth
	
	Side effects
	------------
	Swaps the maximum object(based on rate_of_growth) of array l_arr with the first object
	*/

	//max stores the index of license with most expensive license growth rate in array l
	int max = 0;			

	//tranversing entire array to find most expensive license
	for(int i=1;i<n;i++){
		if(l_arr[i].rate_of_growth > l_arr[max].rate_of_growth)
			max = i;
	}
	
	//Now, max index has most expensive license in l_arr, so swap it with first license object of l_arr
	swap(l_arr[0].rate_of_growth, l_arr[max].rate_of_growth);
	swap(l_arr[0].license_no, l_arr[max].license_no);	
	
	//return the license of first license object in array l_arr
	return l_arr[0].license_no;	
}

void print_order(license l_arr[], int n){
	
	//This function finds and prints the order of buying license
	
	for(int i=0; i<n; i++){
		//call to find maximum from the remaining array l[i..n-1]
		cout<<"License "<<find_max((l_arr+i), n-i);
		cout<<"  : Rate "<<l_arr[i].rate_of_growth<<endl;
	}
}

float amount(license l_arr[], int n){

	/*
	Description
	-----------
	This function returns the total minimized amount to be spend to buy license 
	
	Input variables
	---------------
	- l_arr : array of objects of license type
	- n : number of objects in array l_arr
	Return value
	------------
	None
		
	Side effects
	------------
	Sorts l_arr in decreasing order of rate_of_growth and prints this sorted array.
	*/
	
	float amount  = 0;
	for(int i=0; i<n; i++){
		amount += pow(l_arr[i].rate_of_growth, i); 
	}
	return amount*100;
}
int main(){

	int n;
	cout<<"\t\t\tSOFTWARE LICENSE PROBLEM\n";
	
	while(true){
		cout<<"\n\nEnter number of cryptographic softwares : ";
		cin>>n;	
		if(n>=1)		//number of software must be atleast 1
			break;
		else
			cout<<"\nNo. of softwares should be atleast 1!";
	}
	license *l = new license[n];
	//input rate
	for(int i=0; i<n; i++){
		
		float temp;
		cout<<"\n\nEnter rate of growth for license "<<i+1<<" : ";
		cin>>temp;
		//test whether rate entered is greater than 1 or not
		if(temp <= 1){
			cout<<"\nrate must be greater than 1!";
			i--;
			continue;
		}
		l[i].license_no = i+1;
		l[i].rate_of_growth = temp;
	}
	
	cout<<"\n\nOrder of buying license is \n\n";
	print_order(l, n);

	cout<<"\n\nMinimized amount is : $"<<amount(l, n);
}

________________________________________________________________________________________________________________________________________
.................................................PROGRAMMING APPROACH..................................................................
1. Greedy
2. Iterative

________________________________________________________________________________________________________________________________________
...................................................EXPLANATION.........................................................................

Data structure
	--------------

	- license => {license_no, rate_of_growth}

	- license_no : It refers to the number associated to a license
	- rate_of_growth : the rate by which the price of a license is increasing every month

======================================================================================================================

	-------------------------------
	Function 1 : find_max(l_arr, n)
	-------------------------------

	**********
	Pseudocode
	**********

	find_max(l_arr, n):
    	1.	max = 0
	2.	for i = 1 to n
	3.		if l_arr[i].rate_of_growth > l_arr[max].rate_of_growth	
	4.			max = i
	5.	swap(l_arr[0].rate_of_growth, l_arr[max].rate_of_growth)
	6.	swap(l_arr[0].license_no, l_arr[max].license_no)
	7.	return l_arr[0].license_no

	Description
	-----------
	find_max(l_arr, n) returns the license_no of software having maximum rate_of_growth value in l_arr.
	
	Input variables
	---------------
	- l_arr : array of objects of license type
	- n : number of objects in array l_arr
	
	Return value
	------------
	license number with maximum rate_of_growth
	
	Side effects
	------------
	Swaps the maximum object(based on rate_of_growth) of array l_arr with the first object

======================================================================================================================
	
	----------------------------------
	Function 2 : print_order(l_arr, n)
	----------------------------------
	
	**********
	Pseudocode
	**********

	print_order(l_arr, n):
	1.	for i = 1 to n
	2.		print find_max(l_arr[i..n], n-i)

	Description
	-----------
	print_order(l_arr, n) function finds and prints the order of buying license to minimize cost.

	Input variables
	---------------
	- l_arr : array of objects of license type
	- n : number of objects in array l_arr

	Return value
	------------
	None
		
	Side effects
	------------
	Sorts l_arr in decreasing order of rate_of_growth and prints this sorted array.

======================================================================================================================

	Approach
	--------
	To minimize the cost, license with most expensive rate of growth must be bought first.
	The solution is to find maximum, then second maximum, then third maximum and so on. 
	Since we are interested in immediate best choice, it is a greedy algorithm.
	It can be achieved by sorting the array which will take at best O(nlogn) [merge sort, heap sort].
	We were given the flexibility to find solution in polynomial of n time. 
	So, here is a more ituitive solution.
	The approach is to find maximum of entire array, print the license number and swap it with the beginning of array. 
 	Now, to find second maximum
	find the maximum of l_arr[2..n], since the first maximum is stored at location l_arr[1].
	Similarly find subsequent maximum and print it.
	
----------
Complexity
----------

Total no. of software license to buy = n

The find_max() function works in linear time, 
line 1, 5-7 take constant time. 
loop line 2-4 of function1 iterates n times.

print_order() calls the function find_max() n times, function2 line 1-2.

Therefore, total time complexity is O(n^2). 

Time complexity:	O(n^2)

--------------------------------------------------
Member 1 = Harshul Kumar(14)
Member 2 = Akash (03)
