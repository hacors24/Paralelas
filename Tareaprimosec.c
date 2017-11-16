#include <stdlib.h>
#include <iostream.h>
#include <time.h>

int esprimo(int num2)
{
int a=0;
for(int i=1;i<=num2;i++)
{
    if(num2%i==0) 
    a++;
    if(a>2)
    return 0;
}
return 1;
}

int main(int argc, char** argv) {

clock_t start = clock();
int num;

cout << "Introduce un Numero: " <<endl;
cin >> num; 

for(int j=2;j<=num;j++){

if(esprimo(j))
{
    cout << "Primo: \n" << j << endl;
}

}
    cout << "Tiempo transcurrido: \n" << ((double)clock() - start) / CLOCKS_PER_SEC << endl;
 return 0;
}
