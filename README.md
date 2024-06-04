# edge-edge-distance
Compute the distance between two edges (line segments) in a 3D space robustly. 


## Known Issues

This implementation can have larger errors for intersecting edges. 


## Usage

The core function is `ee_closest_point(x0, x1, x2, x3, t0, t1, parallel_sin_sq_tol)` in `lib/Distance.h`. It takes two edges $(x_0, x_1), (x_2, x_3)$ as input, and returns the ``type`` of the closest points on the two edges. It also writes into `t0` and `t1`, so that the closest points can be computed as `x0 + t0 * (x1 - x0)` and `x2 + t1 * (x3 - x2)`.

We also provide an example executable to read the user input and compute the distance (see "Example"), and some utility scripts to test the function (see "Test"). 


## Build

```bash
mkdir build
cd build
cmake ..
make
```


## Example

```bash
./example/example
```

Sample input:

```
(1.648724e-01 5.538958e-01 9.169785e-01) (4.051462e-01 1.222591e-01 8.325946e-01) (1.026980e-01 1.108083e-01 4.213850e-01) (2.735318e-01 -1.960839e-01 3.613884e-01)
```

Sample Output:
```
type: 5
t0: 1
t1: 0.184954
h0: (4.051462e-01 1.222591e-01 8.325946e-01)
h1: (1.342945e-01 5.404726e-02 4.102884e-01)
dist: 0.506316
```


## Test

Use `tests/testgen` to generate test cases in 3 different categories: `random`, `parallel`, and `coplanar`. 

```bash
./tests/testgen 
```

Use `tests/testscript` to run the test cases in a `.txt` file. 

```bash
./tests/testscript testdata_random.txt
./tests/testscript testdata_parallel.txt
./tests/testscript testdata_coplanar.txt
```

You can also use `tests/testscript` to test your own test cases. 

