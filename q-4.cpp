/*
	Submitted by : AKASH KULSHRESHTHA 
	Roll no		 : 03
	Subject		 : Design and Analysis of Algorithm
	Assignment   : 3, Section A
	Question no. : 4 
*/

#include<iostream>
#include<cstdlib>

using namespace std;


int * final_bill_board ;
			

int sumBillBoard(int * a ,int s){
										//
	int sum = 0;						//		function used to sum the selected bill board
	for (int i = 0; i < s; ++i)			//		using distance constraints
										//		i.e x1 and x2 must be t distance apart
	{									//
		sum = sum+a[i];
	}

	return sum;
}
int maxBillBoard(int * a ,int s,int temp){

	int max = 0;
	int index = 0;
	for (int i = 0; i < s; ++i)			//		function used to find max bill board 
										//		on the basis of its revenue
	{									//		( based on knapsack problem )
		if(max < a[i])					//
		{								
			max = a[i];					
			index = i;
		}
	}
	if(temp == 0)
		return max;
	else
	
		return index;
	
}


int revenueCalculator(int *bill_board, int *revenue,int n,int t,int m){
	
	int max_revenue = 0;							//
	int selected_bill_board = 0;					//		function used to find and calculate 
	int present_bill_board;							//		possible and optimal revenue for the
	for (int i = 0; i < n; ++i)						//		given problem
	{												//
			int *possible_bill_board,*possible_revenue;
			possible_bill_board = new int [n-(i+1)];
			possible_revenue = new int [n-(i+1)];
			final_bill_board = new int [n-(i+1)]; 
	
			present_bill_board = i;
			possible_bill_board[0] = bill_board[i];
			possible_revenue[0] = revenue[i]; 
			int k = 1;
			for (int j = i+1; j < n; ++j)
			{
				// checking the distane contraints with every pair or bill boards
				if( ( bill_board[i] -  bill_board[j] > t ) || ( bill_board[j] -  bill_board[i] > t ) )
				{
						possible_bill_board[k] = bill_board[j];
						possible_revenue[k] = revenue[j];
						k++;
				}

			}

	//		for (int l = 0; l < n-(i+1); ++l)
	//		{
	//			cout<<" NEW "<<l+1<<"	"<<possible_bill_board[l]<<"	"<<possible_revenue[l]<<" NEW ";
	//		}
			int r=0;
			while ( selected_bill_board + possible_bill_board[maxBillBoard(possible_revenue,n-(i+1),1)]  <= m ){
					int index = maxBillBoard(possible_revenue,n-(i+1),1);
					selected_bill_board = selected_bill_board+possible_bill_board[index];
					final_bill_board[r] = possible_bill_board[index]; 		
					max_revenue  = max_revenue + possible_revenue[index];
					possible_bill_board[index] = 0;
					possible_revenue[index] = 0;
					r++;
			}
			cout<<"\n";
	}

return max_revenue;
}


int  main(){
	int n,m;
	int *bill_board,*revenue;
	cout<<"\nEnter length of highway : ";
	cin>>m;
	cout<<"\nAssuming minimum distance between bill board is 5";
	int t = 5;
	cout<<"\nEnter no. of bill boards : ";
	cin>>n;
	bill_board = new int[n];
	revenue = new int[n];
	cout<<"Enter details : ";
	cout<<"\nS.no     Bill Board 			Revenue \n";
	for (int i = 0; i < n; ++i)
	{
		cout<<i+1<<"        ";cin>>bill_board[i];cout<<"              ";cin>>revenue[i];cout<<"\n";
	}
	int temp = revenueCalculator(bill_board,revenue,n,t,m);
//	cout<<"\nOptimal bill boards are : ";
//	int size = sizeof(final_bill_board)/sizeof(final_bill_board[0]);
//	for (int i = 0; i < size; ++i)
//	{
//		cout<<final_bill_board[i]<<" ";
//	}
	cout<<"\nMax Revenue : "<<temp<<"\n";
	return 0;
}
/*
 
 Time Complexity:-
 
 	In this process, we are computing values in the array .
	But for each element of array, array is again iterated for possible bill boards
	:: T(n) = O(n^2) 
  
  
  */
