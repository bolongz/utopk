function [ c ] = plot_mono(A)  
% for c++ to get the return value, myFunc must have a return value    
B = A';
X = [B(3,1), B(4,1), B(5,1), B(6,1)];
Y = [B(3,2), B(4,2), B(5,2), B(6,2)];

fig = figure;
le = loglog(X, Y, '-d');
if B(2,2) == 0
    title('U-Topk Graph of Single Dataset');
else
    title('U-kRanks Graph of Single Dataset');
end
xlabel('k');
if B(1,1) == 0
    ylabel('Time');
else
    ylabel('Depth');
end
print(fig,'Mono_temp','-djpeg');
c = A;
  
end  