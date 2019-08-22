#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "math.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
using namespace std;
int expanh(cv::Mat img,cv::Mat newimg,int m,int n,int num){
	if(num==0){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				newimg.ptr<cv::Vec3b>(i)[j][0]=img.ptr<cv::Vec3b>(i)[j][0];
				newimg.ptr<cv::Vec3b>(i)[j][1]=img.ptr<cv::Vec3b>(i)[j][1];
				newimg.ptr<cv::Vec3b>(i)[j][2]=img.ptr<cv::Vec3b>(i)[j][2];
			}
		}
		return 0;

	}
	int energy[m][n]={0};

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			energy[i][j]=10000;
		}
	}	
	int indexs[n][num]={0};
	//first col
	for(int i=0;i<1;i++){
		for(int j=1;j<m-1;j++){
			energy[j][i]=abs(img.ptr<cv::Vec3b>(j)[i+1][0]-img.ptr<cv::Vec3b>(j)[i][0])
			+abs(img.ptr<cv::Vec3b>(j)[i+1][1]-img.ptr<cv::Vec3b>(j)[i][1])
			+abs(img.ptr<cv::Vec3b>(j)[i+1][2]-img.ptr<cv::Vec3b>(j)[i][2]);
		}
	}
	for(int i=1;i<n-1;i++){
		for(int j=1;j<m-1;j++){
			energy[j][i]=abs(img.ptr<cv::Vec3b>(j)[i-1][0]-img.ptr<cv::Vec3b>(j)[i+1][0])
			+abs(img.ptr<cv::Vec3b>(j)[i-1][1]-img.ptr<cv::Vec3b>(j)[i+1][1])
			+abs(img.ptr<cv::Vec3b>(j)[i-1][2]-img.ptr<cv::Vec3b>(j)[i+1][2])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][2]-img.ptr<cv::Vec3b>(j+1)[i][2])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][1]-img.ptr<cv::Vec3b>(j+1)[i][1])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][0]-img.ptr<cv::Vec3b>(j+1)[i][0])+min(min(energy[j-1][i-1],energy[j+1][i-1]),energy[j][i-1]);
		}
	}
	cout<<"good3"<<endl;
	//last col
	for(int i=n-1;i<n;i++){
		for(int j=1;j<m-1;j++){
			energy[j][i]=abs(img.ptr<cv::Vec3b>(j-1)[i][0]-img.ptr<cv::Vec3b>(j)[i][0])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][1]-img.ptr<cv::Vec3b>(j)[i][1])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][2]-img.ptr<cv::Vec3b>(j)[i][2])+min(min(energy[j+1][i-1],energy[j][i-1]),energy[j-1][i-1]);
		}
	}
	//first line
	for(int i=1;i<n;i++){
		for(int j=0;j<1;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j+1],energy[i-1][j]);
			energy[j][i]=energy[j+1][i];
		}
	}
	cout<<"good3"<<endl;
	//last line
	for(int i=1;i<n;i++){
		for(int j=m-1;j<m;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j-1],energy[i-1][j]);
			energy[j][i]=energy[j-1][i];
		}
	}

	for(int k=0;k<num;k++){
		int minv=9999;
		for(int j=0;j<m;j++){
			if(minv>energy[j][n-1]){
				minv=energy[j][n-1];
				indexs[n-1][k]=j;
				// cout<<j<<endl;
			}
		// cout<<energy[indexs[n-1][k]][n-1]<<endl;
		energy[indexs[n-1][k]][n-1]=9999;
		}
	}

	cout<<"good2"<<endl;
	for(int k=0;k<num;k++){
		for(int i=n-2;i>=0;i--){
			int j=indexs[i+1][k];
			if(indexs[i+1][k]!=0 && indexs[i+1][k]!=m-1){
				int a=min(min(energy[j-1][i],energy[j][i]),energy[j+1][i]);
				if(energy[j][i]==a){
					indexs[i][k]=j;
				}else if(energy[j-1][i]==a){
					indexs[i][k]=j-1;
				}else{
					indexs[i][k]=j+1;
				}
			}else if(indexs[i+1][k]==0){
				int a=min(energy[j][i],energy[j+1][i]);
				if(energy[j][i]==a){
					indexs[i][k]=j;
				}else{
					indexs[i][k]=j+1;
				}
			}else{
				int a=min(energy[j][i],energy[j-1][i]);
				if(energy[j][i]==a){
					indexs[i][k]=j;
				}else{
					indexs[i][k]=j-1;
				}
			}
		}
	}



	for(int i=0;i<n;i++){
		for(int l1=0;l1<num;l1++){
			int kz=1;
			int tmp;
			for(int l2=0;l2<num;l2++){
				if(indexs[i][l2]>indexs[i][l2+1]){
					kz=0;
					tmp=indexs[i][l2+1];
					indexs[i][l2+1]=indexs[i][l2];
					indexs[i][l2]=tmp;
				}
			}
			if (kz){
				break;
			}
		}

		int newind=num+m-1;
		int inind=m-1;
		int index=num-1;
		while (newind>=0){
				// cout<<inind<<endl;
				newimg.ptr<cv::Vec3b>(newind)[i][0]=img.ptr<cv::Vec3b>(inind)[i][0];
				newimg.ptr<cv::Vec3b>(newind)[i][1]=img.ptr<cv::Vec3b>(inind)[i][1];
				newimg.ptr<cv::Vec3b>(newind)[i][2]=img.ptr<cv::Vec3b>(inind)[i][2];
				newind-=1;
				while(inind==indexs[i][index] && index>=0){
					newimg.ptr<cv::Vec3b>(newind)[i][0]=img.ptr<cv::Vec3b>(inind)[i][0];
					newimg.ptr<cv::Vec3b>(newind)[i][1]=img.ptr<cv::Vec3b>(inind)[i][1];
					newimg.ptr<cv::Vec3b>(newind)[i][2]=img.ptr<cv::Vec3b>(inind)[i][2];
					newind=newind-1;
					index=index-1;
				}
				inind-=1;


		}

	}

}
int expanw(cv::Mat img,cv::Mat newimg,int m,int n,int num){
	if(num==0){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				newimg.ptr<cv::Vec3b>(i)[j][0]=img.ptr<cv::Vec3b>(i)[j][0];
				newimg.ptr<cv::Vec3b>(i)[j][1]=img.ptr<cv::Vec3b>(i)[j][1];
				newimg.ptr<cv::Vec3b>(i)[j][2]=img.ptr<cv::Vec3b>(i)[j][2];
			}
		}
		return 0;
	}
	int energy[m][n]={0};

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			energy[i][j]=10000;
		}
	}	
	int indexs[m][num]={0};

	//first line
	for(int i=0;i<1;i++){
		for(int j=1;j<n-1;j++){
			energy[i][j]=abs(img.ptr<cv::Vec3b>(i+1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
			+abs(img.ptr<cv::Vec3b>(i+1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
			+abs(img.ptr<cv::Vec3b>(i+1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2]);
		}
	}
	for(int i=1;i<m-1;i++){
		for(int j=1;j<n-1;j++){
			energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j-1][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			+abs(img.ptr<cv::Vec3b>(i)[j-1][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			+abs(img.ptr<cv::Vec3b>(i)[j-1][2]-img.ptr<cv::Vec3b>(i)[j+1][2])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][2]-img.ptr<cv::Vec3b>(i+1)[j][2])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][1]-img.ptr<cv::Vec3b>(i+1)[j][1])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][0]-img.ptr<cv::Vec3b>(i+1)[j][0])+min(min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j]);
		}
	}

	//last line
	for(int i=m-1;i<m;i++){
		for(int j=1;j<n-1;j++){
			energy[i][j]=abs(img.ptr<cv::Vec3b>(i-1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2])+min(min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j]);
		}
	}

	//first cols
	for(int i=1;i<m;i++){
		for(int j=0;j<1;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j+1],energy[i-1][j]);
			energy[i][j]=energy[i][j+1];
		}
	}

	//last cols
	for(int i=1;i<m;i++){
		for(int j=n-1;j<n;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j-1],energy[i-1][j]);
			energy[i][j]=energy[i][j-1];
		}
	}
	
	for(int k=0;k<num;k++){
		int minv=9999;
		for(int j=0;j<n;j++){
			if(minv>energy[m-1][j]){
				minv=energy[m-1][j];
				indexs[m-1][k]=j;
				// cout<<j<<endl;
			}
		energy[m-1][indexs[m-1][k]]=60000;
		}
	}


	for(int k=0;k<num;k++){

		for(int i=m-2;i>=0;i--){
			int j=indexs[i+1][k];
			if(indexs[i+1][k]!=0 && indexs[i+1][k]!=n-1){
				int a=min(min(energy[i][j-1],energy[i][j]),energy[i][j+1]);
				if(energy[i][j]==a){
					indexs[i][k]=j;
				}else if(energy[i][j-1]==a){
					indexs[i][k]=j-1;
				}else{
					indexs[i][k]=j+1;
				}
			}else if(indexs[i+1][k]==0){
				int a=min(energy[i][j],energy[i][j+1]);
				if(energy[i][j]==a){
					indexs[i][k]=j;
				}else{
					indexs[i][k]=j+1;
				}
			}else{
				int a=min(energy[i][j],energy[i][j-1]);
				if(energy[i][j]==a){
					indexs[i][k]=j;
				}else{
					indexs[i][k]=j-1;
				}
			}
		}
	}

	for(int i=0;i<m;i++){
		for(int l1=0;l1<num;l1++){
			int kz=1;
			int tmp;
			for(int l2=0;l2<num;l2++){
				if(indexs[i][l2]>indexs[i][l2+1]){
					kz=0;
					tmp=indexs[i][l2+1];
					indexs[i][l2+1]=indexs[i][l2];
					indexs[i][l2]=tmp;
				}
			}
			if (kz){
				break;
			}
		}
		// cout<<"good"<<endl;
		// for(int l1=0;l1<num;l1++){
		// 	indexs[i][l1]=0;
		// 	cout<<indexs[i][l1]<<endl;
		// }
		// cout<<"good0"<<endl;
		int newind=num+n-1;
		int inind=n-1;
		int index=num-1;
		while (newind>=0){
				// cout<<inind<<endl;
				newimg.ptr<cv::Vec3b>(i)[newind][0]=img.ptr<cv::Vec3b>(i)[inind][0];
				newimg.ptr<cv::Vec3b>(i)[newind][1]=img.ptr<cv::Vec3b>(i)[inind][1];
				newimg.ptr<cv::Vec3b>(i)[newind][2]=img.ptr<cv::Vec3b>(i)[inind][2];
				newind-=1;
				while(inind==indexs[i][index] && index>=0){
					newimg.ptr<cv::Vec3b>(i)[newind][0]=img.ptr<cv::Vec3b>(i)[inind][0];
					newimg.ptr<cv::Vec3b>(i)[newind][1]=img.ptr<cv::Vec3b>(i)[inind][1];
					newimg.ptr<cv::Vec3b>(i)[newind][2]=img.ptr<cv::Vec3b>(i)[inind][2];
					newind=newind-1;
					index=index-1;
				}
				inind-=1;


		}

	}

}


void semw(cv::Mat img,int m,int n){

	int energy[m][n]={0};

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			energy[i][j]=10000;
		}
	}	
	int indexs[m]={0};

	//first line
	for(int i=0;i<1;i++){
		for(int j=1;j<n-1;j++){
			energy[i][j]=abs(img.ptr<cv::Vec3b>(i+1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
			+abs(img.ptr<cv::Vec3b>(i+1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
			+abs(img.ptr<cv::Vec3b>(i+1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2]);
		}
	}
	for(int i=1;i<m-1;i++){
		for(int j=1;j<n-1;j++){
			energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j-1][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			+abs(img.ptr<cv::Vec3b>(i)[j-1][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			+abs(img.ptr<cv::Vec3b>(i)[j-1][2]-img.ptr<cv::Vec3b>(i)[j+1][2])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][2]-img.ptr<cv::Vec3b>(i+1)[j][2])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][1]-img.ptr<cv::Vec3b>(i+1)[j][1])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][0]-img.ptr<cv::Vec3b>(i+1)[j][0])+min(min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j]);
		}
	}

	//last line
	for(int i=m-1;i<m;i++){
		for(int j=1;j<n-1;j++){
			energy[i][j]=abs(img.ptr<cv::Vec3b>(i-1)[j][0]-img.ptr<cv::Vec3b>(i)[j][0])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][1]-img.ptr<cv::Vec3b>(i)[j][1])
			+abs(img.ptr<cv::Vec3b>(i-1)[j][2]-img.ptr<cv::Vec3b>(i)[j][2])+min(min(energy[i-1][j-1],energy[i-1][j+1]),energy[i-1][j]);
		}
	}

	//first cols
	for(int i=1;i<m;i++){
		for(int j=0;j<1;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j+1],energy[i-1][j]);
			energy[i][j]=energy[i][j+1];
		}
	}

	//last cols
	for(int i=1;i<m;i++){
		for(int j=n-1;j<n;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j-1],energy[i-1][j]);
			energy[i][j]=energy[i][j-1];
		}
	}

	int minv=9999;
	for(int j=0;j<n;j++){
		if(minv>energy[m-1][j]){
			minv=energy[m-1][j];
			indexs[m-1]=j;
		}
	}

	for(int i=m-2;i>=0;i--){
		int j=indexs[i+1];
		if(indexs[i+1]!=0 && indexs[i+1]!=n-1){
			int a=min(min(energy[i][j-1],energy[i][j]),energy[i][j+1]);
			if(energy[i][j]==a){
				indexs[i]=j;
			}else if(energy[i][j-1]==a){
				indexs[i]=j-1;
			}else{
				indexs[i]=j+1;
			}
		}else if(indexs[i+1]==0){
			int a=min(energy[i][j],energy[i][j+1]);
			if(energy[i][j]==a){
				indexs[i]=j;
			}else{
				indexs[i]=j+1;
			}
		}else{
			int a=min(energy[i][j],energy[i][j-1]);
			if(energy[i][j]==a){
				indexs[i]=j;
			}else{
				indexs[i]=j-1;
			}
		}
	}
	// cout<<"good"<<endl;
	for(int i=0;i<m;i++){
		int qs=indexs[i];
		// cout<<qs<<endl;
		for (int j=qs;j<n-1;j++){
			img.ptr<cv::Vec3b>(i)[j][0]=img.ptr<cv::Vec3b>(i)[j+1][0];
			img.ptr<cv::Vec3b>(i)[j][1]=img.ptr<cv::Vec3b>(i)[j+1][1];
			img.ptr<cv::Vec3b>(i)[j][2]=img.ptr<cv::Vec3b>(i)[j+1][2];
		}
	}

}

void semh(cv::Mat img,int m,int n){

	int energy[m][n]={0};

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			energy[i][j]=10000;
		}
	}	
	int indexs[n]={0};
	// cout<<"good3"<<endl;
	//first col
	for(int i=0;i<1;i++){
		for(int j=1;j<m-1;j++){
			energy[j][i]=abs(img.ptr<cv::Vec3b>(j)[i+1][0]-img.ptr<cv::Vec3b>(j)[i][0])
			+abs(img.ptr<cv::Vec3b>(j)[i+1][1]-img.ptr<cv::Vec3b>(j)[i][1])
			+abs(img.ptr<cv::Vec3b>(j)[i+1][2]-img.ptr<cv::Vec3b>(j)[i][2]);
		}
	}
	for(int i=1;i<n-1;i++){
		for(int j=1;j<m-1;j++){
			energy[j][i]=abs(img.ptr<cv::Vec3b>(j)[i-1][0]-img.ptr<cv::Vec3b>(j)[i+1][0])
			+abs(img.ptr<cv::Vec3b>(j)[i-1][1]-img.ptr<cv::Vec3b>(j)[i+1][1])
			+abs(img.ptr<cv::Vec3b>(j)[i-1][2]-img.ptr<cv::Vec3b>(j)[i+1][2])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][2]-img.ptr<cv::Vec3b>(j+1)[i][2])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][1]-img.ptr<cv::Vec3b>(j+1)[i][1])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][0]-img.ptr<cv::Vec3b>(j+1)[i][0])+min(min(energy[j-1][i-1],energy[j+1][i-1]),energy[j][i-1]);
		}
	}
	// cout<<"good3"<<endl;
	//last col
	for(int i=n-1;i<n;i++){
		for(int j=1;j<m-1;j++){
			energy[j][i]=abs(img.ptr<cv::Vec3b>(j-1)[i][0]-img.ptr<cv::Vec3b>(j)[i][0])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][1]-img.ptr<cv::Vec3b>(j)[i][1])
			+abs(img.ptr<cv::Vec3b>(j-1)[i][2]-img.ptr<cv::Vec3b>(j)[i][2])+min(min(energy[j+1][i-1],energy[j][i-1]),energy[j-1][i-1]);
		}
	}
	// cout<<"good3"<<endl;
	//first line
	for(int i=1;i<n;i++){
		for(int j=0;j<1;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j+1],energy[i-1][j]);
			energy[j][i]=energy[j+1][i];
		}
	}
	// cout<<"good3"<<endl;
	//last line
	for(int i=1;i<n;i++){
		for(int j=m-1;j<m;j++){
			// energy[i][j]=abs(img.ptr<cv::Vec3b>(i)[j][0]-img.ptr<cv::Vec3b>(i)[j+1][0])
			// +abs(img.ptr<cv::Vec3b>(i)[j][1]-img.ptr<cv::Vec3b>(i)[j+1][1])
			// +abs(img.ptr<cv::Vec3b>(i)[j][2]-img.ptr<cv::Vec3b>(i)[j+1][2])+min(energy[i-1][j-1],energy[i-1][j]);
			energy[j][i]=energy[j-1][i];
		}
	}
	// cout<<"good3"<<endl;
	int minv=9999;
	for(int j=0;j<m;j++){
		// cout<<energy[j][n-1]<<endl;
		if(minv>energy[j][n-1]){
			minv=energy[j][n-1];
			indexs[n-1]=j;
		}
	}
	// cout<<"good3"<<endl;
	for(int i=n-2;i>=0;i--){
		int j=indexs[i+1];
		if(indexs[i+1]!=0 && indexs[i+1]!=m-1){
			int a=min(min(energy[j-1][i],energy[j][i]),energy[j+1][i]);
			if(energy[j][i]==a){
				indexs[i]=j;
			}else if(energy[j-1][i]==a){
				indexs[i]=j-1;
			}else{
				indexs[i]=j+1;
			}
		}else if(indexs[i+1]==0){
			int a=min(energy[j][i],energy[j+1][i]);
			if(energy[j][i]==a){
				indexs[i]=j;
			}else{
				indexs[i]=j+1;
			}
		}else{
			int a=min(energy[j][i],energy[j-1][i]);
			if(energy[j][i]==a){
				indexs[i]=j;
			}else{
				indexs[i]=j-1;
			}
		}
	}
	// cout<<"good"<<endl;
	for(int i=0;i<n;i++){
		int qs=indexs[i];
		// cout<<qs<<endl;
		for (int j=qs;j<m-1;j++){
			img.ptr<cv::Vec3b>(j)[i][0]=img.ptr<cv::Vec3b>(j+1)[i][0];
			img.ptr<cv::Vec3b>(j)[i][1]=img.ptr<cv::Vec3b>(j+1)[i][1];
			img.ptr<cv::Vec3b>(j)[i][2]=img.ptr<cv::Vec3b>(j+1)[i][2];
		}
	}

}

int main(int argc, char const *argv[]){
	string inputpath = argv[1];
	string outputpath = argv[6];
	cv::Mat img = cv::imread(inputpath);
	string s1,s2,s3,s4;
	s1=argv[2];
	s2=argv[3];
	s3=argv[4];
	s4=argv[5];
	int sw=atoi(s1.c_str());
	int sh=atoi(s2.c_str());
	int ew=atoi(s3.c_str());
	int eh=atoi(s4.c_str());
	int m,n,c;
	m=img.rows;
	n=img.cols;
	c=3;
	for(int i=0;i<sw;i++){

		semw(img,m,n);
		n-=1;
	}
	for(int i=0;i<sh;i++){

		semh(img,m,n);
		m-=1;
	}
	cv::Mat image(m,n,CV_8UC3);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			image.ptr<cv::Vec3b>(i)[j][0]=img.ptr<cv::Vec3b>(i)[j][0];
			image.ptr<cv::Vec3b>(i)[j][1]=img.ptr<cv::Vec3b>(i)[j][1];
			image.ptr<cv::Vec3b>(i)[j][2]=img.ptr<cv::Vec3b>(i)[j][2];
		}
	}
	cv::Mat newimage(m+eh,n,CV_8UC3);
	expanh(image,newimage,m,n,eh);
	cv::Mat newimages(m+eh,n+ew,CV_8UC3);
	expanw(newimage,newimages,m+eh,n,ew);
	cv::imwrite(outputpath,newimages);
}