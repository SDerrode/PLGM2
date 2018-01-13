filter::t_0 = 
[0	0	0]

filter::Q_0 = 
[1	0	0
0	1	0
0	0	1]

%X(t) = X(t-1) + dt dX/dt(t-1) + b(t)
filter::F =
[0.5	0.1	0.1
0.1	0.4	0.2
0.1	0.2	0.5]

filter::Q =
[0.5	0	0
0	2	0.
0	0.	2]

filter::size_x = 1
