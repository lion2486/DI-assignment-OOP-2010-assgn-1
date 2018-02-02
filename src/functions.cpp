#include "classes.h"

using namespace std;

passenger::passenger(double *tmp)
:bust(false),money(tmp)
{
	if(rand()%2 == 1)
		half = false;
	else
		half = true;
	if(rand()%2 == 0){
		ticket = true;
		if(half)
//			train::add_money(hprice);
			*money += hprice;
		else
			*money += price;
	}
	else
		ticket = false;

}
bool passenger::have_ticket(){
	return ticket;
}
bool passenger::half_ticket(){
	return half;
}


waggon::waggon(double *tmp)
:Capacity(0), illegal(0), illegal_unchecked(0),money(tmp)
{
	pas = new passenger*[maxCapacity];
	for(int i=0;i<maxCapacity;i++)
		pas[i] = NULL;
	cout << "A waggon with capacity for " << maxCapacity << " passengers, was created" << endl;
}
waggon::~waggon(){
	for(int i=0; i<maxCapacity; i++)
		delete pas[i];
	delete[] pas;
	cout << "A waggon was destroyed" << endl;
}
void waggon::out(int k){
	if(k>0 && k <= Capacity)
	{
		for(int i=Capacity-k;i<Capacity-1;i++)
		{
			delete pas[i];
			pas[i] = NULL;
		}
		Capacity -= k;
	}
	return;
}
void waggon::in(int k){
	if(k>0 && Capacity+k <= maxCapacity){
		for(int i=Capacity;i<Capacity+k-1;i++)
			pas[i] = new passenger(money);
		Capacity += k;
	}
	return;
}
int waggon::inStation(bool last){
	if(last){
		out(Capacity);
		return 0;
	}
	for(int i=0;i<Capacity;i++)
		if(pas[i] != NULL)
			if(pas[i]->busted())
				deposit(i);
	out(rand()%(Capacity+1));
	in(rand()%(maxCapacity-Capacity+1));
	if(rand()%2 == 0)
		check = true;
	else check = false;
	return 0;
}
void waggon::deposit(int i){
	if(pas[i]->half_ticket())
		*money += rate * passenger::hprice;
	else
		*money += rate * passenger::price;
	delete pas[i];
	for(int j=i;j<Capacity-1;j++)
		pas[j] = pas[j+1];
	Capacity--;
	return;
}
int waggon::betweenStations(bool last){
	if(last)
		return 0;
	for(int i=0;i<Capacity;i++){
		if(pas[i]!=NULL)
			if(!(pas[i]->have_ticket())){
				if(check){
					illegal++;
					pas[i]->busted(true);
				}
				else
					illegal_unchecked ++;
			}
	}
	return 0;
}
int waggon::printStatistics(int i){
	cout << "There was " << illegal << " illegal passengers in waggon(" << i << ")" << endl;
	cout << "There was " << illegal_unchecked << " illegal passengers unchecked in waggon(" << i << ")" << endl;
	return 0;
}

train::train(int a)
:N(a),money(0)
{
	wa = new waggon*[totalWaggons];
	for(int i=0; i<totalWaggons; i++)
		wa[i] = new waggon(&money);
	cout << "A metro train with " << totalWaggons << " waggons, was created" << endl;
}

train::~train(){
	int i = totalWaggons;
	while(i--)
		delete wa[i];
	delete[] wa;
	cout << "A metro train was destroyed" << endl ;
}
int train::operate(){
	for(int j=0;j<N;j++)
	{
		for(int i=0; i<totalWaggons; i++)
			wa[i]->inStation((j==N-1)?true:false);
		for(int i=0; i<totalWaggons; i++)
		 	wa[i]->betweenStations((j==N-1)?true:false);
	}
	return 0;
}
int train::printStatistics(){
	cout << "A metro train was operated for " << N << " stations" << endl;
	for(int i=0; i<totalWaggons; i++)
		wa[i]->printStatistics(i);
	cout << "The money that collected are: " << money << endl;
	return 0;
}
void train::add_money(double i){
	money += i;
	return;
}
