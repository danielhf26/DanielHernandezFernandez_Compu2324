import math as mt
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt



file_name =  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario1/Datos_pendulo2.txt'

data = pd.read_csv(file_name, delimiter=',', header=1, names=['m', 't'])

print(data)

fig=plt.figure(figsize=[18,12])
ax=fig.gca()
plt.plot( data.t, data.m, 'b', label='E=1', linewidth=1)





plt.title(' Energía E=3 \n Condiciones iniciales: φ=0.1, ψ=0.2', fontsize=30)
plt.ylabel(r'Ángulo φ ',fontsize=30)
plt.xlabel(r'Ángulo ψ',fontsize=30)
for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(2)
    
plt.grid()

plt.tick_params(axis="x", labelsize=20, labelrotation=0, labelcolor="black")
plt.tick_params(axis="y", labelsize=20, labelrotation=0, labelcolor="black")
#plt.legend()

#plt.xlim(0,0.3)
#plt.ylim(data.x[0],data.x[100])
plt.show()