import argparse
import matplotlib.pyplot as plt


def get_path():
    parser = argparse.ArgumentParser()
    parser.add_argument("path", help="file path to plot data from", type=str)
    return parser.parse_args().path


def get_data(path):
    with open(path, 'r') as f:
        lines = f.readlines()
        f.close()
    first_line_words = lines[0].split()
    sys_name = first_line_words[0]
    sys_time = float(first_line_words[1])
    positions = [[], [], []]
    for line in lines[1:]:
        words = line.split()
        positions[0].append(float(words[2]))
        positions[1].append(float(words[3]))
        positions[2].append(float(words[4]))
    return sys_name, sys_time, positions


if __name__ == '__main__':
    name, time, data = get_data(get_path())
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title(f"{name} , t = {time:.6e}")
    ax.scatter(data[0], data[1], data[2])
    plt.show()