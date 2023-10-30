import numpy as np
import matplotlib.pyplot as plt


def parseToData(path):
  file = open(path, "r")
  data = []
  for line in file:
    line = line.strip()
    line = line.split(" ")
    data.append(parseToDatapoint(line))
  return data

def parseToDatapoint(line):
  value = [float(line[i]) for i in range(1,len(line))]
  label = float(line[0])
  return value, label

def filterData(data, labels):
  filtered = []
  for i in range(len(data)):
    if data[i][1] not in labels:
      continue
    filtered.append(data[i])
  return filtered

def calcIntensity(data):
  intensity = []
  for i in range(len(data)):
    intensity.append(sum(data[i][0])/len(data[i][0]))
  return intensity



def calcSymmetry(data):
  symmetry=[]
  for i in range(len(data)):
    rev = list(reversed(data[i][0]))
    assymetry= 0
    for j in range(len(data[i][0])):
      assymetry += abs(data[i][0][j] - rev[j])
    assymetry /= len(data[i][0])
    symmetry.append(1-assymetry)
  return symmetry
    
if __name__ == "__main__":
  path = "zip.train"
  data = parseToData(path)
  #print(data[0])
  dataAvgIntensity = np.mean(calcIntensity(data))
  data = filterData(data, [1,5])
  #print(list([data[i][1] for i in range(len(data))]))
  intensity = np.array(calcIntensity(data)) + abs(dataAvgIntensity)
  symmetry = calcSymmetry(data)
  assert(len(intensity) == len(symmetry) == len(data))
  
  plt.figure()
  plt.title("Intensity vs Symmetry")
  plt.xlabel("Intensity")
  plt.ylabel("Symmetry")
  for i in range(len(data)):
    if data[i][1] == 1:
      plt.scatter(intensity[i], symmetry[i], c="blue", marker = "o")
    elif data[i][1] == 5:
      plt.scatter(intensity[i], symmetry[i], c="red", marker = "x")
  plt.savefig("intensity_vs_symmetry.pdf")
  
  