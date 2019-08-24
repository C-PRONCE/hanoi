// 미션3

#include <stdio.h>
#include <windows.h>
 
#define PLATE_MAX 10    
#define SLEEP_TIME 300	  

struct {
	int plate[PLATE_MAX+1];  
    int index;			
} pole[3] = { {0,}, 0 };   
int m_count=0;			 

void startTitle(); 	 
int inputMode();	 
int initTower();		
int inputTo();			
void printTower(); 		 
int solve(int from, int to, int num);		
int m_solve(int from, int to, int num);	
void move(int from, int to); 
int m_FromTo();				   
int checkRule(int from, int to);  
int checkFinish(int to, int tower_num);  

void drawBlock(int size);
void drawBlank(int size);
void drawPole();
 

int main() {

	int tower_num, to, mode;	  
	int is_com;
	
	startTitle(); 	  
	  	
 	tower_num = initTower();
	printf("◎시작 상태◎\n");
	printTower();			
 	to = inputTo();			 
 	mode = inputMode();		

	switch(mode){
		case 1 :
					printf(" 직접 실행=======\n");				
					is_com = m_solve(0, to, tower_num); 
					printf("=================\n");	
					if(is_com ==1)
						printf("Move Count = %d \n", m_count);	
					break;
		case 2 :
					drawPole();
					Sleep(1000); 	 
			
					solve(0, to, tower_num); 	
					printf("-----------------\n");			
					printTower();
					printf("=================\n");
					printf("■ 기둥[0] 에서 기둥[%d]로 원판 이동\n", to);
					printf("  총 %d번 이동하였습니다. \n", m_count); 
					break;
	}
	
    return 0;
}	


void startTitle(){
	printf("\n\n===== Tower of HANOI (하노이 탑) =====\n\n");
}


int inputMode(){
	int num;

	do{
		printf("직접실행은 1번, 자동실행은 2번을 입력하세요: ");
		scanf("%d", &num);
		if(num != 1 && num != 2)
			printf("Error! 1(직접실행) 또는 2(자동실행)를 입력하세요. \n"); 
	}while(num != 1 && num != 2);
	printf("\n");
	
	return num;	 	 
}


int initTower(){ 
	int num;
	int i; 

	do{
		printf("원판의 개수를 입력하세요(1 ~ %d) : ", PLATE_MAX);
		scanf("%d", &num);
		if(num < 1 || num > PLATE_MAX)
			printf("Error! 1 ~ %d 사이의 수를 입력하여주세요. \n", PLATE_MAX); 
	}while(num < 1 || num > PLATE_MAX);
	printf("\n");
	
	for(i=1; i<=num; i++)
		pole[0].plate[i] = num - (i-1);   
	pole[0].index = num;					 
	
	return num;	 	  
}

 
int inputTo(){
	int num;

	do{
		printf("목표기둥 입력하세요 (1 or 2) : ");
		scanf("%d", &num);
		if(num != 1 && num != 2)
			printf("Error! 1 또는 2를 입력하세요. \n"); 
	}while(num != 1 && num != 2);
	printf("\n");
	
	return num;	 	 
}


void printTower() {    
    int i, j;
	
    for(j=0; j<=2; j++) {
    	printf(" %d: ", j);	
        if(pole[j].index == 0 ) printf(" x");   
        else {
			for(i=1; i<=pole[j].index; i++)	 
				printf("%2d ", pole[j].plate[i]);
        }
        printf("\n");
    }
}

  
int solve(int from, int to, int num){	
	int pre_dest;
	
	if(from==0) {
		if(to==1)	pre_dest=2;
		else 		pre_dest=1;
	}else if(from==1){
		if(to==0)	pre_dest=2;
		else		pre_dest=0;	
	}else{
		if(to==0)	pre_dest=1;
		else		pre_dest=0;			
	}

	if(num==1) {
		move(from, to);

		drawPole();	
	}else{
		solve(from, pre_dest, num-1);
		move(from, to);

		drawPole();	
		solve(pre_dest, to, num-1);
	}
	
	m_count++;
	return 1;
}



void move(int from, int to){
	int from_index;
	int to_index;
	
	to_index = pole[to].index;	
	from_index = pole[from].index;
	
	pole[to].plate[ to_index+ 1 ] = pole[from].plate[ from_index ];
	pole[to].index++ ;		

	pole[from].plate[ from_index ] = 0;	  
	pole[from].index-- ;

}

int m_solve(int from, int to, int num){
	int is_move;
	int is_complete;
	 
	while(1){				  
		is_move = m_FromTo(); 			 
		
		if (is_move == 0) {
			printf("Error! \n\a\a");
		}else if(is_move == 9) {
			printf("\n\n\n 0~2 이외의 기둥번호 입력으로 프로그램을 종료합니다. \n");
			is_complete = 0;
			break;	
		}else {		
			printTower();		
			is_complete = checkFinish(to, num);	
		}

		if(is_complete == 1){
			printf(" 축하합니다. \n");
			break;
		}
	}

    return is_complete;
}


int m_FromTo(){
	int from, to;
	int return_value = 9;
	
	printf("   옮길 기둥을 입력하세요. \n");
	printf("   끝내실 땐 0 ~ 2 이외의 번호를 입력하세요. \n");
	printf("   현재 기둥(0~2) -> 목표 기둥(0~2) : ");
	
	do{
		scanf("%d %d", &from, &to);
		if (from<0 || from>2 || to<0 || to>2) 
			break;
		else if(from==to)	 
			printf("Error!! \a 입력된 기둥번호가 같습니다. 다시 입력해주세요. :");
		else {
			return_value = checkRule(from, to);
			break;
		}
			
	}while(from==to);	

  
		if(return_value == 1){

			move(from, to);
			m_count++ ; 	 
		}
	
	return return_value;
}

 
int checkRule(int from, int to){
	int check_value;
	
	if ( pole[from].index == 0)
		check_value = 0;
	else if ( pole[to].index == 0)
		check_value = 1;
	else if ( pole[from].plate[ pole[from].index ] > pole[to].plate[ pole[to].index ] )
		check_value = 0;
	else 
		check_value = 1;

	return check_value;	 
}


int checkFinish(int to, int tower_num){
	
	if(pole[to].index == tower_num)	 
		return 1;	
	 
	return 0;	
		
}

void drawBlock(int size){
	int i;
	for(i=1; i<=size; i++)
		printf("■");
}
	
void drawBlank(int size){
	int i;
	for(i=1; i<=size; i++)
		printf("  ");
}

void drawPole(){
	int i, j;
	
	system("cls");
	for(i=PLATE_MAX; i>=1; i--){
		printf(" | ");
		printf("[%2d] ", i);
		for(j=0;j<=2;j++){
			drawBlock(pole[j].plate[i]);
			drawBlank(PLATE_MAX - pole[j].plate[i]);
				if(pole[j].plate[i]!=0)
					printf("(%2d)",pole[j].plate[i]);
				else
					printf("    ");
		printf(" | ");
		}
		printf("\n");
	}
	printf("        Pole 0                     Pole 1                     Pole 2\n");
	Sleep(SLEEP_TIME);
} 


