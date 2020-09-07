#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int main(void){

	//const char* passbuf = "mkdir a";
	system("raspivid -o video.mp4 -t 10000");
	cout << "helloworld" << endl;
	return 0;
}                                                                                                                                                     
                                                
