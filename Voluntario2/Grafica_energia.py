import pandas as pd
import matplotlib.pyplot as plt

# Cargar datos desde el archivo CSV
filename = 'C:/fisica_computacional/Repositorios_git/DanielHernandezFernandez_Compu2324/Voluntario2/Datos_energias.txt'
data = pd.read_csv(filename, header=None, delimiter=',', names=['Temperatura','Ener', 'Error'])
print(data)
# Calcular la magnetización total
#data['MagTotal'] = data['MagSuperior'] + data['MagInferior']

# Graficar los datos
plt.figure(figsize=(10, 6))

# Graficar la energía
plt.errorbar(data['Temperatura'], data['Ener'], yerr=data['Error'], fmt='-', linewidth=1, capsize=5, elinewidth=2, label='Energía', color='red')



# Añadir etiquetas y título
plt.xlabel('Temperatura ', fontsize=13)
plt.ylabel('Energía ', fontsize=13)
plt.title(' N=128, 10000 Pasos Montecarlo', fontsize=13)
plt.legend()

# Mostrar la gráfica
plt.grid(True)
plt.show()