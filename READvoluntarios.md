
ENTREGA DE LOS EJERCICIOS VOLUNTARIOS:

Se han realizado dos ejercicios voluntarios para la asignatura de fisica computacional en la ugr. El primer voluntario elegido es una simulación del péndulo doble a través del algoritmo de Runge-Kutta.
El segundo voluntario escogido es la simulación del modelo de ising-kawasaki a través de algoitmos montecarlo.
A continuación se detallan los contenidos de cada carpeta.

VOLUNTARIO1: PENDULO DOBLE: 

  -Pendulo.c: Código principal de la simulación. Utiliza el algoritmo de Runge kutta para obtener la dinámica del péndulo doble. Se requiere de "pendulo.h" para ejecutarlo.

  -pendulo.h: posee las funciones utilizadas en el código pendulo.c.
  
  -pendulo_lyapunov.c: Variación del codigo principal en la que se relizan dos simulaciones a la vez, lo que nos permite calcular los coeficientes de lyapunov. Se requiere también "pendulo.h".
  
  -animacion_pendulo.py: programa de python que nos permíte animar el péndulo doble con los datos obtenidos en "pendulo.c".
  
  -Grafica_pendulo.py: prgrama utilizado para obtener los mapas de Poincaré para una única energía.
  
  -Grafica_pendulo_energias.py: programa utilizado para obtener mapas de Poincaré para varias energías a la vez.


VOLUNTARIO2: MODELO DE KAWASAKI:

-Kawasaki.c: Programa que simula el modelo de Kawasaki con condiciones de contorno periódicas en todos los ejes. Requiere de "Funciones_kawasaki.h" para ejecutarse.

  -Kawasaki_contorno.c: Porgrama que simula el modelo de Kawasaki con condiciones de contorno periodicas en un eje y fijas en el otro. Este es el programa utilizado para la obtención de resultados. Requiere de "Funciones_kawasaki.h".
  
  -Funciones_kawasaki.h: aquí se encuentran todas las funciones utilizadas en las simulaciones.
  
  -animacion_Kawasaki.py: programa en python que anima el modelo de Kawasaki a partir de los datos obtenidos de las simulaciones.
  
  -Grafica_mag.py: porgrama en python para graficar las magnetizaciones.
  
  -Grafica_energia.py: programa en python para graficar la energía.
  
  -Grafica_densidad.py: programa en python para graficar las densidades.
