﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW7_錢玟卉_309706024.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define upperbound 200

TForm4 *Form4;
int ** w;
int n;
int d[upperbound];
int visited[upperbound];
int edge[upperbound][upperbound];
void graph(int n, int r, int max, int LargeInt){
	 if(w!=NULL){
	   //	int **s = w;
		for (int i = 0; i < n; i++) {
			delete w[i];
		}
		delete w;
	 }
	 w = new int * [n];
	 for (int i = 0; i < n; i++) {
		  w[i] = new int [n];
	 }
	 for (int i =0; i < n; i++) {
		  for (int j = 0; j < n; j++) {
			  w[i][j] = rand()%r +1;
			  if(w[i][j] > max) w[i][j] = LargeInt;

		  }
		  w[i][i] = LargeInt;
	 }
}

void print(){

	Form4->StringGrid1->RowCount = n+1;
	Form4->StringGrid1->ColCount = n+1;
	for (int i=1; i<=n+1; i++)
	{
		Form4->StringGrid1->Cells[i][0] =  i;
		Form4->StringGrid1->Cells[0][i] =  i;
	}
	for (int i = 0; i < n; i++) {
		for (int j=0; j<n; j++)
		{    Form4->StringGrid1->Cells[j+1][i+1] = IntToStr(w[i][j]);
			// VS C++ ｻyｪkｫh･ﾎ｡G StringGrid1->Rows[i]->Cells[j]->Value = W[i][j];
		}
	}
}





void bellman(int s){

	int min = 99999;
	int number_comlpete = 1;  //紀錄已完成點個數
	int to_be_visited;  //下一個拜訪之點
	Form4->StringGrid2->RowCount = n+1;
	Form4->StringGrid2->ColCount = n+1;
	s = s-1;

	for(int i=0;i<n;i++){visited[i]=0;}  //是否已拜訪
	for(int i=0;i<n;i++){d[i]=w[s][i];}  //第一輪的可連到的weight
	visited[s] = 1; //第一點拜訪
	d[s] = 0; //第一點自己距離為零
	for (int i = 0; i < n; i++) {
		 Form4->StringGrid2->Cells[i+1][1] = d[i];
	}

	while(number_comlpete<n) {
	  for(int i=0;i<n;i++)
	  {
		 if(d[i] <= min&& visited[i]==0)
		 {	min= d[i];
			to_be_visited = i;
		 }        //比較目前最小的路徑選取
	  }
	  for(int i=0;i<n;i++) //relax
	  {
		  if(visited[i]==0)
		  {
			if(d[i]>min+ w[to_be_visited][i])
			{
			   d[i]=min+w[to_be_visited][i];
			}
		  }
	  }
	  number_comlpete++;
	  visited[to_be_visited]=1; //此最後選取點拜訪

	  for (int i = 0; i < n; i++) //更新
	  {
			Form4->StringGrid2->Cells[i+1][number_comlpete] = d[i];
	  }
   }

	for (int i = 1; i <= n+1; i++)
	{
		 if(i==1)
		 {
			Form4->StringGrid2->Cells[0][i] = "初始狀態";
		 }
		 else
		 {
			Form4->StringGrid2->Cells[0][i] =  i-1;
		 }
	}
	for (int i = 1; i <= n; i++)
	{
		Form4->StringGrid2->Cells[i][0] = "經過邊數=" +IntToStr(i) ;
	}

}

void floyd(){

	for (int i = 0; i < n; i++)
	{
	   for (int j = 0; j < n; j++)
	   {
			edge[i][j] = w[i][j];
	   }
	}

	for(int k=0;k<n;k++)
	{
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{
				if (edge[i][j] > edge[i][k]+edge[k][j])
				{
					edge[i][j] = edge[i][k]+edge[k][j];
				}
			}
		}
	}


	// print
	Form4->StringGrid3->RowCount = n+1;
	Form4->StringGrid3->ColCount = n+1;
	for (int i = 1; i <= n+1; i++)
	{      //xｶbｪ・lｭﾈ
		 Form4->StringGrid3->Cells[i][0] =  i;
		 Form4->StringGrid3->Cells[0][i] = i;
	}
	for (int i = 0; i < n; i++)
	{
		  for (int j = 0; j < n; j++)
		  {
			 if(edge[i][j]==99999)
			 {
             Form4->StringGrid3->Cells[j+1][i+1] = "不可抵達";
			 }
			 else
			 {
			 Form4->StringGrid3->Cells[j+1][i+1] = IntToStr(edge[i][j]);
			 }
		  }

	}

}

void transitive(){
int reach[200][200];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			reach[i][j] = w[i][j];

	for (int k = 0; k < n; k++){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				reach[i][j] = reach[i][j] ||  (reach[i][k] && reach[k][j]);
			}
        }
	}
	// print
	Form4->StringGrid4->RowCount = n+1;
	Form4->StringGrid4->ColCount = n+1;

	for (int i = 1; i <= n+1; i++) {      //xｶbｪ・lｭﾈ
		 Form4->StringGrid4->Cells[i][0] =  i;
	}
	for (int i = 1; i <= n+1; i++) {     //yｶbｪ・lｭﾈ
		 Form4->StringGrid4->Cells[0][i] = i;
	}
	for (int i = 0; i < n; i++) {
		  for (int j = 0; j < n; j++) {
			 Form4->StringGrid4->Cells[j+1][i+1] = IntToStr(reach[i][j]);
		  }

	}
}



// --My function library--end--line--
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
	 int range = 0;
	 int max_range = 0;
	 int LargeInt = 0;
	 range = StrToInt(Edit2->Text);
	 max_range = StrToInt(Edit3->Text);
	 LargeInt = StrToInt(Edit4->Text);
	 n = StrToInt(Edit1->Text);
	 graph(n, range, max_range, LargeInt);
	 print();

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button3Click(TObject *Sender)
{
	 int sor = StrToInt(Edit5->Text);
	 bellman(sor);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button4Click(TObject *Sender)
{
	 floyd();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button5Click(TObject *Sender)
{
	 transitive();
}
//---------------------------------------------------------------------------


