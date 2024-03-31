A = load("Pv_M_I+R_U_N_31d_3.mat").A;
B=[];
for i=1:length(A)
  for j = 1:length(A)
    if A(i,j) ~= 0
      B = [B; i,j];
    end
  end
end
csvwrite("FungalGraph.csv", B);