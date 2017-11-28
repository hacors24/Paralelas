#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "typeinfo"
#include <sstream>
#include <cmath>

using namespace std;


int main(int argc, char *argv[] )
{ 
	fstream fichero, fichero2; 
	char linea[30]; 
	int cont = 0;
	int cont2 = 0;
	float perimetro;
	float sumaperimetros = 0;
	
	float puntos[2][15000]; 
	int triangulos[3][15000]; 

	// Abro para lectura 
	fichero.open("puntos", ios::in); 
	// fichero >> linea;           // Leo una primera linea 
	//fichero2.open("prueba_triangulos", ios::in); 
	fichero2.open("triangulos", ios::in); 
	// fichero2 >> linea;           // Leo una primera linea 

	
	
	  ofstream salida[10] = {};
	  salida[0].open ("salida1.csv");	
	
	if(fichero.fail())
	cerr << "Error al abrir el archivo dato.csv" << endl;
	else
	while(!fichero.eof())
	{
	    fichero.getline(linea, sizeof(linea));
	    //cout << linea << endl;
	    
	    std::stringstream sst;
	    sst.str (linea);
	    std::string s = sst.str();
	    // std::cout << "s: "  << s << '\n';	    
	    std::size_t pos = s.find(" ");  
	    // std::cout << "pos: "  << pos << '\n';	  
	    
	    std::string cad1 = s.substr(0,pos);
	    //std::cout << "cad1: " << cad1 << '\n'; 	    

	    std::string s2 = s.substr(pos+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos2 = s2.find(" ");   
	    // std::cout << "pos2: "  << pos2 << '\n'; 
	    
	    std::string cad2 = s2.substr(0,pos2);
	    //std::cout << "cad2: " << cad2 << '\n';  	
	    stringstream geekx(cad2);
	    float cadX = 0;
	    geekx >> cadX;	    

	    std::string s3 = s2.substr(pos2+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos3 = s3.find(" ");   
	    // std::cout << "pos3: "  << pos3 << '\n'; 
	    
	    std::string cad3 = s3.substr(0,pos3);
	    //std::cout << "cad3: " << cad3 << '\n';  
	    stringstream geeky(cad3);
	    float cadY = 0;
	    geeky >> cadY;	
	    
	    stringstream geek(cad1);
	    int indice = 0;
	    geek >> indice;
	    
	    puntos[0][indice] = cadX;
	    puntos[1][indice] = cadY;
	    //std::cout << '\n'; 	
	    
	    cont++;
	}
	
	
	
	if(fichero2.fail())
	cerr << "Error al abrir el archivo dato.csv" << endl;
	else
	while(!fichero2.eof())
	{
	    fichero2.getline(linea, sizeof(linea));
	    //cout << linea << endl;
	    
	    std::stringstream sst;
	    sst.str (linea);
	    std::string s = sst.str();
	    // std::cout << "s: "  << s << '\n';	    
	    std::size_t pos = s.find(" ");  
	    // std::cout << "pos: "  << pos << '\n';	  
	    
	    std::string cad1 = s.substr(0,pos);
	    //std::cout << "cad1: " << cad1 << '\n'; 	 
	    stringstream geek1(cad1);
	    int indice1 = 0;
	    geek1 >> indice1;	    

	    std::string s2 = s.substr(pos+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos2 = s2.find(" ");   
	    // std::cout << "pos2: "  << pos2 << '\n'; 
	    
	    std::string cad2 = s2.substr(0,pos2);
	    //std::cout << "cad2: " << cad2 << '\n';  	 
	    stringstream geek2(cad2);
	    int indice2 = 0;
	    geek2 >> indice2;	    

	    std::string s3 = s2.substr(pos2+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos3 = s3.find(" ");   
	    // std::cout << "pos3: "  << pos3 << '\n'; 
	    
	    std::string cad3 = s3.substr(0,pos3);
	    //std::cout << "cad3: " << cad3 << '\n';   
	    stringstream geek3(cad3);
	    int indice3 = 0;
	    geek3 >> indice3;	  	    
	    
	    triangulos[0][cont2] = indice1;
	    triangulos[1][cont2] = indice2;
	    triangulos[2][cont2] = indice3;	    
	    //std::cout << '\n'; 	
	    
	    cont2++;
	}	
	
	for (int i = 0; i < cont2; i++)
	{
	  float xx1 = 0, xx2 = 0, xx3 = 0, yy1 = 0, yy2 = 0, yy3 = 0;
	  
	  for (int j = 0; j < 3; j++)
	  {
	    //cout << "triangulos[" << i << "][" << j << "]: " << triangulos[i][j] << '\n';
	    
	    int indice = triangulos[j][i];
	    
	    if(j == 0)
	    {
	      xx1 = (float)puntos[0][indice];
	      yy1 = (float)puntos[1][indice];
	      
	      //cout << "xx1: " << xx1 << endl;
	      //cout << "yy1: " << yy1 << endl;
	    }
	    else if(j == 1)
	    {
	      xx2 = (float)puntos[0][indice];
	      yy2 = (float)puntos[1][indice];
	      
	      //cout << "xx2: " << xx2 << endl;
	      //cout << "yy2: " << yy2 << endl;
	    }
	    else if(j == 2)
	    {
	      xx3 = (float)puntos[0][indice];
	      yy3 = (float)puntos[1][indice];
	      
	      //cout << "xx3: " << xx3 << endl;
	      //cout << "yy3: " << yy3 << endl;
	    }
	  }	    
	    
	  float d1,d2,d3;
	  
	  d1 = sqrt(((xx2 - xx1) * (xx2 - xx1))+((yy2 - yy1) * (yy2 - yy1)));
	  //cout << "d1: " << d1 << endl;
	  d2 = sqrt(((xx3 - xx2) * (xx3 - xx2))+((yy3 - yy2) * (yy3 - yy2)));
	  //cout << "d2: " << d2 << endl;
	  d3 = sqrt(((xx3 - xx1) * (xx3 - xx1))+((yy3 - yy1) * (yy3 - yy1)));
	  //cout << "d3: " << d3 << endl;
	  
	  perimetro = d1 + d2 + d3;
	  cout << "perimetro: " << perimetro << endl;
	  cout << "sumaperimetros: " << sumaperimetros << endl;
	  
	  sumaperimetros = sumaperimetros + perimetro;
	}

	// cout << "\nNUMERO DE LINEAS: " << cont << endl; 
	fichero.close();            // Finalmente, cierro 
	fichero2.close();            // Finalmente, cierro 
	for (int i = 0; i < 1; ++i)
	{
		salida[i].close ();
	}
	
	// std::cout << getFileSize("numeros.csv") << std::endl;
	
	cout << "La suma de los perimetros de todos los triangulos es: " << sumaperimetros << endl;
}
