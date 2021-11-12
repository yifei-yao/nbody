#include <getopt.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include "engine.h"

using namespace std;

void Usage();

void UsageHint();

bool ParseRun(const string &, Engine &, long double &, long double &);

bool TestSave(const string &);

int main(int argc, char **argv) {
    int plot = 0;
    int verbose = 0;
    static struct option long_opts[] = {
            {"run",     required_argument, nullptr, 'r'},
            {"help",    no_argument,       nullptr, 'h'},
            {"save",    required_argument, nullptr, 's'},
            {"method",  required_argument, nullptr, 'm'},
            {"plot",    no_argument,       nullptr, 'p'},
            {"log",     required_argument, nullptr, 'l'},
            {"verbose", no_argument,       nullptr, 'v'}
    };
    int ch;
    bool run_flag = false;
    bool save = false;
    string save_path;
    long double end_time = 0, time_limit = 0;
    string method;
    bool log;
    string log_path;
    Engine anEngine;
    while ((ch = getopt_long(argc, argv, "r:hs:m:pl:v", long_opts, nullptr)) !=
           -1) {
        switch (ch) {
            case 'h': {
                Usage();
                return 0;
            }
            case 'r': {
                run_flag = true;
                string arguments = optarg;
                if (!ParseRun(arguments, anEngine, end_time, time_limit)) {
                    UsageHint();
                    return 1;
                }
                break;
            }
            case 's': {
                save = true;
                if (!TestSave(optarg)) {
                    return 1;
                } else {
                    save_path = optarg;
                }
                break;
            }
            case 'm': {
                static set<string> methods = {
                        "euler", "euler_improved", "rk4", "ralston4"};
                if (methods.find(optarg) == methods.end()) {
                    cout << optarg << ": method not found.\n";
                    return 1;
                } else {
                    method = optarg;
                }
                break;
            }
            case 'l': {
                log = true;
                if (!TestSave(optarg)) {
                    return 1;
                } else {
                    log_path = optarg;
                }
                break;
            }
            case 'p': {
                plot = true;
                break;
            }
            case 'v': {
                verbose = true;
                break;
            }
            default:
                cout << "Command not found!\n";
                Usage();
                return 1;
        }
    }
    if (!run_flag) {
        cout << "Missing -r or --run command!\n";
        UsageHint();
    } else {
        anEngine.Run(end_time, time_limit, method, plot, log, log_path,
                     verbose);
        if (save) {
            if (!anEngine.Save(save_path)) {
                cout << save_path << ": Result save failed.\n";
            }
        }
    }
}

void Usage() {
    cout
            << "Usage:\nnbody { -h | -r \"filename1 end_time time_limit\" [-p] [-v] [-s filename2] [-l filename3] [-m method_name] }\n";
    cout << "Options:\n";
    cout << "-h, --help:\n\tShow usage message\n";
    cout << "-r, --run \"filename end_time time_limit\":\n";
    cout << "\tfilename: containing input data\n";
    cout << "\tend_time: the timestamp to terminate simulation\n";
    cout << "\ttime_limit: to finish the simulation in <time_limit> seconds\n";
    cout << "-p, --plot:\n\tLive plot the simulation\n";
    cout << "-v, --verbose:\n\tDisplay verbose data per second\n";
    cout << "-s, --save filename:\n\tSave simulation result to file\n";
    cout << "-l, --log filename:\n\tSave per second data to file\n";
    cout
            << "-m, --method method_name:\n\tSelect a method to run: rk4, euler, euler_improved, ralston4\n";
}

void UsageHint() {
    cout << "Type -h or --help for Usage.\n";
}

bool ParseRun(const string &arguments, Engine &anEngine, long double &end_time,
              long double &time_limit) {
    string path;
    long double until;
    long double in;
    stringstream ss;
    ss << arguments;
    if (ss >> path >> until >> in) {
        if (!anEngine.Load(path)) {
            return false;
        }
        if (until <= anEngine.GetTargetTime()) {
            cout << "End_time " << until << " is less than the curren time "
                 << anEngine.GetTargetTime() << " .\n";
            return false;
        } else {
            end_time = until;
        }
        if (in <= 0) {
            cout << "Time_limit must be positive.\n";
            return false;
        } else {
            time_limit = in;
        }
        return true;
    } else {
        cout << "Incorrect -r or --run usage!\n";
        return false;
    }
}

bool TestSave(const string &path) {
    fstream file;
    file.open(path, ios::out);
    if (!file) {
        cout << path << ": Cannot save to this file or directory.\n";
        return false;
    } else {
        file.close();
        return true;
    }
}