#include<stdio.h>
#include<stdlib.h>

#define MAX_LENGTH 15

void printStr(int **arr, int size);
//arrayi renk stringleri cinsinden bastirir
void shiftRow(int *arr, int size);
//arrayin girilen satirini saga shift eder
int checkUp(int **arr, int i, int size);
//ilgili satir ust satirlar ile sarti sagliyor mu kontrol eder
int backTrack(int **arr, int i, int size);
//verilen matris uygun duruma getirilebiliyorsa getirip asama asama 
//bastirir, getirilemiyorsa sonucun olmadigini bildirir

int main(){
	int i, j, sec=1, n;
	int **arr;
	char renkler[8][MAX_LENGTH] = {"Sari","Mavi","Yesil","Mor","Gri","Lila","Cyan","Siyah"};
	
	for(i=0; i<8; i++)
		printf("%d=%s ",i,renkler[i]);
	printf("\n\n");
	
	
	while(sec == 1){	
		do{
			printf("\nMatris boyutunu(NxN) giriniz:\n");
			scanf("%d",&n);
		}while(n<3 || n>8);
		arr=(int**)malloc(sizeof(int*)*n);
		for(i=0;i<n;i++)
			arr[i]=(int*)malloc(sizeof(int)*n);		//dynamic memory allocation for NxN array
		
		if(arr == NULL){
			printf("Array icin yer ayrilamadi.");
			exit(0);
		}
		
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				printf("Matris[%d][%d] 'i giriniz: \n",i+1,j+1);
				scanf("%d",&arr[i][j]);			//kullanicidan matris deger alimi
			}
		}
		system("CLS");
		printf("Girilen matris:\n");
		printStr(arr,n);				//alinan sayi matrisinin renk matrisi karsiligi
		backTrack(arr,1,n);				//cozum islemi
		
		printf("Cikmak icin 0, tekrar denemek icin 1 tuslayiniz\n");
		scanf("%d",&sec);
		system("CLS");
		fseek(stdin,0,SEEK_SET);
		for(i=0;i<n;i++){ 
    		free(arr[i]);
		}
    	free(arr);
	}
	
	return 0;
}

void printStr(int **arr, int size){
	char renkler[8][MAX_LENGTH] = {"Sari","Mavi","Yesil","Mor","Gri","Lila","Cyan","Siyah"};
	int i,j,indis;
	printf("\n");
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			indis = arr[i][j];
			printf("%s	",renkler[indis]);
		}
		printf("\n\n");
	}
}

void shiftRow(int *arr, int size){
	int i,basaAl;
	basaAl = arr[size-1];	//satirdaki son eleman basa alinacak
	for(i=1; i<size; i++){
		arr[size-i] = arr[size-i-1];	//shift islemi
	}
	arr[0] = basaAl;
}

int checkUp(int **arr, int row, int size){
	int i,j,tmp;
	
		for(j=0; j<size; j++){	//her bir satir elemani icin
			tmp = arr[row][j];
			for(i=row-1; i>=0; i--){
				if(tmp == arr[i][j]){
					return 0;	//ilgili satirda ayni sutun icin yukarda ayni eleman varsa 0 dondur
				}
			}
		}
		return 1; //ust satirlarda ayni elemanlar yoksa 1 dondur	
}

int backTrack(int **arr, int row, int size){
	int i,j;
	if(row >= size){		//eger son row da sartlari saglamissa
		printf("Matris istenilen hale getirildi.Sonuc:\n",row);
		printStr(arr,size);		//initial condition saglandi,matrisi bastir 1 dondur
		return 1;
	}
	else{
		for(i=0;i<size;i++){ 
			if(checkUp(arr,row,size)){ 			//girilen satir numarasindan itibaren
				printf("%d. satira kadar duzeltildi:\n",row);
				printStr(arr,size);
				backTrack(arr,row+1,size);		//satirimiz ust satirlara uyuyorsa sonraki satira gec
				return -1;						//ilk dogru sonuc yeterli, return -1 diger sonuclari da 
			}									//gostermesini engelliyor
			if(i<size-1){			
					shiftRow(arr[row],size); //eger uymuyorsa suanki satiri bir saga kaydir
					//printf("%d. satir saga kaydirildi:\n",row);
					//printStr(arr,size);
				}			
		}
	}
	printf("Cozum bulunamadi\n");
	return 0;				
}

