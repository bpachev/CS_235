from matplotlib import pyplot as plt
import numpy as np

def plot_sin():
  x_range = np.linspace(-2*np.pi,2*np.pi,500)
  y_range = np.sin(x_range)
  plt.plot(x_range,y_range)
  plt.show()
  
  
plot_sin()