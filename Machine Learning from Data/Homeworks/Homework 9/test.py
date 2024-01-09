for i in range(9):
  for j in range(9):
    if i+j <= 8:
      print(str.format("w[{0}][{1}]", i, j))