#include <stdio.h>

main() {

  int magico = rand();
  
  printf("Deme un número de 0 a 100 ");
  int adivinado = getnum();

  if (adivinado > magico) {
    printf("El número es más pequeño");
  } else if (adivinado < magico) {
    printf("El número es más grande");
  } else {
    printf("¡Acertaste!");
  }

}

getnum() {
  int x;
  scanf("%i",&x);
  return(x);
}
