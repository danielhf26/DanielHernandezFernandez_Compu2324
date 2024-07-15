import pandas as pd
import matplotlib.pyplot as plt

# Cargar datos desde el archivo CSV
#Se requieren de 5 archivos que contengan los valores de las densidades de 5 temperaturas, si se quiere graficar solo una densidad, se puede usar el código de Grafica_energia.py
filename = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_densidades1.txt'
filename2 = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_densidades2.txt'
filename3 = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_densidades3.txt'
filename4 = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_densidades4.txt'
filename5 = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_densidades5.txt'
data = pd.read_csv(filename, header=None, delimiter=',', names=['Temperatura', 'MagInferior'])
data2 = pd.read_csv(filename2, header=None, delimiter=',', names=['Temperatura', 'MagInferior'])
data3 = pd.read_csv(filename3, header=None, delimiter=',', names=['Temperatura', 'MagInferior'])
data4 = pd.read_csv(filename4, header=None, delimiter=',', names=['Temperatura', 'MagInferior'])
data5 = pd.read_csv(filename5, header=None, delimiter=',', names=['Temperatura', 'MagInferior'])
print(data)


# Graficar los datos
plt.figure(figsize=(10, 6))

#Graficamos las desidades
plt.errorbar(data['Temperatura'], data['MagInferior'], yerr=data['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, color='blue', label='T=1')
plt.errorbar(data2['Temperatura'], data2['MagInferior'], yerr=data2['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, color='red',label='T=2')
plt.errorbar(data3['Temperatura'], data3['MagInferior'], yerr=data3['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, color='green',label='T=3')
plt.errorbar(data4['Temperatura'], data4['MagInferior'], yerr=data4['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, color='orange',label='T=4')
plt.errorbar(data5['Temperatura'], data5['MagInferior'], yerr=data5['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, color='pink',label='T=5')



# Añadir etiquetas y título
plt.xlabel('Posición eje y ', fontsize=13)
plt.ylabel('Densidad ', fontsize=13)
plt.title(' N=32, 50000 Pasos Montecarlo', fontsize=13)
plt.legend()

# Mostrar la gráfica
plt.grid(True)
plt.show()