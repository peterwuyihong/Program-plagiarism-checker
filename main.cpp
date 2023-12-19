#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=j;i<=(k);i++)
#define per(i,j,k) for(int i=j;i>=(k);i--)
#define all(x) x.begin(),x.end()
const int p=43;
struct Hash{
  string a[10];
  int id[10];
  int tot;
  Hash(){tot=0;}
}H[43];
int Hash(string s){
  int a=0;
  return (s[0]*100+s[s.size()-1])%41;
  rep(i,0,s.size()-1)a=(a*89+s[i]-'a'+p*100)%p;
  return a;
}
int ge(string &str){
	char c=getchar();str.clear();
	if(c==EOF)return 0;
	while(!isalpha(c)&&c!='_'){
		c=getchar();
		if(c==EOF)return 0;
	}
	while(isalpha(c)||c=='_')str.push_back(c),c=getchar();
	return 1;
}
string dic[100];
int n;
int a[100],b[100];
signed main(){
	string fa,fb;
	cout<<"输入判断哪两个程序相似情况"<<endl;
	cin>>fa>>fb;
  freopen("key.txt","r",stdin);
  string s;
	while(ge(s)){
		dic[++n]=s;
		int u=Hash(s);
		H[u].a[++H[u].tot]=s;
		H[u].id[H[u].tot]=n;
	}
	rep(i,0,42)cout<<H[i].tot<<endl;
	freopen(fa.data(),"r",stdin);
	int cnt=0;
	double times=0;
	while(ge(s)){
		int u=Hash(s);
		if(H[u].tot)cnt++;
		rep(i,1,H[u].tot){
			times++;
			if(H[u].a[i]==s){
				a[H[u].id[i]]++;
				break;
			}
		}
	}
	printf("平均查找次数为%.2lf\n",times/cnt);
	rep(i,1,n)printf("%s %d \n",dic[i].data(),a[i]);
	puts("");
	freopen(fb.data(),"r",stdin);
	cnt=0;
	times=0;
	while(ge(s)){
		int u=Hash(s);
		if(H[u].tot)cnt++;
		rep(i,1,H[u].tot){
			times++;
			if(H[u].a[i]==s){
				b[H[u].id[i]]++;
				break;
			}
		}
	} 
	printf("平均查找次数为%.2lf\n",times/cnt);
	rep(i,1,n)printf("%s %d \n",dic[i].data(),b[i]);
	puts("");
	rep(i,1,n)printf("%d ",a[i]);puts("");
	rep(i,1,n)printf("%d ",b[i]);puts("");
	int up=0;
	rep(i,1,n)up+=a[i]*b[i];
	double A=0;
	rep(i,1,n)A+=a[i]*a[i];
	double B=0;
	rep(i,1,n)B+=b[i]*b[i];
	A=sqrt(A),B=sqrt(B);
	double ans=up/A/B;
	printf("余弦相似度为%.6lf\n",ans);
	if(ans<0.85){
		puts("不相似"); 
	}else{
		double d=0;
		rep(i,1,n)d+=(a[i]/A-b[i]/B)*(a[i]/A-b[i]/B);
		d=sqrt(d);
		printf("几何距离%.6lf\n",d);
		if(d<0.25)puts("确实可能相似");
		else puts("可能不相似");
	}
}
