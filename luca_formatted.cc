/*
* Nome programma: ...
*/

//librerie
#include <iostream>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

char saveDir[] = "save.txt";
// int altChunk = 70;
const int larg = 118;
const int alt = 70*3;
bool debug = true;
bool init = false;
int x = 1, y = 1;
string key;
string icon = "*";
string wall = "#";
string land = " ";
string keyParla = "e";
int posTxtx = 0, posTxty = alt + 1;
string mappa[larg+1][alt+1];


int main();
void gotoxy(int x, int y);
void mv();
void printStatic();
void printDinamic();
void coordPos();
void anteprima();
void print(int thisx, int thisy, string tile = "");
void stringMappa();
void save();
void load();
void parla(int posx, int posy, string type,  string frase = "", int txtx = posTxtx, int txty = posTxty, string keyp=keyParla);
void draw(int firstx, int firsty, int secondx = -1, int secondy = -1, string type = wall);



/****************
* Funzione main()
*****************/
int main()
{
    //load();
    stringMappa();
    mv();
    anteprima();
    return 0;
}


/******************************
* mv(): 
* gestisce il movimento del personaggio 
* con i tasti
* W, S, D, A. Tasto 0 per uscire
****************************/
void mv()
{
    bool running = true;
    bool scia = false;
    printStatic();
    do {
		    printDinamic();
			/*#################################*/
		    save();
		    if((key=="w")||(key=="W"))
		        gotoxy(larg,y-10);
		    if((key=="s")||(key=="S"))
		        gotoxy(larg,y+10);
		    key=getch();
			/*#################################*/
		    //MOVIMENTO
		    if((mappa[x][y-1]==land))
		        if((key=="w")||(key=="W"))
		            y--;
		
		    if((mappa[x][y+1]==land))
		        if((key=="s")||(key=="S"))
		            y++;
		
		    if((mappa[x+1][y]==land))
		        if((key=="d")||(key=="D"))
		            x++;
		
		    if((mappa[x-1][y]==land))
		        if((key=="a")||(key=="A"))
		            x--;
		
		    //TASTI
		    if(key=="0")
		        running = false;
		
		    //POSIZIONA PERSONA
		    print(x,y,icon);
		
		    //ANTI SCIA
		    if(!scia)
		    {
		        if(mappa[x+1][y]==icon)
		            print(x+1,y,land);
		
		        if(mappa[x-1][y]==icon)
		            print(x-1,y,land);
		
		        if(mappa[x][y+1]==icon)
		            print(x,y+1,land);
		
		        if(mappa[x][y-1]==icon)
		            print(x,y-1,land);
		    }
		       // coordPos();
    } while(running);  //fine ciclo infinito do while(), 0 per uscire
} //fine funzione mv()



/******************************
* load(): 
* carica il file di caratteri 
* che funge da mappa
*******************************/
void load()
{
    int riempimento = 0;
    int ry=0;
    string i;

    ifstream file (saveDir);

    if(file)
    {
	    while(!file.eof())
		    {
		    file >> i;
		
		    if(i=="ì")
		        i=" ";
		
		    mappa[riempimento][ry] = i;
		
		    if(riempimento<=larg)
		        riempimento++;
		    else
		    {
		        if(ry<=alt)
		            ry++;
		    }
		
		    } //fine while
	
	    /*    for(int i=0;i<=larg;i++)
	    {
	        for(int j=0;j<=alt;j++)
	        {
	            file >> mappa[j][i];
	
	            riempimento++;
	        }
	
	    }*/
    } //fine if(!file)
    anteprima();
    file.close();
    getch();
} //fine funzione load()

void stringMappa()
{
    for(int i=0;i<=larg;i++)
    {
        for(int j=0;j<=alt;j++)
        {
            print(i,j,land);
        }
    }
}


void printDinamic()
{
    // posTxtx = 0, posTxty  ;
    parla(11,11,"O","Grande Cerchio: Salve viandante!");
    parla(12,3,"y"," ");
    if(!init)
        init = true;
} //fine printDinamico()


void printStatic()
{
    draw(0,0,larg,0,wall);    //SOPRA
    draw(0,0,0,alt,wall);       //SINIATRA
    draw(larg,0,larg,alt,wall);     //DESTRA
    draw(0,alt,larg,alt,wall);    //SOTTO
    draw(3,3,10,10,".");
} //fine printStatic()


void coordPos()
{
    gotoxy(110,29); cout << "\t\t";
    gotoxy(110,29); cout << "(" << x << ";" << y << ")";
} //fine coordPos()


void print(int thisx, int thisy, string tile)
{
    if((tile!=land)||(mappa[thisx][thisy]==icon))
    {
        gotoxy(thisx,thisy);
        cout << tile;
    }
    mappa[thisx][thisy] = tile;
} //fine print()


void save()
{
   ofstream file (saveDir);
    for(int i=0;i<alt+1;i++)
    {
        for(int j=0;j<larg+1;j++)
        {
            file << mappa[j][i];
        }
        file << endl;
    }
   file.close();
} //fine save()


void parla(int posx, int posy, string type,  string frase, int txtx, int txty, string keyp)
{
    if(!init)
    print(posx,posy,type);

    if((((x==posx-1)&&(y==posy))||((x==posx+1)&&(y==posy))||((x==posx)&&(y==posy+1))||((x==posx)&&(y==posy-1)))&&(key==keyp))
        {
            gotoxy(txtx,txty); cout << frase;
            getch();
            gotoxy(txtx,txty); cout << "\t\t\t\t\t\t\t\t";
        }

} //fine parla()


void draw(int firstx, int firsty, int secondx, int secondy, string type)
{
    int l, h;

    if((secondx>=0)&&(secondy>=0))
    {
        l = secondx - firstx;
        h = secondy - firsty;
    }
    else
    {
        secondx = firstx + 1;
        secondy = firsty + 1;
        l = 1;
        h = 1;
    }

    for(int i=firstx;i<=firstx+l;i++)
    {
        for(int j=firsty;j<=firsty+h;j++)
        {
            print(i,j,type);
        }
    }

} //fine draw()


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} //fine gotoxy()


void anteprima()
{
    system("cls");
    gotoxy(0,0);
        for(int i=0;i<alt+1;i++)
    {
        for(int j=0;j<larg+1;j++)
        {
            cout << mappa[j][i];
        }
        cout << endl;
    }
    print(0,alt+1,"SALVATO!");
    getch();
} //fine anteprima


//fine programma
