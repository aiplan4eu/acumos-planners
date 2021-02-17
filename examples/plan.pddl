Number of literals: 13
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%] [120%] [130%] [140%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%] [120%] [130%] [140%]
Have identified that bigger values of (charge kenny) are preferable
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
96% of the ground temporal actions in this problem are compression-safe
Initial heuristic = 9.000
b (8.000 | 70.001)b (7.000 | 130.002)b (5.000 | 160.003)b (4.000 | 350.006)b (3.000 | 380.007)
Resorting to best-first search
b (8.000 | 70.001)b (7.000 | 130.002)b (6.000 | 190.003)b (5.000 | 250.004)b (4.000 | 310.005)b (3.000 | 370.006)b (2.000 | 400.007);;;; Solution Found
; States evaluated: 98
; Cost: 400.007
; Time 0.02
0.000: (undock kenny wp0)  [10.000]
10.001: (localise kenny)  [60.000]
70.002: (goto_waypoint kenny wp0 wp1)  [60.000]
130.003: (goto_waypoint kenny wp1 wp2)  [60.000]
190.004: (goto_waypoint kenny wp2 wp3)  [60.000]
250.005: (goto_waypoint kenny wp3 wp4)  [60.000]
310.006: (goto_waypoint kenny wp4 wp0)  [60.000]
370.007: (dock kenny wp0)  [30.000]
