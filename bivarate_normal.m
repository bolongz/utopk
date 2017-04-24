function [ R ] = myFunc(A)  
% for c++ to get the return value, myFunc must have a return value   

%write A into a file.  
%dlmwrite('/home/tao/workspace/test_matlab/A_in_Matlab.txt', A,' '); 
num = A(1,1);
Mu = A(2,:);
Cov = [A(3,:);A(4,:)];

rng default  % For reproducibility
R = mvnrnd(Mu,Cov,num);
%dlmwrite('/home/tao/workspace/test_matlab/R_in_Matlab.txt', R,' ');
end  