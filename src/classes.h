#ifndef CLASSES_H_
#define CLASSES_H_
#include <iostream>

class passenger{
private:
        bool ticket;
        bool half;
        bool bust;
        double *money;
public:
        static const double price = 1.00;
        static const double hprice = 0.50;
        passenger(double *);
        bool have_ticket();
        bool half_ticket();
        bool busted(bool flag = false) {
        	if(flag)
        		bust = true;
        	return bust;
        }
};


class waggon{
private:
	static const int maxCapacity = 60; /*Max passenges in a waggon setted to 60 */
	int Capacity;
	passenger ** pas;
	bool check;
	int illegal;
	int illegal_unchecked;
	double *money;
	static const int rate = 60;
public:
	waggon(double *);
	~waggon();
	int inStation(bool);
	int betweenStations(bool);
	int printStatistics(int);
	bool checked(){ return check; }
	void out(int);
	void in(int);
	void deposit(int);

};
class train{
private:
	static const int totalWaggons = 10;
	int N;
	double money;
	waggon **wa;
public:
	train(int);
	~train();
	int operate();
	int printStatistics();
	void add_money(double i);
};







#endif /* CLASSES_H_ */
