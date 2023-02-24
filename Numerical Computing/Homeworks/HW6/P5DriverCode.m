f = @(x) exp(sin(pi*x).^2);
fx = @(x) 2*pi*cos(pi*x).*sin(pi*x).*f(x);
fxx = @(x) 2*pi^2*f(x)* ((2*cos(pi*x).^2-1 )*sin(pi*x).^2 +cos(pi*x).^2);
a = -1;
b = 1;
n = 101;
for i = 1:n
 xs(i) = a + (b-a)*(i-1)/(n-1);
end
ys = f(xs);
x = linspace(-1.1,1.1,201);

coeff1 = splineCoeff(xs,ys,0,0,0,0);
[y1,yx1] = splineEval(xs,ys,coeff1,x);
figure
plot(xs,ys,'g*',x,y1)
title([ num2str(n) ' Nodes and Natural Spline'])
xlabel("x")
ylabel('y')

figure
plot(xs,fx(xs),'g*',x,yx1)
title([ num2str(n) ' Nodes and Natural Spline Derivatives'])
xlabel("x")
ylabel('y')

figure
plot(x,f(x)-y1,'b',x,(fx(x)-yx1)/10,'g')
title([ num2str(201) ' Evaluation Points and Natural Spline Erorr'])
legend('Error','Derivative Error')

coeff2 = splineCoeff(xs,ys,1,fx(a),1,fx(b));
[y2,yx2] = splineEval(xs,ys,coeff2,x);

figure
plot(xs,ys,'g*',x,y2)
title([ num2str(n) ' Nodes and Clamped Spline'])
xlabel("x")
ylabel('y')

figure
plot(xs,fx(xs),'g*',x,yx2)
title([ num2str(n) ' Nodes and Clamped Spline Derivatives'])
xlabel("x")
ylabel('y')

figure
plot(x,f(x)-y2,'b',x,(fx(x)-yx2)/10,'g')
title([ num2str(201) ' Evaluation Points and Clamped Spline Erorr'])
legend('Error','Derivative Error')

coeff3 = splineCoeff(xs,ys,2,fxx(a),2,fxx(b));
[y3,yx3] = splineEval(xs,ys,coeff3,x);

figure
plot(xs,ys,'g*',x,y3)
title([ num2str(n) ' Nodes and Curvature Spline'])
xlabel("x")
ylabel('y')

figure
plot(xs,fx(xs),'g*',x,yx3)
title([ num2str(n) ' Nodes and Curvature Spline Derivatives'])
xlabel("x")
ylabel('y')

figure
plot(x,f(x)-y3,'b',x,(fx(x)-yx3)/10,'g')
title([ num2str(201) ' Evaluation Points and CurvatureSpline Erorr'])
legend('Error','Derivative Error')


%x = linspace(-1.1,1.1,10)
%[y,yx] = splineEval(xs,ys,coeff,x)
%figure
%plot(x,y)