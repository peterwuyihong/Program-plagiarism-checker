#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=j;i<=(k);i++)
#define per(i,j,k) for(int i=j;i>=(k);i--)
#define all(x) x.begin(),x.end()
const int p=43;
struct Hash{//�����ϣ�� 
  string a[10];//ÿ����ϣֵ��һ������ 
  int id[10];//����ֻ��Ҫ��β������� 
  int tot;//������Ҳ���� 
  Hash(){tot=0;}
}H[43];
int Hash(string s){//�����ϣ���� 
  int a=0;
  return (s[0]*100+s[s.size()-1])%41;
  rep(i,0,s.size()-1)a=(a*89+s[i]-'a'+p*100)%p;
  return a;
}
int ge(string &str){//ֻ����ĸ���»��ߵĶ��뺯�� 
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
	cout<<"�����ж������������������"<<endl;
	cin>>fa>>fb;
  freopen("key.txt","r",stdin);
  string s;
	while(ge(s)){
		dic[++n]=s;
		int u=Hash(s);
		H[u].a[++H[u].tot]=s;//��������ؼ��� 
		H[u].id[H[u].tot]=n;//id�����洢���ֵ���ڼ����ؼ��� 
	}
	rep(i,0,42)cout<<H[i].tot<<' ';//�����ϣֵΪi�м����ؼ��� 
	double u=0;
	rep(i,0,42)u+=(H[i].tot+1)*H[i].tot/2;
	printf("\nƽ�����ҳ���%lf\n",u/n);
	freopen(fa.data(),"r",stdin);
	while(ge(s)){
		int u=Hash(s);
		rep(i,1,H[u].tot){
			if(H[u].a[i]==s){//ֱ������ͬ��ϣֵ�в��ҵ� 
				a[H[u].id[i]]++; 
				break;
			}
		}
	}
	rep(i,1,n)printf("%s %d \n",dic[i].data(),a[i]);
	puts("");
	freopen(fb.data(),"r",stdin);
	while(ge(s)){
		int u=Hash(s);
		rep(i,1,H[u].tot){
			if(H[u].a[i]==s){
				b[H[u].id[i]]++;
				break;
			}
		}
	} 
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
	printf("�������ƶ�Ϊ%.6lf\n",ans);
	if(ans<0.85){
		puts("������"); 
	}else{
		double d=0;
		rep(i,1,n)d+=(a[i]/A-b[i]/B)*(a[i]/A-b[i]/B);
		d=sqrt(d);
		printf("���ξ���%.6lf\n",d);
		if(d<0.25)puts("ȷʵ��������");
		else puts("���ܲ�����");
	}
}
