filter::t_0 = 
[1	0]

filter::Q_0 = 
[0.5	0
0	0]

%X(t) = X(t-1) + dt dX/dt(t-1) + b(t)
filter::F =
[0.8	0
1	0]

filter::Q =
[0.5	0
0	1.5]
filter::size_x = 1

%Constant part of F
EM::F_0 =
[1	0
1	0]
%Constant part of Q
EM::Q_0 =
[1	0
0	1]

%Number of EM iterations
%Default : 0 (filtering and smoothing only!)
nb_iter_EM = 0

%Equivalence constraint
% 0 -> nothing
% 1 -> Deccorelation and known process noise covariance 
% 2 -> Known state equations
% 3 -> Known observation equations
EM::equivalence_type = 0
