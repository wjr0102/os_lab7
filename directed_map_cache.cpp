#include<bits/stdc++.h>
#include<unistd.h>
#include<stdio.h>
#include<string>
#include<iostream>
#include<math.h>

using namespace std;
typedef struct cacheline{
	int valid;
//	int index;
	int tag;
	int data;
}Cacheline;

Cacheline cache[64];
int access_sum = 0;
int hit = 0;
void cache_init();
bool check(string temp);
bool check_data(int new_data,int old_data);
int he_to_de(string temp);

void cache_init(){
	for (int i=0;i<64;i++){
		Cacheline cl = {0,0,0};
		cache[i] = cl;
	}
}

bool check(string temp){
	int data = he_to_de(temp);
	int index = (data % 1024)/16;
	int tag = data / 1024;
//	printf("data:%d,index:%d,tag:%d\n",data,index,tag);
	if (cache[index].valid){
		// Already have the data
		if (tag==cache[index].tag){
		// Hit
			return true;
		}
		else{
		// Miss. Replace the original data
			cache[index].data = data;
			cache[index].tag = tag;
			return false;
		}

	}
	else{
		cache[index].valid = 1;
		cache[index].data = data;
		cache[index].tag = tag;
		return false;
	}
}


int he_to_de(string temp){
	int len = temp.length();
	int sum = 0;
	for (int i=0;i<len;i++){
	//	printf("The %d bit\n",i);
		if (temp[i]>='0'&&temp[i]<='9'){
			sum = sum + (temp[i]-48)*pow(16,len-i-1);
	//		printf("%d",sum);
		}
		else{
			sum = sum +(temp[i]-55)*pow(16,len-i-1);
	//		printf("%d",sum);
		}
	}
	return sum;
}

int main(){
	cache_init();
	string temp;
	getline(cin,temp);
	while (temp.compare("END")!=0){
		access_sum ++;
		if (check(temp)){
			hit ++;
			cout<<"Hit"<<endl;
			//puts("Hit");
		}
		else
			cout<<"Miss"<<endl;
			//puts("Miss");
		getline(cin,temp);
	}
	double result = (double)hit*100/access_sum;
	cout<<"Hit ratio = "<<fixed<<setprecision(2)<<result<<"%"<<endl;
	return 0;
}


