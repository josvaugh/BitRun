//to compile: gcc -o bitrun Bit_Run.c -lncurses
#include <stdio.h>
#include<stdlib.h>
#include <wchar.h>
#include <curses.h>
#include  <ctype.h>
//#include  <pthread.h>
#include <termios.h>
#include<stdio.h>
#include<curses.h>
#include<unistd.h>
#include<stdlib.h>
//ALL VARIABLES MUST REMAIN IN GLOBAL
int i=0,ROW=39,COL=25,j=0,k=1,x=0,y=0,s=1,count=0,money=0,pos=24,t;
float percent=1,time=1;//Don't touch
void game();
void moveobs();
void spawn();

void main_menu_english();
void main_menu_japanese();
void main_menu_spanish();
void main_menu_french();
void menu_languages();
void menu_instuction_english();
void menu_instruction_spanish();
void menu_instruction_japanese();
void menu_instruction_french();

//void start_game();
//void menu_difficulty();
void menu_languages_spanish();
void menu_languages_japanese();
void menu_languages_french();




int main(){
	main_menu_english();
}
void game(){
	initscr();     //in ncurses
    timeout(0);
    curs_set(0);
	while(x<50){	
		move(x,y);
		addstr("|");
		x++;
	}
	x=0;
	y=51;
	while(x<50){
                move(x,y);
                addstr("|");
                x++;
        }

    while(1)
    {
	usleep(12000-time);//DEFAULT GAME SPEED DON'T TOUCH
	noecho();//DISABLE OUTPUT
	move(ROW,COL);//GAME
	if (inch()== '='){//IF COLLISION, END GAME
        	move(100,30);//PRINT PERCENT SPEED POSITION
       	 	printw("You dead!");
		refresh();
		sleep(5);
		scanf("%d",&t);
		endwin();
		exit(0);
	}
	if (inch()== '$'){//IF COLLISION ADD MONEY
		money++;
		delch();
	}
	move(ROW,COL);//GAME
        i=getch();//RECIEVE KEYBOARD INPUT
	echo();//ENABLE OUTPUT
	switch(i){
		case 'A':
		//	UP
			break;
		case 'B':
		//	DOWN;
			break;
		case 'C':
		//	RIGHT
			if (pos<48){
			getyx(stdscr,ROW,COL);//GET CURRENT POSTION
			move(ROW,0);//GAME
			clrtoeol();//CLEAR LINE
			COL++;//INCREASE COLUMN
			move(ROW,COL);//GAME
			addstr("O");//  <-- GAME CHARACTER
			pos++;
			}
			break;
		case 'D':
		//	LEFT
			if (pos>0){
			getyx(stdscr,ROW,COL);//CURRENT POSITION
                        move(ROW,0);//GAME
                        clrtoeol();//CLEAR LINE
			COL--;//DECREASE COLUMN
                        move(ROW,COL);//GAME
			addstr("O");//   <-- GAME CHARACTER
			pos--;
			}
			break;
		case ' ':
		//	SPACE
			break;
		default:
			x=40;//ROW
			y=50;//COLUMN
			while(y>1)//DELETE OBJECTS BEHIND GAME CHARACTER
			{
				move(x,y);
				if(inch()!=' '){//IF ANYTHING BUT A SPACEBAR
					addstr(" ");//ADD A SPACE
				}
				y--;
			}
			move(39,0);
			addstr("|");
			move(39,51);
			addstr("|");
			move(ROW,COL);
			addstr("O");// <-- REPLACE GAME CHARACTER
			break;
	}
	move(ROW,COL);
        if(i>0)
           	i=0;
        else
            	i=1;
	int random=rand() % 5 + 2;//SPAWN # OBJECTS IN ROW (BETWEEN 2 + 5)
	while (random>0){
		if (j>20 + rand() % 350){//SPACE BETWEEN OBJECTS
			spawn();
	    		j=1;
		}
		else
			j++;//DONT TOUCH
		random--;//DONT TOUCH
	}
	if (k>150){//EVERY 150 iterations speed up game
		k=1;
		count++;
		if(time<9000)//DON'T TOUCH
			time=time+50;//SPEED UP GAME EXPONENTIALLY
	}
	else
		k++;//DONT TOUCH
	y=20;
	if (s>10)
	{
		moveobs();
		s=1;
	}
	else
		s++;
	move(0,70);
	percent=((9000-time)/9000);
	percent=1-percent;
	percent=percent*100;
	move(0,70);//PRINT PERCENT SPEED POSITION
	printw("%.0f%%",percent);
	percent=9000;
	move(0,63);//PRINT MONEY POSITION
	printw("$%d",money);
	move(0,75);//PRINT TIME TAKEN POSTION
	printw("%d",count);
        move(ROW,COL);
	refresh();
    }
    endwin();
    return 0;
}

void moveobs()//THIS WHOLE FUNCTION JUST MOVES OBJECTS
{
	y=60;
	while(y>1){
		x=0;
		while(x<40){
                       if (mvinch(x,y)!= ' ' && mvinch(x,y)!='O'){// <- CHARACTER
                                if (mvinch(x,y) == '='){
					move(x,y);
                                	delch();
					insch(' ');
                                	x++;
                                	move(x,y);
                                	addstr("=");
				}
				if (mvinch(x,y) == '$'){
					move(x,y);
                                        delch();
                                        insch(' ');
                                        x++;
                                        move(x,y);
                                        addstr("$");
				}
				x++;
                        }
                        else{
                                move(x,y);
                                x++;
                        }
        	}
		y--;
	}
}
void spawn()//THIS WHOLE FUNCTION SPAWNS OBJECTS
{
       	int cash;
	getyx(stdscr,ROW,COL);
	int limit=rand() % 5;
	while(limit>0){
		cash=rand() % 10;
		move(0,2 + rand() % 48);
		if (cash==9){
			addstr("$");
		}
		else{
			addstr("=");
		}
		limit--;
	}
}
//#######################################################################################

void main_menu_english(){

char answer;

	printf("##################################################\n");
	printf("			BitRun			   \n ");
	printf("##################################################\n");
	printf("		       Welcome			  \n");
	printf("S -> Start			I -> Instructions\n ");
	printf("L -> Languages			E -> Exit	\n");
	while(1){
	switch(getchar()){
		case 's':
		case 'S': game(); break;
		case 'l':
		case 'L': menu_languages(); break;
		case 'i':
		case 'I': menu_instruction_english(); break;
		case 'e':
		case 'E': exit(1); break;
		default:  break;
		//case 'd':
		//case 'D': menu_difficulty();
}
}//switch


}//main_menu_english



//######################################################################################

void menu_languages(){

	char answer;

	printf("##################################################\n");
	printf("		Please Select a Language	  \n");
	printf("S -> Spanish 			J -> Japanese	  \n");
	printf("F -> French			E -> English	  \n");
	printf("B -> Back					  \n");



	t=getchar();
        switch(getchar()){
                case 's':
                case 'S': main_menu_spanish(); break;
                case 'f':
                case 'F': main_menu_french();	break;
                case 'j':
                case 'J': main_menu_japanese(); break;
                case 'e':
		case 'b':
		case 'B':
                case 'E': main_menu_english(); break;
		default:  break;

                }//switch

}//menu_languages


//#########################################################################################

void main_menu_spanish(){

 char answer;

        printf("##################################################\n");
        printf("                        BitRun                     \n ");
        printf("##################################################\n");
        printf("                       Bienvenido                    \n");
        printf("C -> Comenzar                      I -> Instrucciones\n ");
        printf("L -> Lenguages                     S -> Salir       \n");

        switch(getchar()){
                case 'c':
                case 'C': game(); break;
                case 'l':
                case 'L': menu_languages_spanish(); break;
                case 'i':
                case 'I': menu_instruction_spanish(); break;
                case 's':
                case 'S': exit(1); break;
		default:  break;
                //case 'd':
                //case 'D': menu_languages();

                }//switch
}//main_menu_spanish

//#########################################################################################

void main_menu_japanese(){

char answer;

        printf("####################################################\n");
        printf("                        BitRun                     \n ");
        printf("####################################################\n");
        printf("                 ã‚ˆã†ã“ã        	\n");
        printf("S -> å§‹ã‚ã‚‹        I -> ã‚¤ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚·ãƒ§ãƒ³\n ");
        printf("L -> è¨€èªž           E -> å‡ºã‚‹  \n");


	getchar();
        switch(getchar()){
                case 's':
                case 'S': game(); break;
                case 'l':
                case 'L': menu_languages_japanese(); break;
                case 'i':
                case 'I': menu_instruction_japanese(); break;
                case 'e':
                case 'E': exit(1); break;
		default: break;
               // case 'd':
               // case 'D': menu_difficulty();

                }//switch


}//main_menu_japanese

//###############################################################################################

void menu_languages_japanese(){


char answer;

        printf("##################################################\n");
        printf("         è¨€èªžã‚’æ±ºã‚ã¦ãã ã•ã„   \n");
        printf("S -> ã‚¹ãƒšã‚¤ãƒ³èªž    J -> æ—¥æœ¬èªž     \n");
        printf("F -> ãƒ•ãƒ©ãƒ³ã‚¹èªž   E -> è‹±èªž      \n");
        printf("B -> æˆ»ã‚‹                                         \n");



	 while(1){
        switch(getchar()){
                case 's':
                case 'S': main_menu_spanish();
                case 'f':
                case 'F': main_menu_french();
                case 'j':
		case 'b':
		case 'B':
                case 'J': main_menu_japanese();
                case 'e':
                case 'E': main_menu_english();


                }//switch
                }//while



}//japanese_languages_menu

//#################################################################################################

void main_menu_french(){

  char answer;

        printf("##################################################\n");
        printf("                        BitRun                     \n ");
        printf("##################################################\n");
        printf("                       Bienvenue                    \n");
        printf("E -> DÃ©marrer                      I -> Instuctions\n ");
        printf("L -> Lengues                     S -> Sortie       \n");



         while(1){
        switch(getchar()){
                case 'e':
                case 'E': game(); break;
                case 'l':
                case 'L': menu_languages_french(); break;
                case 'i':
                case 'I': menu_instruction_french(); break;
                case 's':
                case 'S': exit(1); break;
                //case 'd':
                //case 'D': menu_difficulty();

                }//switch
                }//while


}//main_menu_french

//############################################################################################################

void menu_languages_spanish(){


       char answer;

        printf("##################################################\n");
        printf("           Por favor seleccione un lenguage          \n");
        printf("E -> EspaÃ±ol                    J - Japons\n");
        printf("F -> FrancÃ©s                    I -> InglÃ©s   \n");
        printf("A -> AtrÃ¡s                                         \n");



         while(1){
        switch(getchar()){
                case 'e':
		case 'a':
		case 'A':
                case 'E': main_menu_spanish();
                case 'f':
                case 'F': main_menu_french();
                case 'j':
                case 'J': main_menu_japanese();
                case 'i':
                case 'I': main_menu_english();


                }//switch
                }//while



}//menu_languages_spanish

//##############################################################################################

void menu_languages_french(){

        char answer;

        printf("##################################################\n");
        printf("        S'il vous plaÃ®t sÃ©lectionner une langue          \n");
        printf("E -> Espagnol                    J -Japonais\n");
        printf("F -> FranÃ§ais                   A -> Anglais   \n");
        printf("V -> Verso                                         \n");


         while(1){
        switch(getchar()){
                case 'e':
                case 'E': main_menu_spanish();
                case 'v':
		case 'V':
	        case 'f':
                case 'F': main_menu_french();
                case 'j':
                case 'J': main_menu_japanese();
                case 'a':
                case 'A': main_menu_english();


                }//switch
                }//while


}//menu_languages_french

//##################################################################################################

void menu_instruction_english(){
	printf("########################################################\n");
	printf("			Instructions			\n");
	printf("Controls: Arrow Keys");
	printf("Avoid the obstacles by using the left and right arrow keys.\n");
	printf("The score will be determined by the times that measures how\n");
	printf("long you last in the game. If an obstacle hits you the game\n");
	printf("will end.\n");
	printf("Press B to return.\n");

	while(1){
	switch(getchar()){
		case 'b':
		case 'B':main_menu_english();
}//switch
}//while

}//instruction_english

//#####################################################################################################

void menu_instruction_japanese(){
	printf("########################################################\n");
        printf("              ã‚¤ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚·ãƒ§ãƒ³                    \n");
        printf("ã‚³ãƒ³ãƒˆãƒ­ãƒ¼ãƒ«: ã‚¢ãƒ­ãƒ¼ã‚­ãƒ¼ã‚¹\n");
        printf("å³ã¨å·¦ã®ã‚¢ãƒ­ãƒ¼ã‚­ãƒ¼ã‚¹ã‚’ä½¿ã£ã¦éšœå®³ã‚’é¿ã‘ã‚‹\n");
        printf("ã“ã®ã‚²ãƒ¼ãƒ ã¯ã‚¿ã‚¤ãƒžãƒ¼ãŒã‚ã‚‹ã‹ã‚‰ãã‚Œã¯ãƒ—ãƒ¬ãƒ¤ãƒ¼ã®ã‚¹ã‚³ã‚¢ã§ã™\n");
        printf("éšœå®³ã‚’è§¦ã£ãŸã‚‰ã‚²ãƒ¼ãƒ ã¯çµ‚ã‚ã‚‹\n");
        printf("B ã‚’ãƒ—ãƒ¬ã‚¹ã—ã¦æˆ»ã‚‹.\n");

        while(1){
        switch(getchar()){
                case 'b':
                case 'B':main_menu_japanese();
}//switch
}//while

}//jap_inst

//######################################################################################################

void menu_instruction_spanish(){
	printf("########################################################\n");
        printf("                        Instrucciones                    \n");
        printf("Controles: Flechas");
        printf("Evita los obstaculos usando las flechas para moverte hacia los lados.\n");
        printf("La puntuaciÃn³ sera determinada por el reloj del juego\n");
        printf("Si tocas a un obstaculo, el juego terminarÃ¡.\n");
        printf("Oprima B para regresar.\n");

        while(1){
        switch(getchar()){
                case 'b':
                case 'B':main_menu_spanish();
}//switch
}//while

}//inst_spa

//#####################################################################################################

void menu_instruction_french(){
	 printf("########################################################\n");
        printf("                        Instructions                    \n");
        printf("contrÃ´les:flÃ¨ches");
        printf("Ã©viter les obstacles et utilisez les flÃ¨ches pour se dÃ©placer.\n");
        printf("Le score sera dÃ©terminÃ© par la minuterie.\n");
        printf("Si vous touchez un obstacle le jeu se terminera.\n");
        printf("Appuyez sur B pour revenir.\n");

        while(1){
        switch(getchar()){
                case 'b':
                case 'B':main_menu_french();
}//switch
}//while

}//fr_inst
