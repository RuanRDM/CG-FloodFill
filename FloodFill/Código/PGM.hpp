#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED

#include <string>
#include <fstream>
#include <Eigen/Dense>
using namespace Eigen;
class PGM
{
public:
    PGM();
    ~PGM();

    bool cordValida(int x, int y){
        if(x>=0 && x<larg && y>=0 && y<alt)
            return true;
        
        return false;
    }

    bool ler(std::string caminho);
	
    bool gravar(std::string caminho);

     //retorna o vetor de pixels por referência! As alteraçõe realizadas fora da classe serão gravadas no vetor!
    unsigned char* & getPixels();
    
    unsigned char getPixel(int x, int y);

    void setPixel(int x, int y, unsigned char cor);

    int getLargura();
	
    int getAltura();

    void criar(int largura, int altura);

    void findCor(int x, int y, unsigned char newColor);

    void floodFill(PGM* img, int x, int y, unsigned char currColor, unsigned char newColor);
private:
    bool lerDado(std::ifstream &arq, std::string *dado);

    std::string tipo;
	int larg;
	int alt;
	int vmax;
	unsigned char* pixels; // unsigned char -> 0 a 255

};

#endif