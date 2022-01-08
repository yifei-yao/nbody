# nbody
Experimental newtonian gravity N-body simulation program.
* Supports a number of integration methods, including the Fourth Order-Runge Kutta Method (RK4), classic Euler, Ralston's fourth-order, and a generalized explicit RK solver with any butcher tableau

* Step size is calculated automatically and dynamically based on time limit and machine performance

* Multithreading is used to display verbose info or progress bar and to save log data during simulation

* Live 3D plotting is supported via [matplotplusplus](https://github.com/alandefreitas/matplotplusplus).


## Prerequisites
* C++17
* CMake 3.14+
* [Gnuplot 5.2.6+](https://riptutorial.com/gnuplot/example/11275/installation-or-setup) (Required at runtime for plotting)
## Build
Go to the project directory

    mkdir nbody-build

    cd nbody-build

    cmake -DCMAKE_BUILD_TYPE=Release ..

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
Simulation is run on solar ephemeris data from 2020-01-01 to 2021-01-1 in 60 seconds on intel i9-9980HK at 2.4 GHz.

Ephemeris data from https://ssd.jpl.nasa.gov. Also in [demo](./demo.txt). Target Body: Earth. Coordinate Origin: Solar System Barycenter. Units: KM-S. Target Time: 2021-Jan-01 00:00:00.

| Method | X | Y | Z | VX | VY | VZ |
| ------ | - | - | - | -- | -- | -- |
| (Reference) NASA Data | -27790490.35695899 | 145531279.5923398 | 8814.216724157333 | -29.77742302555309 | -5.541990311673212 | -0.000085678656151 |
| RK4                   | -27790558.12835918 | 145531288.6611956 | 8814.204206533407 | -29.77742121645497 | -5.542001515416945 | -0.000085865983073 |
| Euler "Classic"       | -27787848.94354407 | 145532314.9671848 | 8828.834733711232 | -29.77716984099415 | -5.541887995794449 | -0.000121750412564 |
| Euler Improved        | -27789212.45618045 | 145531802.6617349 | 8821.539108266456 | -29.77728970033806 | -5.541947841719949 | -0.000104330593613 |
| Ralston4              | -27802582.05469499 | 145526620.2536048 | 8812.341440932937 | -29.77661562550536 | -5.545486526912181 | -0.000187350605708 |

Based on the test, the RK4 method seems to be most accurate and is the recommended method.

## To-dos

* Better 3D animation
* Support unit conversions

## References
https://en.wikipedia.org/wiki/Runge–Kutta_methods
