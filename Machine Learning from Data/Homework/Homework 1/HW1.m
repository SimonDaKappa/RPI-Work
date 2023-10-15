w = [rand(1);rand(1);rand(1)]
n = 1000;
datax = -10 + (20)*rand(n,3)
datay = zeros(n,1);
yp = zeros(1,3)
ym = zeros(1,3)
for i = 1:n
    datax(i,1) = 1;
    datay(i) = sign(w.' * datax(i,:).');
    if(datay(i) == 1)
        yp = [yp; datax(i,:)];
    else
        ym = [ym; datax(i,:)];
    end
end

yp = yp(2:end,:)
ym = ym(2:end,:)
linex = linspace(-10,10,100);
linef = -w(2)/w(3)*linex + -w(1)/w(3);
plot(linex,linef)

xlim([-10 10])
ylim([-10 10])
xlabel("x1")
ylabel("x2")
hold on
scatter(yp(:,2), yp(:,3), "+")
scatter(ym(:,2), ym(:,3), "_")



g = [rand(1);rand(1);rand(1)]
for i = 1:10*n
    m_found = 0;
    for j = 1:n
        %fprintf("y(i) = %d, sign(g.' * datax(j,:).' = %d\n", datay(j), sign(g.' * datax(j,:).'))
        if datay(j) ~= sign(g.' * datax(j,:).')
            %disp("Misclassified found!\n")
            m_found = 1;
            g = g + datay(j)*datax(j,:).';
            %fprintf("Post update: y(i) = %d, sign(g.' * datax(j,:).' = %d\n", datay(j), sign(g.' * datax(j,:).'))
            break
        end
    end
    if m_found == 0
        disp('Cound not find misclassified data point!\n')
        i
        break
    end
end

lineg = -g(2)/g(3)*linex + -g(1)/g(3);
plot(linex, lineg)
legend("F","Positive Data","Negative Data","G")
hold off