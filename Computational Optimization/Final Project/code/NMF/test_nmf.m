load mnistData;

opts.tol = 1e-6;
opts.maxit = 1000;
opts.maxT = 1e4;
r = 12; % r can be tuned


%% run your code
t0 = tic;
[X,Y,out_s] = nmf_func(M,r,opts);
time_s = toc(t0);

fprintf('time = %f, obj = %f\n', time_s, out_s.hist_obj(end));

[~,cols] = max(Y,[],1);
groups = cell(r,1);

for i = 1:r
    groups{i} = find(cols == i);
end

for i = 1:r
    fig = figure('papersize',[10,1],'paperposition',[0,0,10,1]);
    for j = 1:10
        subplot(1,10,j);
        im_ij = reshape(M(:,groups{i}(j)),28,28);
        imshow(im_ij,[]);
    end
    print(fig,'-dpdf',['group',num2str(i)]);
end
