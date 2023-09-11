import random
import matplotlib
matplotlib.use('Agg', force=True)
import matplotlib.pyplot as plt


def flipCoin(coin, flips = 1):
  for _ in range(0, flips):
    val = random.randint(0,1)
    coin["h"] += 1 if val == 1 else 0
    coin["t"] += 1 if val == 0 else 0
  return coin

def selectCoins(CoinList):
  c_1 = CoinList[0]
  c_rand = CoinList[random.randint(1, len(CoinList)-1)]
  CoinList = sorted(CoinList, key = lambda x: x["h"], reverse = True)
  c_max = CoinList[0]
  return (c_1, c_rand, c_max)
  

if __name__ == "__main__":
  # Create array of coin objects
  c_1List = list()
  c_randList = list()
  c_maxList = list()
  
  iterations = 1000
  for _ in range(0, iterations):
    
    CoinList = list()
    CoinCount = 1000
    FlipCount = 10
    fFlipCount = float(FlipCount)
    for i in range(0, CoinCount):
      # Create coin object (head = 1, tail = 0)
      tmpcoin = {"h" : 0, "t" : 0, "id" : i}
      CoinList.append(tmpcoin)
      # Flip coin object
      CoinList[i] = flipCoin(CoinList[i], FlipCount)
    Selected_Coins = selectCoins(CoinList)
    #print(Selected_Coins)
    c_1List.append(Selected_Coins[0]["h"] / fFlipCount)
    c_randList.append(Selected_Coins[1]["h"] / fFlipCount)
    c_maxList.append(Selected_Coins[2]["h"] / fFlipCount)
    #Selected_Frequencies = [Selected_Coins[0]["h"] / fFlipCount, Selected_Coins[1]["h"] / fFlipCount, Selected_Coins[2]["h"] / fFlipCount]
    #print(Selected_Frequencies)
  #print("c_1List: ", c_1List)
  #print("c_randList: ", c_randList)
  #print("c_maxList: ", c_maxList)
  
  # Set Up the subplots
  fig, (ax0, ax1, ax2) = plt.subplots(1, 3, sharey=True)
  fig.suptitle("Coin Frequencies nu")
  # Histogram Plot of c_1
  ax0.set_title('Coin 1')
  ax0.hist(c_1List)
  # Histogram Plot of c_rand
  ax1.set_title("Random Coin")
  ax1.hist(c_randList)
  # Histogram Plot of c_max
  ax2.set_title("Max Coin")
  ax2.hist(c_maxList)
  
  plt.show()
  plt.savefig(str.format("Hw2_{}coins_{}flips_{}Iterations.pdf", CoinCount, FlipCount, iterations))