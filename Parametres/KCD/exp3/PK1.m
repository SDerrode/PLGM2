%EM initialization
%Expectation of initial state
filter::t_0 = 
[0	0]

%Initial state covariance matrix
filter::Q_0 = 
[1	0
0	1]

%Transition matrix
filter::F =
[1	0
1	0]

%Noise covariance matrix
filter::Q =
[1	0
0	1]

%Dimension of x
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
nb_iter_EM = 100

%Equivalence constraint
% 0 -> nothing
% 1 -> Deccorelation and known process noise covariance 
% 2 -> Known state equations
% 3 -> Known observation equations
EM::equivalence_type = 3




EM:first_state_estimation = 1
