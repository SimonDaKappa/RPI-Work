[x1,x2] = meshgrid(-1: 0.05: 20);
constraint_1 = x1 >= 0;
constraint_2 = x2 >= 0;
constraint_3 = x1 + 2*x2 <= 20;
constraint_4 = 2*x1 + x2 <= 20;
Ax = double(constraint_1).*double(constraint_2).*double(constraint_3).*double(constraint_4);
feas_reg = surf(x1,x2,Ax);
set(feas_reg,'LineStyle','none')
view(0,90);

