// terminal is presumed to be 72x24 or so

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 0x400
#define RESET "\x1b[0m"
#define WIDTH 80
#define HEIGH 24
#define DEFBG 0x1e1e2e
#define DEFFG 0xcdd6f4
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
	int fgcol=0x13131e;
	int table= 0x181825;
//	fgcol = 0xFFFFFF;
	if(posX>9 && posX < 17 && posY > 7 && posY < 11)
		color = 0xFFFF88;
	if(posX>16 && posX < 23 && posY > 7 && posY < 11)
		color = 0x8888FF;
	if(posX>9 && posX < 17 && posY > 10 && posY < 14)
		color = 0xFF8888;
	if(posX>16 && posX < 23 && posY > 10 && posY < 14)
		color = 0x88FF88;
	if(posX>14 && posX < 18 && posY > 4 && posY < 8)
		color = 0xFF0000;
	if(posX==16 && (posY == 4 || posY == 8))
		color = 0xFF0000;
	if((posX==14 || posX==18) && (posY == 7))
		color = 0xFF0000;
	if(posX>14 && posX < 18 && posY > 13 && posY < 17)
		color = 0x0000FF;
	if(posX==16 && (posY == 13 || posY == 17))
		color = 0x0000FF;
	if((posX==14 || posX==18) && (posY == 14))
		color = 0x0000FF;
	if(posX>3 && posX < 12 && posY > 9 && posY < 12)
		color = 0x00FF00;
	if(posX>3 && posX < 12 && posY > 9 && posY < 12)
		color = 0x00FF00;
	if(posX>20 && posX < 29 && posY > 9 && posY < 12)
		color = 0xFFFF00;
	if(posX==4 && posY==10){
		printer(posX, posY, color, fgcol, "▛"); return; }
	if(posX==4 && posY==11){
		printer(posX, posY, color, fgcol, "▙"); return; }
	if(posX==28 && posY==10){
		printer(posX, posY, color, fgcol, "▜"); return; }
	if(posX==28 && posY==11){
		printer(posX, posY, color, fgcol, "▟"); return; }
	if(posX==10 && posY==7){
		printer(posX, posY, 0xFFFF88, fgcol, "▜"); return; }
	if(posX==22 && posY==7){
		printer(posX, posY, 0x8888FF, fgcol, "▛"); return; }
	if(posX==25 && posY==7){
		printer(posX, posY, 0xb7bdf8, fgcol, "▘"); return; }
	if(posX==25 && posY==9){
		printer(posX, posY, 0xb7bdf8, fgcol, "▖"); return; }
	if(posX==10 && posY==14){
		printer(posX, posY, 0xFF8888, fgcol, "▟"); return; }
	if(posX==22 && posY==14){
		printer(posX, posY, 0x88FF88, fgcol, "▙"); return; }
	if(posX==25 && posY==14){
		printer(posX, posY, 0xb7bdf8, fgcol, "▖"); return; }
	if(posX==25 && posY==12){
		printer(posX, posY, 0xb7bdf8, fgcol, "▘"); return; }
	if(posX>24 && (posY==10 || posY==11) && color == DEFBG)
		color = table;
	if(posY>2 && posY<19){
		if(posX>24&&color==DEFBG&&(posY<10 || posY>11))return;
		printer(posX, posY, color, fgcol, inp);
	}

} //}}}

void mapshower(int posX, int posY, char inp){ //{{{
	switch(inp){
		case '0': mapPrint(posX, posY, "█"); break;
		case '1': mapPrint(posX, posY, "▄"); break;
		case '2': mapPrint(posX, posY, "▀"); break;
		case '3': mapPrint(posX, posY, "▚"); break;
		case '4': mapPrint(posX, posY, "▞"); break;
		case '5': mapPrint(posX, posY, "▝"); break;
		case '6': mapPrint(posX, posY, "▖"); break;
		case '7': mapPrint(posX, posY, "▘"); break;
		case '8': mapPrint(posX, posY, "▗"); break;
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
	
		
	//printer(1, 5, -1, -1, "▗▄▞▀▘");
} //}}}
//}}}

void indexBox(){ //{{{
	int colBox = 0xb4befe;
	int colIns = 0x313244;
	int table= 0x181825;
	int ofs = 15, ofx=18;
	printer(ofx+2,ofs+ 0, -1,   colBox,   "   ▄▄▄▄");
	printer(ofx+2,ofs+ 1, -1,   colBox,   "▄▟▀▀  ▝▌");
	printer(ofx,ofs+ 2, -1,     colBox, "▗▛▘INDEX ▙▄▄");
	printer(ofx,ofs+ 3, colIns, colBox, "▟                        ▙");
	printer(ofx,ofs+ 4, colIns, colBox, "▌ $ curl she-a.eu/simple ▐");
	printer(ofx,ofs+ 5, colIns, colBox, "▌ $ curl she-a.eu/index  ▐");
	printer(ofx,ofs+ 6, colIns, colBox, "▌ $ curl she-a.eu/about  ▐");
	printer(ofx,ofs+ 7, colIns, colBox, "▌ $ curl she-a.eu        ▐");
	printer(ofx,ofs+ 8, colIns, colBox, "▙ $ curl _               ▟");
	printer(ofx,ofs+ 9, -1,     colBox, "▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘");
	printer(ofx+16,ofs+0,table, colBox,                 " ▄▄▄▄");
	printer(ofx+16,ofs+1,table, colBox,                 "▐▘  ▀▀▙▄");
	printer(ofx+12,ofs+ 2,table, colBox,            "█████ cURLs▝▜▄");
	for(int i=0; i<5; i++){
		printer(ofx+2, ofs+4+i, colIns, 0xa6e3a1, "$");
		printer(ofx+4, ofs+4+i, colIns, 0x89b4fa, "curl");}
	printer(ofx+ 9, ofs+4, colIns, 0xfab387, "she-a.eu");
	printer(ofx+ 9, ofs+5, colIns, 0xfab387, "she-a.eu");
	printer(ofx+ 9, ofs+6, colIns, 0xfab387, "she-a.eu");
	printer(ofx+ 9, ofs+7, colIns, 0xfab387, "she-a.eu");
	printer(ofx+17, ofs+4, colIns, 0xf38ba8, "/simple");
	printer(ofx+17, ofs+5, colIns, 0xf38ba8, "/index");
	printer(ofx+17, ofs+6, colIns, 0xf38ba8, "/about");
	printer(ofx+ 9, ofs+8, colIns, 0xfab387, "sh\e[5m_");
	printer(ofx   , ofs+3, -1,     colBox,   "▟");
	printer(ofx+25, ofs+3, -1,     colBox,   "▙");
	printer(ofx+ 1, ofs+2, colIns, colBox,   "▛▘INDEX ");
	printer(ofx+17, ofs+2, colIns, colBox,   " cURLs▝▜");
	printer(ofx+ 4, ofs+1, colIns, colBox,   "▀▀  ▝");
	printer(ofx+17, ofs+1, colIns, colBox,   "▘  ▀▀");
	printer(ofx+ 9, ofs+1, table , colBox,   "▙");
	printer(ofx+ 8, ofs  , colIns, colBox,   "█");
}  //}}}


void socalBox(){ //{{{
	int colBox = 0xb7bdf8;
	int colIns = 0x24273a;
	int table= 0x181825;
	int ofs = 12, ofx=50;
	printer(ofx+4,ofs+ 0,table, colBox,     "▗▄▄▄▄▖"                   );
	printer(ofx+1,ofs+ 1,table, colBox,  " ▄▛▀    ▜▖"                  );
	printer(ofx,ofs+ 2, table,  colBox, "▗▛▘       ▌"                 );
	printer(ofx,ofs+ 3, table,  colBox, "▟ socials ▙▄▄▄▄▄▄▟ friends ▙");
	printer(ofx,ofs+ 4, colIns, colBox, "▌                          ▐");
	printer(ofx,ofs+ 5, colIns, colBox, "▌    libera   /msg se-a    ▐");
	printer(ofx,ofs+ 6, colIns, colBox, "▌     email    nu@she-a.eu ▐");
	printer(ofx,ofs+ 7, colIns, colBox, "▌    matrix   @nu:she-a.eu ▐");
	printer(ofx,ofs+ 8, colIns, colBox, "▌    github   @nushea      ▐");
	printer(ofx,ofs+ 9, colIns, colBox, "▌   bluesky   @nu.she-a.eu ▐");
	printer(ofx,ofs+10, colIns, colBox, "▜   discord   @.se.a       ▛");
	printer(ofx,ofs+11, colIns, colBox, "▝▙     f̶e̶d̶i̶ ̶ ̶ ̶@̶n̶u̶@̶s̶h̶e̶-̶a̶.̶e̶u̶▟▘");
	printer(ofx,ofs+12, -1,     colBox, " ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘ ");
	
	printer(ofx+18,ofs+ 0, table,  colBox,  "▗▄▄▄▄▖");
	printer(ofx+17,ofs+ 1, table,  colBox, "▗▛    ▀▜▄");
	printer(ofx+17,ofs+ 2, table,  colBox, "▐       ▝▜▖");

	printer(ofx+ 1, ofs+3, colIns, colBox, " socials ");
	printer(ofx+18, ofs+3, colIns, colBox, " friends ");
	printer(ofx+ 1, ofs+2, colIns, colBox, "▛▘       ");
	printer(ofx+18, ofs+2, colIns, colBox, "       ▝▜");
	printer(ofx+ 3, ofs+1, colIns, colBox, "▛▀    ▜");
	printer(ofx+18, ofs+1, colIns, colBox, "▛    ▀▜");
	printer(ofx,   ofs+10, -1, colBox, "▜");
	printer(ofx,   ofs+11, -1, colBox, "▝");
	printer(ofx+27,ofs+10, -1, colBox, "▛");
	printer(ofx+27,ofs+11, -1, colBox, "▘");

	printer(ofx+5,ofs+5,colIns, 0xf38ba8, "libera");
	printer(ofx+14,ofs+5,colIns, 0x89b4fa, "/msg");
	printer(ofx+19,ofs+5,colIns, 0xffffff, "se-a");

	printer(ofx+6,ofs+6,colIns, 0xffffff, "email");
	printer(ofx+15,ofs+6,colIns, 0xffffff, "nu@she-a.eu");
	printer(ofx+17,ofs+6,colIns, 0x89b4fa, "@");

	printer(ofx+5,ofs+7,colIns,  0xffd9f6, "matrix");
	printer(ofx+14,ofs+7,colIns, 0xffffff, "@nu:she-a.eu");
	printer(ofx+14,ofs+7,colIns, 0x89b4fa, "@");
	printer(ofx+17,ofs+7,colIns, 0x89b4fa, ":");

	printer(ofx+5,ofs+8,colIns,  0xa6e3a1, "github");
	printer(ofx+14,ofs+8,colIns, 0xffffff, "@nushea");
	printer(ofx+14,ofs+8,colIns, 0x89b4fa, "@");

	printer(ofx+4,ofs+9,colIns,  0x89dceb, "bluesky");
	printer(ofx+14,ofs+9,colIns, 0xffffff, "@nu.she-a.eu");
	printer(ofx+14,ofs+9,colIns, 0x89b4fa, "@");

	printer(ofx+4,ofs+10,colIns,  0xcba6f7, "discord");
	printer(ofx+14,ofs+10,colIns, 0xffffff, "@.se.a");
	printer(ofx+14,ofs+10,colIns, 0x89b4fa, "@");

	printer(ofx+7,ofs+11,colIns,  0x2e2e3e, "f̶e̶d̶i̶ ̶ ̶ ̶@̶n̶u̶@̶s̶h̶e̶-̶a̶.̶e̶u̶");
}  //}}}

void activBox(){ //{{{
	int colBox = 0xb7bdf8;
	int colIns = 0x181825;
	int ofY=3, ofX=25;
	
	printer(ofX+5,ofY   , colIns, colBox,     "▄▄▄▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄▄▄▄");
	printer(ofX+1,ofY+1, colIns, colBox,  "▄▟▀▀▀                                           ▀▀▀▙▄");
	printer(ofX+1,ofY+2, colIns, colBox,  "█                                                   █");
	printer(ofX, ofY+ 3, colIns, colBox, "█▀                                                   ▀█");
	printer(ofX, ofY+ 4, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+ 5, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+ 6, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+ 7, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+ 8, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+ 9, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+10, colIns, colBox, "█                                                     █");
	printer(ofX, ofY+11, colIns, colBox, "█▄                                                   ▄█");
	printer(ofX, ofY+12, colIns, colBox, " █                                                   █");
	printer(ofX+1,ofY+13,colIns, colBox,  "▀▙▄▄▄                                           ▄▄▄▛▀");
	printer(ofX+5,ofY+14,colIns, colBox,     " ▀▀▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀▀▀▀");

	printer(32, 4, colIns, DEFFG, "Hi, this is Shea, this is Shea's website!");
	printer(32, 6, colIns, DEFFG, "My current projects are: ");
	printer(28, 7, colIns, DEFFG, "→maintaining my email service set up through the");
	printer(27, 8, colIns, DEFFG, "emailwizz scripts");
	printer(28, 9, colIns, DEFFG, "→maintaining the matrix instance through synapse");
	printer(27,10, colIns, DEFFG, "     so i may have an account on my domain");
	printer(28,11, colIns, DEFFG, "     →maintaining the nginx server to serve these");
	printer(27,12, colIns, DEFFG, "objects that refer to my         projects");
	printer(28,13, colIns, DEFFG, "→creating these comfy~~           pages");
	printer(28,14, colIns, DEFFG, "→accomodating myself w             git");
	printer(27,15, colIns, DEFFG, "→kissin      my partner");
} //}}}


void regularOutput(){ //{{{
	printer(1,  1, -1, 0xa6e3a1, "$");
	printer(3,  1, -1, 0x89b4fa, "curl");
	printer(8,  1, -1, 0xfab387, "she-a.eu");
	printer(WIDTH-20, 1, -1, -1, "(minimum size: 80x24)");
	printer(25, 1, -1, -1,"World's most boring trannie\n");
	activBox();
	shoru();
	indexBox();	
	socalBox();	
} //}}}

int main() {
	printf("\x1b[2J");
	for(int i=1; i<=HEIGH; i++)
		for(int j=1; j<=WIDTH; j++)
			if((i+j)%2)
				printer(j, i, -1, 0xb4befe, " ");
			else
			 	printer(j, i, -1, 0x45475a, " ");
	
	regularOutput();
	printer(WIDTH, HEIGH, DEFBG, DEFBG, "~\n");
    return 0;
}

void debugStrings(){ //{{{
	char * temp;
	temp = malloc(BUFFER);
	for(int i=1; i<=WIDTH; i++){
		memset(temp, 0, BUFFER);
		sprintf(temp, "%i", i);
		printer(i, i%3+1, -1, 0xFFFFFF, temp );
	}
	printer(WIDTH/2, 4, -1, -1, "C");
	printCenterX(5, DEFBG, 0x88FF88,"World's most boring tranny\n");
	free (temp);
} //}}}
