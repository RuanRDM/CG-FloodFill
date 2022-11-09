#include "PGM.hpp"
#include <iostream>
using namespace std;

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	PGM *img = new PGM();

	// criar imagem fundo preto
	//img->criar(50, 50);

	//img->ler("exemplo.pgm");
	img->ler("exemplo-fail.pgm");

	unsigned char cor=0;
	int x = 35;
	int y= 10;

	//chama função que busca a cor da coordenada passada por parâmetro
	img->findCor(x,y,cor);

    img->gravar("saida.pgm");

	delete img;
	
	return EXIT_SUCCESS; 
}
