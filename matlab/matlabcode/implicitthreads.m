%fills random large matrix and vector solves for unknown

%used to demonstate built in matlab threading
% solved Ax=b
function implicitthreads(dim)

if ischar(dim)
   dim=str2num(dim)
end

A=rand(dim);
b=rand(dim,1);
x=zeros(dim,1);

tic
x=A\b;
toc
