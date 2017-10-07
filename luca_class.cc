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
string key = "null";
string icon = "*";
string wall = "#";
string land = " ";
string keyParla = "e";
int posTxtx = 0, posTxty = alt + 1;
int cam = 12;
string mappa[larg+1][alt+1];


int main();
void gotoxy(int x, int y);
void mv();
void printStatic();
void printDinamic();
void coordPos();
//void anteprima();  /funzione sostituita da metodo classe MapClass
void print(int thisx, int thisy, string tile = "", bool printLand = false);
//void stringMappa(); /funzione sostituita da metodo classe MapClass
//void save(); /funzione sostituita da metodo classe MapClass
//void load(); /funzione sostituita da metodo classe MapClass
void parla(int posx, int posy, string type,  string frase = "", int txtx = posTxtx, int txty = posTxty, string keyp=keyParla);
void draw(int firstx, int firsty, int secondx = -1, int secondy = -1, string type = wall, bool vuoto = false);


/***********************
* Classe con i metodi per caricamento
* anteprima e salvataggio della mappa
*********************/
class MapClass {
  public:
    
	int stringMappa() {   //metodo stringMappa()
        for(int i=0;i<=larg;i++)
        {
        for(int j=0;j<=alt;j++)
        {
            print(i,j,land);
        }
        }
    } //fine metodo

    void anteprima() {  //metodo anteprima
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
	}  //fine metodo
	
	
	void load() { //metodo load
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
				    }
			    }
	    anteprima();
	    file.close();
	    getch();

	}	
	
	void save() //metodo save
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
	} //fine metodo save

} miamappa; //fine classe con dichiarazione dell'oggetto miamappa usato in main


int main()
{
    //load();
	miamappa.stringMappa();	//sostituito funzione miamappa con metodo classe
    mv();
    miamappa.anteprima(); //sostituito funzione anteprima con metodo classe
    return 0;
}

void mv()
{
    bool running = true;
    bool scia = false;
    printStatic();
    do {
	    printDinamic();
		/*#################################*/
	    miamappa.save();
	    if(key=="w")
	    {
	       if(y>cam)
	            gotoxy(larg,y-cam);
	        else
	            gotoxy(larg,0);
	    }
	
	    if(key=="s")
	    {
	        if(y<alt-cam)
	          gotoxy(larg,y+cam);
	        else
	            gotoxy(larg,alt);
	    }
	
	    if(key=="a")
	    {
	        if(y<alt-cam)
	            gotoxy(larg,y+cam);
	        else
	            gotoxy(larg,alt);
	    }
	
	    if(key=="d")
	    {
	       if(y<alt-cam)
	          gotoxy(larg,y+cam);
	        else
	            gotoxy(larg,alt);
	    }
	
	    key=getch();
	
		/*#################################*/
	
	    //MOVIMENTO
	    if((mappa[x][y-1]==land)||(mappa[x][y-1]==icon))
	        if((key=="w")||(key=="W"))
	            y--;
	
	    if((mappa[x][y+1]==land)||(mappa[x][y+1]==icon))
	        if((key=="s")||(key=="S"))
	            y++;
	
	    if((mappa[x+1][y]==land)||(mappa[x+1][y]==icon))
	        if((key=="d")||(key=="D"))
	            x++;
	
	    if((mappa[x-1][y]==land)||(mappa[x-1][y]==icon))
	        if((key=="a")||(key=="A"))
	            x--;
	
	    //TASTI
	    if(key=="0")
	        running = false;
	
	    if(key=="1")
	        {
	            if(!scia)
	                scia = true;
	            else
	                scia = false;
	        }
	
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
	
	    } while(running);  //fine do while
	    
} //Fine funzione



void printDinamic()
{
    parla(11,11,"O","Grande Cerchio: Salve viandante!");
    parla(12,3,"y"," ");

    if(!init)
        init = true;
}

void printStatic()
{
    draw(0,0,larg,alt,wall,true);
    draw(3,3,10,10,"@",true);
}

void coordPos()
{
    gotoxy(110,29); cout << "\t\t";
    gotoxy(110,29); cout << "(" << x << ";" << y << ")";
}

void print(int thisx, int thisy, string tile, bool printLand)
{
    if((tile!=land)||(mappa[thisx][thisy]==icon)||(printLand==true))
    {
        gotoxy(thisx,thisy);
        cout << tile;
    }
    mappa[thisx][thisy] = tile;
}


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

}

void draw(int firstx, int firsty, int secondx, int secondy, string type, bool vuoto)
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

    if(!vuoto)
    {
        for(int i=firstx;i<=firstx+l;i++)
        {
        for(int j=firsty;j<=firsty+h;j++)
            {
                print(i,j,type);
            }
        }
    }

    if(vuoto)
    {
       draw(firstx,firsty,firstx+l,firsty,type);
       draw(firstx,firsty,firstx,firsty+h,type);
       draw(firstx+l,firsty,firstx+l,firsty+h,type);
       draw(firstx,firsty+h,firstx+l,firsty+h,type);
    }

}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


