@echo off
cd /d "%~dp0"

start "Orbital API" cmd /k ".venv\Scripts\python.exe -m uvicorn api:app --reload"
start "Orbital Frontend" cmd /k "cd frontend && npm.cmd run dev"