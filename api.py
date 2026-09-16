import subprocess
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, Field
from run_simulation import read_positions, output_path, run_sim
from pathlib import Path
from tempfile import TemporaryDirectory
from scenarios import PRESETS
from fastapi.middleware.cors import CORSMiddleware

#expected data from request
class SimulationRequest(BaseModel):
    steps: int = Field(default=25, ge=1, le=10000)
    scenario: str = "earthsunmoon"

app = FastAPI()
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5173"],
    allow_methods=["GET", "POST"],
    allow_headers=["Content-Type"],
)

@app.get("/health")
def health():
    return {"status": "ok"}

@app.get("/positions")
def get_positions():

    positions = read_positions(output_path)

    return {
        "count": len(positions),
        "positions": positions,
    }

@app.post("/simulation")
def simulate(request: SimulationRequest):

    if request.scenario not in PRESETS:
        raise HTTPException(
            status_code=422,
            detail="Unknown scenario.",
        )

    preset = PRESETS[request.scenario]

    with TemporaryDirectory() as temp_dir:
        result_path = Path(temp_dir) / "results.csv"

        try:
            run_sim(
                steps=request.steps,
                output_file=result_path,
                bodies_file=preset["bodies_file"],
                settings_file=preset["settings_file"],
            )
        except subprocess.CalledProcessError:
            raise HTTPException(
                status_code=500,
                detail="The simulation failed to complete.",
            )

        positions = read_positions(result_path)

    return {
        "count": len(positions),
        "positions": positions,
    }

@app.get("/scenarios")
def get_scenarios():
    scenarios = []

    for scenario_id, preset in PRESETS.items():
        scenarios.append({
            "id": scenario_id,
            "name": preset["name"],
        })

    return {"scenarios": scenarios}