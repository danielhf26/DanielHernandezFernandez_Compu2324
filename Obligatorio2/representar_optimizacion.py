## Plantilla de ajuste lineal y gráfica
### Importación de paquetes
# Primero importamos los paquetes y módulos que nos hacen falta:  
# - pandas lo utilizaremos para leer los datos
# - numpy lo usamos para operaciones con vectores y matrices
# - del paquete scipy.optimize importamos la función curve_fit. Esta función nos permite ajustar datos a una función que definamos. En nuestro caso será una función lineal con uno o dos parámetros
# - matplotlib es un módulo para hacer gráficas

import pandas as pd
import numpy as np
from scipy.optimize import curve_fit
from statistics import stdev
from statistics import mean
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

### Fichero de datos
# Aquí definimos el nombre del fichero que tiene los datos.
# Debe ser un fichero con 4 columnas separadas por comas conteniendo en cada columna los valores medidos de x, de y, el error de x y el error de y.  
# La primera fila del fichero debe ser un cabecer con un nombre descriptivo de cada columna (también separado por comas).

file_name = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Obligatorio2/Datos_isin.txt'
#file_name2= 'C:/Codeblocks/datos2.txt'
# file_name3= 'C:/Codeblocks/datos3.txt'
# file_name4= 'C:/Codeblocks/datos.txt'
# file_name5= 'C:/Codeblocks/datos.txt'

### Función de ajuste
# La función que vamos a utilizar es una función lineal con 1 parámetro (y = ax) o dos parámetros (y = ax+b).  
# En función de la que necesitemos, descomentamos una u otra definición.

def func(x, a,b):
    return a*x+b

# def func(x, a, b):
#     return a*x + b

### Lectura de datos
# Leemos y mostramos los datos.  
# Si utilizamos un delimitador diferente de coma ( , ) lo cambiamos en el argumento delimiter.
# > https://pandas.pydata.org/docs/reference/api/pandas.read_csv.html

data = pd.read_csv(file_name, delimiter='\t', names=['x', 'dx', 'y'])
print(data)






fig=plt.figure(figsize=[18,12])
ax=fig.gca()
#plt.errorbar(data.x, data.y, xerr=data.dx, yerr=data.dy,fmt='b.', label='Error relativo', linewidth=2)

plt.plot(data.x, data.dx, 'b-', linewidth=1)
plt.plot(data.x, data.dx, 'b.', linewidth=1, label='Portátil')
plt.plot(data.x, data.y, 'r-', linewidth=1)
plt.plot(data.x, data.y, 'r.', linewidth=1,label='joel')



plt.title("Comparación portátil vs joel", fontsize=25)
plt.ylabel(r'Tiempo requerido (s)',fontsize=25)
plt.xlabel(r'Numero de espines ',fontsize=25)
plt.legend(loc='upper left',fontsize=30)

# Este comando permite modificar el grosor de los ejes:
for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(3)

# Con estas líneas podemos dar formato a los "ticks" de los ejes:
plt.tick_params(axis="x", labelsize=25, labelrotation=0, labelcolor="black")
plt.tick_params(axis="y", labelsize=25, labelrotation=0, labelcolor="black")
plt.grid()

# Aquí dibuja el gráfico que hemos definido.
plt.show()
