function [ c ] = plot_poly(A)  
% for c++ to get the return value, myFunc must have a return value    
B = A';
X = [1, 10, 100, 1000];

fig = figure;

if B(1,15) == 0
    title_temp = sprintf('U-Topk Comparation %d tuples Dataset', B(1, 14));
else
    title_temp = sprintf('U-kRanks Comparation %d tuples Dataset', B(1, 14));
end
title(title_temp);
if B(1,11) == 0
    Y1 = [B(1,1), B(1,3), B(1,5), B(1,7)];
    Y2 = [B(2,1), B(2,3), B(2,5), B(2,7)];
    Y3 = [B(3,1), B(3,3), B(3,5), B(3,7)];
    Y4 = [B(4,1), B(4,3), B(4,5), B(4,7)];
    Y5 = [B(5,1), B(5,3), B(5,5), B(5,7)];
else
    Y1 = [B(1,2), B(1,4), B(1,6), B(1,8)];
    Y2 = [B(2,2), B(2,4), B(2,6), B(2,8)];
    Y3 = [B(3,2), B(3,4), B(3,6), B(3,8)];
    Y4 = [B(4,2), B(4,4), B(4,6), B(4,8)];
    Y5 = [B(5,2), B(5,4), B(5,6), B(5,8)];
end
loglog(X, Y1, '-d', X, Y2, '-o', X, Y3, '-s', X, Y4, '-x', X, Y5, '-+');
xlabel('k');
if B(1,11) == 0
    ylabel('Time');
else
    ylabel('Depth');
end
le1 = sprintf('un(mean = %f)',B(1,13));
le2 = sprintf('un(mean = %f)',B(2,13));
le3 = sprintf('uexp(mean = %f)',B(3,13));
le4 = sprintf('uexp(mean = %f)',B(4,13));
le5 = sprintf('uu');
legend(le1,le2,le3,le4,le5,'Location','northwest')

print(fig,'Poly_temp','-djpeg');
c = A;
  
end  