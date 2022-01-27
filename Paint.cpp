#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int cookieRechargeTime = 10000;
string getBoardCmd=(string)"curl \"https://hydro.ac/api\" -X POST "+
"-H \"User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:96.0) Gecko/20100101 Firefox/96.0\" "+
"-H \"Accept: */*\" "+
"-H \"Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\" "+
"-H \"Accept-Encoding: gzip, deflate, br\" "+
"-H \"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\" "+
"-H \"Referer: https://hydro.ac/paintboard\" "+
"-H \"X-Requested-With: XMLHttpRequest\" "+
"-H \"Origin: https://hydro.ac\" "+
"-H \"Sec-Fetch-Dest: empty\" "+
"-H \"Sec-Fetch-Mode: cors\" "+
"-H \"Sec-Fetch-Site: same-origin\" "+
"-H \"Connection: keep-alive\" "+
"-H \"Cookie: \"%s\" \" "+
"--data-raw \"query=\"%\"7Bpaintboard\"%\"7Bboard\"%\"7D\"%\"7D\" "+
"-s";
string paintPixelCmd=(string)"curl \"https://hydro.ac/api\" -X POST "+
"-H \"User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:96.0) Gecko/20100101 Firefox/96.0\" "+
"-H \"Accept: */*\" "+
"-H \"Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\" "+
"-H \"Accept-Encoding: gzip, deflate, br\" "+
"-H \"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\" "+
"-H \"Referer: https://hydro.ac/paintboard\" "+
"-H \"X-Requested-With: XMLHttpRequest\" "+
"-H \"Origin: https://hydro.ac\" "+
"-H \"Sec-Fetch-Dest: empty\" "+
"-H \"Sec-Fetch-Mode: cors\" "+
"-H \"Sec-Fetch-Site: same-origin\" "+
"-H \"Connection: keep-alive\" "+
"-H \"Cookie: \"%s\" \" "+
"--data-raw \"query=\"%\"7Bpaintboard\"%\"7Bpaint(x\"%\"3A%d\"%\"2Cy\"%\"3A%d\"%\"2Ccolor\"%\"3A%d)\"%\"7D\"%\"7D\" "+
"-s";
int trans(char x)
{
	if(isdigit(x))
		return x-'0';
	if(isalpha(x))
		return 10+x-'a';
	return -1;
}
struct Pixel
{
	int x,y,c;
};
string unZipCmd="bz.exe x -aoa -y %s";
char cmd[65536];
const int boardw=1000,boardh=600;
vector<string> cookies;
int usedCookie=-1;
string boards[610];
int boardNow[1100][610],boardWnt[1100][610];
int wntCnt=0;
void getBoardWnt()
{
	fstream f;
	f.open("tasks.txt",ios::in);
	int x,y,c;
	for(int i=0;i<boardw;i++)
	{
		for(int j=0;j<boardh;j++)
		{
			boardWnt[i][j]=-1;
		}
	}
	while(f>>x>>y>>c)
	{
		boardWnt[x][y]=c;
		wntCnt++;
	}
}
void getCookies()
{
	fstream f;
	f.open("Cookies.txt",ios::in);
	string str;
	while(getline(f,str))
	{
		cookies.push_back(str);
		cout<<"Cookie #"<<cookies.size()<<" : "<<str<<endl;
	}
}
string getCookie()
{
	usedCookie=(usedCookie+1)%cookies.size();
	return cookies[usedCookie];
}
void getBoardNow()
{
	system("del board*");
	sprintf(cmd,(getBoardCmd+" > board.br").c_str(),getCookie().c_str());
//	printf("Command : %s\n",cmd);
	system(cmd);
	sprintf(cmd,(unZipCmd+" > rb").c_str(),"board.br");
	system(cmd);
	system("rename board board.txt > rb");
	fstream fb;
	fb.open("board.txt",ios::in);
	string str="";
	fb>>str;
	for(int i=0,pl=str.find('[',0),pr=pl;i<boardh;i++,pl=pr+1)
	{
		pl=str.find('\"',pl);
		pr=str.find('\"',pl+1);
		boards[i]=str.substr(pl+1,pr-pl-1);
	}
	for(int i=0;i<boardh;i++)
	{
		for(int j=0;j<boardw;j++)
		{
			boardNow[j][i]=(i>0&&j>0?trans(boards[i][j]):-1);
		}
	}
}
vector<Pixel> compareBoard()
{
	vector<Pixel> ans;
	ans.clear();
	for(int i=0;i<boardw;i++)
	{
		for(int j=0;j<boardh;j++)
		{
			if(boardWnt[i][j]==-1)
				continue;
			if(boardNow[i][j]!=boardWnt[i][j])
			{
				// cout<<"diff <"<<i<<","<<j<<"> : "<<boardNow[i][j]<<" != "<<boardWnt[i][j]<<endl;
				ans.push_back((Pixel){i,j,boardWnt[i][j]});
			}
		}
	}
	return ans;
}
bool paintPixel(Pixel p)
{
	string cookie;
	sprintf(cmd,(paintPixelCmd+" > paint.out").c_str(),(cookie=getCookie()).c_str(),p.x,p.y,p.c);
	system(cmd);
	fstream fo;
	fo.open("paint.out",ios::in);
	string s;
	fo>>s;
	if(s=="{\"data\":{\"paintboard\":{\"paint\":null}}}")
	{
		cout<<"Painted pixel <"<<p.x<<","<<p.y<<","<<p.c<<">"<<endl;
		return 1;
	}
	else
	{
		cout<<"Failed to paint pixel <"<<p.x<<","<<p.y<<","<<p.c<<">"<<endl;
		return 0;
	}
}
int main()
{
	getCookies();
	getBoardWnt();
	int rcnt=0;
	while(1)
	{
		rcnt++;
		getBoardNow();
		cout<<"Start cycle "<<rcnt<<endl;
		vector<Pixel> need=compareBoard();
		cout<<"Compare result : "<<need.size()<<"/"<<wntCnt<<" needed to paint";
		cout<<" ("<<1.0*(wntCnt-need.size())/wntCnt*100<<"% completed)"<<endl;
		for(int i=0;i<need.size();i++)
		{
			if(!paintPixel(need[i]))
				i--;
			cout<<"Cycle "<<rcnt<<" : "<<i+1<<"/"<<need.size()<<" painted ";
			cout<<"("<<1.0*(i+1)/need.size()*100<<"% completed)"<<endl;
			Sleep(cookieRechargeTime/cookies.size()+500);
		}
		Sleep(10000);
	}
}
