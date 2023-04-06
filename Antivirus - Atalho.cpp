#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#define E_PASTA dados.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
#define E_SISTEMA dados.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM

char loststrbuffer2[500];
#define MB_Instantaneo(y,x...) sprintf(loststrbuffer2,x);MessageBox(0,loststrbuffer2,y,MB_OK|MB_ICONINFORMATION);
using namespace std;

WIN32_FIND_DATA dados;
HANDLE resultado;
char diretorio[256]="C:\\",pastaSelecionada[250],anterior[250];
int quantidade, pos=1, cursor; 

char tempor[500];

void lista_arquivos(const char *);

//---------------------------------------------------------
//  Início
//---------------------------------------------------------
int main(int argc, char* argv[])
{
    char caminho[10];
    int ret, tempotot, tempoini, tempofim;;
      
    tempoini = clock();
    
    sprintf(caminho,"%c:\\",argv[0][0]);
    
    sprintf(tempor,"Este programa tentará recuperar as pastas\ne apagará os atalhos contidos na unidade %c.\n\nDeseja continuar?\n",argv[0][0]);
    ret = MessageBox(0,tempor,"Aviso",MB_YESNO|MB_ICONINFORMATION);
    
    if(ret == IDYES){
        lista_arquivos(caminho);
        
        tempofim = clock();
        tempotot = tempofim - tempoini;
        printf("O calculo levou %d milissegundos.",tempotot);
    }else{
        printf("Encerrando...");
        Sleep(2000);
        exit(0);
    }
    
    getch();
}

//---------------------------------------------------------
//  lista_arquivos()
//---------------------------------------------------------
void lista_arquivos(const char * cami)
{
    quantidade = 0; 
    char caminho[500];
    strcpy(caminho,cami);

    strcat(caminho,"*"); //para procurar tudo
    cout << "Diretorio atual: ";
    cout << cami << endl << endl;
    
    resultado = FindFirstFile(caminho, &dados);
    do
    {
          if ((E_PASTA) /*&& !(E_SISTEMA)*/)
          {
             if(strcmp(dados.cFileName,".") != 0 && strcmp(dados.cFileName,"..") != 0 )
             {
                 if(pos == quantidade+1)
                 {
                        strcpy(pastaSelecionada,dados.cFileName);
                 }
                 printf("%s\n", dados.cFileName);
                 sprintf(tempor,"attrib \"%s\" -s -h",dados.cFileName);
                 system(tempor);
                 sprintf(tempor,"%s.lnk",dados.cFileName);
                 remove(tempor);
                 //MessageBox(0,dados.cFileName,"Item",MB_OK);
                 quantidade++;
             
             }
          }
    }
    while (FindNextFile(resultado, &dados) != 0);
    
    FindClose(resultado); 
}
