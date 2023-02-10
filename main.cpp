#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "kmap.cpp"//top();
using namespace std;
struct state_2{//2個的kmap要注意 
	vector<string>prd_term;//ex:1 2 0
	vector<bool>if_one_term;
	vector<bool>if_repeat;       
	//string nod_var;//A x
	//bol indicate;	
};
struct save_check_N{
	string term;
	//int index;//用本身的index去代替就好 
}; 
vector<char>out_var_name;//output的變數 
vector<char>variable_name;//in&ps的變數 
vector<bool>check_compl;
void swap(vector<char>&myvec){
	for(int i=0;i<myvec.size();i++){
		if(i==2||i==6||i==10||i==14){
			char temp;
			temp=myvec[i];
			myvec[i]=myvec[i+1];
			myvec[i+1]=temp;
		}
	}
	for(int i=0;i<myvec.size();i++){
		if(i==8||i==9||i==10||i==11){
			char temp;
			temp=myvec[i];
			myvec[i]=myvec[i+4];
			myvec[i+4]=temp;
		}
	}	
}
void swap2(char ary[],int wid){
	for(int i=0;i<wid;i++){
		if(i==2||i==6||i==10||i==14){
			char temp;
			temp=ary[i];
			ary[i]=ary[i+1];
			ary[i+1]=temp;
		}
	}
	for(int i=0;i<wid;i++){
		if(i==8||i==9||i==10||i==11){
			char temp;
			temp=ary[i];
			ary[i]=ary[i+4];
			ary[i+4]=temp;
		}
	}	
}

int main(){
	
	string in_name;
	string out_name;
	cout<<"pleae input the truth table name: "<<endl; 
	cin>>in_name;
	//in_name=argv[1];
	//out_name=argv[2];
	
	ifstream infile(in_name,ios::in);
	if(!infile){
		cout<<"The file can't be found!!!"<<endl;
		exit(1);
	}
	string notuse1;
	string ps_line,in_line,ns_line,out_line;
	int ps_n=1,in_n=1,ns_n=1,out_n=1;
	getline(infile,notuse1);
	//Present(A,B)
	infile>>ps_line;
	for(int i=0;i<ps_line.length();i++){
		if(ps_line[i]==','){
			ps_n++;
		}
	}
	ns_n=ps_n;
	//------------------
	char ps_ch1,ps_ch2,ps_ch3;
	vector<char>ps_vec_1;
	vector<char>ps_vec_2;
	vector<char>ps_vec_3;
	while(1){
		if(ps_n==2){
			infile>>ps_ch1>>ps_ch2;
			if(ps_ch1=='/'){
				break;
				}
			else if(ps_ch2=='/'){
				break;
			}
			else{
				ps_vec_1.push_back(ps_ch1);
				ps_vec_2.push_back(ps_ch2);
			}
		}
		else if(ps_n==1){
			infile>>ps_ch1;
			if(ps_ch1=='/'){
				break;
				}
			else{
				ps_vec_1.push_back(ps_ch1);
				//cout<<"here"<<endl;
			}
		}
		else if(ps_n==3){
			infile>>ps_ch1>>ps_ch2>>ps_ch3;
			if(ps_ch1=='/'){
				break;
				}
			else if(ps_ch2=='/'){
				break;
			}
			else if(ps_ch3=='P'){
				break;
			}
			else{
				ps_vec_1.push_back(ps_ch1);
				ps_vec_2.push_back(ps_ch2);
				ps_vec_3.push_back(ps_ch3);
			}
		}
	}
	
	
	//Input(x,y)--------------------
	infile>>in_line;
	//cout<<in_line;
	for(int i=0;i<in_line.length();i++){
		if(in_line[i]==','){
			in_n++;
		}
	}
	//------------------
	char in_ch1,in_ch2,in_ch3;
	vector<char>in_vec_1;
	vector<char>in_vec_2;
	vector<char>in_vec_3;
	//cout<<"in_n"<<in_n<<endl;
	while(1){
		if(in_n==2){
			infile>>in_ch1>>in_ch2;
			if(in_ch1=='/'){
				break;
				}
			else if(in_ch2=='/'){
				break;
			}
			else{
				in_vec_1.push_back(in_ch1);
				in_vec_2.push_back(in_ch2);
			}
		}
		else if(in_n==1){
			infile>>in_ch1;
			if(in_ch1=='/'){
				break;
				}
			else{
				in_vec_1.push_back(in_ch1);
			}
		}
		else if(in_n==3){
			infile>>in_ch1>>in_ch2>>in_ch3;
			if(in_ch1=='/'){
				break;
				}
			else if(in_ch2=='/'){
				break;
				}
			else if(in_ch3=='I'){
				break;
			}
			else{
				in_vec_1.push_back(in_ch1);
				in_vec_2.push_back(in_ch2);
				in_vec_3.push_back(in_ch3);
			}
		}
	}
//	for(int i=0;i<in_vec_1.size();i++){
//		cout<<in_vec_1[i]<<" "<<in_vec_2[i]<<" "<<in_vec_3[i]<<endl;
//	}
	
	//Next(A,B)------------
	infile>>ns_line;
	char ns_ch1,ns_ch2,ns_ch3;
	vector<char>ns_vec_1;
	vector<char>ns_vec_2;
	vector<char>ns_vec_3;
	while(1){
		if(ns_n==2){
			infile>>ns_ch1>>ns_ch2;
			if(ns_ch1=='/'){
				break;
				}
			else if(ns_ch2=='/'){
				break;
				}
			else{
				ns_vec_1.push_back(ns_ch1);
				ns_vec_2.push_back(ns_ch2);
			}
		}
		else if(ns_n==1){
			infile>>ns_ch1;
			if(ns_ch1=='/'){
				break;
				}
			else{
				ns_vec_1.push_back(ns_ch1);
			}
		}
		else if(ns_n==3){
			infile>>ns_ch1>>ns_ch2>>ns_ch3;
			if(ns_ch1=='/'){
				break;
				}
			else if(ns_ch2=='/'){
				break;
				}
			else if(ns_ch3=='N'){
				break;
				}	
			else{
				ns_vec_1.push_back(ns_ch1);
				ns_vec_2.push_back(ns_ch2);
				ns_vec_3.push_back(ns_ch3);
			}
		}
	}
	//cout<<"ns_n"<<ns_n<<endl;
//	for(int i=0;i<ns_vec_1.size();i++){
//		cout<<ns_vec_1[i]<<endl;
//	}
	//Output(y)
	infile>>out_line;
	
	//cout<<out_line;
	out_n=0;
	for(int i=0;i<out_line.length();i++){
		if(out_line[i-1]=='('&&out_line[i+1]==','){
			out_var_name.push_back(out_line[i]);
			out_n++;
		}
		else if(out_line[i-1]==','&&out_line[i+1]==','){
			out_var_name.push_back(out_line[i]);
			out_n++;
		}
		else if(out_line[i-1]==','&&out_line[i+1]==')'){
			out_var_name.push_back(out_line[i]);
			out_n++;
		}
		else if(out_line[i-1]=='('&&out_line[i+1]==')'){
			out_var_name.push_back(out_line[i]);
			out_n++;
		}	
	}
	int bol=1;
	for(int i=0;i<out_var_name.size();i++){
		//cout<<"out_var_name"<<out_var_name[i]<<endl;
		if(out_var_name[i]=='0'){
			bol=0;
			out_n=0; 
		}
	}
	//----out_vec宣告 
	//cout<<"out_n"<<out_n<<endl;
	
	const int a=pow(2,in_n+ps_n);
	//cout<<"a"<<a<<endl;
	const int b=out_n;
	char out_vec[b][a];
	for(int i=0;i<b;i++){
		for(int j=0;j<a;j++){
			out_vec[i][j]='0';
		}
	}
	
	if(bol!=0){
		for(int i=0;i<out_line.length();i++){
		if(out_line[i]==','){
			//out_n++;
			}
		}
		//cout<<"out_n"<<out_n<<endl;
		vector<char>temp;
		
		//	char temp_ary[a];
		char read;
		for(int i=0;i<pow(2,in_n+ps_n)*out_n;i++){
			infile>>read;
			temp.push_back(read);
			//cout<<read<<" ";
		}
		for(int i=0;i<pow(2,in_n+ps_n)*out_n;i++){
			//cout<<temp[i]<<" ";
		}
		
		int ct=0;
		for(int i=0;i<(b*a);i++){
			//cout<<"i%out_n"<<i%out_n<<" ";
			//cout<<"ct"<<ct<<" ";
			out_vec[i%out_n][ct]=temp[i];
			//cout<<"out_vec[i%out_n][ct]"<<out_vec[i%out_n][ct]<<endl;
			if(i%out_n==out_n-1){
				ct++;
			}
			if(ct==pow(2,in_n+ps_n)){
				ct=0;
			}	
		}
	}
	//-----------check-----------------------
//	for(int i=0;i<b;i++){
//		for(int j=0;j<a;j++){
//			cout<<out_vec[i][j]<<" ";
//		}
//		cout<<endl;
//	}
	//----------重排-------------------------------------
	
	if(ps_n!=1||in_n!=1){
		if(ns_n==1){
			swap(ns_vec_1);
		}
		else if(ns_n==2){
			swap(ns_vec_1);//寫檔之前再用即可 
			swap(ns_vec_2);
		}
		else if(ns_n==3){
			swap(ns_vec_1);//寫檔之前再用即可 
			swap(ns_vec_2);
			swap(ns_vec_3);//寫檔之前再用即可 
		}
		//防呆未完成!!! 
	}
	
	ofstream outfile("kmap_in.txt",ios::out);
	outfile<<ns_n+out_n<<endl;
	//寫ns 的variable 
	if(ns_n==1){
		outfile<<in_n+ps_n<<endl;
		for(int i=0;i<ns_vec_1.size();i++){
			outfile<<ns_vec_1[i]<<" ";
		}
		outfile<<endl;
	}
	else if(ns_n==2){
		outfile<<in_n+ps_n<<endl;
		for(int i=0;i<ns_vec_1.size();i++){
			outfile<<ns_vec_1[i]<<" ";
		}
		outfile<<endl;
		
		outfile<<in_n+ps_n<<endl;
		for(int i=0;i<ns_vec_2.size();i++){
			outfile<<ns_vec_2[i]<<" ";
		}
		outfile<<endl;
		
	}
	else if(ns_n==3){
		outfile<<in_n+ps_n<<endl;
		for(int i=0;i<ns_vec_1.size();i++){
			outfile<<ns_vec_1[i]<<" ";
		}
		outfile<<endl;
		
		outfile<<in_n+ps_n<<endl;
		for(int i=0;i<ns_vec_2.size();i++){
			outfile<<ns_vec_2[i]<<" ";
		}
		outfile<<endl;
		
		outfile<<in_n+ps_n<<endl;
		for(int i=0;i<ns_vec_3.size();i++){
			outfile<<ns_vec_3[i]<<" ";
		}
		outfile<<endl;
	}
	
	if(bol!=0){
		for(int i=0;i<out_n;i++){
			swap2(out_vec[i],pow(2,in_n+ps_n));
		}
		for(int i=0;i<out_n;i++){
			outfile<<in_n+ps_n<<endl;
			for(int j=0;j<pow(2,in_n+ps_n);j++){
				outfile<<out_vec[i][j]<<" ";
			}
			outfile<<endl;
		}
	}
	
	//------------------------------------------------------------
	top();
	//------------------------------------------------------------
	//抓變數in&ns
	
	for(int i=0;i<ps_line.length();i++){
		if(ps_line[i-1]=='('&&ps_line[i+1]==','){
			variable_name.push_back(ps_line[i]);
			check_compl.push_back(0);
		}
		else if(ps_line[i-1]==','&&ps_line[i+1]==','){
			variable_name.push_back(ps_line[i]);
			check_compl.push_back(0);
		}
		else if(ps_line[i-1]==','&&ps_line[i+1]==')'){
			variable_name.push_back(ps_line[i]);
			check_compl.push_back(0);
		}
		else if(ps_line[i-1]=='('&&ps_line[i+1]==')'){
			variable_name.push_back(ps_line[i]);
			check_compl.push_back(0);
		}	
	}
	//-----------------------------------------------------
	for(int i=0;i<in_line.length();i++){
		if(in_line[i-1]=='('&&in_line[i+1]==','){
			variable_name.push_back(in_line[i]);
			check_compl.push_back(0);
		}
		else if(in_line[i-1]==','&&in_line[i+1]==','){
			variable_name.push_back(in_line[i]);
			check_compl.push_back(0);
		}
		else if(in_line[i-1]==','&&in_line[i+1]==')'){
			variable_name.push_back(in_line[i]);
			check_compl.push_back(0);
		}
		else if(in_line[i-1]=='('&&in_line[i+1]==')'){
			variable_name.push_back(in_line[i]);
			check_compl.push_back(0);
		}	
	}
	//ps_line,in_line,ns_line,out_line; 
	//cout<<"variable_name"<<endl;
//	for(int j=0;j<variable_name.size();j++){
//		cout<<"variable_name"<<variable_name[j]<<endl;
//	}
//	for(int j=0;j<check_compl.size();j++){
//		cout<<"check_compl"<<check_compl[j]<<endl;
//	}
	cout<<endl;
	
	//--------------------stage 2------------------------------------
	vector<state_2>stage_data(ns_n+out_n);//-----------------------------------------------------------------------------------------------------------------	
	infile.close();
	outfile.close();
	ifstream infile2("kmap_out.txt",ios::in);
	int stage_n=0;
	while(!infile2.eof()){
		string input;
		getline(infile2,input);
		//cout<<input<<endl;
		if(input[0]=='#'){
			stage_n++;
		}
		//cout<<"stage_n-1 "<<stage_n-1<<" ";
		if(input[0]!='#'){
			stage_data[stage_n-1].prd_term.push_back(input);	
		}
	} 
	stage_data[stage_n-1].prd_term.pop_back();
	//cout<<"stage_data[stage_n-1].prd_term的大小"<<endl;
//	for(int i=0;i<stage_data.size();i++){
//		//cout<<stage_data[i].prd_term.size()<<endl;
//	} 
//	cout<<endl;
//	for(int i=0;i<stage_data.size();i++){
//		for(int j=0;j<stage_data[i].prd_term.size();j++){
//			//cout<<stage_data[i].prd_term[j]<<" ";
//		}
//		//cout<<endl;
//	}
	//cout<<"here 6"<<endl;

//------------------開始做expression-------------------------
	cout<<"Please input the name of the circuit diagram"<<endl; 
	cin>>out_name; 
	ofstream outfile2(out_name,ios::out);
	int keep_inverter=0;
	for(int i=0;i<stage_data.size();i++){
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			for(int k=0;k<stage_data[i].prd_term[j].size();k++){
				if(stage_data[i].prd_term[j][k]=='0'){
					//cout<<"!"<<stage_data[i].nod_var<<" = "<<"NOT("<<stage_data[i].nod_var<<")"<<endl;	
					keep_inverter++;		
				}
			}
		}
	}
	outfile2<<"# "<<in_n<<" input"<<endl;
	outfile2<<"# "<<out_n<<" output"<<endl;
	outfile2<<"# "<<keep_inverter<<" inverter"<<endl;
	outfile2<<"# "<<ns_n<<" flip-flops"<<endl;

	 
	bool rp;
	for(int i=0;i<ns_n+out_n;i++){
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			rp=0;
			for(int m=0;m<i;m++){			//只要和比自己前面的幾行比即可 
				for(int k=0;k<stage_data[m].prd_term.size();k++){
					if(stage_data[i].prd_term[j]==stage_data[m].prd_term[k]){
						//cout<<"i j"<<i<<" "<<j<<endl;
						//cout<<"m k"<<m<<" "<<k<<endl;
						stage_data[i].if_repeat.push_back(1);
						rp=1;
					}
				}
			}
			if(rp==0){
				stage_data[i].if_repeat.push_back(0);
			}
		}
	}
	//cout<<"here3"<<endl;
	for(int i=0;i<ns_n+out_n;i++){
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			int ct_0_1=0;
			for(int k=0;k<stage_data[i].prd_term[j].length();k++){
				if(stage_data[i].prd_term[j][k]=='0'||stage_data[i].prd_term[j][k]=='1'){
					ct_0_1++;
				}				
			}
			if(ct_0_1==1){
				stage_data[i].if_one_term.push_back(1);
				}
			else {
				stage_data[i].if_one_term.push_back(0);
				}
			}
		}
	//cout<<"here5"<<endl;
//	for(int i=0;i<ns_n+out_n;i++){
//		for(int j=0;j<stage_data[i].if_repeat.size();j++){
//			cout<<stage_data[i].if_repeat[j]<<" ";
//		}
//		cout<<endl;
//	}
//	
//	for(int i=0;i<ns_n+out_n;i++){
//		for(int j=0;j<stage_data[i].if_one_term.size();j++){
//			cout<<stage_data[i].if_one_term[j]<<" ";
//		}
//		cout<<endl;
//	}
	
	//cout<<"here4"<<endl;
	int ct_size=0;
	
	for(int i=0;i<ns_n+out_n;i++){
		for(int j=0;j<stage_data[i].if_repeat.size();j++){
			if(stage_data[i].if_one_term[j]!=1&&stage_data[i].if_repeat[j]!=1){
				ct_size++;
			}
		}
	}
	//cout<<"here1"<<endl;
//	for(int i=0;i<ns_n+out_n;i++){
//		cout<<stage_data[i].if_repeat.size()<<endl;
//	}
//	
//	for(int i=0;i<ns_n+out_n;i++){
//		for(int j=0;j<stage_data[i].if_repeat.size();j++){
//			cout<<stage_data[i].if_repeat[j]<<" ";
//		}
//		cout<<endl;
//	}
	
//	for(int i=0;i<ns_n+out_n;i++){
//		for(int j=0;j<stage_data[i].if_one_term.size();j++){
//			cout<<stage_data[i].if_one_term[j]<<" ";
//		}
//		cout<<endl;
//	}
	int k=0;
	vector<save_check_N>find_N(ct_size);
	for(int i=0;i<ns_n+out_n;i++){
		for(int j=0;j<stage_data[i].if_repeat.size();j++){
			if(stage_data[i].if_one_term[j]!=1&&stage_data[i].if_repeat[j]!=1){
				//cout<<stage_data[i].if_one_term[j]<<" "<<stage_data[i].if_repeat[j]<<endl;
				//cout<<stage_data[i].prd_term[j]<<endl;
				find_N[k].term=stage_data[i].prd_term[j];
				//cout<<find_N[k].term<<endl;
				k++;
			}
		}
	}
	
	//cout<<"here2"<<endl;
//	for(int i=0;i<find_N.size();i++){
//		//cout<<find_N[i].term<<" ";
//	}	

	//--------------------------------------------------------------
//	for(int i=0;i<ns_n;i++){
//		for(int j=0;j<stage_data[i].if_one_term.size();j++){
//			cout<<stage_data[i].if_one_term[j]<<" ";
//		}
//		cout<<endl;
//	}
//	
//	//cout<<"stage_data[i].if_repeat.size()"<<stage_data[i].if_repeat.size();
//	for(int i=0;i<ns_n;i++){
//		for(int j=0;j<stage_data[i].if_repeat.size();j++){
//			cout<<stage_data[i].if_repeat[j]<<" ";
//		}
//		cout<<endl;
//	}
	//---------------------------N的輸出------------------------------------- 
	vector<int>save_gate_times(out_n+ns_n);
	for(int i=0;i<out_n+ns_n;i++){
		save_gate_times[i]=0;//負責記錄跑了幾次，目前已初始化 
	}
	//---------------------------確認次數------------------------------ 
	for(int i=0;i<ns_n+out_n;i++){
		int ct_comma=0;
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			for(int k=0;k<find_N.size();k++){
				if(stage_data[i].prd_term[j]==find_N[k].term){
					//cout<<"上半部"<<endl; 
					ct_comma++;
				}
			} 
			if(stage_data[i].if_one_term[j]==1){
				for(int k=0;k<stage_data[i].prd_term[j].size();k++){
					if(stage_data[i].prd_term[j][k]=='0'){
						//cout<<"下半部"<<endl; 
						ct_comma++;
					}
					else if(stage_data[i].prd_term[j][k]=='1'){
						//cout<<"下半部"<<endl; 
						ct_comma++;
					}	
				}	
			}
		} 
		save_gate_times[i]=ct_comma;
	}
//	for(int i=0;i<save_gate_times.size();i++){
//		cout<<save_gate_times[i]<<endl;
//	}
	//---------------------------完成剩下的輸出------------------------------ 
	int and_gate_n=find_N.size();
	int or_gate_n=0;
	for(int i=0;i<save_gate_times.size();i++){
		if(save_gate_times[i]!=1){
			or_gate_n++;
		}
	}
	outfile2<<"# "<<or_gate_n+and_gate_n<<" gates "<<"("<<and_gate_n<<" ANDs + "<<or_gate_n<<" ORs)"<<endl;
	outfile2<<endl;
	for(int i=ps_n;i<variable_name.size();i++){
		outfile2<<"INPUT("<<variable_name[i]<<")"<<endl;
	}
	for(int j=0;j<out_var_name.size();j++){
		if(out_n!=0){
			outfile2<<"OUTPUT("<<out_var_name[j]<<")"<<endl;
		}
	}
	outfile2<<endl;
	//------------------------------------------------------------------------------
//	for(int i=0;i<stage_data.size();i++){
//		for(int j=0;j<stage_data[i].prd_term.size();j++){
//			cout<<stage_data[i].prd_term[j]<<" ";
//		}
//		cout<<endl;
//	}
	
	for(int i=0;i<stage_data.size();i++){
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			for(int k=0;k<stage_data[i].prd_term[j].size();k++){
				if(stage_data[i].prd_term[j][k]=='0'){
					if(check_compl[k/2]!=1){
						outfile2<<"!"<<variable_name[k/2]<<" = "<<"NOT("<<variable_name[k/2]<<")"<<endl;
						check_compl[k/2]=1;	
					}	
				}
			}
		}
	}
	//-----------------------確認AND2的逗號------------------------------------------------
	vector<int>save_nod_times(find_N.size());
	for(int i=0;i<find_N.size();i++){
		save_nod_times[i]=0;//負責記錄跑了幾次，目前已初始化 
	}
	
	for(int i=0;i<find_N.size();i++){
		int ct_and=0;
		for(int j=0;j<find_N[i].term.length();j++){
			if(find_N[i].term[j]=='1'){
				ct_and++;
			}
			else if(find_N[i].term[j]=='0'){
				ct_and++;
			}
		}
		save_nod_times[i]=ct_and;
	}

	for(int i=0;i<find_N.size();i++){
		int ct_and_out=0;
		outfile2<<"N"<<i+1<<" = "<<"AND(";
		for(int j=0;j<find_N[i].term.length();j++){
			if(find_N[i].term[j]=='1'){
				ct_and_out++;
				if(ct_and_out<save_nod_times[i]){
					outfile2<<variable_name[j/2]<<", ";
				}
				else{
					outfile2<<variable_name[j/2];
				}
			}
			else if(find_N[i].term[j]=='0'){
				ct_and_out++;
				if(ct_and_out<save_nod_times[i]){
					outfile2<<"!"<<variable_name[j/2]<<", ";
				}
				else{
					outfile2<<"!"<<variable_name[j/2];
				}
			}
		}
		outfile2<<")"<<endl;
	}
	
	
	for(int i=0;i<ns_n;i++){
		int ct_D_out=0;
		if(save_gate_times[i]!=1){
			outfile2<<"D"<<variable_name[i]<<" = OR(";
		}
		else{
			outfile2<<"D"<<variable_name[i]<<" = ";
		}
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			for(int k=0;k<find_N.size();k++){
				if(stage_data[i].prd_term[j]==find_N[k].term){
					ct_D_out++;
					if(ct_D_out<save_gate_times[i]){
						outfile2<<"N"<<k+1<<",";
					}
					else {
						outfile2<<"N"<<k+1;
					}
				}
			} 
			if(stage_data[i].if_one_term[j]==1){
				for(int k=0;k<stage_data[i].prd_term[j].size();k++){
					if(stage_data[i].prd_term[j][k]=='0'){
						ct_D_out++;
						if(ct_D_out<save_gate_times[i]){
							outfile2<<"!"<<variable_name[k/2]<<", ";
						}
						else{
							outfile2<<"!"<<variable_name[k/2];
						}
					}
					else if(stage_data[i].prd_term[j][k]=='1'){
						ct_D_out++;
						if(ct_D_out<save_gate_times[i]){
							outfile2<<variable_name[k/2]<<", ";
						}
						else{
							outfile2<<variable_name[k/2];
						}
					}	
				}	
			}
		} 
		if(save_gate_times[i]!=1){
			outfile2<<")"<<endl;
		}
		else{
			outfile2<<endl;
		}
	}
	//--------------------------------------------------------
	int ct_out_var=0;
	for(int i=ns_n;i<ns_n+out_n;i++){
		int ct_comma=0;
		if(save_gate_times[i]!=1){
			outfile2<<out_var_name[ct_out_var]<<" = OR(";
		}
		else{
			outfile2<<out_var_name[ct_out_var]<<" = ";
		}
		ct_out_var++;
		for(int j=0;j<stage_data[i].prd_term.size();j++){
			for(int k=0;k<find_N.size();k++){
				if(stage_data[i].prd_term[j]==find_N[k].term){
					ct_comma++;
					if(ct_comma<save_gate_times[i]){
						outfile2<<"N"<<k+1<<",";
					}
					else{
						outfile2<<"N"<<k+1;
					}
				}
			} 
			
			if(stage_data[i].if_one_term[j]==1){
				for(int k=0;k<stage_data[i].prd_term[j].size();k++){
					if(stage_data[i].prd_term[j][k]=='0'){
						ct_comma++;
						if(ct_comma<save_gate_times[i]){
							outfile2<<"!"<<variable_name[k/2]<<", ";
						}
						else{
							outfile2<<"!"<<variable_name[k/2];
						}
					}
					else if(stage_data[i].prd_term[j][k]=='1'){
						ct_comma++;
						if(ct_comma<save_gate_times[i]){
							outfile2<<variable_name[k/2]<<", ";
						}
						else{
							outfile2<<variable_name[k/2];
						}
					}	
				}	
			}
		} 
		if(save_gate_times[i]!=1){
			outfile2<<")"<<endl;
		}
		else{
			outfile2<<endl;
		}
	}
	//--------------------------------------------------------
	for(int i=0;i<ns_n;i++){
		outfile2<<variable_name[i]<<" = D(D"<<variable_name[i]<<",CLK)"<<endl;
	}
	outfile2<<"#END"<<endl;
	cout<<"the circuit diagram has been successfully generated!"<<endl;
	return 0;
}

