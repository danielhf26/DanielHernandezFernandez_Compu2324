import math as mt
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt



file_name =  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario1/Datos_pendulo.txt'
file_name2=  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario1/Datos_pendulo2.txt'
file_name3=  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario1/Datos_pendulo3.txt'
file_name4 =  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario1/Datos_pendulo4.txt'
file_name5 =  'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario1/Datos_pendulo5.txt'
data = pd.read_csv(file_name, delimiter=',', header=1, names=['m', 't'])
data2 = pd.read_csv(file_name2, delimiter=',', header=1, names=['m', 't'])
data3 = pd.read_csv(file_name3, delimiter=',', header=1, names=['m', 't'])
data4 = pd.read_csv(file_name4, delimiter=',', header=1, names=['m', 't'])
data5 = pd.read_csv(file_name5, delimiter=',', header=1, names=['m', 't'])
print(data)

fig=plt.figure(figsize=[18,12])
ax=fig.gca()
plt.plot( data.t, data.m, 'orange', label=' φ=0.2, ψ=0.2', linewidth=1)
plt.plot( data2.t, data2.m, 'b', label=' φ=0.201, ψ=0.201',linewidth=1)
# plt.plot( data3.t, data3.m, 'r', label='E=5',linewidth=1)
# plt.plot( data4.t, data4.m, 'violet', label='E=10',linewidth=1)
# plt.plot( data5.t, data5.m, 'g', label='E=15',linewidth=1)




plt.title(' Energía E=15', fontsize=30)
plt.ylabel(r'Ángulo φ ',fontsize=30)
plt.xlabel(r'Ángulo ψ',fontsize=30)
for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(2)
    
plt.legend(fontsize=25)
plt.grid()

plt.tick_params(axis="x", labelsize=20, labelrotation=0, labelcolor="black")
plt.tick_params(axis="y", labelsize=20, labelrotation=0, labelcolor="black")
#plt.legend()

#plt.xlim(0,0.3)
#plt.ylim(data.x[0],data.x[100])
plt.show()