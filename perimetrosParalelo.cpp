#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "typeinfo"
#include <sstream>
#include <cmath>
#include "mpi.h"

using namespace std;


int main(int argc, char *argv[] )
{ 
 	MPI_Status estado;
	int rank,num_procs;
 
	MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

	
	int num0 = 0;	
	int num = 0;
	fstream fichero, fichero2; 
	char linea[30]; 
	int cont = 0;
	int cont2 = 0;
	float sumatoria = 0;
	float perimetro;
	float sumaperimetros = 0;	
	
	//std::string puntos[15000][2];
	float puntos2[2][15000]; 
	//std::string triangulos[15000][3]; 
	int triangulos2[3][15000]; 	
	
if(rank == 0)
{
	// Abro para lectura 
	fichero.open("puntos", ios::in); 
	// fichero >> linea;           // Leo una primera linea 
	//fichero2.open("prueba_triangulos", ios::in); 
	fichero2.open("triangulos", ios::in); 
	// fichero2 >> linea;           // Leo una primera linea 

		
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
	    
	    puntos2[0][indice] = cadX;
	    puntos2[1][indice] = cadY;
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
	    
	    triangulos2[0][cont2] = indice1;
	    triangulos2[1][cont2] = indice2;
	    triangulos2[2][cont2] = indice3;
	    //std::cout << '\n'; 	
	    
	    cont2++;
	}  
	
	  for(int pr=1; pr<num_procs; pr++)
	  {	  
	    //Envia y recibe mensajes
	    MPI_Send(&cont2 //referencia al vector de elementos a enviar
		    ,1 // tamaño del vector a enviar
		    ,MPI_INT // Tipo de dato que envias
		    ,pr // pid del proceso destino
		    ,0 //etiqueta
		    ,MPI_COMM_WORLD); //Comunicador por el que se manda	  
	    
	    //Envia y recibe mensajes
	    MPI_Send(&cont //referencia al vector de elementos a enviar
		    ,1 // tamaño del vector a enviar
		    ,MPI_INT // Tipo de dato que envias
		    ,pr // pid del proceso destino
		    ,6 //etiqueta
		    ,MPI_COMM_WORLD); //Comunicador por el que se manda	 	    
	    
	    for(int k=0; k<3; k++)
	    {
	      MPI_Send(&triangulos2[k] //referencia al vector de elementos a enviar
		      ,cont2 // tamaño del vector a enviar
		      ,MPI_INT  // Tipo de dato que envias
		      ,pr // pid del proceso destino
		      ,1+k //etiqueta
		      ,MPI_COMM_WORLD); //Comunicador por el que se manda	  
	    }
	    
	    for(int k2=0; k2<2; k2++)
	    {
	      MPI_Send(&puntos2[k2] //referencia al vector de elementos a enviar
		      ,cont // tamaño del vector a enviar
		      ,MPI_FLOAT  // Tipo de dato que envias
		      ,pr // pid del proceso destino
		      ,4+k2 //etiqueta
		      ,MPI_COMM_WORLD); //Comunicador por el que se manda	  
	    }
	    
	   // MPI_Reduce(&sumatoria, 0, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	  }
	
	
	
}
else
{

  
  
   	  MPI_Recv(&num0 // Referencia al vector donde se almacenara lo recibido
		  ,1 // tamaño del vector a recibir
		  ,MPI_INT // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,6 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est 
  
  	  MPI_Recv(&num // Referencia al vector donde se almacenara lo recibido
		  ,1 // tamaño del vector a recibir
		  ,MPI_INT // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,0 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est

	  
  	  MPI_Recv(&triangulos2[0] // Referencia al vector donde se almacenara lo recibido
		  ,num // tamaño del vector a recibir
		  ,MPI_INT  // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,1 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est	 
	  
  	  MPI_Recv(&triangulos2[1] // Referencia al vector donde se almacenara lo recibido
		  ,num // tamaño del vector a recibir
		  ,MPI_INT  // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,2 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est	  
	  
  	  MPI_Recv(&triangulos2[2] // Referencia al vector donde se almacenara lo recibido
		  ,num // tamaño del vector a recibir
		  ,MPI_INT  // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,3 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est	
	  
  	  MPI_Recv(&puntos2[0] // Referencia al vector donde se almacenara lo recibido
		  ,num0 // tamaño del vector a recibir
		  ,MPI_INT  // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,4 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est	 
	  
  	  MPI_Recv(&puntos2[1] // Referencia al vector donde se almacenara lo recibido
		  ,num0 // tamaño del vector a recibir
		  ,MPI_INT  // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,5 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del est	  


	
	int l;
	  
	  if(num_procs > 1)
	  {
	    l = num / (num_procs - 1);
	  }
	  else
	  {
	    l = num / num_procs;
	  }	
	
	  int min = (rank-1)*l;
	  int max;
	  
	  if(rank == (num_procs - 1))
	  {	    
	    max = num;
	  }
	  else
	  {
	    max = (rank*l)-1;
	  }		
	
	//cout << "MIN: " << min << endl;
	//cout << "MAX: " << max << endl;
	
	 float sumaperimetros2 = 0;
	  
 	for (int i = min; i <= max; i++)
	{
	  
	  float xx1 = 0, xx2 = 0, xx3 = 0, yy1 = 0, yy2 = 0, yy3 = 0;
	  
	  for (int j = 0; j < 3; j++)
	  {
	    // cout << "triangulos2[" << j << "][" << i << "]: " << triangulos2[j][i] << '\n';
	    
	    int indice = (int)triangulos2[j][i];
	    
	    if(j == 0)
	    {
	      xx1 = (float)puntos2[0][indice];
	      yy1 = (float)puntos2[1][indice];
	      
	      //cout << "xx1: " << xx1 << endl;
	      //cout << "yy1: " << yy1 << endl;
	    }
	    else if(j == 1)
	    {
	      xx2 = (float)puntos2[0][indice];
	      yy2 = (float)puntos2[1][indice];
	      
	      //cout << "xx2: " << xx2 << endl;
	      //cout << "yy2: " << yy2 << endl;
	    }
	    else if(j == 2)
	    {
	      xx3 = (float)puntos2[0][indice];
	      yy3 = (float)puntos2[1][indice];
	      
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
	  
	  perimetro = (float)(d1 + d2 + d3);
	  //cout << "perimetro: " << perimetro << " | Rank: " << rank << endl;
	  
	  sumaperimetros2 = (float)(sumaperimetros2 + perimetro);
	  
	} 
	
	//cout << "sumaperimetros2: " << sumaperimetros2 << " | Rank: " << rank << endl; 
	
	MPI_Send(&sumaperimetros2 //referencia al vector de elementos a enviar
	,1 // tamaño del vector a enviar
	,MPI_FLOAT // Tipo de dato que envias
	,0 // pid del proceso destino
	,7 //etiqueta
	,MPI_COMM_WORLD); //Comunicador por el que se manda
	
	
	sumaperimetros = sumaperimetros2;
	//MPI_Reduce(&sumatoria, &sumaperimetros, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);  // No funciono
	
}

 	if(rank == 0)
	{
	  float sumaperimetros2 = 0;
	  float sumaperimetros3 = 0;
	  
	  for(int pr=1; pr<num_procs; pr++)
	  { 
	    
	    MPI_Recv(&sumaperimetros2 // Referencia al vector donde se almacenara lo recibido
		    ,1 // tamaño del vector a recibir
		    ,MPI_FLOAT // Tipo de dato que recibe
		    ,pr // pid del proceso origen de la que se recibe
		    ,7 // etiqueta
		    ,MPI_COMM_WORLD // Comunicador por el que se recibe
		    ,&estado); // estructura informativa del est	    
	    
	    sumaperimetros3 = sumaperimetros3 + sumaperimetros2;
	    cout << "Suma parcial proceso: " << pr << ": " << sumaperimetros2 << endl;
	    
	  }
	  
	    cout << "Sumaperimetros total: " << sumaperimetros3 << endl;
	  
	}
	
	
    MPI_Finalize();  
    	
    return 0;	
}
