import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import matplotlib
import random
import main
matplotlib.use('TkAgg')

points, addpoints = [], []
centres = [0]
max_rad = 0

root = tk.Tk()

text = tk.Text(root, width=40, height=2)
text.grid(row=11, column=1)


def update_text(centres, max_rad):
    text.delete(1.0, tk.END)
    text.insert(1.0, "R = " + str(max_rad) + "\n(" + str(centres[0][0]) + "; " + str(centres[0][1])+")")


def init():
    global points
    points = []


def update():
    plt.clf()
    global points, addpoints
    points.extend(addpoints)
    addpoints = []
    [centres, max_rad] = main.solve(points)
    if max_rad == 0:
        start()
        return
    update_text(centres, max_rad)
    fig.canvas.draw()


def quit():
    root.quit()
    root.destroy()


def addpoint(event):
    ax = fig.add_subplot(111)
    inv = ax.transData.inverted()
    print(inv.transform((event.x, event.y)))
    [x, y] = inv.transform((event.x, event.y))
    y *= -1
    addpoints.append([x, y])
    plt.plot(x, y, marker='o')
    fig.canvas.draw()


def addrandom():
    x = random.randint(-20, 20)
    y = random.randint(-20, 20)
    addpoints.append([x, y])
    plt.plot(x, y, marker='o')
    fig.canvas.draw()


def start():
    plt.clf()
    plt.xlim(-20, 20)
    plt.ylim(-20, 20)
    global points, addpoints
    addpoints = []
    init()
    fig.canvas.draw()


def undo():
    if len(addpoints)==0:
        print("no points")
        return
    [x, y] = addpoints.pop()
    plt.text(x, y, "undo")
    temp, = plt.plot(x, y, marker='o')
    temp.set_visible(False)
    temp.remove()
    fig.canvas.draw()


def fromfile():
    plt.clf()
    global points
    points = main.read_from_file("in1.txt")
    [centres, max_rad] = main.solve(points)
    update_text(centres, max_rad)
    fig.canvas.draw()


def genrand():
    plt.clf()
    global points
    points = main.gen_points(100)
    [centres, max_rad] = main.solve(points)
    update_text(centres, max_rad)
    fig.canvas.draw()


plt.xlim(-20, 20)
plt.ylim(-20, 20)
fig = plt.figure(1, figsize=(10,10), dpi=100)

canvas = FigureCanvasTkAgg(fig, master=root)
plot_widget = canvas.get_tk_widget()
fig.canvas.mpl_connect('button_press_event', addpoint)
init()

plot_widget.grid(row=0, column=1)
plot_widget.bind("<Button-1>", addpoint)

frame = tk.Frame(root)
frame.grid(row=0, column=0)
tk.Button(frame,text="Update",command=update).grid(row=5, column=1)
tk.Button(frame, text="Quit", command=quit).grid(row=7, column=1)
tk.Button(frame, text="Add random point", command=addrandom).grid(row=3, column=1)
tk.Button(frame, text="Start", command=start).grid(row=1, column=1)
tk.Button(frame, text="Undo", command=undo).grid(row=4, column=1)
tk.Button(frame, text="From file", command=fromfile).grid(row=9, column=1)
tk.Button(frame, text="Generate random", command=genrand).grid(row=10, column=1)

root.mainloop()