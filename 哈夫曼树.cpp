#include <iostream>
#include <cstdint>
#include "二叉树.h"



int32_t main() {
	//英文字母使用频率表:(%)
	//A 8.19,B 1.47,C 3.83,D 3.91,E 12.25,F 2.26,G 1.71,H 4.57,I 17.10 J,0.14
	//K 0.41,L 3.77,M 3.34,N 7.06,O 7.26,P 2.89,Q 0.09,R 6.85,S 6.36,T 9.41
	//U 2.58,V 1.09,W 1.59,X 0.21,Y 1.58,Z 0.08
	double frequency[26] = { 8.19,1.47,3.83,3.91,12.25,2.26,1.71,4.57,7.10,
		0.14,0.41,3.77,3.34,7.06,7.26,2.89,0.09,6.85,6.36,9.41,2.58,1.09
		,1.59,0.21,1.58,0.08 };
	int32_t arr_size = 26;
	for (int32_t i = 0; i < arr_size; i++) {
		for (int32_t j = i; j < arr_size; j++) {
			if (frequency[i] > frequency[j]) {
				//cout << frequency[i] << " " << frequency[j] << endl;
				double temp = frequency[j];
				frequency[j] = frequency[i];
				frequency[i] = temp;
			}
		}
		//cout << frequency[i] << endl;
	}

	int32_t num_layers = arr_size - 1;
	int32_t WPL = 0;
	for (int32_t i = 0; i < arr_size - 1; i++, num_layers--) {
		double data1 = frequency[i];
		double data2 = frequency[i + 1];
		//cout << data1 << " " << data2 << endl;

		if (num_layers == 1) 
			cout << "num_layers:" << num_layers << endl;
		frequency[i + 1] = data1 + data2;
		if (i == 0) 
			WPL += num_layers * (data1 + data2);
		else
			WPL += num_layers * frequency[i + 1];
		cout << WPL << endl << data1 << " " << data2 << endl << num_layers << endl;
	}
	//cout << frequency[25] << endl;;
	cout << WPL << endl;




	return 0;
}