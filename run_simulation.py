from pathlib import Path
import subprocess
import csv

#reads csv data for c++ file to write
def read_positions(csv_path):
    with csv_path.open(newline="") as file:
        reader = csv.DictReader(file)
        positions = []

        for row in reader:
            position = {
                "step": int(row["step"]),
                "body": row["body"],
                "x": float(row["x"]),
                "y": float(row["y"]),
            }
            positions.append(position)

    return positions



project_dir = Path(__file__).resolve().parent
executable = project_dir / "x64" / "Debug" / "solar system.exe"
output_path = project_dir / "output" / "python_results.csv"

#function to run the solution
def run_sim(steps=25, output_file=output_path, bodies_file="scenarios/earthsunmoon.txt", settings_file="settings/earthsunmoon_settings.txt"):
    subprocess.run(
        [
            str(executable),
            str(bodies_file),
            str(settings_file),
            str(output_file),
            str(steps),
        ],
        cwd=project_dir,
        check=True,
    )



if __name__ == "__main__":
    run_sim(
    steps=10,
    output_file=project_dir / "output" / "test_results.csv",
    bodies_file="scenarios/binarystar.txt",
    settings_file="settings/binarystar_settings.txt",
    )
    positions = read_positions(project_dir / "output" / "test_results.csv")
    print("Recorded positions:", len(positions))
    print("First position:", positions[0])