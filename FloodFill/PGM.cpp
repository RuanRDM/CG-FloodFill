#include "PGM.hpp"
#include <iostream>
#include <cmath>
#define _PI 3.14159265358979323846
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

PGM::PGM()
{
    pixels = nullptr;
    larg = 0;
    alt = 0;
    tipo = "";
}

PGM::~PGM()
{
    if (pixels)
        delete pixels;
    pixels = nullptr;
}

int PGM::getLargura()
{
    return larg;
}

int PGM::getAltura()
{
    return alt;
}

unsigned char *&PGM::getPixels()
{
    return pixels;
}

unsigned char PGM::getPixel(int x, int y)
{
    return pixels[y * larg + x];
}

void PGM::setPixel(int x, int y, unsigned char cor)
{

    if (pixels)
        pixels[y * larg + x] = cor;
}

bool PGM::ler(string caminho)
{
    ifstream arq;
    string aux;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    if (!lerDado(arq, &aux))
    {
        cout << "PGM: erro ao ler o tipo da imagem\n";
        return false;
    }
    tipo = aux;

    if (!lerDado(arq, &aux))
    {
        cout << "PGM: erro ao ler a largura da imagem\n";
        return false;
    }
    larg = atoi(aux.c_str());

    if (!lerDado(arq, &aux))
    {
        cout << "PGM: erro ao ler a altura da imagem\n";
        return false;
    }
    alt = atoi(aux.c_str());

    if (!lerDado(arq, &aux))
    {
        cout << "PGM: erro ao ler o valor máximo de cor\n";
        return false;
    }
    vmax = atoi(aux.c_str());

    if (pixels)
        delete pixels;
    pixels = new unsigned char[larg * alt];

    int i = 0;
    while (!arq.eof())
    {
        if (!lerDado(arq, &aux))
        {
            break;
        }

        pixels[i] = (unsigned char)atoi(aux.c_str());
        i++;
    }

    // cout << "i: " << i << endl;
    if (i != larg * alt)
    {
        cout << "PGM: erro ao ler os pixels\n";
        return false;
    }

    // cout << this->tipo << endl;
    // cout << this->larg << endl;
    // cout << this->alt << endl;
    // cout << this->vmax << endl;

    return true;
}

bool PGM::gravar(string caminho)
{

    if (!pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << tipo << endl;

    arq << larg << " " << alt << endl;

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = larg * alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int)pixels[i] << endl;
        arq.flush();
    }

    arq.close();
    return true;
}

bool PGM::lerDado(ifstream &arq, string *dado)
{
    string aux;
    while (!arq.eof())
    {
        arq >> aux;
        if (aux.size() > 0 && aux[0] == '#')
        {
            std::getline(arq, aux);
        }
        else if (aux.size() > 0)
        {
            *dado = aux;
            return true;
        }

        aux = "";
    }
    return false;
}

void PGM::criar(int largura, int altura)
{
    this->larg = largura;
    this->alt = altura;
    this->tipo = "P2";
    pixels = new unsigned char[this->larg * this->alt];
    for(int i=0; i< this->larg * this->alt; i++)
        pixels[i] = 0;

}

void PGM::findCor(int x, int y, unsigned char newColor)
{
    unsigned char currColor = getPixel(x, y);

    // Chama função recursiva passando por parametro a imagem, cor atual, coordenadas e nova cor
    floodFill(this,x,y,currColor,newColor);
}

void PGM::floodFill(PGM* img, int x, int y, unsigned char currColor, unsigned char newColor) 
{   
    // Casos de retorno
    if (!(img->cordValida(x,y))){
        return;
    } 
    if (getPixel(x, y) != currColor){
        return;
    } 
    if (getPixel(x, y) == newColor){
        return;
    }
    // Seta Pixel com a nova cor
    img->setPixel(x, y, newColor); 
  
    // Chamada recursiva para N, O, L, S
    floodFill(img,x+1, y, currColor, newColor); 
    floodFill(img,x-1, y, currColor, newColor); 
    floodFill(img,x, y+1, currColor, newColor); 
    floodFill(img,x, y-1, currColor, newColor);

    // Chamada recursiva para NE, NO, SO, SE
    floodFill(img,x+1, y+1, currColor, newColor);
    floodFill(img,x-1, y-1, currColor, newColor);
    floodFill(img,x+1, y-1, currColor, newColor);
    floodFill(img,x-1, y+1, currColor, newColor);    
}