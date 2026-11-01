import { useEffect, useState } from 'react'


type Scenario = {
    id: string
    name: string
}

type Position = {
    step: number
    body: string
    x: number
    y: number
}

function App() {

    const [submittedSteps, setSubmittedSteps] = useState<number | null>(null)
    const [steps, setSteps] = useState(100)
    const [status, setStatus] = useState('')
    const [isRunning, setIsRunning] = useState(false)
    const [scenarios, setScenarios] = useState<Scenario[]>([])
    const [selectedScenario, setSelectedScenario] = useState('')
    const [positions, setPositions] = useState<Position[]>([])
    const [currentStep, setCurrentStep] = useState(1)
    const [isPlaying, setIsPlaying] = useState(false)
    const [playbackDelay, setPlaybackDelay] = useState(100)

    async function handleRun() {
        setSubmittedSteps(steps)
        setIsRunning(true)
        setIsPlaying(false)
        setStatus('Running simulation...')

        try {
            const response = await fetch('http://127.0.0.1:8000/simulation', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    steps: steps,
                    scenario: selectedScenario,
                }),
            })

            if (!response.ok) {
                throw new Error(`Request failed: ${response.status}`)
            }

            const data = await response.json()
            setPositions(data.positions)
            setCurrentStep(1)
            setStatus(`Received ${data.count} position records.`)
        } catch (error) {
            setStatus(error instanceof Error ? error.message : 'Request failed.')
        } finally {
            setIsRunning(false)
        }
    }

    useEffect(() => {
        const controller = new AbortController()

        async function loadScenarios() {
            try {
                const response = await fetch('http://127.0.0.1:8000/scenarios', {
                    signal: controller.signal,
                })

                if (!response.ok) {
                    throw new Error(`Could not load scenarios: ${response.status}`)
                }

                const data = await response.json()
                setScenarios(data.scenarios)
            } catch (error) {
                if (!controller.signal.aborted) {
                    setStatus(
                        error instanceof Error ? error.message : 'Could not load scenarios.'
                    )
                }
            }
        }

        loadScenarios()

        return () => controller.abort()
    }, [])

    const visiblePositions = positions.filter(
        (position) => position.step === currentStep
    )

    const lastStep = positions.reduce(
        (highest, position) => Math.max(highest, position.step),
        1
    )

    useEffect(() => {
        if (!isPlaying) return

        const timer = window.setTimeout(() => {
            const nextStep = Math.min(currentStep + 1, lastStep)

            setCurrentStep(nextStep)

            if (nextStep >= lastStep) {
                setIsPlaying(false)
            }
        }, playbackDelay)

        return () => window.clearTimeout(timer)
    }, [isPlaying, currentStep, lastStep, playbackDelay])

    return (
        <main>
            <h1 className='title'>Orbital Simulator</h1>
            <h6 id='by-header'>by Daniel Hayat</h6>

            <div className='selection-container'>
                <div className='accordion scenario-selector'>
                    <div className='accordion-item'>
                        <h2 className='accordion-header'>
                            <button className="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#collapseOne" aria-expanded="false" aria-controls="collapseOne">
                                Choose the body scenario you would like to view!
                            </button>
                        </h2>
                        <div id="collapseOne" className="accordion-collapse collapse hide" data-bs-parent="#accordionExample">
                            <div className="accordion-body">
                                <div className="btn-group" role="group" aria-label="Basic radio toggle button group">
                                    <input 
                                        type="radio" 
                                        className="btn-check" 
                                        name="btnradio" 
                                        id="btnradio1" 
                                        autoComplete="off"
                                        checked={selectedScenario === 'earthsunmoon'}
                                        onChange={() => setSelectedScenario('earthsunmoon')}
                                        disabled={isRunning}
                                    />
                                    <label className="btn btn-earthsunmoon scenario-btn" htmlFor="btnradio1">Earth, Sun, and Moon</label>

                                    <input 
                                        type="radio" 
                                        className="btn-check" 
                                        name="btnradio" 
                                        id="btnradio2" 
                                        autoComplete="off"
                                        checked={selectedScenario === 'binarystar'}
                                        onChange={() => setSelectedScenario('binarystar')}
                                        disabled={isRunning}
                                    />
                                    <label className="btn btn-binarystars scenario-btn" htmlFor="btnradio2">Binary Stars</label>

                                    <input 
                                        type="radio" 
                                        className="btn-check" 
                                        name="btnradio" 
                                        id="btnradio3" 
                                        autoComplete="off"
                                        checked={selectedScenario === 'collisiontest'}
                                        onChange={() => setSelectedScenario('collisiontest')}
                                        disabled={isRunning}
                                    />
                                    <label className="btn btn-collision scenario-btn" htmlFor="btnradio3">Collision Test</label>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <div className='name-btn-row'>
                    <div className="card scenario-name">
                        <div id='selected-scenario-title'>
                            <h2 className='card-title'>Selected scenario: </h2>
                        </div>
                        <div id='current-scenario'>
                            <h2>{selectedScenario}</h2>
                        </div>
                    </div>

                    <div className='run-sim-btn'>
                        <input
                            type="number"
                            min={1}
                            max={10000}
                            value={steps}
                            placeholder="Steps to run"
                            onChange={(event) => setSteps(Number(event.target.value))}
                        />
                        <button
                            className='button'
                            onClick={handleRun} 
                            disabled={isRunning || selectedScenario === ''}
                        >
                            {isRunning ? 'Running...' : 'Run simulation'}
                        </button>

                        
                    </div>
                </div>

                <p role="status">{status}</p>

                    {submittedSteps != null && (
                        <p>Last submitted step count: {submittedSteps}</p>
                    )}
                <p>Requested steps: {steps}</p>
                <p>Stored positions: {positions.length}</p>

                <button
                    disabled={positions.length === 0 || isRunning}
                    onClick={() => {
                        if (!isPlaying && currentStep >= lastStep) {
                            setCurrentStep(1)
                        }
                        setIsPlaying(!isPlaying)
                    }}
                >
                    {isPlaying ? 'Pause' : 'Play'}
                </button>
                <label>
                    Playback delay: {playbackDelay} ms
                    <input
                        type="range"
                        min={20}
                        max={300}
                        step={10}
                        value={playbackDelay}
                        onChange={(event) => setPlaybackDelay(Number(event.target.value))}
                />
                </label>

                <label>
                    Displayed step: {currentStep}
                    <input
                        type="range"
                        min={1}
                        max={lastStep}
                        value={currentStep}
                        disabled={positions.length === 0}
                        onChange={(event) => setCurrentStep(Number(event.target.value))}
                        />  
                </label>
                {positions.length > 0 && (
                    <p>
                        First record: {positions[0].body},
                        step {positions[0].step},
                        x = {positions[0].x},
                        y = {positions[0].y}
                    </p>
                )}
                <ul style={{ listStyle: "none"}}>
                    {visiblePositions.map((position) => (
                        <li key={position.body}>
                            {position.body}: x = {position.x}, y = {position.y}
                        </li>
                    ))}
                </ul>
            </div>

            <div id='displayBox'>
                <svg
                    width="50%"
                    viewBox="0 0 500 300"
                    style={{border: '2px solid gray'}}
                >
                    {visiblePositions.map((position) => (
                        <circle
                            key={position.body}
                            cx={250 + position.x}
                            cy={150 - position.y}
                            r={6}
                            fill="orange"
                        >
                            <title>{position.body}</title>
                        </circle>
                    ))}
                </svg>
            </div>
        </main>
    )
}

export default App