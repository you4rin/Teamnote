// boj.kr/11653
#include<cstdio>
#include<vector>

using namespace std;

int arr[10000010];
vector<int> p;

void sieve(){
	for(int i=2;i<10000001;++i){
		if(!arr[i])p.push_back(i);
		for(auto j:p){
			if(i*j>10000000)break;
			arr[i*j]=j;
			if(i%j==0)break;
		}
	}
}

int main(){
	int n;
	sieve();
	scanf("%d",&n);
	for(auto i:p){
		if(n==1)break;
		while(n%i==0){
			printf("%d\n",i);
			n/=i;
		}
	}
}