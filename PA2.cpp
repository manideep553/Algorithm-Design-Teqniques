#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <math.h>
#include <climits>

using namespace std;
int **balcost;
int **costcal;
queue <int> q;
queue <int> q2;
queue <int> qc;
queue <int> qc1;

ofstream outputfile;

void queuefunc(int amount, int bal, int cycle, int totalcost, int firstcyclecost, int totalcycle, int *array, int *elementarray, int *costarray,int balconst)
{

	int *temparrayofcost= new int[balconst*balconst];
	int *temparrayofelements= new int[balconst*balconst];
	int *elementsofcycle = new int[bal+1];
	
	int topelement = 0;
	int topelementcost = 0;
	int rembalance = 0;
	//int sizeoftemp = pow(bal + 1, 2.0);
	int sizeoftemp =balconst*balconst;
//	cout << "sizoftemp" << sizeoftemp;
//	cout<<"hello"<<endl;

	int count1 = 0;
	
	
if(cycle<totalcycle-1)
{
	while (!q.empty())
	{
		topelement = q.front();
		topelementcost = qc.front();
		rembalance = firstcyclecost - topelement;
	//	cout<<"first cycle cost"<<firstcyclecost<<"  "<<topelement<<endl;
		for (int i = 0; i <= bal; i++)
		{
			int x = balcost[i][rembalance] + topelement;
	//		cout<<"i "<<balcost[i][rembalance];
	//		cout<<"x value"<<x<<"   ";
			int arrayelement = balcost[i][rembalance];
	//		cout<<"array element"<<arrayelement<<endl;
			int y = array[arrayelement];
			//cout<<"  "<<" y before"<<y<<endl; 
			y = y + topelementcost;
			//cout<<"  "<<" y after"<<y<<endl; 
			temparrayofcost[count1] = y;
			temparrayofelements[count1] = x;
			count1++;
		}
		q.pop();
		qc.pop();
	}
	//cout<<"size"<<sizeoftemp<<endl;
	cout<<endl;
	for (int i = 0; i < sizeoftemp; i++)
	{
		//	cout <<"data in the elemets"<< temparrayofcost[i] << "  " << temparrayofelements[i] << endl;
	}
	cout<<endl;
	cycle++;
	//	cout<<cycle;

	for (int i = 0; i <= bal; i++)
	{
		elementsofcycle[i] = (amount*cycle) + i;
	}
	
	for (int i = 0; i <= bal; i++)
	{
		int tempcost = INT_MAX;
		//cout<<elementsofcycle[i]<<endl;
		int firstelement = elementsofcycle[i];
		//cout<<"firstelement"<<firstelement<<endl;
		elementarray[i] = firstelement;

		for (int j = 0; j <= sizeoftemp; j++)
		{
			if (firstelement == temparrayofelements[j])
			{
				int costofelement = temparrayofcost[j];
				//cout<<costofelement<<endl;
				if (costofelement < tempcost)
				{
					tempcost = costofelement;
					costarray[i] = tempcost;

				}
			}

		}
		q.push(elementarray[i]);
		qc.push(costarray[i]);
			//	cout << "element     " << elementarray[i] << "mincost      " << costarray[i] << "    " << tempcost << endl;
	}
	}
	//cout << "cycle" << cycle << "total cycle" << totalcycle;

	
	
	if (cycle < totalcycle - 1)
	{
		int tar = (cycle*amount) + bal;
		queuefunc(amount, bal, cycle, totalcost, tar, totalcycle, array, elementarray, costarray,balconst);
	}
	else
	{
		//cout<<"hello this is second part";
	}


	for (int i = 0; i <= bal; i++)
	{
		//x = element
		//y = cost
		int lastelement = elementarray[i];
		int lastcost = costarray[i];
		int z = totalcost - elementarray[i];
		//cout<<"last element to be addaed"<<z;
		int lastcost1 = array[z];
		//cout<<"last cost"<<lastcost1<<endl;
		elementarray[i] = lastelement + z;
		costarray[i] = lastcost1 + lastcost;
	}

	int result = INT_MAX;
	for (int i = 0; i <= bal; i++)
	{
		//cout<<"last elements "<<elementarray[i];
		//cout<<"last costs "<<costarray[i]<<endl;

		if (costarray[i] < result)
		{
			result = costarray[i];
			//cout<<"result!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<result;
		}
	}
	cycle++;
	//cout<<"laast cycle"<<cycle;
	//cout<<"totalcycle"<<totalcycle;
	if (cycle == totalcycle)
	{
		//cout << "**********************************************************   reult   " << result << endl;
		outputfile<<result<<endl;
		return;
	}
}

int main(int argc, char *argv[])
{
	int *array = new int[10000];
	string line;
	int *elementarray, *costarray;
	int num, numsize;
	ifstream datafile;
	datafile.open(argv[3]);
	//ifstream datafile("data.txt");
	outputfile.open(argv[2]);

	if (datafile.is_open())
	{
		while (!datafile.eof())
		{
			datafile >> num >> numsize;
			array[num] = numsize;
			// cout << num <<" "<<numsize<<endl;
		}
		datafile.close();
	}
	else
	{
	//	cout << "Unable to open file";
	}
//	cout << array[10000] << endl;
	int numoflines;
	ifstream testfile;
	testfile.open(argv[1]);
	testfile >> numoflines;
//	cout << numoflines << endl;

	for (int i = 0; i < numoflines; i++)
	{
		int numofcycles, amount, balance;
		testfile >> numofcycles >> amount >> balance;

		int balconst = balance;
		balconst=balance+1;
		if (balance == 0)
		{
		//	cout << "the cost of check" << numofcycles * array[amount];
			outputfile<<numofcycles * array[amount]<<endl;
		}
		else
		{
			int totalcost = numofcycles * amount;

			balcost = new int*[balconst];
			for (int j = 0; j <balconst; j++)
			{
				balcost[j] = new int[balconst];
			}

			int taramount = amount;

			for (int j = 0; j <= balance; j++)
			{
				for (int k = 0; k <= balance; k++)
				{
					balcost[j][k] = taramount + k;
				}
				taramount--;
			}


			for (int j = 0; j <= balance; j++)
			{
				for (int k = 0; k <= balance; k++)
				{
				//	cout << balcost[j][k] << " ";
				}
				//cout << endl;
			}

			int cycle = numofcycles;

			int bal = balance;

			elementarray = new int[balconst];
			costarray = new int[balconst];
			
			for (int j = 0; j <= balance; j++)
			{
				q.push(amount + j);
				elementarray[j] = amount + j;
				qc.push(array[amount + j]);
				costarray[j] = array[amount + j];
			}

			for (int j = 0; j <= balance; j++)
			{
			//	cout << amount + j << "   ";
			//	cout << array[amount + j] << endl;
			}

			queuefunc(amount, balance, 1, totalcost, amount + bal, cycle, array, elementarray, costarray,balconst);
		
			while (!q.empty())
			{
				q.pop();
			}
			while (!qc.empty())
			{
				qc.pop();
			}
		}
	}
	cout << "output is printed to output file" ;
	return 0;
}
