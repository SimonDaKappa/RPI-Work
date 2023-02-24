data = [0.59 3980;0.8 2200;0.95 1850;0.45 6100;0.79 2100;0.79 2100;0.90 2000;0.65 4200;0.65 4200; 0.79 2440;0.69 3300;0.79 2300;0.49 6000;1.09 1190;0.95 1960;0.79 2760;0.65 4330;0.45 6960;0.60 4160;0.89 1990;0.79 2860;0.99 1920;0.85 2160];
% (a)
t = data(1:length(data),1);
b = data(1:length(data),2);
A = ones(length(data),2);
A(:,2) = t;
Ata = A.'*A;
Atb = A.'*b;
xbar = Ata\Atb
S = @(x) xbar(1) + xbar(2)*x;
x = linspace(0,1,101);
y = S(x);
figure
plot(x,y,'b',t,b,'r*',.6791,3932.38,'g*')
xlabel('Price')
ylabel('Sales/Week')
title('Demand Curve')
legend('Demand','Data','Optimal Price')
RMSE = norm(b-A*xbar)/sqrt(length(b)) 
% (b)
figure
profit = @(x) S(x-0.23).*x;
negprofit = @(x) -profit(x);
bestprice = fminbnd(profit,0,1)
plot(x,profit(x),'b',.6791,3932.38,'g*')
xlabel('Price')
ylabel('Profit')
title("Profit Curve")
legend('Profit','Optimal Price')