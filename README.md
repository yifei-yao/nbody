# nbody
Experimental newtonian gravity N-body simulation program.
* Supports a number of intergreation methods, including the Fourth Order-Runge Kutta Method (RK4), classic Euler, Ralston's fourth-order, and a generalized explicit RK solver with any butcher tableau

* Step size is calculated automatically and dynamically based on time limit and machine performance

* Multithreading is used to display verbose info or progress bar and to save log data during simulation

* Live 3D plotting is supported via [matplotplusplus](https://github.com/alandefreitas/matplotplusplus).


## Prerequisites
* C++17
* CMake 3.14+
* Matplot++ (Embed in CMakeLists with automatic download)
* [Gnuplot 5.2.6+](https://riptutorial.com/gnuplot/example/11275/installation-or-setup) (Required at runtime)
## Build
Go to the project directory

    mkdir nbody-build

    cd nbody-build

    cmake ..

    make

## Usage

    nbody { -h | -r "filename1 end_time time_limit" [-p] [-v] [-s filename2] [-l filename3] [-m method_name] }
Options:

    -h, --help:
        Show usage message
        
    -r, --run "filename end_time time_limit":
        filename: containing input data in format specified below
        end_time: the timestamp to terminate simulation, must be greater than the staring time from the input file
        time_limit: to finish the simulation in <time_limit> seconds
        
    -p, --plot:
        Live plot the simulation
        
    -v, --verbose:
        Display verbose data per second
        
    -s, --save filename:
        Save simulation result to file
        
    -l, --log filename:
        Save per second data to file
        
    -m, --method method_name:
        Select a method to run: rk4, euler, euler_improved, ralston4

Example:

    ./nbody -r "../demo.txt 31622400 20" -p -v

## File format (see [demo](./demo.txt))

    system_name  system_time

    body1_name  gravitational_parameter(GM)  x_position  y_position  z_position  x_velocity  y_velocity  z_velocity

    body2_name  gravitational_parameter(GM)  x_position  y_position  z_position  x_velocity  y_velocity  z_velocity

    body3_name  gravitational_parameter(GM)  x_position  y_position  z_position  x_velocity  y_velocity  z_velocity
    
    ...

## 1 Minute Ephemeris Test
Simulation is run on solar ephemeris data from 2020-01-01 to 2021-01-1 in 60 seconds on intel i9-9980HK processor.

Ephemeris data from https://ssd.jpl.nasa.gov. Also in [demo](./demo.txt). Target Body: Earth. Coordinatese Origin: Solar System Barycenter. Units: KM-S. Time: 2021-Jan-01 00:00:00.

| Method | X | Y | Z | VX | VY | VZ |
| ------ | - | - | - | -- | -- | -- |
| (Reference) NASA Data | -27790490.35695899 | 145531279.5923398 | 8814.216724157333 | -29.77742302555309 | -5.541990311673212 | -0.000085678656151 |
| RK4                          | -27790873.64566389 | 145531204.9783596 | 8814.186222578265 | -29.77740827953653 | -5.542068690011103 | -0.000085841785718 |
| Euler "Classic"              | -27784007.23367431 | 145533811.2019798 | 8851.133386938507 | -29.77685077368753 | -5.541754477495280 | -0.000169792923043 |
| Euler Improved               | -27787189.57566320 | 145532564.1920737 | 8832.729469206849 | -29.77710945764749 | -5.541868574965185 | -0.000130693943158 |
| Ralston4                     | -27857364.17170360 | 145505715.2585099 | 8846.985279501034 | -29.77423945488506 | -5.562197916939682 | -0.000548913841268 |

Based on the test, the RK4 method seems to be most accurate and is the recommanded method.

## To-dos

* Better 3D animations
* Support unit conversions

## References
https://en.wikipedia.org/wiki/Runge–Kutta_methods
