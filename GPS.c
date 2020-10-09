/*
	christan bechi
	augusto vinicius

*/

#include<windows.h>
#include<string.h>
#include<wingdi.h>
#include<stdio.h>
#include<commctrl.h>

//Constantes
#define tamanho 10
#define ComboBox1 1
#define ComboBox2 2
#define ListBox2 3
#define Button_Calcular 4
#define ChekBox 5
#define DataGrid1 6
#define DataGrid2 7
#define DataGrid3 8
#define LimpOrigem 9
#define LimpDestino 10
#define Exit 11
#define PK 12
#define Mostrar 13
#define Ocultar 14
#define LimpInfo 15
#define SobreP 17
#define defaul 16

void menu(char cida[50]);
int inicio,Bini,ida[10]= {0},con,ckBox=0,somaDist=0;
float somaPreco=0;
HWND hwnd;

//Função para criar a barra de menu
Menu(HWND hwnd){
	HBITMAP sai = (HBITMAP) LoadImage(NULL,"_img/sair.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP mais = (HBITMAP) LoadImage(NULL,"_img/mais.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP menos = (HBITMAP) LoadImage(NULL,"_img/menos.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP Borracha = (HBITMAP) LoadImage(NULL,"_img/borra.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP pincel = (HBITMAP) LoadImage(NULL,"_img/pincel.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP pano = (HBITMAP) LoadImage(NULL,"_img/pano.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP vasso = (HBITMAP) LoadImage(NULL,"_img/vasso.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP Borracha2 = (HBITMAP) LoadImage(NULL,"_img/borra2.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HBITMAP infor = (HBITMAP) LoadImage(NULL,"_img/in.bmp",IMAGE_BITMAP,18,18,LR_LOADFROMFILE);
	HMENU principal = CreateMenu();
	HMENU popcao = CreateMenu();
	HMENU popcao2 = CreateMenu();
	AppendMenu(principal, MF_POPUP, (UINT_PTR)popcao, "Ferramentas");
	AppendMenu(popcao, MF_STRING, (UINT_PTR) LimpOrigem, "Limpar Origem");
	AppendMenu(popcao, MF_STRING, (UINT_PTR) LimpDestino, "Limpar Destino");
	AppendMenu(popcao, MF_STRING, (UINT_PTR) PK, "Limpar Preco/Km");
	AppendMenu(popcao, MF_STRING, (UINT_PTR) defaul, "Limpar Tudo");
	AppendMenu(popcao, MF_SEPARATOR, (UINT_PTR) NULL, NULL);
	AppendMenu(popcao, MF_STRING, (UINT_PTR) SobreP, "Sobre");
	AppendMenu(popcao, MF_STRING, (UINT_PTR) Exit, "Sair");
	AppendMenu(principal, MF_POPUP, (UINT_PTR)popcao2, "Descrição");
	AppendMenu(popcao2, MF_STRING, (UINT_PTR) Mostrar, "Mostrar");
	AppendMenu(popcao2, MF_STRING, (UINT_PTR) Ocultar,"Ocultar"); 
	AppendMenu(popcao2, MF_STRING, (UINT_PTR) LimpInfo,"Limpar");
	SetMenuItemBitmaps(popcao, SobreP, MF_BYCOMMAND,infor,infor); 
	SetMenuItemBitmaps(popcao,Exit,MF_BYCOMMAND,sai,sai);
	SetMenuItemBitmaps(popcao,LimpOrigem,MF_BYCOMMAND,pincel,pincel);
	SetMenuItemBitmaps(popcao,LimpDestino,MF_BYCOMMAND,vasso,vasso);
	SetMenuItemBitmaps(popcao,PK,MF_BYCOMMAND,pano,pano);
	SetMenuItemBitmaps(popcao,defaul,MF_BYCOMMAND,Borracha2,Borracha2);
	SetMenuItemBitmaps(popcao2,Mostrar,MF_BYCOMMAND,mais,mais);  
	SetMenuItemBitmaps(popcao2,Ocultar,MF_BYCOMMAND,menos,menos);
	SetMenuItemBitmaps(popcao2,LimpInfo,MF_BYCOMMAND,Borracha,Borracha); 
	SetMenu(hwnd,popcao2); 
	SetMenu(hwnd,principal);  
	SetMenu(hwnd,popcao); 
}

void concast(char *msg, char vetP[][50]){
	int i=0,con=0,ind=0,c=0;
	char dest[100];
	while(msg[i] != '\0'){
		if(msg[i] == '@'){
			for(c=0;vetP[con][c]!='\0';c++){
				dest[ind] = vetP[con][c];
				ind++;
			}
			con++;
		}else{
			dest[ind] = msg[i];
			ind++;
		}
		i++;
	}
	dest[ind] = '\0';
	strcpy(vetP[0],dest);
}

//Função para juntar abreviaturas
void abreviatura(char *origem, char destino[], char retorno[]){
	int i=0,f=0;
	while(origem[i]!='\0'){
		retorno[i] = origem[i];
		i++;
	}
	retorno[i++] = ' ';
	retorno[i++] = 'x';
	retorno[i++] = ' ';
	while(destino[f]!='\0'){
		retorno[i+f] = destino[f];
		f++;
	}
	retorno[i+f] = '\0';
}

//Criação da Thread
DWORD WINAPI BannerSlide(HWND ban){
	int image=0;
	while(1){
		switch(image){
			case 0:{
				HBITMAP img1 = (HBITMAP) LoadImage(NULL,"_img/gps5.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img1);
				image++;
				break;
			}
			case 1:{
				HBITMAP img2 = (HBITMAP) LoadImage(NULL,"_img/aviao.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img2);
				image++;
				break;
			}
			case 2:{
				HBITMAP img3 = (HBITMAP) LoadImage(NULL,"_img/gps.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img3);
				image++;
				break;
			}
			case 3:{
				HBITMAP img4 = (HBITMAP) LoadImage(NULL,"_img/gps1.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img4);
				image++;
				break;
			}
			case 4:{
				HBITMAP img5 = (HBITMAP) LoadImage(NULL,"_img/gps2.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img5);
				image++;
				break;
			}
			case 5:{
				HBITMAP img6 = (HBITMAP) LoadImage(NULL,"_img/gps3.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img6);
				image++;
				break;
			}
			case 6:{
				HBITMAP img7 = (HBITMAP) LoadImage(NULL,"_img/gps4.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
				SendMessage((HWND) ban, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) img7);
				image = 0;
				break;
			}
		}
		Sleep(2000); 
	}
}

HINSTANCE GBox,logoS;
HWND Group,lg;

LRESULT CALLBACK chamada(HWND hand, UINT inti, WPARAM wp, LPARAM lp){
	switch(inti){
		case WM_CREATE:{
			HBITMAP teste = (HBITMAP) LoadImage(NULL,"_img/gpsS.bmp",IMAGE_BITMAP,70,70,LR_LOADFROMFILE);
			lg = CreateWindow(WC_STATIC,"",SS_BITMAP|WS_VISIBLE|WS_CHILD,71,60,70,70,hand,NULL,logoS,NULL);
			SendMessage((HWND) lg, (UINT) STM_SETIMAGE, (WPARAM) NULL, (LPARAM) teste);			
			EnableWindow(hwnd, FALSE); 
			Group = CreateWindow(WC_STATIC,"",BS_GROUPBOX|WS_VISIBLE|WS_BORDER|WS_CHILD,10,21,205,240,hand,NULL,GBox,NULL);
			CreateWindow(WC_STATIC,"SOBRE",WS_VISIBLE|WS_CHILD,18,13,50,18,hand,NULL,GBox,NULL);
			CreateWindow(WC_STATIC,"GUIA E GPS",WS_VISIBLE|WS_CHILD,67,150,80,18,hand,NULL,GBox,NULL);
			CreateWindow(WC_STATIC,"Versão: 1.7",WS_VISIBLE|WS_CHILD,70,170,80,18,hand,NULL,GBox,NULL); 
			CreateWindow(WC_STATIC,"Auguato Vinicius Dos Santos",WS_VISIBLE|WS_CHILD,19,195,190,18,hand,NULL,GBox,NULL);
			CreateWindow(WC_STATIC,"Christian Ferreira Bechi",WS_VISIBLE|WS_CHILD,35,212,160,18,hand,NULL,GBox,NULL);
			CreateWindow(WC_STATIC,"copyright@Augusto-Christian",WS_VISIBLE|WS_CHILD,18,240,190,18,hand,NULL,GBox,NULL); 
			break;
		}
		case WM_COMMAND:{
			break;
		}
		case WM_DESTROY:{
			PostQuitMessage(0); 
			EnableWindow(hwnd, TRUE); 
			break;
		}
		default:{
			DefWindowProc(hand,inti,wp,lp);
			break;
		}
	}
}

int WINAPI T_Sobre(HINSTANCE sobre1, HINSTANCE sobre2, LPSTR lpCmdLine, HWND modo){
	HWND sob;
	MSG men;
	WNDCLASSEXA s;
	s.cbSize = sizeof(s);
	s.cbWndExtra = 0;
	s.cbClsExtra = 0;
	s.hInstance = sobre1;
	s.hCursor = LoadCursor(NULL,IDC_ARROW);
	s.hIconSm = NULL;
	s.hIcon = LoadImage(NULL,"_img/info.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
	s.hbrBackground = (HBRUSH) COLOR_BACKGROUND+1;
	s.lpfnWndProc = chamada; 
	s.lpszMenuName = NULL;
	s.lpszClassName = "sobre";
	s.style = CS_DBLCLKS;
	UnregisterClass("sobre", sobre1);
	if(!RegisterClassEx(&s)){
		MessageBox(NULL,"Não foi possivel registrar a classe!","Error",0x40);
	}
	sob = CreateWindow("sobre","Sobre o programa",WS_OVERLAPPED|WS_SYSMENU,520,210,230,300,NULL,NULL,sobre1,NULL);
	ShowWindow(sob,1);
	while(GetMessage(&men,NULL,0,0)){
		TranslateMessage(&men);
		DispatchMessage(&men); 
	} 
	return men.wParam;
}

//Cidades
char Cidades[][50] = {"São Paulo","Sorocaba","Taubate","Rio de Janeiro","Santos","Natal","Pelotas","Barretos","Bauru","Curitiba"};
char Abre[][50] = {"SP","Soroc.","Tauba.","RJ","Santos","Natal","Pelot.","Barre.","Bauru","Curit."};

//Coordenadas
float dist[][tamanho]={{-6,107,140,429,72,2981,1427,422,325,408}
					  ,{100.00,-6,223,495,164,3029,1379,432,257,396}
					  ,{125.00,170.00,-6,306,212,2855,1547,0,0,592}
					  ,{400.00,450.00,250.00,-6,587,-1,1815,813,740,835}
					  ,{70.00,150.00,200.00,450.00,-6,3032,1398,531,421,414}
					  ,{980.00,990.00,990.00,-1,995.00,-6,4306,-1,2938,3309}
					  ,{450.00,450.00,475.00,500.00,450.00,600.00,-6,1697,1478,980}
					  ,{350.00,240.00,75.00,600.00,500.00,-1,600.00,-6,0,730}
					  ,{400.00,250.00,75.00,175.00,375.00,600.00,650.00,75.00,-6,497}
					  ,{375.00,350.00,350.00,400.00,325.00,750.00,600.00,550.00,400.00,-6}};

LRESULT CALLBACK WindowsProc(HANDLE handle, UINT inteiro, WPARAM wpa, LPARAM lpa);

int WINAPI WinMain(HINSTANCE janela1, HINSTANCE janela2, LPSTR lpCmdLine, int tipo){
	HBRUSH color = (HBRUSH) CreateSolidBrush(RGB(0,128,0));
	MSG message;
	WNDCLASSEX esc;
	esc.cbSize = sizeof(WNDCLASSEX);
	esc.cbClsExtra = 0;
	esc.cbWndExtra = 0;
	esc.hInstance = janela1;
	esc.hbrBackground = (HBRUSH) color;
	esc.hIcon = LoadImage(janela1,"_img/gps.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
	esc.hIconSm = LoadImage(janela1,"_img/gps.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
	esc.hCursor = LoadCursor(NULL,IDC_ARROW);
	esc.lpfnWndProc = WindowsProc;
	esc.lpszMenuName = NULL;
	esc.lpszClassName = "Jan";
	esc.style = CS_DBLCLKS;
	if(!RegisterClassEx(&esc)){
		MessageBox(NULL,"Não foi possivel Registrar a Classe!","ERROR",MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow("Jan","Christian e Augusto",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,490,170,287,383,NULL,NULL,janela1,NULL);
	ShowWindow(hwnd,tipo);
	while(GetMessage(&message,NULL,0,0)){
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}

HWND combo1,combo2,text1,text2,list1,list2,cap1,cap2,banner,check,butn1,data1,data2,data3;
HINSTANCE cb1,cb2,ct1,ct2,ls1,ls2,ca1,ca2,btn1,ban,ckb,dt1,dt2,dt3;

LRESULT CALLBACK WindowsProc(HANDLE handle, UINT inteiro, WPARAM wpa, LPARAM lpa){
	char origem[20] = {' '}, destino[20] = {' '};
	int x=0,d=0,o=0;
	switch(inteiro){
		case WM_CREATE:{
			FILE *arq;
			if((arq=fopen("Ferramentas/Cidades.txt","r"))==NULL)
				MessageBox(NULL,"Não foi possivel abrir o arquivo","Error",MB_ICONERROR);
			HBITMAP bann = (HBITMAP) LoadImage(NULL,"_img/gps.bmp",IMAGE_BITMAP,270,100,LR_LOADFROMFILE);
			banner = CreateWindow(WC_STATIC,"",WS_BORDER|SS_BITMAP|WS_CHILD|WS_VISIBLE,5,4,270,80,handle,NULL,ban,NULL);
			SendMessage((HWND) banner, (UINT) STM_SETIMAGE, (WPARAM) IMAGE_BITMAP, (LPARAM) bann);
			combo1 = CreateWindow(WC_COMBOBOX,"",CBS_DROPDOWN|CBS_HASSTRINGS|WS_VISIBLE|WS_CHILD|WS_OVERLAPPED|WS_VSCROLL,6,210,134,100,handle, (HMENU) ComboBox1 ,cb1,NULL);
			combo2 = CreateWindow(WC_COMBOBOX,"",WS_DISABLED|CBS_DROPDOWN|CBS_HASSTRINGS|WS_VISIBLE|WS_OVERLAPPED|WS_CHILD|WS_VSCROLL,146,210,130,100,handle, (HMENU) ComboBox2, cb2, NULL);
			//Carrega o Combobox Origem e Destino
			while(!feof(arq)){
				fgets(origem,20,arq);
				SendMessage(combo1,CB_ADDSTRING,(WPARAM) NULL, (LPARAM) origem);
				SendMessage(combo2,CB_ADDSTRING, (WPARAM) NULL,(LPARAM) origem);
			}
			SendMessage(combo1, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
			SendMessage(combo2,CB_SETCURSEL, (WPARAM) 3, (LPARAM) 0);
			//Cria os controles
			text1 = CreateWindow("EDIT","Km",WS_CHILD|WS_VISIBLE|ES_CENTER|WS_DISABLED,40,300,100,25,handle, NULL, ct1, NULL);
			text2 = CreateWindow("EDIT","Preço",WS_CHILD|WS_VISIBLE|ES_CENTER|WS_DISABLED,150,300,100,25,handle, NULL, ct2, NULL);
			list1 = CreateWindow(WC_LISTBOX,"",WS_CHILD|WS_VISIBLE|WS_HSCROLL,6,110,134,80,handle,NULL,ls1,NULL);
			list2 = CreateWindow(WC_LISTBOX,"",WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY,146,110,130,80,handle,(HMENU) ListBox2,ls2,NULL);
			cap1 = CreateWindow(WC_STATIC, "Origem:", WS_CHILD|WS_VISIBLE,6,190,134,20,handle,NULL,ca1,NULL);
			cap2 = CreateWindow(WC_STATIC, "Destino(s):", WS_CHILD|WS_VISIBLE,146,190,130,20,handle,NULL,ca2,NULL);
			butn1 = CreateWindow(WC_BUTTON,"Calcular",WS_DISABLED|WS_VISIBLE|WS_CHILD,95,265,100,30,handle,(HMENU) Button_Calcular,btn1,NULL);
			check = CreateWindow(WC_BUTTON,"Multi Destino",WS_DISABLED|WS_VISIBLE|WS_CHILD|BS_CHECKBOX,146,234,130,25,handle,(HMENU) ChekBox, ckb, NULL);
			data1 = CreateWindow(WC_LISTBOX,"",WS_VSCROLL|ES_READONLY|ES_CENTER|WS_VISIBLE|WS_CHILD|WS_BORDER,2,358,124,80,handle, (HMENU) DataGrid1, dt1, NULL);
			data2 = CreateWindow(WC_LISTBOX,"",ES_READONLY|ES_CENTER|WS_VISIBLE|WS_CHILD|WS_BORDER,126,358,61,80,handle,(HMENU) DataGrid2,dt2,NULL);
			data3 = CreateWindow(WC_LISTBOX,"",ES_READONLY|ES_CENTER|WS_VISIBLE|WS_CHILD|WS_BORDER,187,358,92,80,handle,(HMENU) DataGrid3,dt3,NULL);
			CreateWindow(WC_STATIC, "        Cidade(s)       |   Km(s)  |   Preço(s)   ", WS_CHILD|WS_VISIBLE,3,339,275,20,handle,NULL,ca2,NULL);
			//Cria uma nova Thread para o slide do banner
			DWORD slide;
			HWND sld = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)BannerSlide,banner,0,&slide); 
			Menu(handle);
			break;
		}	
		case WM_COMMAND:{
			
			//CheckBox - Verifica se ao clicar ele está checado ou não. Caso esteje, ele tira o check. Caso contrario ele da um check.
			if(LOWORD(wpa) == ChekBox){
				if(IsDlgButtonChecked(handle,ChekBox) == TRUE){
					CheckDlgButton(handle,ChekBox, BST_UNCHECKED);
				}else{
					CheckDlgButton(handle,ChekBox, BST_CHECKED);
				}
			}
			
			//ComboBox
			if(HIWORD(wpa) == CBN_SELCHANGE){
				switch(LOWORD(wpa)){
					case ComboBox1:{
							//Seta a origem
							SendMessage((HWND) list1, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) NULL);//Sempre que for selecionado uma nova origem a anterior é apagada
							o = SendMessage((HWND) lpa,(UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0); //Obtem o indice do item selecionado.
							inicio = o;
							Bini = o;
							EnableWindow(combo2, TRUE); 
							EnableWindow(check, TRUE);
							SendMessage((HWND) lpa, CB_GETLBTEXT, (WPARAM) o, (LPARAM) origem); //Obtem o nome do item selecionado(com o index pegado anteriormente
							SendMessage((HWND) list1, LB_ADDSTRING, (WPARAM) NULL, (LPARAM) origem); //Adiciona uma string ao listBox
						break;
					}
					case ComboBox2:{	
						//Seta o Destino
						if(IsDlgButtonChecked(handle,ChekBox)  == FALSE){
							//É realizado caso o check for falso
							EnableWindow(butn1,TRUE); 
							int ind;
							for(ind=0;ind<=con;ind++)
								SendMessage((HWND) list2, (UINT) LB_DELETESTRING,(WPARAM) 0, (LPARAM) NULL);
							con = 0;
							d = SendMessage((HWND) lpa, (UINT) CB_GETCURSEL,(WPARAM)0,(LPARAM)0);
							ida[0] = d;
							con++;
							SendMessage((HWND) lpa,(UINT) CB_GETLBTEXT,(WPARAM) d, (LPARAM) destino);
							SendMessage((HWND) list2, (UINT) LB_ADDSTRING, (WPARAM) NULL, (LPARAM) destino);
						}else{
							//É realizado caso o check for verdadeiro. Liberando setar mais de um destino.
							if((SendMessage((HWND) list2, LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0)) < 10){ //Verifica se a quantidade de destino é menor que 10
								EnableWindow(butn1,TRUE);
								d = SendMessage((HWND) lpa, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
								ida[con] = d;
								con++;
								SendMessage((HWND) lpa, (UINT) CB_GETLBTEXT, (WPARAM) d,(LPARAM) destino);
								SendMessage((HWND) list2, LB_ADDSTRING, (WPARAM) NULL, (LPARAM) destino);
							}else{
								MessageBox(NULL,"Não pode ter mais de 10 destinos","ERROR",0X10);
							}
						}
						break;
					}
				}
			}
			
			//ListBox2 ->
			if(LOWORD(wpa) == ListBox2){
				if(HIWORD(wpa) == LBN_DBLCLK){
					int pega,cont; 
					pega = SendMessage((HWND) list2, (UINT) LB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage((HWND) list2, (UINT) LB_DELETESTRING, (WPARAM) pega, (LPARAM) NULL);
					ida[pega] = ida[pega+1];
					for(cont=1;cont<con;cont++){
						ida[pega+cont] = ida[pega+cont+1];
					}
					con--;				
				}
			}
			
			//DataGrid
			if(LOWORD(wpa) == DataGrid1 || LOWORD(wpa) == DataGrid2 || LOWORD(wpa) == DataGrid3){
				int index;
					for(index=0;index<=10;index++){
						SendMessage((HWND) data1, (UINT) LB_SETSEL, (WPARAM) FALSE, (LPARAM) index);
						SendMessage((HWND) data2, (UINT) LB_SETSEL, (WPARAM) FALSE, (LPARAM) index);
						SendMessage((HWND) data3, (UINT) LB_SETSEL, (WPARAM) FALSE, (LPARAM) index);
					}
					index = SendMessage((HWND) lpa, (UINT) LB_GETCURSEL, (WPARAM)0,(LPARAM)0);
					SendMessage((HWND) data1, (UINT) LB_SETSEL, (WPARAM) TRUE, (LPARAM) index);
					SendMessage((HWND) data2, (UINT) LB_SETSEL, (WPARAM) TRUE, (LPARAM) index);
					SendMessage((HWND) data3, (UINT) LB_SETSEL, (WPARAM) TRUE, (LPARAM) index);  
				if(HIWORD(wpa) == LBN_DBLCLK){
					int num = SendMessage((HWND) data1, (UINT) LB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
					char recebe[3][50];
					SendMessage((HWND) data1, (UINT) LB_GETTEXT, (WPARAM) num, (LPARAM) recebe[0]);
					SendMessage((HWND) data2, (UINT) LB_GETTEXT, (WPARAM) num, (LPARAM) recebe[1]);
					SendMessage((HWND) data3, (UINT) LB_GETTEXT, (WPARAM) num, (LPARAM) recebe[2]);
					concast("Trajeto: @ \nDistancia: @ \nValor gasto: @",recebe); 
					MessageBox(NULL,recebe[0],"Informações",0x40);
				}
			}
			
			//Menu Bar
			switch(LOWORD(wpa)){
				case LimpOrigem :{
					SendMessage((HWND) list1, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) NULL);
					inicio = -7;
					break;
				}
				case LimpDestino:{
					int ind;
					for(ind=0;ind<=con;ind++){
						SendMessage((HWND) list2, (UINT) LB_DELETESTRING,(WPARAM) 0, (LPARAM) NULL);
						ida[ind] = 0;
					}
					d =0;
					con = 0;
					break;
				}
				case Exit:{
					PostQuitMessage(0); 
					break;
				}
				case PK:{
					SetWindowText(text1,"Km");
					SetWindowText(text2,"Preço");
					break;
				}
				case defaul:{
					int ind,i;
					for(ind=0;ind<=con;ind++)
						SendMessage((HWND) list2, (UINT) LB_DELETESTRING,(WPARAM) 0, (LPARAM) NULL);
					con = 0;
					SendMessage((HWND) list1, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) NULL);
					SetWindowText(text1,"Km");
					SetWindowText(text2,"Preço");
					SetWindowPos(handle,NULL,490,170,287,383,0);
					for(i=0;i<=10;i++){
						SendMessage((HWND) data1, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
						SendMessage((HWND) data2, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
						SendMessage((HWND) data3, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
					}
					SendMessage((HWND) combo1, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
					SendMessage((HWND) combo2, (UINT)CB_SETCURSEL, (WPARAM)3, (LPARAM)0);
					EnableWindow(combo2, FALSE);
					EnableWindow(butn1, FALSE);
					CheckDlgButton(handle,ChekBox,BST_UNCHECKED);
					EnableWindow(check, FALSE);  
					break;
				}
				case Mostrar:{
					SetWindowPos(handle,NULL,490,150,288,476,0);
					break;
				}
				case Ocultar:{
					SetWindowPos(handle,NULL,490,170,287,383,0);
					break;
				}
				case LimpInfo:{
					int i;
					for(i=0;i<=10;i++){
						SendMessage((HWND) data1, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
						SendMessage((HWND) data2, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
						SendMessage((HWND) data3, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
					}
					break;
				}
				case SobreP:{
					T_Sobre(NULL,NULL,NULL,handle); 
					break;
				}
			}
			
			//Button
			if(LOWORD(wpa) == Button_Calcular){
				int coluna=0,linha=0,origem=0,destino=0,i=0;
				char teste[50],aux[50] = "R$ ",tmp[50];
				somaPreco = 0;
				somaDist = 0;
				inicio = Bini;
				SetWindowText(text1,"Km");
				SetWindowText(text2,"Preço");
				for(i=0;i<=10;i++){
					SendMessage((HWND) data1, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
					SendMessage((HWND) data2, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
					SendMessage((HWND) data3, (UINT) LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
				}
				if(IsDlgButtonChecked(handle,ChekBox) == TRUE && SendMessage((HWND) list2, (UINT) LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0) > 1 && SendMessage((HWND) list1, (UINT) LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0) > 0){
					SetWindowPos(handle,NULL,490,150,288,476,0);
				}else{
					SetWindowPos(handle,NULL,490,170,287,383,0);
				}
				if(SendMessage(list1,LB_GETCOUNT,0,0) == 0 && SendMessage(list2,LB_GETCOUNT,0,0) == 0){
					MessageBox(NULL,"O campo \"Origem\" E \"Destino\" não podem ficar em branco!","Vazios!",0x10);
				}else if(SendMessage(list1,LB_GETCOUNT,0,0) == 0){
							MessageBox(NULL,"O campo \"Origem\" não pode ficar em branco!","Vazio!",0x10);
					  }else if(SendMessage(list2,LB_GETCOUNT,0,0) == 0){
					    	MessageBox(NULL,"O campo \"Destino\" não pode ficar em branco!","Vazio!",0x10);
					  }else{
							for(i=0;i<con;i++){
								for(coluna=0;coluna<tamanho;coluna++){
									for(linha =0;linha<tamanho;linha++){
										if(coluna==inicio && ida[i]==linha){
											if(inicio < ida[i]){
												if(dist[inicio][ida[i]] == -1){
													MessageBox(handle, "Não realizamos esse trajeto!","OPS!",MB_ICONWARNING);
												}else if(dist[inicio][ida[i]] == -6){
													MessageBox(handle, "Você não pode ter a origem igual ao destino!","OPS!",MB_ICONWARNING);
												}else{
														if(dist[inicio][ida[i]] == 0){
															MessageBox(handle, "Cidades Vizinhas","Ebah!",MB_ICONWARNING);
															if(somaDist > 0){
																itoa(somaDist,teste,10);
																strcat(teste," Km");
																SetWindowText(text1,teste);
															}else{
																SetWindowText(text1,"Cid. Vizinha");
															}
															SendMessage((HWND) data2, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) "Vizinha");
															abreviatura(Abre[inicio],Abre[ida[i]],tmp); 
															SendMessage((HWND) data1, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) tmp);
														}else{
															abreviatura(Abre[inicio],Abre[ida[i]],tmp); 
															SendMessage((HWND) data1, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) tmp);
															somaDist += dist[inicio][ida[i]];
															itoa(dist[inicio][ida[i]],teste,10);
															SendMessage((HWND) data2, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) teste);
															itoa(somaDist,teste,10);
															strcat(teste," Km");
															SetWindowText(text1,teste);
														}
														if(dist[ida[i]][inicio] == 0){
															somaPreco += 75;
															SendMessage((HWND) data3, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) "R$ 75.00");
														}else{
															somaPreco += dist[ida[i]][inicio];
															sprintf(teste,"%.2f",dist[ida[i]][inicio]);
															strcpy(aux,"R$ ");
															strcat(aux,teste);
															SendMessage((HWND) data3, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) aux);
														}
														sprintf(teste,"%.2f",somaPreco);
														strcpy(aux,"R$ ");
														strcat(aux,teste);
														SetWindowText(text2, aux);
														switch(ida[i]){
															case 3:{
																MessageBox(handle,"O Pão de Açúcar – que fica a 400 metros acima do nível do mar – pode ser considerado o segundo lugar mais procurado pelos turistas na cidade. O passeio começa com a viagem de bondinho, um teleférico todo de vidro onde você consegue visualizar toda a paisagem incrível à sua volta.",Cidades[3],0x40);
																break;
															}
															case 4:{
																MessageBox(handle,"O Museu de Pesca oferece a seus visitantes uma visão geral dos principais grupos marinhos do Brasil e de várias partes do mundo. Possui o maior acervo de conchas do País, com 21 mil exemplares. Entre elas se destacam duas da espécie gigante Tridacna gigas, natural das Filipinas, sendo que a maior tem um metro de comprimento e pesa 148 Kg.",Cidades[4],0x40);
																break;
															}
															case 5:{
																MessageBox(handle,"A Fortaleza dos Reis Magos, possui um formato de estrela que faz alusão às batalhas travadas por portugueses, holandeses e franceses. Tombado pelo Instituto do Patrimônio Histórico Nacional (IPHAN), este forte foi desativado em 1934. É possível fazer uma visita guiada, onde é contada toda a história do local.",Cidades[5],0x40);
																break;
															}
															case 6:{
																MessageBox(handle,"O Museu registra e mostra documentos e objetos coletados junto a população da colonia francesa, na colonia maciel. Ao lado do museu tem o Restaurante Grupelli, com excelente comida colonial",Cidades[6],0x40);
																break;
															}
															case 9:{
																MessageBox(handle,"O Centro Histórico de Curitiba é um bom ponto de partida para percorrer a cidade. A região preserva os séculos passados, quando Curitiba era apenas a pequena Vila de Nossa Senhora da Luz dos Pinhais. Ao percorrer as ruas de pedra do centro, você poderá visitar Igreja da Ordem Terceira de São Francisco de Chagas.",Cidades[9],0x40);
																break;
															}
														}
												}
											}else{
												if(dist[inicio][ida[i]] == -1){
													MessageBox(handle, "Não realizamos esse trajeto!","OPS!",MB_ICONERROR);
												}else if(dist[inicio][ida[i]] == -6){
													MessageBox(handle, "Você não pode ter a origem igual ao destino!","OPS!",MB_ICONERROR);
												}else{
														if(dist[ida[i]][inicio] == 0){
															MessageBox(handle, "Cidades Vizinhas","Ebah!",MB_ICONWARNING);
															if(somaDist > 0){
																itoa(somaDist,teste,10);
																strcat(teste," Km");
																SetWindowText(text1,teste);
															}else{
																SetWindowText(text1,"Cid. Vizinha");
															}
															SendMessage((HWND) data2, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) "Vizinha");
															abreviatura(Abre[inicio],Abre[ida[i]],tmp);
															SendMessage((HWND) data1, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) tmp);
														}else{
															abreviatura(Abre[inicio],Abre[ida[i]],tmp);
															SendMessage((HWND) data1, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) tmp);
															somaDist += dist[ida[i]][inicio];
															itoa(dist[ida[i]][inicio],teste,10);
															SendMessage((HWND) data2, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) teste);
															itoa(somaDist,teste,10);
															strcat(teste," Km");
															SetWindowText(text1,teste);
														}  			
														if(dist[inicio][ida[i]] == 0){
															somaPreco += 75;
															SendMessage((HWND) data3, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) "R$ 75.00");
														}else{
															sprintf(teste,"%.2f",dist[inicio][ida[i]]);
															strcpy(aux,"R$ ");
															strcat(aux,teste);
															SendMessage((HWND) data3, (UINT) LB_ADDSTRING,(WPARAM) 0,(LPARAM) aux);
															somaPreco += dist[inicio][ida[i]];
														}
														sprintf(teste,"%.2f", somaPreco);
														strcpy(aux,"R$ ");
														strcat(aux,teste);
														SetWindowText(text2, aux);
														switch(ida[i]){
															case 3:{
																MessageBox(handle,"O Pão de Açúcar – que fica a 400 metros acima do nível do mar – pode ser considerado o segundo lugar mais procurado pelos turistas na cidade. O passeio começa com a viagem de bondinho, um teleférico todo de vidro onde você consegue visualizar toda a paisagem incrível à sua volta.",Cidades[3],0x40);
																break;
															}
															case 4:{
																MessageBox(handle,"O Museu de Pesca oferece a seus visitantes uma visão geral dos principais grupos marinhos do Brasil e de várias partes do mundo. Possui o maior acervo de conchas do País, com 21 mil exemplares. Entre elas se destacam duas da espécie gigante Tridacna gigas, natural das Filipinas, sendo que a maior tem um metro de comprimento e pesa 148 Kg.",Cidades[4],0x40);
																break;
															}
															case 5:{
																MessageBox(handle,"A Fortaleza dos Reis Magos, possui um formato de estrela que faz alusão às batalhas travadas por portugueses, holandeses e franceses. Tombado pelo Instituto do Patrimônio Histórico Nacional (IPHAN), este forte foi desativado em 1934. É possível fazer uma visita guiada, onde é contada toda a história do local.",Cidades[5],0x40);
																break;
															}
															case 6:{
																MessageBox(handle,"O Museu registra e mostra documentos e objetos coletados junto a população da colonia francesa, na colonia maciel. Ao lado do museu tem o Restaurante Grupelli, com excelente comida colonial",Cidades[6],0x40);
																break;
															}
															case 9:{
																MessageBox(handle,"O Centro Histórico de Curitiba é um bom ponto de partida para percorrer a cidade. A região preserva os séculos passados, quando Curitiba era apenas a pequena Vila de Nossa Senhora da Luz dos Pinhais. Ao percorrer as ruas de pedra do centro, você poderá visitar Igreja da Ordem Terceira de São Francisco de Chagas.",Cidades[9],0x40);
																break;
															}
														}
													
												}
											}
				
										}
									}
								}
								if(dist[inicio][ida[i]] != -1){
									strcpy(tmp," ");
									inicio = ida[i];
								}
							}
				}
			}
			break;
		}	
		case WM_CTLCOLORSTATIC:{
			HDC color = (HDC) cap1;
			SetBkColor(color, RGB(255,0,0));
			break;
		}
		case WM_DESTROY:{
			PostQuitMessage(0);
			break;
		}
		default:{
			DefWindowProc(handle,inteiro,wpa,lpa);
			break;
		}
	}
}


