#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define R_MAX 2147483647
static long long unsigned int SEED = 0x1;

int max(int a,int b);

int cmpfunc (const void * a, const void * b);

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

void srnd(int seed);

int rnd(int from, int to);

void prvotna_draha(int herna_draha[], int n);

void generovanie_blockerov(int m1,int n, int herna_draha[],int blockery[]);

void generovanie_boosterov(int m2,int n, int herna_draha[],int boostery[]);

void vypis_blockerov_a_boosterov(int blockery[],int boostery[], int m1, int m2);



//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int main() {
    int seed, n, m1, m2, tah = 0, R1, R2, d, pomocna,winner;
    scanf("%d %d %d %d", &seed, &n, &m1, &m2);
    if (n / 2 < (m1 + m2)&&seed<1) {
        return 1;
    }
    srnd(seed);

    int herna_draha[n], blockery[m1], boostery[m2], hraci[] = {2, 1}, pos[] = {-1, -1}, boost[] = {0, 0}, hotspot[n];

    prvotna_draha(herna_draha,n);
    prvotna_draha(hotspot,n);
    generovanie_blockerov(m1,n,herna_draha,blockery);
    qsort(blockery, m1, sizeof(int), cmpfunc);
    generovanie_boosterov(m2,n, herna_draha,boostery);
    qsort(boostery, m2, sizeof(int), cmpfunc);
    vypis_blockerov_a_boosterov(blockery, boostery, m1, m2);

    while(pos[tah%2]<n){
        tah++;
        printf("\n[%d,%d] ",tah,hraci[tah%2]);
        printf("[%d,%d] ",pos[tah%2],boost[tah%2]);
        R1=rnd(1, 6);
        R2=rnd(1, 6);
        printf("[%d,%d] ",R1,R2);
        if(pos[tah%2]==-1){
            if(R1+R2>7){
                pos[tah%2]=(R1+R2)-7;
                d=pos[tah%2];
                hotspot[d]++;
            }
            if (pos[tah%2] == pos[(tah+1)%2]){
                pos[(tah+1)%2] = -1;
            }
            else if ((pos[tah%2] == 2) && (boost[tah%2] == 0)){
                pos[(tah)%2] = -1;
            }

            else if ((pos[tah%2] == 2) && (boost[tah%2] > 0)){
                boost[tah%2]++;
            }
            printf("[%d,%d]",pos[tah%2],boost[tah%2]);
        }
        else{
            if((pos[(tah+1)%2]>=0&&pos[tah%2]<pos[(tah+1)%2]&&R1==6&&R2==6)||(pos[(tah+1)%2]>=0&&pos[tah%2]>pos[(tah+1)%2]&&R1==1&&R2==1)){
                d=pos[(tah+1)%2];
                pomocna=pos[tah%2];
                pos[(tah+1)%2]=pomocna;
                pos[tah%2]=d;
                hotspot[d]++;
                hotspot[pomocna]++;
            }
            else{
                d=pos[tah%2]+max(R1,R2)+boost[tah%2];
                hotspot[d]++;
                pos[tah%2]=d;
                if(pos[tah%2]==pos[(tah+1)%2]){
                    pos[(tah+1)%2]=-1;
                }
                switch (herna_draha[d]){
                    case 1:
                        herna_draha[d]=0;
                        if(boost[tah%2]>0){
                            boost[tah%2]=0;
                        }
                        else{
                            pos[tah%2]=-1;
                        }
                        break;
                    case 2:
                        herna_draha[d]=0;
                        boost[tah%2]++;
                        break;
                }
            }
            printf("[%d,%d]",pos[tah%2],boost[tah%2]);
        }
        winner=hraci[tah%2];
    }
    printf("\nWINNER:%d",winner);
    qsort(hotspot, n, sizeof(int), cmpfunc);
    printf("\nHOTSPOT:%d",hotspot[n-1]);

    return 0;
}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

int cmpfunc (const void * a, const void * b) {
    return (*(int *) a - *(int *) b);
}

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

void prvotna_draha(int herna_draha[], int n){
    for(int i=0;i<=n;i++)
    {
        herna_draha[i]=0;
    }
}

void generovanie_blockerov(int m1,int n, int herna_draha[],int blockery[]) {
    int x = 0, blocker;
    while (x < m1) {
        blocker = rnd(1, n - 1);
        if (herna_draha[blocker] != 1) {
            herna_draha[blocker] = 1;
            blockery[x]=blocker;
            x++;
        }
    }
}

void generovanie_boosterov(int m2,int n, int herna_draha[],int boostery[]) {
    int x = 0, booster;
    while (x < m2) {
        booster = rnd(1, n - 1);
        if (herna_draha[booster] != 1&&herna_draha[booster]!=2) {
            herna_draha[booster] = 2;
            boostery[x]=booster;
            x++;
        }
    }
}

void vypis_blockerov_a_boosterov(int blockery[],int boostery[], int m1, int m2){
    printf("BLOCK:");
    for(int i=0;i<m1;i++){
        printf("%d ",blockery[i]);
    }
    printf("\nBOOST:");
    for(int i=0;i<m2;i++){
        printf("%d ",boostery[i]);
    }
}
int max(int a,int b){
    if(a<b){
        return b;
    }
    else{
        return a;
    }
}