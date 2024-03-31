import matplotlib.pyplot as plt
import networkx as nx
import numpy as np
import pandas as pd
import scipy
from contextlib import redirect_stdout
import scipy.stats as st
import statsmodels.api as sm
from scipy.stats._continuous_distns import _distn_names
from sklearn.gaussian_process.kernels import RBF
from sklearn.kernel_ridge import KernelRidge

class graphStat:
  graph = nx.Graph()
  degree_sequence = []
  degree_average = 0
  degree_variance = 0
  clustering_coefficients = []
  diameter = 0
  radius = 0
  eccentricity_sequence = []
  eccentricity_avg = 0
  connected_components_sizes = []
  largest_connected_component = 0
  longest_sp_sequence = []


def readGraph(path):
  # Import  adjacency list into networkx
  return nx.read_adjlist(path, delimiter = " ")

def degreeStatiscs(G):
  degree_sequence = sorted((d for n, d in G.graph.degree()), reverse=True)
  # return degree sequence, average, variance
  return degree_sequence, np.mean(degree_sequence), np.var(degree_sequence)

def longestShortestPaths(G):
  for n in G.graph.nodes():
    try:
      paths = nx.single_source_shortest_path(G.graph, source = n, cutoff = G.graph.number_of_nodes()).values()
      G.longest_sp_sequence.append(max([len(path) for path in paths]))
    except:
      pass

# UNUSED - MIXING OF CONT AND DISCRETE DISTR. IS A NIGHTMARE
def findBestDistribution(data):
  size = len(data)
  y, x = np.histogram(data, bins = 100, density = True)
  
  dist_results=[]
  dist_names = ["norm", "powerlaw", "poisson"]
  for dist_name in dist_names:
    dist = getattr(scipy.stats, dist_name)
    params = dist.fit(y)
    arg = params[:-2]
    loc = params[-2]
    scale = params[-1]  
    if arg:
        pdf_fitted = dist.pdf(x, *arg, loc=loc, scale=scale) * size
    else:
        pdf_fitted = dist.pdf(x, loc=loc, scale=scale) * size
    sse = np.sum(np.power(y - pdf_fitted[:-1], 2.0))
    dist_results.append((dist, params, sse))
  return sorted(dist_results, key=lambda x: x[2])[0]    
     
# UNUSED - DID NOT WORK WELL ON REAL DATA
def approxPDFPolynomial(data, deg = 25):
  hist, bins = np.histogram(data, bins = 100, density = False)
  coeff = np.polyfit(bins[:-1], hist, deg)
  return coeff, bins[:-1], hist

def approxPDFRegression(data):
  hist, bins = np.histogram(data, bins = 100, density = False)
  kernel = RBF()
  model = KernelRidge(kernel = kernel)
  model.fit(bins[:-1].reshape(-1,1), hist)
  return model, bins[:-1], hist

if __name__ == "__main__":
  # Read graph
  G = graphStat()
  path = "DC.txt"
  title = "District of Columbia Roads"
  doER = False
  doBA = True
  G.graph = readGraph(path)
  
  
  # Compute degree statistics
  G.degree_sequence, G.degree_average, G.degree_variance = degreeStatiscs(G)
  if doER and not doBA:
    print("DoER, avgdeg = " + str(G.degree_average))
    G.graph = nx.erdos_renyi_graph(G.graph.number_of_nodes(), G.degree_average/(G.graph.number_of_nodes() - 1))
    print("ER, edge# = " + str(nx.number_of_edges(G.graph)))
    title += " ER"
    # Compute degree statistics
    G.degree_sequence, G.degree_average, G.degree_variance = degreeStatiscs(G)
    
  if doBA and not doER:
    print("DoBA, avgdeg = " + str(G.degree_average))
    G.graph = nx.barabasi_albert_graph(G.graph.number_of_nodes(), min(G.degree_sequence))
    title += " BA"
    # Compute degree statistics
    G.degree_sequence, G.degree_average, G.degree_variance = degreeStatiscs(G)
    
  # Compute distance based statistics
  if nx.is_connected(G.graph):
     G.eccentricity_sequence = list(nx.eccentricity(G.graph).values())
  else:
    for component in nx.connected_components(G.graph):
      G.eccentricity_sequence += list(nx.eccentricity(G.graph.subgraph(component)).values())
  G.diameter = max(G.eccentricity_sequence)
  G.radius = min((G.eccentricity_sequence))
  G.eccentricity_avg = np.mean(G.eccentricity_sequence) 
  # Compute component based statistics
  G.connected_components_sizes = [len(c) for c in nx.connected_components(G.graph)]
  G.largest_connected_component = max(G.connected_components_sizes)
  # Compute clustering based statistics
  G.clustering_coefficients = list(nx.clustering(G.graph).values())
  # Compute list of max(ssps)
  longestShortestPaths(G)
  
  
  # Formatted Ouptut
  with open(title + " Out.txt", 'w') as f:
    with redirect_stdout(f):
      print("Graph: " + title)
      print("Number of Nodes: " + str(G.graph.number_of_nodes()))
      print("Number of Edges: " + str(G.graph.number_of_edges()))
      print("Degree Average: " + str(G.degree_average))
      print("Degree Variance: " + str(G.degree_variance))
      print("Diameter: " + str(G.diameter))
      print("Radius: " + str(G.radius))
      print("Average Eccentricity: " + str(G.eccentricity_avg))
      print("Number of Connected Components: " + str(len(G.connected_components_sizes)))
      print("Largest Connected Component: " + str(G.largest_connected_component))
      print("Degree Distribution: " + str(G.degree_sequence))
      print("Longest Shortest Paths: " + str(G.longest_sp_sequence))
      print("Longest shortest Path Average: " + str(np.mean(G.longest_sp_sequence)))
      print("Longest Shortest Path Variance: " + str(np.var(G.longest_sp_sequence)))
      print("Clustering Coefficients: " + str(G.clustering_coefficients))
      print("Clustering Coefficient Average: " + str(np.mean(G.clustering_coefficients)))
      print("Clustering Coefficient Variance: " + str(np.var(G.clustering_coefficients)))
      print("Connected Component Sizes: " + str(G.connected_components_sizes))
      print("Connected Component Size Average: " + str(np.mean(G.connected_components_sizes)))
      print("Connected Component Size Variance: " + str(np.var(G.connected_components_sizes)))
  f.close()
  
  
  
  # Plotting Distributions
  # Degree Distribution
  plt.figure()
  plt.hist(G.degree_sequence, bins = 100)
  model, bins, hist = approxPDFRegression(G.degree_sequence)
  plt.plot(bins,10* model.predict(bins.reshape(-1,1)), label = "Best Fit")
  plt.title(title + " Degree Distribution")
  plt.xlabel("Degree")
  plt.ylabel("Frequency")
  #plt.yscale("log")
  plt.ylim(0,max(hist))
  plt.hist(G.degree_sequence, bins = 100)
  plt.savefig(title + " Degree Distribution.pdf")
  plt.legend()
  
  # SSSP Length Distribution
  plt.figure()
  plt.title(title + " SSSP Length Distribution")
  plt.xlabel("Length")
  plt.ylabel("Frequency")
  plt.hist(G.longest_sp_sequence, bins = 100)
  model, bins, hist = approxPDFRegression(G.longest_sp_sequence)
  plt.plot(bins, 9 * model.predict(bins.reshape(-1,1)), label = "Best Fit")
  plt.savefig(title + " SSSP Length Distribution.pdf")
  
  # Clustering Coefficient Distribution
  plt.figure()
  plt.title(title + " Clustering Coefficient Distribution")
  plt.xlabel("Clustering Coefficient")
  plt.ylabel("Frequency")
  #plt.yscale("log")
  plt.hist(G.clustering_coefficients, bins = 100)
  model, bins, hist = approxPDFRegression(G.clustering_coefficients)
  plt.plot(bins, model.predict(bins.reshape(-1,1)), label = "Best Fit")
  plt.ylim(0,max(hist))
  plt.savefig(title + " Clustering Coefficient Distribution.pdf")
  
  # Connected Component Size Distribution
  plt.figure()
  plt.title(title + " Connected Component Size Distribution")
  plt.xlabel("Size")
  plt.ylabel("Frequency")
  plt.hist(G.connected_components_sizes, bins = 100)
  model, bins, hist = approxPDFRegression(G.connected_components_sizes)
  plt.plot(bins, model.predict(bins.reshape(-1,1)), label = "Best Fit")
  plt.ylim(0,max(hist))
  plt.savefig(title + " Connected Component Size Distribution.pdf")
  