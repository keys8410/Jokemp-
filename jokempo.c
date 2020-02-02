#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define B 219

// prot. functs
void gotoxy(int x, int y); // coordenadas
void info_01(); // info >> regras
void info_02(int x, int y, int z); // info >> placar de pontos
void screen_01(); // info >> tela de jogadores
void screen_012(); // info >> tela de jogador 01 
void screen_02(int n); // info >> tela de jogador 02
void jokempo(); // minigame >> pedra, papel e tesoura
void em(); // empate
void pe(); // jog. 00 >> pedra vence tesoura (1 e 3)
void pa(); // jog. 00 >> papel vence pedra (2 e 1)
void te(); // jog. 00 >> tesoura corta o papel (3 e 2)
void placar(int x, int y); // placar final >> vencedor final
void lines(int n); // linhas >> horizontais
void vLines(int n, int x, int y); // linhas >> verticais com coordenadas

/* 
	02 de fevereiro de 2020	
    Departamento de T.I., UniProjeção (Taguatinga, Campus I)
    
    Sistemas de Informação (3º semestre)
    Autor: Yan Almeida Garcia

	00) jokempô
		No Janken-pon, os jogadores devem simultaneamente esticar a mão, na qual cada um formou um símbolo
		(que significa pedra, papel ou tesoura).
		Então, os jogadores comparam os símbolos para decidir quem ganhou, da seguinte forma:

		- Pedra ganha da tesoura (amassando-a ou quebrando-a);
		- tesoura ganha do papel (cortando-o);
		- papel ganha da pedra (embrulhando-a).

		Caso dois jogadores façam o mesmo gesto, ocorre um empate, e geralmente se joga de novo até desempatar. 
		Este jogo possui uma única regra: não é permitido mostrar pedra duas vezes seguidas.
		
		Referência bibliográfica:
			[01]. "Pedra, papel e tesoura", disponível em: https://pt.wikipedia.org/wiki/Pedra,_papel_e_tesoura
			[02]. "Colorindo texto e plano de fundo de programas em C no S.O. Windows", disponível em: "http://personalizandoc.blogspot.com/2012/11/colorindo-texto-e-plano-de-fundo.html"
*/


	// global vars
	int i, j;
	char op;
	
int main(){	
	jokempo();
	
	return 0;
}

// functions
	// coordenadas
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
	// info >> regras
void info_01(){
	int n = 82, o = 80, p = 9, q = 5;
		
	gotoxy(o, 3);
	lines(p);
	printf(" COMO JOGAR ");
	lines(p);
	
	gotoxy(n, 5);
	printf(" O PAPEL EMBRULHA A PEDRA ");
	gotoxy(n, 6);
	printf(" A PEDRA QUEBRA A TESOURA ");
	gotoxy(n, 7);
	printf(" A TESOURA CORTA O PAPEL ");
	
	gotoxy(o, 9);
	lines(30);
	vLines(q, o, 4);
	vLines(q, 109, 4);
}
	// info >> placar de pontos
void info_02(int x, int y, int z){
	int o = 80, p = 11, q = 5;
	
	info_01();
	
	gotoxy(o, 12);
	lines(p);
	printf(" PONTOS ");
	lines(p);
	
	gotoxy(o + 7, 14);
	printf(" JOGADOR 01: %*d ", 2, x);
	gotoxy(o + 7, 15);
	printf(" JOGADOR 02: %*d ", 2, y);
	gotoxy(o + 7, 16);
	printf(" EMPATES:    %*d ", 2, z);
	
	gotoxy(o, 18);
	lines(30);
	vLines(q, o, 13);
	vLines(q, 109, 13);
	
	screen_01();
}
	// info >> tela de jogadores
void screen_01(){
	int n = 10, o = 8, p = 3, r = 16;
	
	gotoxy(o, 3);
	lines(p);
	printf(" JOGADOR 01 ");
	lines(p);
	
	printf(" JOGADOR 02 ");
	lines(p);
	
	gotoxy(n, 5);  
	printf(" 1 - PEDRA         PEDRA - 1");
	gotoxy(n, 6);
	printf(" 2 - PAPEL         PAPEL - 2");
	gotoxy(n, 7);
	printf(" 3 - TESOURA     TESOURA - 3");
	
	gotoxy(o, 9);
	lines(33);
	vLines(5, o, 4); // left
	vLines(5, 24, 4); // middle
	vLines(5, 40, 4); // right
}
	// info >> 
void screen_012(){
	int n = 10, o = 8, p = 3, r = 16;
		
	gotoxy(o, 12);
	lines(r);
	
	gotoxy(n, 14);
	printf(" JOG. 01: ");
	gotoxy(o, r);
	lines(r);
	vLines(p, o, 13);
	vLines(p, 23, 13);
}
	// info >> tela de jogador 02
void screen_02(int n){
	int o = 25, p = 3, q = 16;
	
	Sleep(350);
	
	gotoxy(o, 12);
	lines(q);
	
	gotoxy(27, 14);
	printf(" JOG. 02: %d", n);
	gotoxy(o, 16);
	lines(q);
	vLines(p, o, 13);
	vLines(p, 40, 13);
	
}
	// minigame >> pedra, papel e tesoura
void jokempo(){
	int player, cpu;
	int pP = 0, pC = 0, emp = 0; // contagem de pontos >> player e CPU
	
	system("color 17");
	
	do{		
		do{		
			system("cls");			
			info_02(pP, pC, emp);
			screen_012();
			
			gotoxy(20, 14); // cursor scanf
			scanf(" %d", &player);
		}while(player < 1 || player > 3);

		srand(time(NULL));
		cpu = 1 + rand() % 3;
		
		
		switch(cpu){
			case 1:
				screen_02(cpu);
	
				break;
			case 2:
				screen_02(cpu);
				
				break;
			case 3:
				screen_02(cpu); 

				break;
		}
			// condiçoes para vencer >> player x CPU
		if(player == 1 && cpu == 3){ 
			pe();
			pP++;
		}else if(player == 2 && cpu == 1){
			pa();
			pP++;
		}else if(player == 3 && cpu == 2){
			te();
			pP++;
		}else if(cpu == 1 && player == 3){ 
			pe();
			pC++;
		}else if(cpu == 2 && player == 1){
			pa();
			pC++;
		}else if(cpu == 3 && player == 2){
			te();
			pC++;
		}else{ // empate >> jog. 01 e jog. 02
			em();
			emp++;
		}
		
		Sleep(175);
		info_02(pP, pC, emp);
		
		gotoxy(8, 19);
		printf("Deseja jogar novamente [S/N]: ");
		
		fflush(stdin);
		scanf(" %c", &op);
	}while(toupper(op) == 'S');	
	
	placar(pP, pC);
}
// condição de vitória
	// Pedra ganha da tesoura (quebrando-a).
	// Tesoura ganha do papel (cortando-o).
	// Papel ganha da pedra (embrulhando-a). 

	// empate
void em(){
	int n = 3, m = 49;
	
	Sleep(225);
	
	gotoxy(m, 3);
	lines(n);
	printf(" JOGUE NOVAMENTE ");
	lines(n);
	
	gotoxy(51, 5);
	printf(" TIVEMOS UM EMPATE ");
	
	gotoxy(m, 7);
	lines(23);
	
	vLines(3, m, 4);
	vLines(3, 71, 4);
}
	// jog. 00 >> pedra vence tesoura (1 e 3)
void pe(){
	int n = 5, m = 46;
	
	Sleep(225);
	
	gotoxy(m, 3);
	lines(n);
	printf(" TEMOS UM VENCEDOR ");
	lines(n);
	
	gotoxy(48, 5);
	printf(" A PEDRA QUEBRA A TESOURA ");
	
	gotoxy(m, 7);
	lines(29);
	
	vLines(3, m, 4);
	vLines(3, 74, 4);
}
	// jog. 00 >> papel vence pedra (2 e 1)
void pa(){
	int n = 5, m = 46;
	
	Sleep(225);
	
	gotoxy(m, 3);
	lines(n);
	printf(" TEMOS UM VENCEDOR ");
	lines(n);
	
	gotoxy(48, 5);
	printf(" O PAPEL EMBRULHA A PEDRA ");
	
	gotoxy(m, 7);
	lines(29);
	
	vLines(3, m, 4);
	vLines(3, 74, 4);
}
	// jog. 00 >> tesoura corta o papel (3 e 2)
void te(){
	int n = 5, m = 46;
	
	gotoxy(m, 3);
	lines(n);
	printf(" TEMOS UM VENCEDOR ");
	lines(n);
	
	gotoxy(48, 5);
	printf(" A TESOURA CORTA O PAPEL ");
	
	gotoxy(m, 7);
	lines(29);
	
	vLines(3, m, 4);
	vLines(3, 74, 4);
}
	//	placar final >> vencedor final
void placar(int x, int y){
	int e = 144, n = 7, o = 12, p = 47, q = 3;
	
	gotoxy(p, o);
	lines(n);
	printf(" VOC%c VENCEU ", 210);
	lines(n);
	
	vLines(q, p, o + 1);
	vLines(q, 73, o + 1);

	gotoxy(p, 16);
	lines(27);
	
	gotoxy(p + 2, 14);

	if(x > y) printf(" PARAB%cNS, JOGADOR 01! ", e); // se jog. 01 vencer
	else if(x < y) printf(" PARAB%cNS, JOGADOR 02! ", e); // se jog. 02 vencer
	else printf(" OH N%cO. JOGO EMPATADO ", 199);
	getch();

	system("cls");
}
	// linhas >> horizontais
void lines(int n){
	for(i = 0; i < n; i++) printf("%c", B);
}
	// linhas >> verticais com coordenadas
void vLines(int n, int x, int y){	
	for(i = 0; i < n; i++){
		gotoxy(x, y + i);
		printf("%c", B);	
	} 
}	
