A1 = [1 1 0; 1 1/2 sqrt(3)/2;1 -1/2 sqrt(3)/2; 1 -1 0;1 -1/2 -sqrt(3)/2; 1 1/2 -sqrt(3)/2];
b1 = [4;2;0;-5;-1;3];
ATA1 = A1.'*A1;
ATb1 = A1.'*b1;
xbar1 = inv(ATA1)*ATb1

RMSE1 = norm(b1-A1*xbar1)/sqrt(length(b1))

x = linspace(0,1,101);
F3 = @(x) xbar1(1) + xbar1(2)*cos(2*pi*x)+xbar1(3)*sin(2*pi*x);
y = F3(x);
figure
plot(x,y,'b',[0;1/6;1/3;1/2;2/3;5/6],b1,'r*')
title('F3')

A2 = [1 1 0 1; 1 1/2 sqrt(3)/2 -1/2;1 -1/2 sqrt(3)/2 -1/2; 1 -1 0 1;1 -1/2 -sqrt(3)/2 -1/2; 1 1/2 -sqrt(3)/2 -1/2];
b2 = b1;
ATA2 = A2.'*A2;
ATb2 = A2.'*b2;
xbar2 = inv(ATA2)*ATb2

RMSE2 = norm(b2-A2*xbar2)/sqrt(length(b2))
F4 = @(x) xbar2(1) + xbar2(2)*cos(2*pi*x)+xbar2(3)*sin(2*pi*x) + xbar2(4)*cos(4*pi*x);
y2 = F4(x);
figure
plot(x,y2,'b',[0;1/6;1/3;1/2;2/3;5/6],b2,'r*')
title('F4')
