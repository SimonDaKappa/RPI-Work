
imdb_file = input("Enter the name of the IMDB file ==> ").strip()
prefix = input("Prefix: ")
print(prefix)
last_name_count = set([])
names_want = set([])
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')
    name = words[0].strip()
    last_name = name.split(",")[0]
    if last_name != "":
        last_name_count.add(last_name)
        if prefix in last_name:
            names_want.add(last_name)
print(len(last_name_count),"last names")
print(len(names_want),"start with",prefix)
    