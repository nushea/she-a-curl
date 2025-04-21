// terminal is presumed to be 72x24 or so

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 0x400
#define RESET "\x1b[0m"
#define WIDTH 80
#define HEIGH 24
#define DEFBG 40
#define DEFFG 97
void debugStrings();
void mapPrint();
void printer(int posX, int posY, int bg, int fg, char * output){ //{{{
	if(bg > 0xFFFFFF)
		bg=0xFFFFFF;
	if(fg > 0xFFFFFF)
		fg=0xFFFFFF;
	if(bg == -1)
		bg = DEFBG;
	if(fg == -1)
		fg = DEFFG;
	char * oup;
	oup = malloc(BUFFER);
    memset(oup, 0, BUFFER);
	if(bg > -1)
		sprintf(oup, "%s\x1b[%i;%iH\x1b[38;2;%i;%i;%i;48;2;%i;%i;%im%s%s", RESET,posY, posX, fg/0x10000, (fg/0x100)%0x100, fg%0x100, bg/0x10000, (bg/0x100)%0x100, bg%0x100, output, RESET);
	printf("%s", oup);
	printf(RESET);
	free(oup);
} //}}}
//
void sprinter(int posX, int posY, int bg, int fg, char * output){ //{{{
	char * oup;
	oup = malloc(BUFFER);
    memset(oup, 0, BUFFER);
	if(bg > -1)
		sprintf(oup, "%s\x1b[%i;%iH\x1b[%i;%im%s%s", RESET,posY, posX, fg, bg, output, RESET);
	printf("%s", oup);
	printf(RESET);
	free(oup);
} //}}}

void printCenterX(int posY, int bg, int fg, char * output){ //{{{
	printer((WIDTH/2-strlen(output)/2)*(strlen(output) < WIDTH), posY, bg, fg, output);
} //}}}


//{{{ SHORU STUFF

unsigned int map[32][32];
char temp[32][32];
void shoruCommit(){ //{{{
	for(int i=0;i<32;i++)
		for(int j=0;j<32;j++){
			if(!(map[i][j]&(1<<(temp[i][j]-'0'))) && temp[i][j] != ' '){
				map[i][j]=map[i][j] | 1<<(temp[i][j]-'0');
//				printf("%i %i = %b %c|\t",i, j,map[i][j],temp[i][j]);
				}
			for(int k=0; k<10; k++)
				if(map[i][j]&(1<<k) && (map[i][j]!=(1<<k))){
					map[i][j]=1;
				}
			if(map[i][j] ==1){
				temp[i][j]='0';
				continue;
			}
			
		}
} //}}}

void mapPrint(int posX, int posY, char * inp){ //{{{
	int color=DEFBG;
	int fgcol=90;
//	fgcol = 97;
	if(posX>14 && posX < 18 && posY > 4 && posY < 8)
		color = 41; //RED
	if(posX==16 && (posY == 4 || posY == 8))
		color = 41; //RED
	if((posX==14 || posX==18) && (posY == 7))
		color = 41; //RED
	if(posX>14 && posX < 18 && posY > 13 && posY < 17)
		color = 44; //GREEN
	if(posX==16 && (posY == 13 || posY == 17))
		color = 44; //GREEN
	if((posX==14 || posX==18) && (posY == 14))
		color = 44; //GREEN
	if(posX>3 && posX < 12 && posY > 9 && posY < 12)
		color = 42;	//BLUE
	if(posX>3 && posX < 12 && posY > 9 && posY < 12)
		color = 42; //BLUE
	if(posX>20 && posX < 29 && posY > 9 && posY < 12)
		color = 43; //YELLO
	if(posY>2 && posY<19){
		if(posX>24&&color==DEFBG&&(posY<10 || posY>11))return;
		if(posX>30) return;
//		printer(posX, posY, color, fgcol, " ");
		if(!strcmp(inp, "▄")||!strcmp(inp, "▀"))
			sprinter(posX, posY, color, fgcol, inp);
		else if(strcmp(inp, " "))
			sprinter(posX, posY, color, fgcol, "█");
		else
		 	sprinter(posX, posY, color, color, " ");
	}

} //}}}

void mapshower(int posX, int posY, char inp){ //{{{
	switch(inp){
		case '0': mapPrint(posX, posY, "█"); break;
		case '1': mapPrint(posX, posY, "▄"); break;
		case '2': mapPrint(posX, posY, "▀"); break;
		case '3': mapPrint(posX, posY, "▚"); break;
		case '4': mapPrint(posX, posY, "▞"); break;
		case '5': mapPrint(posX, posY, " "); break;
		case '6': mapPrint(posX, posY, "▖"); break;
		case '7': mapPrint(posX, posY, "▘"); break;
		case '8': mapPrint(posX, posY, " "); break;
		case ' ': mapPrint(posX, posY, " "); break;
		default:  {
			char t[5]; sprintf(t,"%i",inp);
			//printer(posX, posY,-1,-1, t); break;
		}
	}
} //}}}

void shoru(){ //{{{
	for(int i=0;i<32;i++)
		for(int j=0; j<32; j++)
			temp[i][j]=' ';
	for(int i=0;i<4;i++){//{{{
//		printer(1+i*6, 10-i, -1, -1, "▗▄▄▞▀▀▘");
		temp[10-i][1+i*6]='\0';
		strcat(temp[10-i],  "8114227");
		temp[10-i][8+i*6]=' ';
//		printer(1+(1+i)*6, 14-i, -1, -1, "▗▄▄▞▀▀▘");
		temp[14-i][1+(1+i)*6]='\0';
		strcat(temp[14-i],  "8114227");
		temp[14-i][8+(1+i)*6]=' ';
//		printer(1+i*6, 11+i, -1, -1, "▝▀▀▚▄▄▖");
		temp[11+i][1+i*6]='\0';
		strcat(temp[11+i],  "5223116");
		temp[11+i][8+i*6]=' ';
//		printer(1+(1+i)*6, 7+i, -1, -1, "▝▀▀▚▄▄▖");
		temp[7+i][1+(i+1)*6]='\0';
		strcat(temp[7+i],  "5223116");
		temp[7+i][8+(i+1)*6]=' ';
		
		//printer(16+i*2,3+(i*3), -1, -1, "█");
		temp[3+i*3][16+i*2]='0';
		//printer(16+i*2,4+(i*3), -1, -1, "▀▄");
		temp[4+i*3][16+i*2]='2';
		temp[4+i*3][17+i*2]='1';
		//printer(16+i*2,5+(i*3), -1, -1, " █");
		temp[5+i*3][17+i*2]='0';
		//printer(15-i*2,3+(i*3), -1, -1, " █");
		temp[3+i*3][16-i*2]='0';
		//printer(15-i*2,4+(i*3), -1, -1, "▄▀");
		temp[4+i*3][15-i*2]='1';
		temp[4+i*3][16-i*2]='2';
		//printer(15-i*2,5+(i*3), -1, -1, "█ ");
		temp[5+i*3][15-i*2]='0';

		//printer(9+i*2,7+(i*3), -1, -1, "█");
		temp[7+i*3][9+i*2]='0';
		//printer(9+i*2,8+(i*3), -1, -1, "▀▄");
		temp[8+i*3][9+i*2]='2';
		temp[8+i*3][10+i*2]='1';
		//printer(9+i*2,9+(i*3), -1, -1, " █");
		temp[9+i*3][10+i*2]='0';
		//printer(22-i*2,7+(i*3), -1, -1, " █");;
		temp[7+i*3][23-i*2]='0';
		//printer(22-i*2,8+(i*3), -1, -1, "▄▀");
		temp[8+i*3][22-i*2]='1';
		temp[8+i*3][23-i*2]='2';
		//printer(22-i*2,9+(i*3), -1, -1, "█ ");
		temp[9+i*3][22-i*2]='0';
		shoruCommit();

	}//}}}
	
	//{{{ bad elementes
	for(int i = 12; i<21; i++){
		temp[10][i]='1';
		temp[11][i]='2';
	}
	for(int i = 9; i<13; i++){
		temp[i][16]='0';
	}
	for(int i=0; i<3;i++){
		{
			 map[8][i+11]=0;
			temp[8][i+11]=' ';
			 map[9][i+11]=0;
			temp[9][i+11]=' ';

			 map[8][i+19]=0;
			temp[8][i+19]=' ';
			 map[9][i+19]=0;
			temp[9][i+19]=' ';
		}
		{
			 map[12][i+11]=0;
			temp[12][i+11]=' ';
			 map[13][i+11]=0;
			temp[13][i+11]=' ';

			 map[12][i+19]=0;
			temp[12][i+19]=' ';
			 map[13][i+19]=0;
			temp[13][i+19]=' ';
		}
	}
	for(int i=0;i<2;i++){
		temp[8][17+i]='2';
		temp[8][15-i]='2';
		temp[13][17+i]='1';
		temp[13][15-i]='1';
	}
	temp[8][16]='1';
	temp[13][16]='2';
	temp[11][11]='1';
	temp[10][11]='2';
	temp[11][21]='1';
	temp[10][21]='2';

	temp[7][13]='1';
	temp[7][19]='1';
	temp[14][13]='2';
	temp[14][19]='2';


	//}}}
	
	for(int i=0; i<32; i++)
		for(int j=0; j<32; j++){
			mapshower(i, j, temp[j][i]);
		}
	int col=90;
	sprinter(7,11,42, col,"▄");
	sprinter(7,10,42, col,"▀");
	sprinter(25,11,43, col,"▄");
	sprinter(25,10,43, col,"▀");
	sprinter(10, 8,103, col,"▄");
	sprinter(10,13,101, col,"▀");
	sprinter(22, 8,106, col,"▄");
	sprinter(22,13,102, col,"▀");
	for(int i=0;i<5;i++){
		sprinter(11+i,9,103,  col," ");
		sprinter(17+i,9,106,  col," ");
		sprinter(11+i,12,101, col," ");
		sprinter(17+i,12,102, col," ");
	}
	for(int i=0;i<3;i++){
		sprinter(11+i,8,103,  col," ");
		sprinter(19+i,8,106,  col," ");
		sprinter(11+i,13,101, col," ");
		sprinter(19+i,13,102, col," ");
	}
	for(int i=0;i<4;i++){
		sprinter(12+i,10,103, col,"▄");
		sprinter(17+i,10,106, col,"▄");
		sprinter(12+i,11,101, col,"▀");
		sprinter(17+i,11,102, col,"▀");
	}
	for(int i=0;i<2;i++){
		sprinter(14+i,8,103,  col,"▀");
		sprinter(17+i,8,106,  col,"▀");
		sprinter(14+i,13,101, col,"▄");
		sprinter(17+i,13,102, col,"▄");
	}
	
		
	//printer(1, 5, -1, -1, "▗▄▞▀▘");
} //}}}
//}}}

void indexBox(){ //{{{
	int colBox = 96;
	int colIns = 40;
	int table= 40;
	int ofs = 15, ofx=18;
	sprinter(ofx+4,ofs+0,colIns, colBox,     "┌──┴┐");
	sprinter(ofx+1,ofs+1,colIns, colBox,  "┌──┘   └┐");
	sprinter(ofx,ofs+ 2, colIns, colBox, "┌┘ INDEX └──");
	sprinter(ofx,ofs+ 3, colIns, colBox, "│                        │");
	sprinter(ofx,ofs+ 4, colIns, colBox, "│ $ curl she-a.eu/simple │");
	sprinter(ofx,ofs+ 5, colIns, colBox, "│ $ curl she-a.eu/index  │");
	sprinter(ofx,ofs+ 6, colIns, colBox, "│ $ curl she-a.eu/about  │");
	sprinter(ofx,ofs+ 7, colIns, colBox, "│ $ curl she-a.eu        │");
	sprinter(ofx,ofs+ 8, colIns, colBox, "└┐$ curl _              ┌┘");
	sprinter(ofx+1,ofs+9,colIns, colBox,  "└──────────────────────┘");
	sprinter(ofx+16,ofs+0,table, colBox,                 " ┌───┐");
	sprinter(ofx+16,ofs+1,table, colBox,                 "┌┘   └──┐");
	sprinter(ofx+12,ofs+ 2,table, colBox,            "────┘ cURLs └┬");
	for(int i=0; i<5; i++){
		sprinter(ofx+2, ofs+4+i, colIns, 32, "$");
		sprinter(ofx+4, ofs+4+i, colIns, 94, "curl");}
	
	sprinter(ofx+9, ofs+4, colIns, 93, "she-a.eu");
	sprinter(ofx+9, ofs+5, colIns, 93, "she-a.eu");
	sprinter(ofx+9, ofs+6, colIns, 93, "she-a.eu");
	sprinter(ofx+9, ofs+7, colIns, 93, "she-a.eu");

	sprinter(ofx+17, ofs+4, colIns, 95, "/simple");
	sprinter(ofx+17, ofs+5, colIns, 95, "/index");
	sprinter(ofx+17, ofs+6, colIns, 95, "/about");
	sprinter(ofx+ 9, ofs+8, colIns, 93, "sh\e[5m_");
}  //}}}


void socalBox(){ //{{{
	int colBox = 96;
	int colIns = 40;
	int table= 40;
	int ofs = 12, ofx=50;
	sprinter(ofx+4,ofs+ 0,table, colBox,     "┌────┐"                   );
	sprinter(ofx+2,ofs+ 1,table, colBox,   "┌─┘    └┐"                  );
	sprinter(ofx,ofs+ 2, table,  colBox, "┌─┘       │"                 );
	sprinter(ofx,ofs+ 3, table,  colBox, "│ socials └──────┘ friends │");
	sprinter(ofx,ofs+ 4, colIns, colBox, "│                          │");
	sprinter(ofx,ofs+ 5, colIns, colBox, "┤    libera   /msg se-a    ├");
	sprinter(ofx,ofs+ 6, colIns, colBox, "│     email    nu@she-a.eu │");
	sprinter(ofx,ofs+ 7, colIns, colBox, "│    matrix   @nu:she-a.eu │");
	sprinter(ofx,ofs+ 8, colIns, colBox, "│    github   @nushea      │");
	sprinter(ofx,ofs+ 9, colIns, colBox, "│   bluesky   @nu.she-a.eu │");
	sprinter(ofx,ofs+10, colIns, colBox, "└┐  discord   @.se.a      ┌┘");
	sprinter(ofx+1,ofs+11,colIns,colBox,  "│ not fedi   @nu@she-a.eu│");
	sprinter(ofx+1,ofs+12,colIns,colBox,  "└────────────────────────┘");
	
	sprinter(ofx+18,ofs+ 0, table,  colBox,  "┌────┐");
	sprinter(ofx+17,ofs+ 1, table,  colBox, "┌┘    └─┐");
	sprinter(ofx+17,ofs+ 2, table,  colBox, "│       └─┐");

	sprinter(ofx+5,ofs+5,colIns, 95, "libera");
	sprinter(ofx+14,ofs+5,colIns, 96, "/msg");
	sprinter(ofx+19,ofs+5,colIns, 97, "se-a");

	sprinter(ofx+6,ofs+6,colIns,  97, "email");
	sprinter(ofx+15,ofs+6,colIns, 97, "nu@she-a.eu");
	sprinter(ofx+17,ofs+6,colIns, 96, "@");

	sprinter(ofx+5,ofs+7,colIns,  91, "matrix");
	sprinter(ofx+14,ofs+7,colIns, 97, "@nu:she-a.eu");
	sprinter(ofx+14,ofs+7,colIns, 96, "@");
	sprinter(ofx+17,ofs+7,colIns, 96, ":");

	sprinter(ofx+5,ofs+8,colIns,  92, "github");
	sprinter(ofx+14,ofs+8,colIns, 97, "@nushea");
	sprinter(ofx+14,ofs+8,colIns, 96, "@");

	sprinter(ofx+4,ofs+9,colIns,  94, "bluesky");
	sprinter(ofx+14,ofs+9,colIns, 97, "@nu.she-a.eu");
	sprinter(ofx+14,ofs+9,colIns, 96, "@");

	sprinter(ofx+4,ofs+10,colIns,  96, "discord");
	sprinter(ofx+14,ofs+10,colIns, 97, "@.se.a");
	sprinter(ofx+14,ofs+10,colIns, 96, "@");

	sprinter(ofx+3,ofs+11,colIns,  90, "not fedi   @nu@she-a.eu");
}  //}}}

void activBox(){//{{{
	int colBox = 0x88FFFF;
	int colIns = 0x181825;
	int ofY=3, ofX=25;
	
	sprinter(ofX, ofY  ,   40, 96, "┌─────────────────────────────────────────────────────┐");
	sprinter(ofX, ofY+1,   40, 96, "│                                                     │");
	sprinter(ofX, ofY+2,   40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 3,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 4,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 5,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 6,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 7,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 8,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+ 9,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+10,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+11,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+12,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+13,  40, 96, "│                                                     │");
	sprinter(ofX, ofY+14,  40, 96, "└─────────────────────────────────────────────────────┘");

	sprinter(32, 4, DEFBG, 97, "Hi, this is Shea, this is Shea's website!");
	sprinter(32, 6, DEFBG, 97, "My current projects are: ");
	sprinter(28, 7, DEFBG, 97, "→maintaining my email service set up through the");
	sprinter(27, 8, DEFBG, 97, "emailwizz scripts");
	sprinter(28, 9, DEFBG, 97, "→maintaining the matrix instance through synapse");
	sprinter(27,10, DEFBG, 97, "     so i may have an account on my domain");
	sprinter(28,11, DEFBG, 97, "     →maintaining the nginx server to serve these");
	sprinter(27,12, DEFBG, 97, "objects that refer to my         projects");
	sprinter(28,13, DEFBG, 97, "→creating these comfy~~          pages");
	sprinter(28,14, DEFBG, 97, "→accomodating myself w             git");
	sprinter(27,15, DEFBG, 97, "→kissin      my partner");
}//}}}


void regularOutput(){
	sprinter(1, 1, 32, DEFBG, "$");
	sprinter(3, 1, 94, DEFBG, "curl");
	sprinter(8, 1, 93, DEFBG, "she-a.eu");
	sprinter(16,1, 95, DEFBG, "/simple");
	sprinter(WIDTH-20, 1, 37, DEFBG, "(minimum size: 80x24)");
	sprinter(26,1, 37, DEFBG,"World's most boring trannie\n");
	activBox();
	shoru();
	indexBox();	
	socalBox();	
}

int main() {
	printf("\x1b[2J");
	for(int i=1; i<=HEIGH; i++)
		for(int j=1; j<=WIDTH; j++)
			if((i+j)%2)
				sprinter(j, i, DEFBG, 37, " ");
			else
			 	sprinter(j, i, DEFBG, 97, " ");
	
	regularOutput();
	sprinter(WIDTH, HEIGH, DEFBG, DEFBG, "\n");
    return 0;
}

