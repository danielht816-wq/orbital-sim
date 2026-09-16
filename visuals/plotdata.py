import sys
import pandas as pd
import matplotlib.pyplot as plt

from matplotlib.animation import FuncAnimation
from matplotlib.widgets import Slider
from matplotlib.markers import MarkerStyle

if len(sys.argv) < 2:
    print("Usage: py plotdata.py <csv_file>")
    sys.exit()

csv_file = sys.argv[1]
df = pd.read_csv(csv_file)

bodies = df["body"].unique()
steps = sorted(df["step"].unique())

fig, ax = plt.subplots()
plt.subplots_adjust(bottom=0.25)

ax.set_title("Orbital Animation")
ax.set_xlabel("X Position")
ax.set_ylabel("Y Position")
ax.grid(True)
ax.axis("equal")

padding = 30
x_min = df["x"].min()
x_max = df["x"].max()
y_min = df["y"].min()
y_max = df["y"].max()
plot_range = max(x_max - x_min, y_max - y_min)
ax.set_xlim(x_min - padding, x_max + padding)
ax.set_ylim(y_min - padding, y_max + padding)

points = {}
trails = {}

for body in bodies:
    
    point, = ax.plot([], [], 'o', label=body)
    trail, = ax.plot([], [], '-', linewidth=1)
    points[body] = point
    trails[body] = trail

ax.legend()

def update(frame):
    current_step = steps[frame]

    for body in bodies:
        body_data = df[df["body"] == body]
        current_row = body_data[body_data["step"] == current_step]

        if not current_row.empty:
            x = current_row["x"].values[0]
            y = current_row["y"].values[0]
            points[body].set_data([x], [y])

        trail_data = body_data[body_data["step"] <= current_step]
        trails[body].set_data(trail_data["x"], trail_data["y"])

    return list(points.values()) + list(trails.values())

ani = FuncAnimation(
    fig,
    update,
    frames=len(steps),
    interval=30,
    blit=True,
    repeat=False
)

# speed slider
slider_ax = plt.axes([0.2, 0.08, 0.6, 0.03])
speed_slider = Slider(
    ax=slider_ax,
    label="Animation Delay",
    valmin=1,
    valmax=200,
    valinit=30
)

def update_speed(value):
    ani.event_source.interval = value

speed_slider.on_changed(update_speed)

plt.show()