% Homework 2 Driver Code
g = @(x) ((1-x)/3)^(1/3)
root = fixedPoint(g,0.6,1e-5,20);
g = @(x) 1-3*x^3
root = fixedPoint(g,0.6,1e-5,20);
g = @(x) (1+6*x^3)/(1+9*x^2)
root = fixedPoint(g,0.6,1e-5,20);
