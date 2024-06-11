import math as mt
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt



file_name =  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_magnetizacion.txt'
data = pd.read_csv(file_name, delimiter='\t', names=['T', 'm', 'mi', 'dmi', 'ms', 'dms'])
print(data)

fig=plt.figure(figsize=[18,12])
ax=fig.gca()
#plt.plot( data.T, data.m, 'b.', label='Energía total')
#plt.plot( data.T, data.mi, 'r.', label= 'Cinética')
#plt.plot( data.T, data.mi, 'g.', label='Potencial')
plt.plot(data.T, data.mi, 'b-', linewidth=1)
plt.errorbar(data.T, data.y, xerr=data.dx, yerr=data.dy,fmt='b.', label='Error relativo', linewidth=2)
print(data.mi)

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