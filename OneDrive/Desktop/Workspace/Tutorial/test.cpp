#include<stdio.h>
#include<conio.h>
#define MAX 100
int daDuyet[100];

struct Graph
{
    int numbervertices;
    int a[MAX][MAX];
};

struct edge
{
    int v1,v2,weighted; 
    /* V1 : dinh 1 
        weighted : trong so 
    */
};

void docFile(Graph &x){
	FILE *f;
	f = fopen("prim3.txt","rt");
	if(f == NULL){
		printf("Khong mo duoc file !");
		return;
	}
	// doc du lieu
	fscanf(f,"%d",&x.numbervertices); // doc so 6 vao dinh 
	for(int i =0;i < x.numbervertices; i++)
		for(int j = 0; j < x.numbervertices; j++)
			fscanf(f,"%d",&x.a[i][j]);
		
		

	fclose(f); // dong file
		
}

int ktVoHuong(Graph g){
	for(int i=0;i< g.numbervertices;i++)
		for(int j=0; j<g.numbervertices;j++)
			if(g.a[i][j] != g.a[j][i])
				return 0; // return 0 do thi co huong 
			return 1;// return 1 do thi vo huong
}
void xuatDT(Graph x){
	printf("%3d\n",x.numbervertices);
	for(int i =0; i < x.numbervertices; i++)
	{
		// xuat dong i ra
		for(int j=0; j<x.numbervertices;j++)
			printf("%3d",x.a[i][j]);
		// xuong dong
		printf("\n");
	}
}

void DFS(int s, Graph g){
    daDuyet[s]=1;
    for (int i = 0; i < g.numbervertices; i++)
    {
        if (daDuyet[i]==0 && g.a[s][i]!=0)
        
            DFS(i,g);
    }
}
int timSoTPLT(Graph g){
    for (int i = 0; i < 100; i++)
    
        daDuyet[i]=0;
    
    int soTPLP=0;
    for (int i = 0; i < g.numbervertices; i++)
    {
        if (daDuyet[i]==0)
        {
            soTPLP++;
            DFS(i,g);
        }
        
    }
    return soTPLP;
    
}

void prim(Graph g){
    if (timSoTPLT(g) != 1)
    {
        printf("\nDO THI KHONG LIEN THONG !");
        return;
    }
    int vt[100]={0},nET= 0;// khai bao va 
                            //khoi tao tap hop VT chua cac dinh thuoc cay khung
    edge ET[100];           // khai bao tap hop ET, chua cac canh thuoc cay khung 
                            // nET: la so canh cua cay khung
    vt[0]=1;
    int min;
    edge minEdge;
    while (nET<g.numbervertices-1)
    {
        min = 1000;// 1000 lon hon tat ca cac trong so cua do thi
        for (int i = 0; i < g.numbervertices; i++)
        {
            if (vt[i]==1)// cac dinh thuoc vt
            {
                for (int j = 0; j < g.numbervertices; j++)
                {
                    if (vt[j]==0 && g.a[i][j]!=0 && g.a[i][j] < min)
                    {
                        minEdge.v1=i;
                        minEdge.v2=j;
                        minEdge.weighted=g.a[i][j];
                        min = g.a[i][j];
                    }
                }
            }
        }
        ET[nET++]=minEdge;
        vt[minEdge.v2]=1;
    }
    // xuat cay khung nho nhat
    printf("\nKRUSKAL ------CAY KHUNG NHO NHAT GOM CAC CANH :\n");
    int totalWeighred =0;
    for (int i = 0; i < nET; i++)
    {
        totalWeighred += ET[i].weighted;
        printf("\nt(%d,%d) = %d",ET[i].v1,ET[i].v2,ET[i].weighted);
    }
    printf("\nCAY KHUNG CO TONG TRONG SO = %d",totalWeighred);
}  

void kruskal(Graph g){
    edge e[200], ET[100];// khai bao 2 tap hop: E: moi canh cua do thu, ET: cac canh cua cay khung
    int nE=0,nET=0;// khoi tao nE va ET rong 
    // doc het cac canh cua do thi chua vao E
    for (int i = 0; i < g.numbervertices-1; i++)
    {
        for (int j = 0; j < g.numbervertices+1; j++)
        {
            if (g.a[i][j] != 0)
            {
                e[nE].v1 =i;
                e[nE].v2 =j;
                e[nE].weighted =g.a[i][j];
                nE++;
            }
        }
    }
    // sap xep cac canh thuoc E trong so tang dan
    edge tam;
    for (int i = 0; i < g.numbervertices; i++)
    {
        for (int j = 0; j < g.numbervertices; j++)
        {
            if (e[i].weighted > e[j].weighted)// sai thu tu
            {
                tam=e[i];
                e[j]=e[i];
                e[j]=tam;
            }
            
        }
        
    }
    // xet tung canh cua E
    int nhan[100];
    for (int i = 0; i < nE; i++)// khoi tao rung gom so dinh cay, 
    {
        nhan[i]=i;
    }
    for (int i = 0; i < nE; i++)
    {
        if (nhan[e[i].v1] != nhan[e[i].v2])
        {
            ET[nET++]=e[i]; // dua no vao cay khung
            // sua nhan cho e[i].v1 va e[i].v2 
            int giatri=nhan[e[i].v2];
            for (int k = 0; i < g.numbervertices; k++)
            {
                if (nhan[k]==giatri)
                
                    nhan[k]=nhan[e[i].v1];
            }
        }
        if (nET == g.numbervertices-1)
        {
            break;
        }
        
    }
    printf("\nKRUSKAL ------CAY KHUNG NHO NHAT GOM CAC CANH :\n");
    int totalWeighred =0;
    for (int i = 0; i < nET; i++)
    {
        totalWeighred += ET[i].weighted;
        printf("\nt(%d,%d) = %d",ET[i].v1,ET[i].v2,ET[i].weighted);
    }
    printf("\nCAY KHUNG CO TONG TRONG SO = %d",totalWeighred);
}  



int main(){
    Graph g;
    docFile(g);
    xuatDT(g);
    prim(g);
    kruskal(g);

    return 0;

}