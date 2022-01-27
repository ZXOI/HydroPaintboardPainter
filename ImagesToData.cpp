#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
char cmd[1024];
int main()
{
	fstream fi;
	fi.open("ImagesToData.cfg",ios::in);
	string p;
	int x,y;
	system("del tasks.txt");
	while(fi>>p>>x>>y)
	{
		sprintf(cmd,"python ImageToData.py %s %d %d",p.c_str(),x,y);
		system(cmd);
	}
}