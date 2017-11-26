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
	
	std::string puntos[50000][2]; 
	std::string triangulos[50000][3]; 

	// Abro para lectura 
	fichero.open("puntos", ios::in); 
	// fichero >> linea;           // Leo una primera linea 
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

	    std::string s3 = s2.substr(pos2+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos3 = s3.find(" ");   
	    // std::cout << "pos3: "  << pos3 << '\n'; 
	    
	    std::string cad3 = s3.substr(0,pos3);
	    //std::cout << "cad3: " << cad3 << '\n';    
	    
	    stringstream geek(cad1);
	    int indice = 0;
	    geek >> indice;
	    
	    puntos[indice][0] = cad2;
	    puntos[indice][1] = cad3;
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

	    std::string s2 = s.substr(pos+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos2 = s2.find(" ");   
	    // std::cout << "pos2: "  << pos2 << '\n'; 
	    
	    std::string cad2 = s2.substr(0,pos2);
	    //std::cout << "cad2: " << cad2 << '\n';  	    

	    std::string s3 = s2.substr(pos2+1); 
	    // std::cout << "s2: "  << s2 << '\n';      
	    std::size_t pos3 = s3.find(" ");   
	    // std::cout << "pos3: "  << pos3 << '\n'; 
	    
	    std::string cad3 = s3.substr(0,pos3);
	    //std::cout << "cad3: " << cad3 << '\n';    
	    
	    triangulos[cont2][0] = cad1;
	    triangulos[cont2][1] = cad2;
	    triangulos[cont2][2] = cad3;
	    //std::cout << '\n'; 	
	    
	    cont2++;
	}	
	
	for (int i = 0; i < cont2; i++)
	{
	  float xx1 = 0, xx2 = 0, xx3 = 0, yy1 = 0, yy2 = 0, yy3 = 0;
	  
	  for (int j = 0; j < 3; j++)
	  {
	    cout << "triangulos[" << i << "][" << j << "]: " << triangulos[i][j] << '\n';
	    
	    stringstream geek(triangulos[i][j]);
	    int indice = 0;
	    geek >> indice;
	    
	    if(j == 0)
	    {
	      std::string x1 = puntos[indice][0];
	      std::string y1 = puntos[indice][1];
	      
	      cout << "x1: " << x1 << endl;
	      cout << "y1: " << y1 << endl;
	      
	      stringstream geekx(x1);
	      float X1 = 0;
	      geekx >> X1;
	      xx1 = X1;
	      
	      stringstream geeky(y1);
	      float Y1 = 0;
	      geeky >> Y1;
	      yy1 = Y1;
	    }
	    else if(j == 1)
	    {
	      std::string x2 = puntos[indice][0];
	      std::string y2 = puntos[indice][1];
	      
	      cout << "x2: " << x2 << endl;
	      cout << "y2: " << y2 << endl;
	      
	      stringstream geekx(x2);
	      float X2 = 0;
	      geekx >> X2;
	      xx2 = X2;
	      
	      stringstream geeky(y2);
	      float Y2 = 0;
	      geeky >> Y2;
	      yy2 = Y2;
	    }
	    else if(j == 2)
	    {
	      std::string x3 = puntos[indice][0];
	      std::string y3 = puntos[indice][1];
	      
	      cout << "x3: " << x3 << endl;
	      cout << "y3: " << y3 << endl;
	      
	      stringstream geekx(x3);
	      float X3 = 0;
	      geekx >> X3;
	      xx3 = X3;
	      
	      stringstream geeky(y3);
	      float Y3 = 0;
	      geeky >> Y3;
	      yy3 = Y3;
	    }
	  }
	    
	  float d1,d2,d3;
	  
	  //d1 = sqrt(((xx2 – xx1)*(xx2 – xx1))+((yy2 – yy1)*(yy2 – yy1)));
	  d1 = xx2 - xx1;
	  cout << "d1: " << d1 << endl;
	  
	}

	// cout << "\nNUMERO DE LINEAS: " << cont << endl; 
	fichero.close();            // Finalmente, cierro 
	fichero2.close();            // Finalmente, cierro 
	for (int i = 0; i < 1; ++i)
	{
		salida[i].close ();
	}
	
	// std::cout << getFileSize("numeros.csv") << std::endl;
}
