/*
  #include <stdio.h>
  #include <stdlib.h>

  #define TRUE 1
  #define FALSE 0
 
  typedef struct {
      int on;
  } Lampada;

 Lampada* NewLampada() {
     Lampada* lamp = malloc(sizeof(Lampada*));
     lamp->on = FALSE;
     return lamp;
 }

 void Click(Lampada* lamp) {
     if (lamp->on == FALSE) {
         lamp->on = TRUE;
     } else {
         lamp->on = FALSE;
     }
 }

 int main() {
     Lampada* lamp = NewLampada();
     if (TRUE) {
         Click(lamp);
     }
     printf("%d\n", lamp->on);
     return 0;
 }

*/
  #include <stdio.h>

  void adder(int* x, int n, int max) {
      while (*x < max) {
          *x += n;
      }
      max *= 2;
  }

 void subtractor(int* x, int n, int max) {
     while (*x >= max) {
         *x -= n;
     }
 }

 int main() {
     int a, b, c;
     scanf("%d %d %d", &a, &b, &c);
     b = 2;
     adder(&a, b, c);
     subtractor(&a, b, c);
     printf("%d %d %d\n", a, b, c);
 }