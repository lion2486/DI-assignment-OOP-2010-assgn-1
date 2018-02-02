#include <iostream>
#include "classes.h"

using namespace std;

int main(int argc, char * argv[]){
	int N;
	if(argc < 2)
	{
		cout << "Give the number of the stations: " << endl;
		scanf("%d", &N);
	}
	else
		N = atoi(argv[1]);
	srand(time(NULL));
	train tr(N);
	tr.operate();
	tr.printStatistics();
	return 0;
}


