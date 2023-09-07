"""
Simon Gibson - Exam 2 Question 1
"""

def init_network(file,user): #creates a list of connections for a user id in a file
     file = open(file)
     f = file.read()
     connections = []
     for line in f:
         ids = line.split("|")
         id1 = ids[0].strip()
         id2 = ids[1].strip()
         if id1 == user:
             connections.append(id2)
         elif id2 == user:
             connections.append(id1)
     print(connections)
     return connections
 
def complete_network(file,n): # [[]] where each sublist is a an id, so genereate a list of lists with len(total ids) sublists in itnis number of id's
    network = list( init_network(file,x) for x in range(n)) 
    return network

def print_network(network):
    print("Complete Network")
    for i in range(len(network)):
        print("{} :".format(i),network[i])
  

def find_GCF_connection(network,user): #loop over over each user id that is not given userid, check each connection in that subnetowrk and see if subnetwork[userid] contains that connection, if so c++. <- Habit 
    c_const = 0  
    GCF = 0
    GCF_list = []
    temp_connections = []
    for j in range(len(network)):
        c = 0
        if j != user:
            for connection in network[j]:
                if connection in network[user]:
                    c+=1
                    temp_connections.append(connection)
        if c > c_const:
            GCF = j
            c_const = c
            GCF_list = temp_connections[:]
        temp_connections.clear()
    print("User whose connections match the most =>",GCF)
    print("Matching connections are:\n",GCF_list,sep='')
         
if __name__ == "__main__":
    file = "social_network.txt"
    userid = input("Enter the user Id =>")
    print(init_network(file,userid))
    network = complete_network(file,10)
    print_network(network)
    find_GCF_connection(network,userid)
    