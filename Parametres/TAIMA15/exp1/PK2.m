%EM initialization
%Expectation of initial state
filter::t_0 = 
[0	0	0]

%Initial state covariance matrix
filter::Q_0 = 
[1	0	0
0	1	0
0	0	1]

%Transition matrix
filter::F =
[0.5	0.1	0.1
0.1	0.4	0.2
0.1	0.2	0.5]

%Noise covariance matrix
filter::Q =
[1	0	0
0	1	0
0	0	1]

filter::size_x = 1
filter::size_y = 2

%Constant part of F
EM::F_0 =
[0.5	0.1	0.1
0.1	0.4	0.2
0.1	0.2	0.5]

%Constant part of Q
EM::Q_0 =
[1	0	0
0	1	0
0	0	1]

%Number of EM iterations
%Default : 0 (filtering and smoothing only!)
nb_iter_EM = 300

%Equivalence constraint
% 0 -> nothing
% 1 -> Deccorelation and known process noise covariance 
% 2 -> Known state equations
% 3 -> Known observation equations
EM::equivalence_type = 0

%Constraining F
%Block ids of the rows.
%Default: PKF estimation
F::block::sets =
[1	1	1]

F::block(1)::hypothesis = "known_block"
F::block(1)::P = "I"
F::block(2)::hypothesis = "known_block"
F::block(2)::P = "I"


%Constraining Q
%Block ids of the rows.
%Default: F::block::sets
Q::block::sets = [1	2	2]
Q::block(1)::hypothesis = "free_block"
Q::block(2)::hypothesis = "t2_block"
Q::block(2)::P = "I"
Q::block(2)::t2_block::nb_lambda = 1
Q::block(2)::t2_block::M(1) = 
[1	0.25
0.25	1]

EM:first_state_estimation = 0
