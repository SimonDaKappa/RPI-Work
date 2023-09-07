imdb_file = input("Enter the name of the IMDB file ==> ").strip()
print(imdb_file)
counts = dict()
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')
    name = words[0].strip()
    if name in counts:
        counts[name] += 1
    else:
        counts[name] = 1
max_val = 0
m_v_old = 0
occurences = 0
n = ""
for name in counts:
    max_val = max(max_val,counts[name])
    if max_val > m_v_old:
        occurences = counts[name]
        n = name
        m_v_old = max_val
print(n,"appears most often:",max_val,"times")
temp = counts.copy()        
for name in counts:
    if temp[name] != 1:
        del temp[name]
print(len(temp),"people appear once")

