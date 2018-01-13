%EM initialization
%Expectation of initial state
filter::t_0 = 
[0	0	0	0	0	0];

%Initial state covariance matrix
filter::Q_0 = 
[50	0	0	0	0	0
0	50	0	0	0	0
0	0	50	0	0	0
0	0	0	50	0	0
0	0	0	0	1	0
0	0	0	0	0	1];

%Transition matrix
filter::F =
[1	0	1	0	0	0
0	1	0	1	0	0
0	0	0	0	0	0
0	0	0	0	0	0
1	0	0	0	0	0
0	1	0	0	0	0];

%Noise covariance matrix
filter::Q =
[5	0	0	0	0	0
0	5	0	0	0	0
0	0	5	0	0	0
0	0	0	5	0	0
0	0	0	0	1	0
0	0	0	0	0	1];

%Dimension of x
filter::size_x = 4;

%Constant part of F
EM::F_0 =
[1	0	1	0	0	0
0	1	0	1	0	0
0	0	0	0	0	0
0	0	0	0	0	0
1	0	0	0	0	0
0	1	0	0	0	0];

%Constant part of Q
EM::Q_0 =
[5	0	0	0	0	0
0	5	0	0	0	0
0	0	5	0	0	0
0	0	0	5	0	0
0	0	0	0	1	0
0	0	0	0	0	1];
%Number of EM iterations
%Default : 0 (filtering and smoothing only!)
nb_iter_EM = 1000;

%Equivalence constraint
% 0 -> nothing
% 1 -> Deccorelation and known process noise covariance 
% 2 -> Known state equations
% 3 -> Known observation equations
EM::equivalence_type = 0;

EM:first_state_estimation = 1;


%Constraining F
%Block ids of the rows.
%Default: PKF estimation
F::block::sets =
[1	1	1	1	1	1];

%Block hypothesis
% "known_block" or 0 : known block
% "free_block" or 3 : free block (t1_block where M = I )
% "t1_block" or 1 : F = G M 
% "t2_block" or 2 : F = \sum_{i=1}^{n_{\lambda}} \lambda_i M_i
%Block transformation matrix
% - "I" or "Identity" for Identity
% - matrix if not
% I by default
F::block(1)::hypothesis = "known_block";
F::block(1)::P = "I";
F::block(1)::t1_block::M = "Kalman";

%Block hypothesis
% "known_block" or 0 : known block
% "free_block" or 3 : free block (t1_block where M = I )
% "t1_block" or 1 : F = G M 
% "t2_block" or 2 : F = \sum_{i=1}^{n_{\lambda}} \lambda_i M_i
%Block transformation matrix
% - "I" or "Identity" for Identity
% - matrix if not
% I by default
F::block(2)::hypothesis = "t1_block";
F::block(2)::P = "I";
F::block(2)::t1_block::M = 
[0	0	1	0	0	0
0	0	0	1	0	0
1	0	0	0	0	0
0	1	0	0	0	0]

%Block hypothesis
% "known_block" or 0 : known block
% "free_block" or 3 : free block (t1_block where M = I )
% "t1_block" or 1 : F = G M 
% "t2_block" or 2 : F = \sum_{i=1}^{n_{\lambda}} \lambda_i M_i
%Block transformation matrix
% - "I" or "Identity" for Identity
% - matrix if not
% I by default
F::block(3)::hypothesis = "known_block";
F::block(3)::P = "I";
F::block(3)::t1_block::M = "Kalman";


%Constraining Q
%Block ids of the rows.
%Default: F::block::sets
Q::block::sets = [2	2	2	2	3	3];
Q::block(1)::hypothesis = "free_block";
Q::block(2)::hypothesis = "free_block";
Q::block(3)::hypothesis = "free_block";
EM:first_state_estimation = 0;

