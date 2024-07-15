import pandas as pd
import matplotlib.pyplot as plt

# Cargar datos desde el archivo CSV
filename = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_energias.txt'
data = pd.read_csv(filename, header=None, delimiter=',', names=['Temperatura','Magtotal', 'MagSuperior', 'ErrorSup', 'MagInferior', 'ErrorInf'])
print(data)
# Calcular la magnetización total
#data['MagTotal'] = data['MagSuperior'] + data['MagInferior']

# Graficar los datos
plt.figure(figsize=(10, 6))

# Graficar la magnetización superior
plt.errorbar(data['Temperatura'], data['MagSuperior'], yerr=data['ErrorSup'], fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Magnetización Superior', color='red')

# Graficar la magnetización inferior
plt.errorbar(data['Temperatura'], data['MagInferior'], yerr=data['ErrorInf'], fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Magnetización Inferior',color='blue')

# Graficar la magnetización total
plt.plot(data['Temperatura'], data['Magtotal'], '-.', linewidth=1, label='Magnetización Total', color='green')

# Añadir etiquetas y título
plt.xlabel('Temperatura ', fontsize=13)
plt.ylabel('Magnetización ', fontsize=13)
plt.title(' N=64, 50000 Pasos Montecarlo', fontsize=13)
plt.legend()

# Mostrar la gráfica
plt.grid(True)
plt.show()