I_h = eye(5);
I_h(end,end) = 0;
I_h
w = ones(4,1);
w
W_b = [w; 10];
W_b' * I_h * W_b
w'*w