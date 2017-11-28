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
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);	// Número de procesos
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);		// Número proceso

	
	int num0 = 0;
	int num = 0;
	char linea[30]; 
	int cont = 0;
	int cont2 = 0;
	float sumatoria = 0;
	float perimetro;
	float sumaperimetros = 0;
	
	float puntos[2][15000]; 
	int triangulos[3][15000]; 
	
	fstream f_puntos, f_triangulos; 
	
	
	// HAGO LECTURA DE LOS FICHEROS EN EL PROCESO "0"
	if(rank == 0)
	{
		// Abro ficheros 
		f_puntos.open("puntos", ios::in); 
		f_triangulos.open("triangulos", ios::in); 

		// PASO DATOS DE FICHERO "puntos" A UN ARRAY DE FLOAT
		if(f_puntos.fail())
		cerr << "Error al abrir el archivo puntos" << endl;
		else
		while(!f_puntos.eof())
		{
		    f_puntos.getline(linea, sizeof(linea));
		    
		    std::stringstream sst;
		    sst.str (linea);
		    std::string s = sst.str();	    
		    std::size_t pos = s.find(" ");    
		    
		    std::string cad1 = s.substr(0,pos);    

		    std::string s2 = s.substr(pos+1);
		    std::size_t pos2 = s2.find(" ");
		    
		    std::string cad2 = s2.substr(0,pos2);
		    stringstream geekx(cad2);
		    float cadX = 0;
		    geekx >> cadX;	    

		    std::string s3 = s2.substr(pos2+1);     
		    std::size_t pos3 = s3.find(" ");
		    
		    std::string cad3 = s3.substr(0,pos3);  
		    stringstream geeky(cad3);
		    float cadY = 0;
		    geeky >> cadY;	    
		    
		    stringstream geek(cad1);
		    int indice = 0;
		    geek >> indice;
		    
		    puntos[0][indice] = cadX;
		    puntos[1][indice] = cadY;
		    
		    cont++;
		}
		
		
		// PASO DATOS DE FICHERO "triangulos" A UN ARRAY DE ENTEROS
		if(f_triangulos.fail())
		cerr << "Error al abrir el archivo triangulos" << endl;
		else
		while(!f_triangulos.eof())
		{
		    f_triangulos.getline(linea, sizeof(linea));
		    
		    std::stringstream sst;
		    sst.str (linea);
		    std::string s = sst.str();	    
		    std::size_t pos = s.find(" ");    
		    
		    std::string cad1 = s.substr(0,pos); 
		    stringstream geek1(cad1);
		    int indice1 = 0;
		    geek1 >> indice1;	    

		    std::string s2 = s.substr(pos+1);    
		    std::size_t pos2 = s2.find(" ");   
		    
		    std::string cad2 = s2.substr(0,pos2);
		    stringstream geek2(cad2);
		    int indice2 = 0;
		    geek2 >> indice2;	    

		    std::string s3 = s2.substr(pos2+1); 
		    std::size_t pos3 = s3.find(" ");
		    
		    std::string cad3 = s3.substr(0,pos3);
		    stringstream geek3(cad3);
		    int indice3 = 0;
		    geek3 >> indice3;	  	    
		    
		    triangulos[0][cont2] = indice1;
		    triangulos[1][cont2] = indice2;
		    triangulos[2][cont2] = indice3;
		    
		    cont2++;
		}  
		
		// ENVÍO MENSAJE DE PROCESO "0" A LOS DEMAS PROCESOS
		for(int pr=1; pr<num_procs; pr++)
		{  
		  MPI_Send(&cont2, 1, MPI_INT, pr, 0, MPI_COMM_WORLD);  
		  MPI_Send(&cont, 1, MPI_INT, pr, 6, MPI_COMM_WORLD);    
		  
		  for(int k=0; k<3; k++)
		  {
		    MPI_Send(&triangulos[k], cont2, MPI_INT, pr, 1+k, MPI_COMM_WORLD);
		  }
		  
		  for(int k2=0; k2<2; k2++)
		  {
		    MPI_Send(&puntos[k2], cont, MPI_FLOAT, pr, 4+k2, MPI_COMM_WORLD);
		  }
		}
	}
	else
	{
		   int l;
		   float sumaperimetros2 = 0;
	  
		// RECIVO MENSAJE DE PROCESO "0"
		  MPI_Recv(&num0, 1, MPI_INT, 0, 6, MPI_COMM_WORLD, &estado);  
		  MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &estado);
		  MPI_Recv(&triangulos[0],num,MPI_INT,0,1,MPI_COMM_WORLD,&estado);
		  MPI_Recv(&triangulos[1],num,MPI_INT,0,2,MPI_COMM_WORLD,&estado);
		  MPI_Recv(&triangulos[2],num,MPI_INT,0,3,MPI_COMM_WORLD,&estado);
		  MPI_Recv(&puntos[0],num0,MPI_INT,0,4,MPI_COMM_WORLD,&estado);
		  MPI_Recv(&puntos[1],num0,MPI_INT,0,5,MPI_COMM_WORLD,&estado);
		
		  
		// DEFINO LOS MÁXIMOS Y MÍNIMOS DE CADA PROCESO PARA CÁLCULAR PERIMETROS		  
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
		
		
		 // CÁLCULO PERIMETROS Y LOS SUMO DE FORMA PARCIAL POR CADA PROCESO		  
		  for (int i = min; i <= max; i++)
		  {	    
		    float xx1 = 0, xx2 = 0, xx3 = 0, yy1 = 0, yy2 = 0, yy3 = 0;
		    
		    for (int j = 0; j < 3; j++)
		    {	      
		      int indice = (int)triangulos[j][i];
		      
		      if(j == 0)
		      {
			xx1 = (float)puntos[0][indice];
			yy1 = (float)puntos[1][indice];
		      }
		      else if(j == 1)
		      {
			xx2 = (float)puntos[0][indice];
			yy2 = (float)puntos[1][indice];
		      }
		      else if(j == 2)
		      {
			xx3 = (float)puntos[0][indice];
			yy3 = (float)puntos[1][indice];
		      }
		    }
		      
		    float d1,d2,d3;
		    
		    d1 = sqrt(((xx2 - xx1) * (xx2 - xx1))+((yy2 - yy1) * (yy2 - yy1)));
		    d2 = sqrt(((xx3 - xx2) * (xx3 - xx2))+((yy3 - yy2) * (yy3 - yy2)));
		    d3 = sqrt(((xx3 - xx1) * (xx3 - xx1))+((yy3 - yy1) * (yy3 - yy1)));
		    
		    perimetro = (float)(d1 + d2 + d3);
		    //cout << "perimetro: " << perimetro << " | Rank: " << rank << endl;
		    
		    sumaperimetros2 = (float)(sumaperimetros2 + perimetro);	    
		  } 
		
		
		// ENVÍO SUMA PARCIAL DE PRIMETROS A PROCESO "0"
		MPI_Send(&sumaperimetros2,1,MPI_FLOAT,0,7,MPI_COMM_WORLD);
		//cout << "sumaperimetros2: " << sumaperimetros2 << " | Rank: " << rank << endl; 
	}

	
	// RECIVO SUMAS PARCIALES Y LAS SUMO PARA OBTENER LA SUMATORIA TOTAL
 	if(rank == 0)
	{
	  float sumaperimetros2 = 0;
	  float sumaperimetros3 = 0;
	  
	  for(int pr=1; pr<num_procs; pr++)
	  { 	    
	    MPI_Recv(&sumaperimetros2,1,MPI_FLOAT,pr,7,MPI_COMM_WORLD,&estado);  	    
	    sumaperimetros3 = sumaperimetros3 + sumaperimetros2;
	    cout << "Suma parcial proceso: " << pr << ": " << sumaperimetros2 << endl;	    
	  }
	  
	  cout << "Sumaperimetros total: " << sumaperimetros3 << endl;	  
	}
	
	
    MPI_Finalize();  
   
    return 0;	
}
