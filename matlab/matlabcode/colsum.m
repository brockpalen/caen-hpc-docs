%example parallel job from MATLAB manual
function total_sum = colsum
if labindex == 1 
  % Send magic square to other labs 
  A = labBroadcast(1,magic(numlabs)) 
else 
  % Receive broadcast on other labs 
  A = labBroadcast(1) 
end 

% Calculate sum of column identified by labindex for this lab 
column_sum = sum(A(:,labindex)) 
% Calculate total sum by combining column sum from all labs 
total_sum = gplus(column_sum)
