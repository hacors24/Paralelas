#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#include<iostream>

using namespace std;
 
int main(int argc, char *argv[])
{
    clock_t cl = clock();
  
	MPI_Status estado;
	int rank,num_procs;
	int i,j, contador;
 
	MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificadoror
 
	int num,n;
	int L;
	int l;
    
    
 	if(rank == 0)
	{
	  //cout << "Introduce un numero: " << endl;
	  //cin >> num;
	  num = 1000000;
	  
	  if(num_procs > 1)
	  {
	    L = num / (num_procs - 1);
	  }
	  else
	  {
	    L = num / num_procs;
	  }
	  // cout << "Soy el proceso " << rank << " L: " <<  "\n" << L << endl;
	  
	  for(int pr=1; pr<num_procs; pr++)
	  {	  
	    //Envia y recibe mensajes
	    MPI_Send(&L //referencia al vector de elementos a enviar
		    ,1 // tamaño del vector a enviar
		    ,MPI_INT // Tipo de dato que envias
		    ,pr // pid del proceso destino
		    ,0 //etiqueta
		    ,MPI_COMM_WORLD); //Comunicador por el que se manda	    
	  }
	  
	    MPI_Send(&num //referencia al vector de elementos a enviar
		    ,1 // tamaño del vector a enviar
		    ,MPI_INT // Tipo de dato que envias
		    ,(num_procs-1) // pid del proceso destino
		    ,1 //etiqueta
		    ,MPI_COMM_WORLD); //Comunicador por el que se manda		  

	}
	else
	{   
    
	  MPI_Recv(&l // Referencia al vector donde se almacenara lo recibido
		  ,1 // tamaño del vector a recibir
		  ,MPI_INT // Tipo de dato que recibe
		  ,0 // pid del proceso origen de la que se recibe
		  ,0 // etiqueta
		  ,MPI_COMM_WORLD // Comunicador por el que se recibe
		  ,&estado); // estructura informativa del estado

	  // cout<< "Soy el proceso "<<rank<<" y he recibido "<<l<<endl;
	  
	  int min = (rank-1)*l;
	  int max;
	  
	  if(rank == (num_procs - 1))
	  {
	    MPI_Recv(&n // Referencia al vector donde se almacenara lo recibido
		    ,1 // tamaño del vector a recibir
		    ,MPI_INT // Tipo de dato que recibe
		    ,0 // pid del proceso origen de la que se recibe
		    ,1 // etiqueta
		    ,MPI_COMM_WORLD // Comunicador por el que se recibe
		    ,&estado); // estructura informativa del estado	
	    
	    max = n;
	  }
	  else
	  {
	    max = (rank*l)-1;
	  }
	    
	  
	  for(int j = min; j <= max; j++)
	  {
		  int a=0;
		  for(int i=1;i<=j;i++)
		  {
		      if(j%i==0) // si num1 módulo de i es 0, incrementamos a en 1.
		      a++;
		  }

		  if(a==2) // Si al final del bucle, a vale 2, el número es primo, porque tiene solamente 2 divisores.
		  {
		    //cout << "Soy el proceso " << rank << " primo: " << j << endl;
		    cout << j << endl;
		  }
	  }	  
	}	
	
    MPI_Finalize();   
	
	//cout <<  "\nTIEMPO EJECUCION: " << (clock()-cl)/CLOCKS_PER_SEC << " s" << endl;
	cout <<  "TIEMPO EJECUCION: " << (clock()-cl)*1000/CLOCKS_PER_SEC << " ms" << endl;
	//cout <<  "TIEMPO EJECUCION: " << (clock()-cl) << " microsegundos" << endl;
	
    return 0;
}
