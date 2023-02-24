function [splineX,splineY] = P4Spline(n)
theta = linspace(0,2*pi,n+1);
X = 2*cos(theta);
Y = 1*sin(theta);

%figure()
%plot(X,Y)
%title([num2str(n) ' Points - X,Y pair values'])
%xlabel('X')
%ylabel('Y')
%axis equal

splineX = spline(theta,X);
coeffX = splineX.coefs

splineY = spline(theta,Y);
coeffY = splineY.coefs


thetaplot = linspace(0,2*pi,101);
XS = ppval(splineX, thetaplot);
XY = ppval(splineY, thetaplot);
figure()
thetaT = linspace(0,2*pi,201);
xT = 2*cos(thetaT);
yT = 1*sin(thetaT);
plot(XS,XY,'g',X,Y,'r*', xT,yT, 'b--')
legend('Interpolated Values','Data Point', 'True Values')
title([num2str(n) ' Points - Spline Interpolation 101 Points'])
xlabel('X')
ylabel('Y')
axis equal

end