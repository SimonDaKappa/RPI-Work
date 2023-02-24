data = [0 53.05;5 73.04;10 98.31;15 139.78;20 193.47;25 260.20;30 320.39];
xc = gaussNewton( @r,@rx,[50; 0.1],1e-5,20)
xd = data(:,1);
yd = data(:,2);
x = linspace(0,30,201);
f = @(x) xc(1)*exp(xc(2)*(x));
y = f(x);
figure
plot(xd,yd,'r*',x,y,'b')
title('Automobile Supply Data')
xlabel('Year - 1950')
ylabel('Y')
legend('Data Points', 'Nonlinear LSF')

data2 = [1 8;2 12.3;3 15.5;4 16.8; 5 17.1; 6 15.8;7 15.2;8 14.0];
xc2 = gaussNewton(@r2,@rx2,[5;-.1],1e-5,20)
f2 = @(x) xc2(1)*x.*exp(xc2(2)*x);
x2 = linspace(1,16,201);
y2 = f2(x2);
xd2 = data2(:,1); yd2 = data2(:,2);
figure
plot(xd2,yd2,'r*',x2,y2,'b')
title('Drug Concentration in Blood')
xlabel('Hour')
ylabel('Concentration')
legend('Data Points', 'Nonlinear LSF')