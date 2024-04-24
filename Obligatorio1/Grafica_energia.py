import math as mt
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt



file_name =  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Obligatorio1/Datos_Energia.txt'
data = pd.read_csv(file_name, delimiter='\t', header=1, names=['m', 'V', 'E', 't'])
print(data)

fig=plt.figure(figsize=[18,12])
ax=fig.gca()
plt.plot( data.t, data.m, 'b', label='Energía total')
plt.plot( data.t, data.E, 'r', label= 'Cinética')
plt.plot( data.t, data.V, 'g', label='Potencial')

plt.ylabel(r'Energía',fontsize=30)
plt.xlabel(r'Tiempo',fontsize=30)
for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(2)
    
plt.grid()

plt.tick_params(axis="x", labelsize=20, labelrotation=0, labelcolor="black")
plt.tick_params(axis="y", labelsize=20, labelrotation=0, labelcolor="black")
plt.legend()

#plt.xlim(0,0.3)
#plt.ylim(data.x[0],data.x[100])
plt.show()